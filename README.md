# Smart-Parking-Assist-System
# Smart Parking Assist System

## Overview

The **Smart Parking Assist System** is an embedded systems project built around the **ATmega2560 microcontroller** to assist drivers during parking through real-time distance measurement, visual indicators, and audible alerts.

The system uses an HC-SR04 ultrasonic sensor to measure the distance between the vehicle and an obstacle. Based on the measured distance, LEDs indicate the parking safety level, while an active buzzer generates alerts to help the driver respond appropriately. An IR sensor monitors parking slot occupancy, and two seven-segment displays present the measured distance.

A key focus of this project is **low-level embedded C programming and hardware abstraction**. Peripheral operations are implemented through custom drivers for GPIO, timers, ultrasonic sensing, IR sensing, and seven-segment displays, providing practical experience with microcontroller peripherals and modular firmware design.

## Key Features

* **Real-time distance measurement:** Measures the distance to nearby obstacles using an HC-SR04 ultrasonic sensor.
* **Multi-level parking guidance:** Uses green, yellow, and red LEDs to indicate different distance and caution levels.
* **Audible alerts:** An active buzzer provides distance-dependent warning patterns.
* **Parking slot monitoring:** An IR sensor detects whether a parking slot is available or occupied.
* **Distance display:** Two seven-segment displays show the measured distance in centimeters.
* **Custom peripheral drivers:** Uses modular drivers for GPIO, timer, ultrasonic sensor, IR sensor, and seven-segment display.
* **Bare-metal learning:** Emphasizes direct register-level peripheral control through custom hardware abstraction functions rather than relying on Arduino peripheral libraries.

## Hardware Components

* ATmega2560 / Arduino Mega 2560 board
* HC-SR04 ultrasonic distance sensor
* HW-201 IR obstacle sensor
* Green, yellow, and red LEDs
* Active buzzer
* Two seven-segment displays
* Current-limiting resistors and connecting wires

## Working Principle

1. The ultrasonic sensor measures the distance between the vehicle and the obstacle.
2. The firmware classifies the measured distance into parking guidance levels.
3. LEDs indicate the current safety level.
4. The buzzer generates warning patterns according to the distance classification.
5. Two seven-segment displays show the distance reading.
6. The IR sensor independently monitors parking slot occupancy.

## Software and Development

* **Microcontroller:** ATmega2560
* **Programming language:** Embedded C / C++
* **Development environment:** Arduino IDE or PlatformIO
* **Architecture:** Modular firmware with custom hardware abstraction drivers

## Learning Outcomes

This project provides hands-on experience in embedded C programming, GPIO configuration, timer operation, sensor interfacing, register-level programming, driver development, and integration of multiple hardware peripherals.

## Project Goal

To develop a practical, modular embedded system that demonstrates how microcontroller-based sensing, real-time decision-making, and human-readable alerts can improve parking assistance and slot monitoring.

---

**Note:** This project is an educational prototype. Sensor readings and warning thresholds should be calibrated and validated for the intended installation environment before practical deployment.
