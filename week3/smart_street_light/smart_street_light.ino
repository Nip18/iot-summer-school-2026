int ldrPin = A0;
int pirPin = 10;
int ledPin = 11; // PWM pin

unsigned long motionStartTime = 0;
int mode = 0; // 0 = DAYTIME, 1 = NIGHT_IDLE, 2 = NIGHT_ACTIVE

void setup() {
  pinMode(pirPin, INPUT);
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
  Serial.println("[00:00:00] EVENT: System Booted");
}

void loop() {
  int ldrValue = analogRead(ldrPin);
  bool motion = (digitalRead(pirPin) == HIGH);
  unsigned long currentTime = millis();

  // Mode 0: DAYTIME
  if (mode == 0) {
    analogWrite(ledPin, 0);
    if (ldrValue < 400) { // Ambient dark threshold
      mode = 1;
      logEvent("Dark detected. Motion detection enabled.");
    }
  }

  // Mode 1: NIGHT_IDLE (Dim to 20%)
  else if (mode == 1) {
    analogWrite(ledPin, 51); // 20% of 255
    
    if (ldrValue >= 400) {
      mode = 0;
      logEvent("Daylight detected. Turning LED OFF.");
    } else if (motion) {
      mode = 2;
      motionStartTime = currentTime;
      logEvent("Motion detected! Turning LED to full brightness.");
    }
  }

  // Mode 2: NIGHT_ACTIVE (Full brightness)
  else if (mode == 2) {
    analogWrite(ledPin, 255);

    if (motion) {
      motionStartTime = currentTime; // Reset 30s window if motion continues
    }

    if (currentTime - motionStartTime >= 30000) {
      if (ldrValue >= 400) {
        mode = 0;
        logEvent("Daylight detected. Turning LED OFF.");
      } else {
        mode = 1;
        logEvent("No motion after 30 sec: Dimming LED to 20%.");
      }
    }
  }
}

void logEvent(String msg) {
  unsigned long secs = millis() / 1000;
  int s = secs % 60;
  int m = (secs / 60) % 60;
  int h = (secs / 3600) % 24;

  char timeStr[12];
  sprintf(timeStr, "[%02d:%02d:%02d]", h, m, s);

  Serial.print(timeStr);
  Serial.print(" EVENT: ");
  Serial.println(msg);
}
