#include <WiFi.h>
#include <WebServer.h>
#include <DHT.h>

#define DHTPIN 4
#define DHTTYPE DHT11

const char* ssid = "YOUR_WIFI_NAME";
const char* password = "YOUR_WIFI_PASSWORD";

DHT dht(DHTPIN, DHTTYPE);

WebServer server(80);

void handleRoot()
{
  float temp = dht.readTemperature();
  float hum = dht.readHumidity();

  String webpage =
  "<!DOCTYPE html><html><head>"
  "<meta http-equiv='refresh' content='3'>"
  "<title>Weather Dashboard</title>"
  "<style>"
  "body{font-family:Arial;text-align:center;background:#eef2f3;}"
  "h1{color:#0066cc;}"
  ".card{background:white;padding:20px;margin:40px auto;width:300px;border-radius:12px;box-shadow:0 0 10px gray;}"
  "</style></head><body>";

  webpage += "<div class='card'>";
  webpage += "<h1>ESP32 Weather Dashboard</h1>";
  webpage += "<h2>Temperature</h2>";
  webpage += "<p>";
  webpage += String(temp);
  webpage += " &deg;C</p>";

  webpage += "<h2>Humidity</h2>";
  webpage += "<p>";
  webpage += String(hum);
  webpage += " %</p>";

  webpage += "</div></body></html>";

  server.send(200, "text/html", webpage);
}

void setup()
{
  Serial.begin(115200);

  dht.begin();

  WiFi.begin(ssid, password);

  Serial.print("Connecting");

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }

  Serial.println();
  Serial.println("Connected!");

  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  server.on("/", handleRoot);

  server.begin();
}

void loop()
{
  server.handleClient();
}