/*
 * STATE DIAGRAM:
 * [IDLE] -> (Coin) -> [COIN_INSERTED] -> (Select) -> [ITEM_SELECTED] -> [DISPENSING] -> back to [IDLE]
 * *Note: Cancel button resets back to [IDLE].
 */

const int BTN_COIN = 2;
const int BTN_SELECT = 3;
const int BTN_CANCEL = 4;

const int LED_IDLE = 8;
const int LED_COIN = 9;
const int LED_SELECT = 10; 

// 4 distinct states
enum VendingState { IDLE, COIN_INSERTED, ITEM_SELECTED, DISPENSING };
VendingState currentState = IDLE;

void setup() {
  // Configure buttons with active LOW
  pinMode(BTN_COIN, INPUT_PULLUP);
  pinMode(BTN_SELECT, INPUT_PULLUP);
  pinMode(BTN_CANCEL, INPUT_PULLUP);

  pinMode(LED_IDLE, OUTPUT);
  pinMode(LED_COIN, OUTPUT);
  pinMode(LED_SELECT, OUTPUT);

  Serial.begin(9600);
  Serial.println("SYSTEM BOOT: State changed to IDLE");
  updateLEDs();
}

void loop() {
  // read button inputs (LOW means pressed)
  bool coinPressed = (digitalRead(BTN_COIN) == LOW);
  bool selectPressed = (digitalRead(BTN_SELECT) == LOW);
  bool cancelPressed = (digitalRead(BTN_CANCEL) == LOW);

  // if cancel is pressed in any active state, reset to IDLE
  if (cancelPressed && (currentState == COIN_INSERTED || currentState == ITEM_SELECTED)) {
    delay(200); // debounce
    currentState = IDLE;
    Serial.println("TRANSITION: Cancel pressed. State changed to IDLE");
    updateLEDs();
    while(digitalRead(BTN_CANCEL) == LOW); // wait for button release
    return;
  }

  // state machine logic switch
  switch (currentState) {
    
    case IDLE:
      if (coinPressed) {
        delay(200); // debounce
        currentState = COIN_INSERTED;
        Serial.println("TRANSITION: Coin inserted. State changed to COIN_INSERTED");
        updateLEDs();
        while(digitalRead(BTN_COIN) == LOW); // wait for release
      }
      break;

    case COIN_INSERTED:
      if (selectPressed) {
        delay(200);
        currentState = ITEM_SELECTED;
        Serial.println("TRANSITION: Item selected. State changed to ITEM_SELECTED");
        updateLEDs();
        while(digitalRead(BTN_SELECT) == LOW);
      }
      break;

    case ITEM_SELECTED:
      // jump immediately into the dispensing state automatically
      currentState = DISPENSING;
      Serial.println("TRANSITION: Authorizing payout. State changed to DISPENSING");
      updateLEDs();
      break;

    case DISPENSING:
      Serial.println("ACTION: Ejecting your item... please wait.");
      delay(3000); // wait 3 seconds to simulate hardware motor dispensing item
      
      currentState = IDLE;
      Serial.println("TRANSITION: Dispense complete. State changed to IDLE");
      updateLEDs();
      break;
  }
}

// to update the LEDs based on the active state
void updateLEDs() {
  if (currentState == IDLE) {
    digitalWrite(LED_IDLE, HIGH);
    digitalWrite(LED_COIN, LOW);
    digitalWrite(LED_SELECT, LOW);
  } 
  else if (currentState == COIN_INSERTED) {
    digitalWrite(LED_IDLE, LOW);
    digitalWrite(LED_COIN, HIGH);
    digitalWrite(LED_SELECT, LOW);
  } 
  else if (currentState == ITEM_SELECTED) {
    digitalWrite(LED_IDLE, LOW);
    digitalWrite(LED_COIN, LOW);
    digitalWrite(LED_SELECT, HIGH);
  } 
  else if (currentState == DISPENSING) {
    // light up all indicators during dispensing action
    digitalWrite(LED_IDLE, HIGH);
    digitalWrite(LED_COIN, HIGH);
    digitalWrite(LED_SELECT, HIGH);
  }
}
