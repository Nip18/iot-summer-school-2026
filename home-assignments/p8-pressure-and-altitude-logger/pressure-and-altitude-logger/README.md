# Project 8 - Pressure Logger

## Objective

Develop an ESP32-based pressure monitoring system that measures atmospheric pressure using the BMP280 sensor, logs the readings, and displays real-time pressure data for environmental monitoring.

## Components Used

- ESP32 Dev Board
- BMP280 Pressure Sensor
- SSD1306 OLED Display (optional)
- Breadboard
- Jumper Wires

## Circuit Connections

| Component | ESP32 Pin |
|-----------|-----------|
| BMP280 SDA | GPIO 21 |
| BMP280 SCL | GPIO 22 |
| OLED SDA | GPIO 21 |
| OLED SCL | GPIO 22 |

## Libraries Used

- Adafruit BMP280
- Adafruit GFX
- Adafruit SSD1306
- Wire

## Features

- Real-time atmospheric pressure measurement
- Pressure trend monitoring
- Live OLED display (optional)
- Serial Monitor logging
- Continuous sensor updates

## Working Principle

The ESP32 communicates with the BMP280 sensor over the I2C interface to measure atmospheric pressure. The readings are continuously displayed on the Serial Monitor and optionally on an OLED display. Pressure data can be monitored over time to observe environmental changes and trends.

## How to Run

1. Connect all components.
2. Upload the Arduino sketch.
3. Open the Serial Monitor.
4. Observe the real-time pressure readings.

## Expected Output

- Live atmospheric pressure readings.
- Pressure values displayed on the OLED (optional).
- Continuous logging on the Serial Monitor.
- Smooth real-time updates.

## Folder Structure

```
Project8/
│── Project8.ino
└── README.md
```

## Future Improvements

- SD card data logging
- Cloud storage integration
- Pressure trend graphs
- Weather prediction using pressure changes
- Mobile dashboard for remote monitoring