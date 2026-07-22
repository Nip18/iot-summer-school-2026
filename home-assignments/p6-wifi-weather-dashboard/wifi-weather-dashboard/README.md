# Project 6 - Weather Dashboard

## Objective

Develop an ESP32-based weather monitoring system that measures temperature, humidity, atmospheric pressure, and light intensity, while hosting a live web dashboard for real-time monitoring.

## Components Used

- ESP32 Dev Board
- DHT11 Temperature & Humidity Sensor
- BMP280 Pressure Sensor
- LDR (Light Dependent Resistor)
- 10kΩ Resistor
- SSD1306 OLED Display (optional)
- Breadboard
- Jumper Wires

## Circuit Connections

| Component | ESP32 Pin |
|-----------|-----------|
| DHT11 Data | GPIO 4 |
| BMP280 SDA | GPIO 21 |
| BMP280 SCL | GPIO 22 |
| LDR Output | GPIO 34 |
| OLED SDA | GPIO 21 |
| OLED SCL | GPIO 22 |

## Libraries Used

- WiFi
- ESPAsyncWebServer
- AsyncTCP
- DHT Sensor Library
- Adafruit BMP280
- Adafruit GFX
- Adafruit SSD1306

## Features

- Real-time temperature monitoring
- Humidity monitoring
- Atmospheric pressure monitoring
- Ambient light intensity measurement
- Live web dashboard
- OLED display (optional)
- Serial Monitor output

## Working Principle

The ESP32 continuously collects data from the DHT11, BMP280, and LDR sensors. The sensor readings are displayed on the Serial Monitor and optionally on an OLED display. Simultaneously, the ESP32 hosts a web server that provides a live dashboard, allowing users connected to the same Wi-Fi network to monitor environmental conditions through a web browser.

## How to Run

1. Connect all components.
2. Update the Wi-Fi SSID and password in the code.
3. Upload the Arduino sketch.
4. Open the Serial Monitor and note the ESP32 IP address.
5. Open the IP address in a web browser to access the dashboard.

## Expected Output

- Live temperature, humidity, pressure, and light readings.
- Real-time web dashboard updates.
- OLED displays sensor readings (optional).
- Continuous Serial Monitor updates.

## Folder Structure

```
Project6/
│── Project6.ino
└── README.md
```

## Future Improvements

- Cloud data logging
- Historical data visualization
- Weather forecasting
- Mobile-responsive dashboard
- Email and notification alerts