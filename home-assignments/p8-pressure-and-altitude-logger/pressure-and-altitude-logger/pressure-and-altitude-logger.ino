#include <Wire.h>

void scanPins(int sda, int scl) {
  Wire.end();
  Wire.begin(sda, scl);
  delay(100);

  Serial.print("Scanning SDA=");
  Serial.print(sda);
  Serial.print(" SCL=");
  Serial.println(scl);

  bool found = false;

  for (byte addr = 1; addr < 127; addr++) {
    Wire.beginTransmission(addr);
    if (Wire.endTransmission() == 0) {
      Serial.print("Found 0x");
      Serial.println(addr, HEX);
      found = true;
    }
  }

  if (!found)
    Serial.println("Nothing found");
}

void setup() {
  Serial.begin(115200);
  delay(1000);

  scanPins(21,22);
  scanPins(18,19);
  scanPins(25,26);
  scanPins(32,33);
}

void loop() {}