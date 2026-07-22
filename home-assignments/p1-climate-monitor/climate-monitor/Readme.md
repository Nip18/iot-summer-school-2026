# Project 1 - Smart Climate Monitor

## Objective

Design an ESP32-based climate monitoring system that continuously measures temperature and humidity, alerts the user when environmental conditions become uncomfortable, and displays live sensor readings.

## Components Used

- ESP32 Dev Board
- DHT11 Temperature & Humidity Sensor
- SSD1306 OLED Display (optional)
- Green LED
- Red LED
- Active Buzzer
- Breadboard
- Jumper Wires

## Circuit Connections

| Component | ESP32 Pin |
|-----------|-----------|
| DHT11 Data | GPIO 4 |
| Green LED | GPIO 25 |
| Red LED | GPIO 26 |
| Buzzer | GPIO 27 |
| OLED SDA | GPIO 21 |
| OLED SCL | GPIO 22 |

## Libraries Used

- DHT sensor library
- Adafruit SSD1306
- Adafruit GFX

## Features

- Real-time temperature monitoring
- Real-time humidity monitoring
- Comfort level detection
- LED status indication
- Audible alert for abnormal conditions
- OLED live display (optional)
- Serial Monitor output

## Working Principle

The ESP32 continuously reads temperature and humidity from the DHT11 sensor. Based on predefined threshold values, the system determines whether the environment is comfortable or uncomfortable. LEDs and the buzzer provide visual and audible feedback, while sensor readings are displayed on the OLED display and Serial Monitor.

## How to Run

1. Connect all components.
2. Upload the Arduino sketch.
3. Open the Serial Monitor.
4. Observe live sensor readings and alerts.

## Expected Output

- Live temperature and humidity values.
- Green LED during normal conditions.
- Red LED and buzzer during abnormal conditions.
- OLED displays current readings.

## Folder Structure

```
Project1/
│── Project1.ino
└── README.md
```

## Future Improvements

- Wi-Fi dashboard
- Data logging
- ThingSpeak integration
- Mobile notifications
- Historical trend visualization