
#include <WiFi.h>
#include <WebServer.h>
#include <PubSubClient.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <DHT.h>

/************ WiFi ************/
const char* ssid = "Wokwi-GUEST";
const char* password = "";

/************ MQTT ************/
const char* mqttServer = "broker.hivemq.com";
const int mqttPort = 1883;

WiFiClient espClient;
PubSubClient mqttClient(espClient);
WebServer server(80);

/************ OLED ************/
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

Adafruit_SSD1306 display(
  SCREEN_WIDTH,
  SCREEN_HEIGHT,
  &Wire,
  -1
);

/************ Pins ************/
#define DHTPIN      4
#define DHTTYPE     DHT11

#define PIR_PIN     13
#define BUZZER_PIN  14

#define RED_LED     25
#define GREEN_LED   2

#define RELAY1      26
#define RELAY2      27

#define BUTTON1     0
#define BUTTON2     32

#define LDR_PIN     34
#define MQ2_PIN     35

DHT dht(DHTPIN, DHTTYPE);

/************ Variables ************/
float temperature = 0;
float humidity = 0;

int gasRaw = 0;
int gasPercent = 0;

int lightRaw = 0;
int lightPercent = 0;

bool motion = false;

bool fanState = false;
bool lightState = false;
bool gasAlert = false;

/************ WiFi ************/
void connectWiFi() {

  Serial.print("Connecting WiFi");

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {

    delay(500);
    Serial.print(".");

  }

  Serial.println();
  Serial.println("WiFi Connected");
  Serial.println(WiFi.localIP());

}

/************ MQTT ************/
void connectMQTT() {

  while (!mqttClient.connected()) {

    Serial.println("Connecting MQTT...");

    if (mqttClient.connect("ESP32HomeHub")) {

      Serial.println("MQTT Connected");

    } else {

      delay(2000);

    }

  }

}

void readSensors() {

  temperature = dht.readTemperature();
  humidity = dht.readHumidity();

  gasRaw = analogRead(MQ2_PIN);
  gasPercent = map(gasRaw, 0, 4095, 0, 100);

  lightRaw = analogRead(LDR_PIN);
  lightPercent = map(lightRaw, 4095, 0, 0, 100);

  motion = digitalRead(PIR_PIN);

}

void automationLogic() {

  // Gas Detection
  if (gasPercent > 50) {

    gasAlert = true;

    digitalWrite(BUZZER_PIN, HIGH);
    digitalWrite(RED_LED, HIGH);

  }
  else {

    gasAlert = false;

    digitalWrite(BUZZER_PIN, LOW);
    digitalWrite(RED_LED, LOW);

  }

  // Fan Control
  if (temperature > 30) {

    fanState = true;

  } else {

    fanState = false;

  }

  digitalWrite(RELAY1, fanState ? LOW : HIGH);

  // Light Control
  if (lightPercent < 30 || motion) {

    lightState = true;

  } else {

    lightState = false;

  }

  digitalWrite(RELAY2, lightState ? LOW : HIGH);

  digitalWrite(GREEN_LED, lightState);

}

void updateOLED() {

  display.clearDisplay();

  display.setTextSize(1);
  display.setCursor(0,0);
  display.print("Temp: ");
  display.print(temperature);
  display.println(" C");

  display.print("Hum : ");
  display.print(humidity);
  display.println("%");

  display.print("Gas : ");
  display.print(gasPercent);
  display.println("%");

  display.print("Light:");
  display.print(lightPercent);
  display.println("%");

  display.print("PIR : ");

  if(motion)
    display.println("YES");
  else
    display.println("NO");

  display.display();

}

void publishMQTT() {

  if(!mqttClient.connected())
    connectMQTT();

  mqttClient.loop();

  mqttClient.publish(
    "iitjammu/home/temperature",
    String(temperature).c_str()
  );

  mqttClient.publish(
    "iitjammu/home/humidity",
    String(humidity).c_str()
  );

  mqttClient.publish(
    "iitjammu/home/gas",
    String(gasPercent).c_str()
  );

  mqttClient.publish(
    "iitjammu/home/light",
    String(lightPercent).c_str()
  );

  mqttClient.publish(
    "iitjammu/home/motion",
    motion ? "1" : "0"
  );

}

void setupWebServer() {

  server.on("/", HTTP_GET, []() {

    String page;

    page += "<!DOCTYPE html><html>";
    page += "<head>";
    page += "<meta http-equiv='refresh' content='3'>";
    page += "<title>IoT Home Automation</title>";
    page += "</head><body>";

    page += "<h2>IoT Home Automation Hub</h2>";

    page += "<hr>";

    page += "<p><b>Temperature:</b> ";
    page += String(temperature);
    page += " C</p>";

    page += "<p><b>Humidity:</b> ";
    page += String(humidity);
    page += " %</p>";

    page += "<p><b>Gas:</b> ";
    page += String(gasPercent);
    page += " %</p>";

    page += "<p><b>Light:</b> ";
    page += String(lightPercent);
    page += " %</p>";

    page += "<p><b>Motion:</b> ";
    page += (motion ? "Detected" : "No Motion");
    page += "</p>";

    page += "<hr>";

    page += "<p><b>Fan Relay:</b> ";
    page += (fanState ? "ON" : "OFF");
    page += "</p>";

    page += "<p><b>Light Relay:</b> ";
    page += (lightState ? "ON" : "OFF");
    page += "</p>";

    page += "<p><b>Gas Alert:</b> ";
    page += (gasAlert ? "YES" : "NO");
    page += "</p>";

    page += "</body></html>";

    server.send(200, "text/html", page);

  });

  server.begin();

}

void setup() {

  Serial.begin(115200);

  pinMode(PIR_PIN, INPUT);

  pinMode(BUZZER_PIN, OUTPUT);

  pinMode(RED_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);

  pinMode(RELAY1, OUTPUT);
  pinMode(RELAY2, OUTPUT);

  pinMode(BUTTON1, INPUT_PULLUP);
  pinMode(BUTTON2, INPUT_PULLUP);

  digitalWrite(RELAY1, HIGH);
  digitalWrite(RELAY2, HIGH);

  Wire.begin(21,22);

  display.begin(SSD1306_SWITCHCAPVCC,0x3C);
  display.clearDisplay();
  display.display();

  dht.begin();

  connectWiFi();

  mqttClient.setServer(mqttServer, mqttPort);

  connectMQTT();

  setupWebServer();

  Serial.println("System Ready");

}

void loop() {

  readSensors();

  automationLogic();

  updateOLED();

  publishMQTT();

  server.handleClient();

  delay(1000);

}