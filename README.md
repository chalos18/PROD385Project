# Location-Based IoT Map - Monopoly style

**Author:** Ana Oliveira

- [Location-Based IoT Map - Monopoly style](#location-based-iot-map---monopoly-style)
  - [Introduction](#introduction)
  - [Project Overview](#project-overview)
  - [1. Project Requirements and System Architecture](#1-project-requirements-and-system-architecture)
    - [Inputs](#inputs)
    - [Outputs](#outputs)
  - [3. System Requirements](#3-system-requirements)
    - [Bill of materials](#bill-of-materials)
  - [4. Powering the System](#4-powering-the-system)
  - [5. How-To: Cloud Setup and Messaging](#5-how-to-cloud-setup-and-messaging)


## Introduction
This documentation provides:
- Full **technical documentation**
- Step-by-step **how-to instructions**
- Design justification for mechanical, electronic, and software components

The document is intended to be readable by someone recreating the project from scratch.


## Project Overview
This project implements a **location-aware Internet of Things (IoT) system** that combines **cloud-based communication**, **physical outputs**, and a **mechanical element** to create a playful but meaningful way of sharing presence and activity.

A mobile phone uses geofencing to detect when the user enters or leaves predefined locations (home, work, university, and rock climbing). These events are published as **MQTT messages** to a **HiveMQ cloud broker** and processed using **Node-RED** running on **Raspberry Pi** devices. Based on these messages, LEDs embedded in a Monopoly-style map of Christchurch illuminate to show the user’s current location, while an **LCD1602 display** provides contextual text such as availability and weather information.

In addition to geofencing, a **PIR motion sensor** installed at home acts as a local digital input, detecting presence in the room and sending updates to the same cloud infrastructure. This allows the system to distinguish between simply being at home and actively being present.

The project also includes a mechanical subsystem: a **TT DC motor–driven climbing rope mechanism** controlled by physical buttons. This system winds and unwinds a rope attached to a LEGO climber, adding tangible, physical motion to the otherwise data-driven map. Together, these elements form a fully networked, **interactive IoT device** that translates digital information into meaningful physical feedback.

## 1. Project Requirements and System Architecture

This project meets the requirements of designing and building a connected, Internet of Things (IoT) enabled mechanical device by combining internet-based communication with physical interaction. Location data is sent to a cloud-based MQTT server using geofencing and PIR-triggered events, allowing the IoT map to update real-world outputs such as LEDs and an LCD screen.

A clear mechanical component is included through a TT DC motor–controlled climbing rope mechanism, which physically moves a LEGO figure using electronic control and physical buttons. This satisfies the requirement for a device that is both connected and mechanical.

The project demonstrates multiple electronic-input-driven and wireless behaviours. A PIR sensor detects movement at home and sends messages to the cloud, while geofencing acts as a virtual wireless input for other locations. All events are transmitted over the internet to a HiveMQ server, where Node-RED processes the data and controls LEDs, LCD messages, and system behaviour. As a result, the device responds primarily to internet-sourced data, meeting the criteria for internet-based control.

The system also satisfies the requirement for multiple inputs and outputs. Digital inputs include the PIR sensor, push buttons, and geofence events, while analogue input is provided through real-time weather data retrieved from an online API. Outputs include digital LEDs, an LCD display, and a PWM-controlled DC motor, resulting in a well-rounded and responsive IoT system.

---

### Inputs
| Input                    | Type     | Description                                                            |
| ------------------------ | -------- | ---------------------------------------------------------------------- |
| PIR motion sensor        | Digital  | Detects movement at home and sends a cloud message indicating presence |
| Push buttons             | Digital  | Manual control of climbing mechanism (up / down)                       |
| Geofence location events | Digital  | Wireless location-based events triggered by entering defined areas     |
| Weather API data         | Analogue | Continuous environmental data such as temperature and conditions       |

### Outputs
| Output        | Type           | Description                                                  |
| ------------- | -------------- | ------------------------------------------------------------ |
| LEDs          | Digital        | Indicates current location on the physical map               |
| LCD1602 (I²C) | Digital        | Displays location messages and real-time weather information |
| TT DC motor   | Analogue (PWM) | Winds and unwinds rope to move LEGO climber                  |


---

## 3. System Requirements

### Bill of materials

Before starting the build, the following components were required to ensure the project could be developed, tested, and deployed successfully. Several components were chosen based on availability, ease of prototyping, and the need to test multiple subsystems in parallel.

**Microcontrollers & Computing**
- 2 × Raspberry Pi (Model 3 and Model 4)
    - Used to handle IoT communication, server interaction, control of LEDs, LCD display, and PIR motion detection node.
    - **Note**: One Raspberry Pi could be replaced with a lower-cost microcontroller such as a Wemos D1 Mini for a more budget-friendly build
- Arduino Mega
    - Used to control the TT DC motor climbing rope mechanism and handle physical button inputs
- Raspberry Pi GPIO HAT (solderable)
    - Provides extended and more reliable GPIO access for soldering LEDs and other permanent connections

**Power Components**

- Battery pack (for Raspberry Pi 4)
    - Enables portable operation of the IoT map
- Wall power adapter (for Raspberry Pi 3)
    - Provides stable power during development and testing
- 2 × AA batteries
    - Used to power motors and standalone prototypes

**Electronics & Wiring**

- 4 × Yellow LEDs
    - Indicate different locations on the physical map
- 4 × 220Ω or 330Ω resistors
    - Protect LEDs from overcurrent
- 3 × Female pin headers
    - Used for modular and replaceable connections
- Soldering wire (e.g., 4 red and 4 black wires, ~10 cm each)
    - Used for permanent LED and power connections
- Jumper wires (recommended in bulk)
    - Female-to-female
    - Male-to-male
    - Female-to-male
    - Buying packs is recommended, as multiple prototypes were often active at the same time
- Breadboards (minimum of 2, ideally 3)
    - Used for testing individual subsystems (LEDs, sensors, motors) simultaneously

**Sensors & Displays**

- PIR motion sensor
    - Detects movement at the home location and triggers server updates.
- LCD1602 I²C display
    - Displays location-based text messages in a clear and user-friendly way.

**Mechanical Components**

- TT DC motor
    - Climbing rope anchor system
- L293D Dual Full-Bridge Motor Driver IC
    - Allows safe control of DC motor direction and speed
- Fishing line (or similar)
    - Acts as the climbing rope
- LEGO minifigure (or similar)
    - Represents a climber and provides a playful, physical element to the project
- Wooden lid to hold rope into place when attached to TT DC motor (see pictures below, different alternatives could be used)

**Optional (Final Presentation & Enclosure)**
- 3D-printed PIR sensor and LCD holder
    - Improves durability and presentation of the final device
- 3D-printed location icons (e.g. house, campus)
    - Enhances clarity and visual appeal of the physical map
- Plywood (approx. 30 × 30 cm)
    - Used to construct the base map and mounting structure
- Wood glue
    - For assembling the plywood frame

---

## 4. Powering the System

The system is designed to operate continuously, as its usefulness depends on always being available. Disposable batteries are avoided wherever possible in favour of USB and mains-powered solutions.

- Raspberry Pi 3 (PIR sensor): powered via wall adapter for continuous home monitoring
- Raspberry Pi 4 (LEDs and LCD): powered via USB power bank for portability
- Arduino Mega (motor system): powered via USB wall adapter; can be disconnected when not in use

This approach improves reliability, reduces maintenance, and supports long-term operation.

## 5. How-To: Cloud Setup and Messaging

A serverless HiveMQ Cloud cluster is used to receive MQTT messages from the phone and sensors. Topics are defined for location updates, motion detection, and system control. Node-RED subscribes to these topics and routes messages to GPIO outputs and display logic.

1. Start a serverless Hive MQ Cloud cluster to receive MQTT messages
2. Connect 4 LEDs in series for our first circuit prototype
    
    <img src="images/LED_prototype_1.JPEG" alt="Alt text" width="400" height="400">
    <img src="images/LED_prototype_1.JPEG" alt="Alt text" width="400" height="400">
    <img src="images/LED_prototype_schematic.jpg" alt="Alt text" width="500" height="500">

3. 

