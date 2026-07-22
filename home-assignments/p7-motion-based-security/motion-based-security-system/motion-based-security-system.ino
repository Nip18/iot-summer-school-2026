/*
 * ==========================================================
 * Project 7: Motion-Based Security System
 * IIT Jammu Summer School 2026
 * ==========================================================
 * Components:
 * - Arduino Uno
 * - PIR Motion Sensor
 * - Green LED
 * - Red LED
 * - Active Buzzer
 * ==========================================================
 */

const int PIR_PIN = 2;

const int GREEN_LED = 8;
const int RED_LED   = 9;

const int BUZZER = 10;

bool motionDetected = false;

void setup() {

  pinMode(PIR_PIN, INPUT);

  pinMode(GREEN_LED, OUTPUT);
  pinMode(RED_LED, OUTPUT);
  pinMode(BUZZER, OUTPUT);

  digitalWrite(GREEN_LED, HIGH);
  digitalWrite(RED_LED, LOW);
  digitalWrite(BUZZER, LOW);

  Serial.begin(9600);

  Serial.println("--------------------------------");
  Serial.println(" Motion-Based Security System");
  Serial.println("--------------------------------");
  Serial.println("Waiting for PIR to stabilize...");
  delay(5000);
  Serial.println("System Armed");
}

void loop() {

  motionDetected = digitalRead(PIR_PIN);

  if (motionDetected) {

    digitalWrite(GREEN_LED, LOW);
    digitalWrite(RED_LED, HIGH);

    tone(BUZZER, 1200);

    Serial.println("⚠ Motion Detected!");

  }
  else {

    digitalWrite(GREEN_LED, HIGH);
    digitalWrite(RED_LED, LOW);

    noTone(BUZZER);

    Serial.println("Monitoring...");
  }

  delay(500);
}