const int LED_PIN = 3;       // PWM pin 
const int BUTTON_PIN = 2;    // mode switch button

int currentMode = 1;         // start in Mode 1
int lastButtonState = HIGH;  // Default state

void setup() {
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP); // active LOW
  Serial.begin(9600);
  Serial.println("Mode 1: Slow Breathing (3s cycle)");
}

void loop() {
  checkButton();

  if (currentMode == 1) {
    // Mode 1: Slow breathing (3-second cycle: ~1.5s fade up, ~1.5s fade down)
    fadeLED(6); // 6ms step delay * 255 steps = ~1530ms per half cycle
  } 
  else if (currentMode == 2) {
    // Mode 2: Fast pulse (0.5-second cycle: ~0.25s up, ~0.25s down)
    fadeLED(1); // 1ms step delay * 255 steps = ~255ms per half cycle
  } 
  else if (currentMode == 3) {
    // Mode 3: SOS pattern
    runSOS();
  }
}

// for smoothly fading the LED up and down
void fadeLED(int stepDelay) {
  // Fade In
  for (int brightness = 0; brightness <= 255; brightness++) {
    analogWrite(LED_PIN, brightness);
    delay(stepDelay);
    
    if (checkButton()) return; 
  }

  // Fade Out
  for (int brightness = 255; brightness >= 0; brightness--) {
    analogWrite(LED_PIN, brightness);
    delay(stepDelay);
    
    if (checkButton()) return;
  }
}

// to handle the SOS Morse Code transmission
void runSOS() {
  int dotTime = 150;  // Duration for a short flash
  int dashTime = 450; // Duration for a long flash

  // 3 Dots
  for (int i = 0; i < 3; i++) {
    flash(dotTime);
    if (checkButton()) return;
  }
  delay(200);

  // 3 Dashes
  for (int i = 0; i < 3; i++) {
    flash(dashTime);
    if (checkButton()) return;
  }
  delay(200);

  // 3 Dot
  for (int i = 0; i < 3; i++) {
    flash(dotTime);
    if (checkButton()) return;
  }

  // Inter-word delay gap before repeating the SOS loop
  for (int i = 0; i < 10; i++) {
    delay(100);
    if (checkButton()) return;
  }
}

// to blink the LED for a precise duration
void flash(int duration) {
  analogWrite(LED_PIN, 255); // LED fully on
  delay(duration);
  analogWrite(LED_PIN, 0);   // LED fully off
  delay(150);                // Gap between elements
}

//to check if the button has been pressed and cycle modes
bool checkButton() {
  int currentButtonState = digitalRead(BUTTON_PIN);

  // detect a transition (HIGH to LOW transition means pressed)
  if (currentButtonState == LOW && lastButtonState == HIGH) {
    delay(50); // software debounce pause to filter out mechanical noise
    
    if (digitalRead(BUTTON_PIN) == LOW) {
      currentMode++;
      if (currentMode > 3) {
        currentMode = 1;
      }

      // to print status updates over the serial interface
      if (currentMode == 1) {
        Serial.println("Mode 1: Slow Breathing (3s cycle)");
      } else if (currentMode == 2) {
        Serial.println("Mode 2: Fast Pulse (0.5s cycle)");
      } else if (currentMode == 3) {
        Serial.println("Mode 3: SOS Pattern (... --- ...)");
      }

      // turn off the LED during transitions
      analogWrite(LED_PIN, 0); 
      
      // wait until the user releases the button before continuing
      while (digitalRead(BUTTON_PIN) == LOW);
      
      lastButtonState = currentButtonState;
      return true; 
    }
  }
  
  lastButtonState = currentButtonState;
  return false;
}
