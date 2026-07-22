#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1

// Ultrasonic Pins
#define TRIG_PIN 5
#define ECHO_PIN 18

// Output Pins
#define GREEN_LED 26
#define RED_LED 25
//#define BUZZER 27

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

long duration;
float distance;
String status;

void setup() {

  Serial.begin(115200);

  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  pinMode(GREEN_LED, OUTPUT);
  pinMode(RED_LED, OUTPUT);
  //pinMode(BUZZER, OUTPUT);

  digitalWrite(GREEN_LED, LOW);
  digitalWrite(RED_LED, LOW);
  //digitalWrite(BUZZER, LOW);

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("OLED Failed");
    while (true);
  }

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(10, 25);
  display.println("Parking Assistant");
  display.display();

  delay(2000);
}

void readDistance() {

  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);

  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);

  digitalWrite(TRIG_PIN, LOW);

  duration = pulseIn(ECHO_PIN, HIGH);

  distance = duration * 0.0343 / 2;
}

void checkDistance() {

  if (distance > 50) {

    status = "SAFE";

    digitalWrite(GREEN_LED, HIGH);
    digitalWrite(RED_LED, LOW);
    //digitalWrite(BUZZER, LOW);

  }
  else if (distance > 20) {

    status = "CAUTION";

    digitalWrite(GREEN_LED, LOW);
    digitalWrite(RED_LED, HIGH);
    //digitalWrite(BUZZER, LOW);

  }
  else {

    status = "STOP";

    digitalWrite(GREEN_LED, LOW);
    digitalWrite(RED_LED, HIGH);
    //digitalWrite(BUZZER, HIGH);

  }
}

void updateDisplay() {

  display.clearDisplay();

  display.setTextSize(1);

  display.setCursor(0, 0);
  display.print("Distance:");

  display.setCursor(0, 15);
  display.print(distance);
  display.println(" cm");

  display.setCursor(0, 35);
  display.print("Status:");

  display.setCursor(0, 50);
  display.print(status);

  display.display();
}

void loop() {

  readDistance();
  
  Serial.print("Duration = ");
  Serial.println(duration);
  
  checkDistance();

  updateDisplay();

  // CSV Output
  Serial.print(distance);
  Serial.print(",");
  Serial.println(status);

  delay(200);
}