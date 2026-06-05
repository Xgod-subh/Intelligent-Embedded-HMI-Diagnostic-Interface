# Intelligent Embedded HMI & Diagnostic Interface

## Project Overview

This project implements a professional Human-Machine Interface (HMI) for an embedded battery monitoring system using ESP32 and a 16x2 I2C LCD.

The interface automatically rotates between multiple diagnostic screens displaying battery data, analytics, protection status, and fault diagnostics. During critical conditions, a fault-priority override mechanism immediately displays warning information to the user.

---

## Features

* Automatic multi-screen LCD interface
* Live battery voltage monitoring
* Battery health analytics
* Protection status display
* Fault diagnostics display
* Fault-priority screen override
* Non-blocking architecture using millis()
* Smooth LCD screen rotation
* ESP32-based implementation
* Wokwi simulation support

---

## Hardware Used

* ESP32 DevKit
* 16x2 I2C LCD
* Potentiometer
* Push Button
* Wokwi Simulator

---

## Pin Connections

| Component     | ESP32 Pin |
| ------------- | --------- |
| Potentiometer | GPIO34    |
| Push Button   | GPIO27    |
| LCD SDA       | GPIO21    |
| LCD SCL       | GPIO22    |

---

## HMI Screens

### Battery Data

Displays real-time battery voltage.

### Analytics

Displays battery health condition.

### Protection Status

Shows SAFE or FAULT status.

### Diagnostics

Displays active fault information.

### Fault Override

Immediately overrides normal screens when:

* Low Voltage
* Over Voltage
* Sensor Error

---

## Technologies Used

* ESP32
* Arduino IDE
* Embedded C++
* Wokwi
* LCD Interface Design
* Event Driven Programming

---

## Author

Subhronil Haldar

Electrical and Electronics Engineering


