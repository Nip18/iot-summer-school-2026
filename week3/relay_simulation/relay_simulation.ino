#include "DHT.h"

int dhtPin = 4;
int relayLedPin = 12; 
int buttonPin = 3;

DHT dht(dhtPin, DHT11);

bool relayState = false;
bool overrideMode = false;
unsigned long lastPollTime = 0;
bool lastRelayState = false;

void setup() {
  pinMode(relayLedPin, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP);
  Serial.begin(9600);
  dht.begin();
}

void loop() {
  unsigned long currentMillis = millis();

  // Manual Override Button
  if (digitalRead(buttonPin) == LOW) {
    delay(50); // debounce
    if (digitalRead(buttonPin) == LOW) {
      overrideMode = true; 
      relayState = !relayState; // toggle state
      while(digitalRead(buttonPin) == LOW); // wait for release
    }
  }

  // Read sensor every 2 seconds
  if (currentMillis - lastPollTime >= 2000) {
    lastPollTime = currentMillis;
    float tempC = dht.readTemperature();

    if (!isnan(tempC)) {
      // Automate logic if manual override is inactive
      if (!overrideMode) {
        if (tempC > 32.0) {
          relayState = true;
        } else if (tempC < 28.0) {
          relayState = false;
        }
      } else {
        // Clear manual override when conditions drop back down below safety limit
        if (tempC <= 28.0 && relayState == true) {
          overrideMode = false;
        }
      }

      // Log changes to Serial Monitor
      if (relayState != lastRelayState) {
        Serial.print("Temperature: ");
        Serial.print(tempC, 1);
        Serial.print(" C | Relay State changed to: ");
        Serial.println(relayState ? "ON" : "OFF");
        lastRelayState = relayState;
      }
    }
  }

  digitalWrite(relayLedPin, relayState ? HIGH : LOW);
}
