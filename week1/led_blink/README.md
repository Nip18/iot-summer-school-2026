# Week 1: Variable Speed LED Blink

An embedded systems application that reads an analog signal from a potentiometer to dynamically control the blinking frequency of an onboard/external LED while streaming live iteration updates via a serial interface.

---

## Hardware Required
* *Microcontroller:* Arduino Uno R3 (or compatible board)
* *Actuator:* 1x Light Emitting Diode (LED)
* *Current-Limiting Resistor:* 1x $220\,\Omega$ Resistor (to protect the LED)
* *Control Input:* 1x $10\,\text{k}\Omega$ Linear Potentiometer
* *Prototyping:* 1x Solderless Breadboard & Male-to-Male jumper wires
* *Interface:* 1x USB Type-A to Type-B cable

---

## Circuit Diagram Description
Below is the point-to-point electrical schematic layout:

1. **Power & Ground Rails:** * Connect the Arduino **5V** pin to the positive (+) rail of the breadboard.
   * Connect the Arduino **GND** pin to the negative (-) rail of the breadboard.
2. **Potentiometer Connections:**
   * *Left Terminal (Pin 1):* Connected to the Ground (GND) rail.
   * *Middle Terminal / Wiper (Pin 2):* Connected directly to Arduino Analog Input pin **A0**.
   * *Right Terminal (Pin 3):* Connected to the 5V power rail.
3. **LED Output Connections:**
   * *Anode (Longer leg):* Connected to Arduino Digital Pin **13** through a $220\,\Omega$ protection resistor.
   * *Cathode (Shorter leg):* Connected directly back to the Ground (GND) rail.

---

## How to Upload Code(Step-by-Step)
1. **Open IDE:** Launch the official Arduino IDE on your computer.
2. **Copy Source:** Copy the contents of the `led_blink.ino` script from this folder and paste it into a fresh sketch window.
3. **Hardware Interface:** Connect your Arduino board to your machine using the USB cable.
4. **Target Board Selection:** Navigate to `Tools > Board` and select **Arduino Uno**.
5. **Port Identification:** Go to `Tools > Port` and select the active COM port assigned to the connected board.
6. **Compile & Flash:** Click the **Verify** (checkmark) button to ensure no syntax errors exist, then click the **Upload** (right-facing arrow) button to flash the binary to the microcontroller.

---

## Expected Output
* **Visual Behavior:** Rotating the dial on the potentiometer will smoothly shift the LED blinking behavior. Turning it completely clockwise increases the delay up to roughly 1 second per state transition, while turning it counter-clockwise speeds up the loop into a rapid flicker.
* **Serial Telemetry:** When opening the **Serial Monitor** (`Tools > Serial Monitor`) configured at a baud rate of **9600**, the terminal will print live updating strings matching the iteration loop:
  ```text
  Blink count: 1
  Blink count: 2
  Blink count: 3


## Troubleshooting Tips
*Issue 1*: Serial Monitor Output Garbage Text
Fix: Ensure the baud rate dropdown in the bottom-right corner of your Serial Monitor window is explicitly set to 9600 baud to match the firmware configuration (Serial.begin(9600)).

*Issue 2*: The LED Stays Entirely On or Entirely Off
Fix: Verify the orientation of the LED. The longer leg (anode) must face digital pin 13, and the shorter leg (cathode) must face ground. Also, double-check that your potentiometer connections are not loose.

*Issue 3*: "Failed uploading: uploading error" Message in IDE
Fix: Disconnect the USB cable, close potential background applications utilizing the connection, plug the cable back into a different USB port, and ensure you re-select the correct active port under Tools > Port.
