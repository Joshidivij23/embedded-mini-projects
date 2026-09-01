# Embedded Mini Projects

Small, self-contained Arduino projects demonstrating hands-on work with sensors, actuators, and external hardware modules. Each project lives in its own folder with a single sketch.

## Projects

### 1. Solar Tracking System (`solar-tracking-pid/`)

A dual-axis solar tracker that automatically orients a panel toward the strongest light source using four LDR (light-dependent resistor) sensors and two servo motors.

**How it works:**
- Four LDRs are arranged in a top-left/top-right/bottom-left/bottom-right configuration.
- The sketch compares the averaged light readings across each axis (top vs. bottom, left vs. right) and incrementally drives the corresponding servo toward the brighter side.
- Each servo's range is bounded by software soft limits (20°-160°) to keep it within a safe mechanical range.

**Hardware:** Arduino Uno, 2 servo motors, 4 LDR sensors

**Dependency:** `Servo.h` (Arduino core library)

### 2. GSM-Based Home Security System (`gsm-home-security/`)

A PIR motion-triggered security system that sends an SMS alert and places a phone call through a GSM module when motion is detected.

**How it works:**
- A PIR motion sensor is continuously polled via `analogRead()`.
- When the reading crosses a threshold, the sketch sends an SMS alert through the GSM module using AT commands, then places a phone call.
- Uses `SoftwareSerial` to communicate with the GSM module independently of the board's main serial connection (which is kept free for debug logging).

**Hardware:** Arduino Uno, GSM module (SIM800/SIM900-style), PIR motion sensor

**Dependency:** `SoftwareSerial.h` (Arduino core library)

**Note on credentials:** the phone number in this sketch is a placeholder (`+YYxxxxxxxxxx`). Replace it with your own number in both the SMS and auto-dial sections before flashing.

## Board setup

Both sketches target the **Arduino Uno** (AVR architecture). In the Arduino IDE, make sure **Tools → Board** is set to Arduino Uno before compiling. These sketches will fail to build on non-AVR boards (e.g. ESP32) since `Servo.h` and this project's approach are written specifically for AVR-class hardware.

## Known limitations

- The solar tracker's soft limits keep the servo within its declared safe range, but there's no persistent state across power cycles. On reset, both servos return to their initial position and the tracker has to re-orient from scratch.
- The GSM security system has no debounce or cooldown after triggering. A sustained motion event can result in repeated back-to-back calls/SMS messages rather than a single alert per intrusion.
- Neither project includes automated tests; both were validated through direct hardware testing during development.

## Background

Both projects were built as hands-on personal/coursework exercises to practice sensor integration, closed-loop control (PID-style servo positioning), and external hardware communication (GSM AT commands) on Arduino.
