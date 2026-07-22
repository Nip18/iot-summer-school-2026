# P4 – Smart Soil Moisture Monitoring & Automatic Irrigation System

## 📌 Objective

The Smart Soil Moisture Monitoring & Automatic Irrigation System is an ESP32-based IoT project designed to automate plant irrigation by monitoring soil moisture and environmental conditions. The system continuously measures soil moisture, temperature, and humidity, displays real-time information on an OLED display, and automatically controls a water pump (simulated using a relay) when the soil becomes dry. A manual override button allows the user to activate the pump whenever required.

---

# Features

* 🌱 Real-time Soil Moisture Monitoring
* 🌡️ Temperature & Humidity Monitoring using DHT11
* 📺 OLED Dashboard
* 🚿 Automatic Irrigation using Relay
* 🔴🟢 LED Status Indicators
* ✋ Manual Pump Override Button
* 📈 Soil Moisture Percentage Calculation
* 🔄 Hysteresis-based Pump Control
* 🖥️ Serial Monitor Logging

---

# Components Required

| Component                                                            | Quantity    |
| -------------------------------------------------------------------- | ----------- |
| ESP32 Dev Board                                                      | 1           |
| Capacitive Soil Moisture Sensor                                      | 1           |
| DHT11 Sensor                                                         | 1           |
| SSD1306 OLED Display                                                 | 1           |
| 2-Channel Relay Module                                               | 1           |
| Green LED                                                            | 1           |
| Red LED                                                              | 1           |
| Push Button                                                          | 1           |
| 220Ω Resistors                                                       | 2           |
| 10kΩ Resistor (Button Pull-down, optional if not using INPUT_PULLUP) | 1           |
| Breadboard                                                           | 1           |
| Jumper Wires                                                         | As Required |

---

# Hardware Connections

## Soil Moisture Sensor

| Soil Sensor | ESP32         |
| ----------- | ------------- |
| VCC         | 3V3           |
| GND         | GND           |
| AOUT        | GPIO34        |
| DOUT        | Not Connected |

---

## DHT11

| DHT11 | ESP32 |
| ----- | ----- |
| VCC   | 3V3   |
| GND   | GND   |
| DATA  | GPIO4 |

*(If you're using the bare 4-pin DHT11, add a **10kΩ pull-up resistor** between VCC and DATA.)*

---

## OLED Display (I²C)

| OLED | ESP32  |
| ---- | ------ |
| VCC  | 3V3    |
| GND  | GND    |
| SDA  | GPIO21 |
| SCL  | GPIO22 |

---

## Relay Module

| Relay | ESP32                                           |
| ----- | ----------------------------------------------- |
| VCC   | 5V *(or 3.3V if your relay module supports it)* |
| GND   | GND                                             |
| IN1   | GPIO27                                          |

---

## LEDs

### Green LED

| LED         | ESP32                          |
| ----------- | ------------------------------ |
| Anode (+)   | GPIO25 (through 220Ω resistor) |
| Cathode (-) | GND                            |

### Red LED

| LED         | ESP32                          |
| ----------- | ------------------------------ |
| Anode (+)   | GPIO26 (through 220Ω resistor) |
| Cathode (-) | GND                            |

---

## Push Button

| Push Button    | ESP32 |
| -------------- | ----- |
| One Terminal   | GPIO0 |
| Other Terminal | GND   |

*(The code uses `INPUT_PULLUP`, so no external pull-down resistor is needed.)*

---

# Working Principle

1. ESP32 reads the soil moisture sensor.
2. ADC value is converted into a moisture percentage.
3. DHT11 measures temperature and humidity.
4. OLED displays:

   * Soil Moisture
   * Temperature
   * Humidity
   * Soil Status
   * Pump Status
   * Moisture Bar Graph
5. If moisture falls below **30%**, the relay turns ON.
6. The relay remains ON until moisture rises above **40%** (hysteresis).
7. Green LED indicates healthy soil.
8. Red LED indicates dry soil and pump operation.
9. Pressing the push button activates the relay manually for **5 seconds**, after which the system returns to automatic mode.

---

# OLED Display

```
SMART IRRIGATION

Moist: 46%    OPTIMAL

Temp: 29.1 C
Hum : 71%

Pump : OFF

███████████---------
```

---

# Serial Monitor Output

```
--------------------------------
ADC Value      : 2084
Moisture       : 46%
Temperature    : 29.2 C
Humidity       : 70 %
Soil Status    : OPTIMAL
Pump           : OFF
Mode           : AUTO
```

---

# Moisture Calibration

Before using the project:

1. Keep the sensor **in air** and note the ADC value.
2. Insert it into **wet soil or water** and note the ADC value.
3. Update these values in the code:

```cpp
const int dryValue = 3200;
const int wetValue = 1200;
```

This ensures accurate moisture percentage calculation.

---

# Applications

* Smart Irrigation
* Home Gardening
* Greenhouses
* Indoor Plant Monitoring
* Precision Agriculture
* IoT-based Farming Systems

---

# Libraries Required

* Adafruit GFX
* Adafruit SSD1306
* DHT Sensor Library by Adafruit
* Wire (Built-in)

---

# Expected Outcome

The ESP32 continuously monitors soil moisture and environmental conditions, automatically controls irrigation using a relay, displays all important information on an OLED screen, and provides manual control through a push button. This project demonstrates sensor integration, embedded programming, automation, and IoT-based smart agriculture using the ESP32.
