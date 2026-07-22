#include "BluetoothSerial.h"

BluetoothSerial SerialBT;

// ---------------- PIN DEFINITIONS ----------------

#define RELAY1      27

#define LED1        18
#define LED2        19

#define BUTTON1     33
#define BUTTON2     32

#define BT_LED      2

// ---------------- VARIABLES ----------------

bool relay1State = false;
bool relay2State = false;

bool lastButton1 = HIGH;
bool lastButton2 = HIGH;

unsigned long lastDebounce1 = 0;
unsigned long lastDebounce2 = 0;

const unsigned long debounceDelay = 50;

String command;

// -------------------------------------------------

void updateOutputs() {

  digitalWrite(RELAY1, relay1State);

  digitalWrite(LED1, relay1State);
  digitalWrite(LED2, relay2State);

}

// -------------------------------------------------

void sendStatus() {

  SerialBT.println("------ STATUS ------");

  SerialBT.print("Light 1 : ");
  SerialBT.println(relay1State ? "ON" : "OFF");

  SerialBT.print("Light 2 : ");
  SerialBT.println(relay2State ? "ON" : "OFF");

  SerialBT.println("--------------------");

}

// -------------------------------------------------

void processCommand(String cmd) {

  cmd.trim();

  switch(cmd.charAt(0)) {

    case '1':
      relay1State = true;
      SerialBT.println("Light 1 ON");
      break;

    case '2':
      relay1State = false;
      SerialBT.println("Light 1 OFF");
      break;

    case '3':
      relay2State = true;
      SerialBT.println("Light 2 ON");
      break;

    case '4':
      relay2State = false;
      SerialBT.println("Light 2 OFF");
      break;

    case '5':
      relay1State = true;
      relay2State = true;
      SerialBT.println("ALL ON");
      break;

    case '6':
      relay1State = false;
      relay2State = false;
      SerialBT.println("ALL OFF");
      break;

    case '7':
      sendStatus();
      break;

    default:
      SerialBT.println("Invalid Command");
      break;

  }

  updateOutputs();

}

// -------------------------------------------------

void setup() {

  Serial.begin(115200);

  SerialBT.begin("IIT_IoT_HomeCtrl");

  pinMode(RELAY1, OUTPUT);

  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);

  pinMode(BT_LED, OUTPUT);

  pinMode(BUTTON1, INPUT_PULLUP);
  pinMode(BUTTON2, INPUT_PULLUP);

  digitalWrite(RELAY1, LOW);

  digitalWrite(LED1, LOW);
  digitalWrite(LED2, LOW);

  digitalWrite(BT_LED, LOW);

  Serial.println("Bluetooth Home Controller Ready");

}

// ---------------- BUTTON HANDLING ----------------

void checkButtons() {

  bool currentButton1 = digitalRead(BUTTON1);
  bool currentButton2 = digitalRead(BUTTON2);

  // Button 1
  if (currentButton1 != lastButton1) {
    lastDebounce1 = millis();
  }

  if ((millis() - lastDebounce1) > debounceDelay) {

    if (currentButton1 == LOW && lastButton1 == HIGH) {

      relay1State = !relay1State;

      updateOutputs();

      Serial.println("Button 1 Pressed");

      SerialBT.print("Light 1 ");
      SerialBT.println(relay1State ? "ON" : "OFF");

    }
  }

  lastButton1 = currentButton1;


  // Button 2
  if (currentButton2 != lastButton2) {
    lastDebounce2 = millis();
  }

  if ((millis() - lastDebounce2) > debounceDelay) {

    if (currentButton2 == LOW && lastButton2 == HIGH) {

      relay2State = !relay2State;

      updateOutputs();

      Serial.println("Button 2 Pressed");

      SerialBT.print("Light 2 ");
      SerialBT.println(relay2State ? "ON" : "OFF");

    }
  }

  lastButton2 = currentButton2;

}

// ---------------- SERIAL DEBUG ----------------

void printDebug() {

  static unsigned long lastPrint = 0;

  if (millis() - lastPrint >= 2000) {

    lastPrint = millis();

    Serial.println("---------------");

    Serial.print("Relay 1 : ");
    Serial.println(relay1State ? "ON" : "OFF");

    Serial.print("Relay 2 : ");
    Serial.println(relay2State ? "ON" : "OFF");

    Serial.println("Bluetooth Ready");

  }

}

// ---------------- LOOP ----------------

void loop() {

  // Bluetooth Connected Indicator
  digitalWrite(BT_LED, SerialBT.hasClient());

  // Read Bluetooth Commands
  if (SerialBT.available()) {

    command = SerialBT.readStringUntil('\n');

    Serial.print("Received : ");
    Serial.println(command);

    processCommand(command);

  }

  // Manual Buttons
  checkButtons();

  // Serial Debug
  printDebug();

}