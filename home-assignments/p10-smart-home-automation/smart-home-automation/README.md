# Project 10: IoT Home Automation Hub

## Overview

The IoT Home Automation Hub integrates multiple environmental sensors and output devices into a single ESP32-based smart home system. The project demonstrates sensor monitoring, automatic device control, OLED visualization, web-based monitoring, and MQTT communication.

The objective is to simulate a basic smart home controller capable of making simple automation decisions based on environmental conditions.

---

## Components Used

- ESP32 DevKit V1
- DHT11 Temperature & Humidity Sensor
- MQ-2 Gas Sensor
- LDR
- PIR Motion Sensor
- SSD1306 OLED Display
- 2 Relay Modules
- Active Buzzer
- Red LED
- Green LED
- Push Buttons
- Breadboard
- Jumper Wires

---

## Features

- Temperature monitoring
- Humidity monitoring
- Gas leak detection
- Ambient light sensing
- Motion detection
- OLED live display
- Automatic relay control
- LED status indication
- Buzzer alerts
- MQTT data publishing
- Web dashboard
- WiFi connectivity

---

## Sensor Monitoring

### DHT11

Measures:

- Temperature
- Humidity

Used for automatic fan control and environmental monitoring.

---

### MQ-2

Measures gas concentration.

If gas exceeds the predefined threshold:

- Red LED turns ON
- Buzzer activates
- MQTT alert is generated

---

### PIR Sensor

Detects human movement.

Used to automate lighting.

---

### LDR

Measures surrounding light intensity.

The lighting relay is automatically switched depending on ambient brightness.

---

## Automation Logic

### Fan Control

The cooling relay automatically turns ON whenever the measured temperature exceeds the configured threshold.

---

### Lighting Control

The lighting relay turns ON when:

- Motion is detected, or
- Ambient light is low.

Otherwise it remains OFF.

---

### Gas Alarm

Whenever gas concentration crosses the danger threshold:

- Red LED turns ON
- Buzzer sounds continuously
- OLED displays warning
- MQTT publishes alert

---

## OLED Display

The SSD1306 OLED continuously displays:

- Temperature
- Humidity
- Gas Level
- Light Level
- Motion Status

The display updates in real time.

---

## MQTT

Sensor values are periodically published to MQTT topics.

Example topics:

- Temperature
- Humidity
- Gas Level
- Light Level
- Motion Detection

This allows integration with cloud dashboards or other IoT applications.

---

## Web Dashboard

The ESP32 hosts a lightweight web server over WiFi.

The webpage displays:

- Temperature
- Humidity
- Gas Level
- Light Level
- Motion Status
- Fan Status
- Light Status
- Gas Alarm Status

The dashboard refreshes automatically at regular intervals.

---

## Working Principle

1. ESP32 connects to WiFi.
2. Sensors are initialized.
3. Sensor values are continuously read.
4. Automation rules determine relay outputs.
5. OLED updates with current readings.
6. Data is published via MQTT.
7. Web dashboard provides live monitoring.

---

## Applications

- Smart Home Automation
- Gas Leak Monitoring
- Motion-based Lighting
- Environmental Monitoring
- IoT Dashboard Demonstration
- Educational IoT Projects

---

## Future Improvements

- Mobile application control
- Cloud database integration
- Voice assistant support
- Email/SMS notifications
- Automatic logging of sensor history
- Energy consumption monitoring
- Remote relay control