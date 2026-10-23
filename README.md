# IoT-Based Smart Helmet for Alcohol Detection, Accident Monitoring, and Real-Time GPS Alerts

##  Project Overview

The IoT-Based Smart Helmet is an ESP32-based safety prototype designed to monitor alcohol-sensor readings, helmet-wearing status, and potential accidents. The system uses sensor inputs and embedded control logic to provide alerts and control an ignition-related relay output.

The current Wokwi simulation demonstrates the core sensing and control logic. GPS tracking and GSM-based emergency SMS alerts are planned enhancements.

##  Objectives

- Monitor alcohol-sensor readings using a configurable threshold.
- Detect helmet-wearing status using a push-button input in the simulation.
- Control the relay output based on helmet status and alcohol-sensor readings.
- Monitor motion data using an MPU6050 accelerometer and gyroscope.
- Provide visual and audio alerts using an LED, LCD, and buzzer.
- Extend the system with GPS location tracking and GSM emergency notifications.

##  Hardware Components

- ESP32 development board
- Potentiometer (simulates the alcohol-sensor input in the current circuit)
- MPU6050 accelerometer and gyroscope
- I2C 16×2 LCD
- Relay module
- Buzzer
- LED
- Push button
- Connecting wires

**Planned additions:** MQ-3 alcohol sensor, GPS module (NEO-6M), and GSM module (SIM800L).
## Software and Tools

- Wokwi circuit simulator
- Arduino IDE / ESP32 Arduino framework
- Embedded C/C++
- LiquidCrystal_I2C library
- Adafruit MPU6050 library
- Adafruit Unified Sensor library
- Wire and Math libraries

##  Working Principle

1. Initialize the ESP32, LCD, GPIO pins, and MPU6050 sensor.
2. Read the analog input connected to GPIO 34.
3. Compare the input reading with the configured threshold.
4. Read the helmet-status push button connected to GPIO 27.
5. Enable or disable the relay output according to the helmet and alcohol-input conditions.
6. Monitor MPU6050 acceleration readings for sudden changes.
7. Display status information on the LCD and serial monitor.
8. Activate the buzzer when an alcohol threshold is exceeded, the helmet is not detected as worn, or a potential accident is detected.

##  Pin Configuration

| Component | ESP32 connection |

 Alcohol-sensor simulation input -  | GPIO 34 |
 Helmet-status push button - | GPIO 27 |
 Relay control -  | GPIO 25 |
 Buzzer - | GPIO 26 |
 LED - | GPIO 12 |
 LCD SDA - | GPIO 21 |
 LCD SCL - | GPIO 22 |
 MPU6050 SDA - | GPIO 21 |
 MPU6050 SCL - | GPIO 22 |

##  Simulation

The project circuit is designed and tested in the Wokwi simulation environment.

![Smart Helmet Simulation (simulation1.png)

##  Current Implementation Status

- ESP32 firmware for sensor inputs and output control
- Alcohol-input threshold logic
- Helmet-status input
- LCD and serial-monitor status display
- Relay, LED, and buzzer control
- Basic MPU6050 acceleration-threshold demonstration

##  Future Enhancements

- Integrate and calibrate a physical MQ-3 alcohol sensor.
- Improve accident detection and reduce false alarms.
- Add GPS-based location acquisition.
- Implement GSM-based emergency SMS alerts.
- Test the integrated system on physical hardware.
- Evaluate detection accuracy, response time, and reliability.

##  Safety Disclaimer

This is an educational prototype and is not a certified vehicle safety device. The simulated analog reading does not represent a verified blood-alcohol concentration, and the basic acceleration threshold is not a validated accident detector. Do not connect the prototype to a real vehicle ignition system without appropriate engineering safeguards and professional testing.


