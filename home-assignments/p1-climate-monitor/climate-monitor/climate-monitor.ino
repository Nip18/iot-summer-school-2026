#include <Wire.h>
#include <DHT.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// =====================
// Display Configuration
// =====================
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1

// =====================
// DHT Configuration
// =====================
#define DHTPIN 4
#define DHTTYPE DHT11

// =====================
// Output Pins
// =====================
#define RED_LED 26
#define GREEN_LED 25
// #define BUZZER 27

// =====================
// Objects
// =====================
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
DHT dht(DHTPIN, DHTTYPE);

// =====================
// Sensor Variables
// =====================
float temperature = 0.0;
float humidity = 0.0;

// Track min & max temperature
float minTemp = 100.0;
float maxTemp = -100.0;

// Comfort status
String comfortStatus = "";

void readSensor() {

  temperature = dht.readTemperature();
  humidity = dht.readHumidity();

  if (isnan(temperature) || isnan(humidity)) {
    Serial.println("Failed to read DHT11!");
    return;
  }

  // Update Min & Max Temperature
  if (temperature < minTemp)
    minTemp = temperature;

  if (temperature > maxTemp)
    maxTemp = temperature;
}

void checkComfort() {

  // Comfortable Conditions
  if (temperature >= 0 && temperature <= 38 &&
      humidity >= 40 && humidity <= 80) {

    comfortStatus = "COMFORT";

    digitalWrite(GREEN_LED, HIGH);
    digitalWrite(RED_LED, LOW);
    // digitalWrite(BUZZER, LOW);
  }

  // Cool Conditions
  else if (temperature < 20) {

    comfortStatus = "COOL";

    digitalWrite(GREEN_LED, LOW);
    digitalWrite(RED_LED, LOW);
    // digitalWrite(BUZZER, LOW);
  }

  // Hot Conditions
  else if (temperature > 30 && temperature <= 35) {

    comfortStatus = "HOT";

    digitalWrite(GREEN_LED, LOW);
    digitalWrite(RED_LED, HIGH);
    // digitalWrite(BUZZER, LOW);
  }

  // Dangerous Conditions
  else {

    comfortStatus = "DANGER";

    digitalWrite(GREEN_LED, LOW);
    digitalWrite(RED_LED, HIGH);
    // digitalWrite(BUZZER, HIGH);
  }

}

void updateDisplay() {

  display.clearDisplay();

  display.setTextSize(1);
  display.setCursor(0, 0);
  display.print("Temp: ");
  display.print(temperature);
  display.println(" C");

  display.setCursor(0, 15);
  display.print("Humidity: ");
  display.print(humidity);
  display.println(" %");

  display.setCursor(0, 30);
  display.print("Status:");

  display.setCursor(0, 45);
  display.print(comfortStatus);

  display.display();
}

void setup() {

  // Start Serial Monitor
  Serial.begin(115200);

  // Initialize DHT Sensor
  dht.begin();

  // Set output pins
  pinMode(RED_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);
  // pinMode(BUZZER, OUTPUT);

  // Turn everything OFF initially
  digitalWrite(RED_LED, LOW);
  digitalWrite(GREEN_LED, LOW);
  // digitalWrite(BUZZER, LOW);

  // Initialize OLED
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("OLED Initialization Failed!");
    while (true);
  }

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);

  display.setCursor(15, 25);
  display.println("Climate Monitor");

  display.display();

  delay(2000);

  display.clearDisplay();
}

void loop() {

  // Read sensor values
  readSensor();

  // If sensor reading failed, skip this cycle
  if (isnan(temperature) || isnan(humidity)) {
    delay(2000);
    return;
  }

  // Check comfort level
  checkComfort();

  // Update OLED
  updateDisplay();

  // Print CSV format to Serial Monitor
  Serial.print(temperature);
  Serial.print(",");
  Serial.print(humidity);
  Serial.print(",");
  Serial.println(comfortStatus);

  // Wait before next reading
  delay(2000);
}