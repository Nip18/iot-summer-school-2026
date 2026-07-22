# Project 2: Gas & Fire Safety Alert System

## Overview

This project implements a home safety monitoring system capable of detecting hazardous gas leaks and fire conditions. The system continuously monitors the surrounding environment using an MQ-2 gas sensor and a flame detection input. Depending on the detected hazard level, it provides visual indications using LEDs and audible alerts through a buzzer.

Since Wokwi does not provide an official Flame Sensor component, a pushbutton was used to simulate the digital active-low output of a flame sensor.

---

## Components Used

- Arduino Uno R3
- MQ-2 Gas Sensor
- Pushbutton (simulated Flame Sensor)
- Active Buzzer
- Green LED
- Yellow LED
- Red LED
- 3 × 220Ω Resistors
- Breadboard
- Jumper Wires

---

## Circuit Connections

| Component | Arduino Pin |
|-----------|-------------|
| MQ-2 AO | A0 |
| Flame Sensor (Pushbutton) | D7 |
| Green LED | D10 |
| Yellow LED | D11 |
| Red LED | D12 |
| Active Buzzer | D9 |

---

## Working Principle

The MQ-2 sensor continuously measures gas concentration using its analog output. The analog value is converted into a percentage (0–100%).

The flame detector is simulated using a pushbutton connected with the internal pull-up resistor enabled. When the button is pressed, the input becomes LOW, mimicking the behaviour of an active-low flame sensor.

The system evaluates the inputs every cycle and classifies the environment into three safety levels.

### SAFE

Conditions:

- Gas level below 30%
- No flame detected

Actions:

- Green LED ON
- Yellow LED OFF
- Red LED OFF
- Buzzer OFF

---

### WARNING

Conditions:

- Gas level between 30% and 60%

Actions:

- Yellow LED ON
- Green LED OFF
- Red LED OFF
- Buzzer beeps once every second

---

### DANGER

Triggered when:

- Gas level exceeds 60%, or
- Flame is detected

Actions:

- Red LED ON
- Continuous buzzer
- Status displayed on Serial Monitor

---

## Serial Monitor Output

The system continuously prints sensor readings and the current safety state.

Example:

Gas: 18% | Flame: NO | STATUS: SAFE

Gas: 46% | Flame: NO | STATUS: WARNING

Gas: 82% | Flame: YES | STATUS: DANGER

---

## Features

- Continuous gas monitoring
- Simulated flame detection
- Three-level safety indication
- Visual LED alerts
- Audible buzzer alerts
- Real-time Serial Monitor status
- Active-low flame sensor implementation
- Non-blocking warning buzzer using millis()

---

## Testing

The following test cases were verified:

✔ Safe condition

✔ Warning condition

✔ Gas danger condition

✔ Flame danger condition

✔ Combined gas + flame danger condition

---

## Note

The MQ-2 sensor normally requires approximately 1–2 minutes of warm-up time before stable readings are obtained on physical hardware. In Wokwi simulation, sensor values respond immediately.