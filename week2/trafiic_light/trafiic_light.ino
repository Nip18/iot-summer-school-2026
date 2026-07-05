// pin Configurations
const int RED_PIN = 10;
const int YEL_PIN = 9;
const int GRN_PIN = 8;
const int BUTTON_PIN = 7;

// finite State Machine States
enum TrafficState { STATE_RED, STATE_YELLOW, STATE_GREEN, STATE_PEDESTRIAN };
TrafficState currentState = STATE_RED;

unsigned long stateStartTime = 0;
unsigned long stateDuration = 5000; // Start with RED duration (5s)
volatile bool pedestrianRequested = false;

void setup() {
  pinMode(RED_PIN, OUTPUT);
  pinMode(YEL_PIN, OUTPUT);
  pinMode(GRN_PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP); // active LOW config
  
  Serial.begin(9600);
  stateStartTime = millis();
  logState("RED");
}

void loop() {
  unsigned long currentMillis = millis();
  
  // debounced check for pedestrian button press (active LOW)
  if (digitalRead(BUTTON_PIN) == LOW && !pedestrianRequested && currentState != STATE_PEDESTRIAN) {
    delay(50); // small debounce delay
    if (digitalRead(BUTTON_PIN) == LOW) {
      pedestrianRequested = true;
    }
  }

  // interrupt the natural flow immediately if a pedestrian requests crossing
  if (pedestrianRequested && currentState != STATE_PEDESTRIAN && currentState != STATE_RED) {
    currentState = STATE_PEDESTRIAN;
    stateStartTime = currentMillis;
    stateDuration = 8000;
    pedestrianRequested = false;
    logState("PEDESTRIAN INTERRUPT (RED FORCE)");
  }

  // update the physical hardware states and check phase timers
  switch (currentState) {
    case STATE_RED:
      updateLEDs(HIGH, LOW, LOW);
      if (currentMillis - stateStartTime >= stateDuration) {
        currentState = STATE_YELLOW;
        stateStartTime = currentMillis;
        stateDuration = 2000;
        logState("YELLOW");
      }
      break;

    case STATE_YELLOW:
      updateLEDs(LOW, HIGH, LOW);
      if (currentMillis - stateStartTime >= stateDuration) {
        currentState = STATE_GREEN;
        stateStartTime = currentMillis;
        stateDuration = 4000;
        logState("GREEN");
      }
      break;

    case STATE_GREEN:
      updateLEDs(LOW, LOW, HIGH);
      if (currentMillis - stateStartTime >= stateDuration) {
        currentState = STATE_RED;
        stateStartTime = currentMillis;
        stateDuration = 5000;
        logState("RED");
      }
      break;

    case STATE_PEDESTRIAN:
      updateLEDs(HIGH, LOW, LOW); //force RED immediately
      if (currentMillis - stateStartTime >= stateDuration) {
        //safe release back into standard flow sequence
        currentState = STATE_GREEN; 
        stateStartTime = currentMillis;
        stateDuration = 4000;
        logState("GREEN");
      }
      break;
  }
}

void updateLEDs(int red, int yellow, int green) {
  digitalWrite(RED_PIN, red);
  digitalWrite(YEL_PIN, yellow);
  digitalWrite(GRN_PIN, green);
}

void logState(String stateName) {
  Serial.print("[");
  Serial.print(millis());
  Serial.print(" ms] Traffic Phase Changed to: ");
  Serial.println(stateName);
}
