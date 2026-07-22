# Project 5 - Bluetooth Home Controller

## Objective

Develop an ESP32-based Bluetooth home automation system that allows users to wirelessly control electrical appliances using simple Bluetooth commands.

## Components Used

- ESP32 Dev Board
- HC-05 Bluetooth Module
- 2-Channel Relay Module
- Push Buttons (optional)
- LEDs (for indication)
- Breadboard
- Jumper Wires

## Circuit Connections

| Component | ESP32 Pin |
|-----------|-----------|
| HC-05 TX | GPIO 16 (RX2) |
| HC-05 RX | GPIO 17 (TX2) |
| Relay IN1 | GPIO 25 |
| Relay IN2 | GPIO 26 |
| Button 1 | GPIO 32 |
| Button 2 | GPIO 33 |

## Libraries Used

- BluetoothSerial (ESP32)

## Features

- Bluetooth-based appliance control
- Relay switching
- Manual button override
- Real-time command feedback
- Serial Monitor logging
- Simple single-character commands

## Working Principle

The ESP32 receives commands from a Bluetooth-connected smartphone via the HC-05 module. Based on the received command, it switches the corresponding relay to control connected appliances. Manual push buttons can also be used to operate the relays independently, while the Serial Monitor displays the current system status.

## How to Run

1. Connect all components.
2. Upload the Arduino sketch.
3. Pair your smartphone with the HC-05 Bluetooth module.
4. Send the predefined commands using any Bluetooth terminal app.
5. Observe the relay operation and status updates.

## Expected Output

- Successful Bluetooth connection.
- Relay switches ON/OFF according to received commands.
- Manual buttons override Bluetooth control.
- Serial Monitor displays received commands and relay status.

## Folder Structure

```
Project5/
│── Project5.ino
└── README.md
```

## Future Improvements

- Mobile application with graphical interface
- Voice-controlled operation
- Wi-Fi and IoT integration
- Scheduling and automation
- Energy consumption monitoring