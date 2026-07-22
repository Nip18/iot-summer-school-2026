#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <DHT.h>

// ---------------- OLED ----------------
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// ---------------- Pins ----------------
#define SOIL_PIN     35
#define DHT_PIN      4
#define DHT_TYPE     DHT11

#define RELAY_PIN    26
#define RED_LED      25
#define GREEN_LED    2
#define BUZZER       14
#define BUTTON_PIN   15

DHT dht(DHT_PIN, DHT_TYPE);

// -------- Calibration Values --------
// Change these after testing your sensor
const int DRY_VALUE = 1800;
const int WET_VALUE = 50;

// ---------- Pump Logic ----------
bool pumpOn = false;
bool manualMode = false;

unsigned long lastRead = 0;
unsigned long manualStart = 0;

const unsigned long interval = 5000;     // Demo: 5 sec
const unsigned long manualTime = 5000;   // Manual watering 5 sec

void setup() {

  Serial.begin(115200);

  pinMode(RELAY_PIN, OUTPUT);
  pinMode(RED_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);
  pinMode(BUZZER, OUTPUT);

  pinMode(BUTTON_PIN, INPUT_PULLUP);

  digitalWrite(RELAY_PIN, HIGH);    // Relay OFF (Active LOW)
  digitalWrite(RED_LED, LOW);
  digitalWrite(GREEN_LED, LOW);
  digitalWrite(BUZZER, LOW);

  dht.begin();

  Wire.begin(21,22);

  if(!display.begin(SSD1306_SWITCHCAPVCC,0x3C)){
    Serial.println("OLED Failed");
    while(1);
  }

  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);
  display.setTextSize(2);
  display.setCursor(15,20);
  display.println("P4 Smart Watering System");
  display.display();
  delay(2000);
}

void loop() {

  if(digitalRead(BUTTON_PIN)==LOW && !manualMode){

    manualMode=true;
    manualStart=millis();

    digitalWrite(RELAY_PIN,LOW);

    Serial.println("Manual Watering");

  }

  if(manualMode){

    if(millis()-manualStart>=manualTime){

      manualMode=false;
      digitalWrite(RELAY_PIN,HIGH);

    }

  }

  if(millis()-lastRead>=interval){

    lastRead=millis();

    int rawMoisture=analogRead(SOIL_PIN);

    int moisturePercent=map(rawMoisture,
                            DRY_VALUE,
                            WET_VALUE,
                            0,
                            100);

    moisturePercent=constrain(moisturePercent,0,100);

    float temp=dht.readTemperature();

    String status="OPTIMAL";

    if(!manualMode){

      if(!pumpOn && moisturePercent<30){

        pumpOn=true;

      }

      if(pumpOn && moisturePercent>40){

        pumpOn=false;

      }

      digitalWrite(RELAY_PIN,pumpOn?LOW:HIGH);

    }

    if(moisturePercent<30){

      status="DRY";

      digitalWrite(RED_LED,HIGH);
      digitalWrite(GREEN_LED,LOW);
      digitalWrite(BUZZER,HIGH);

    }

    else if(moisturePercent<=70){

      status="OPTIMAL";

      digitalWrite(RED_LED,LOW);
      digitalWrite(GREEN_LED,HIGH);
      digitalWrite(BUZZER,LOW);

    }

    else{

      status="WET";

      digitalWrite(RED_LED,LOW);
      digitalWrite(GREEN_LED,HIGH);
      digitalWrite(BUZZER,LOW);

    }

    Serial.println("----------------------");
    Serial.print("Raw Soil : ");
    Serial.println(rawMoisture);

    Serial.print("Moisture : ");
    Serial.print(moisturePercent);
    Serial.println("%");

    Serial.print("Temp : ");
    Serial.print(temp);
    Serial.println(" C");

    Serial.print("Status : ");
    Serial.println(status);

    display.clearDisplay();

    display.setTextSize(1);

    display.setCursor(0,0);
    display.print("Soil: ");
    display.print(moisturePercent);
    display.println("%");

    display.setCursor(0,12);
    display.print("Temp: ");
    display.print(temp);
    display.println(" C");

    display.setCursor(0,24);
    display.print("Status:");
    display.println(status);

    display.drawRect(5,48,118,10,WHITE);

    int bar=map(moisturePercent,0,100,0,116);

    display.fillRect(6,49,bar,8,WHITE);

    display.display();

  }

}