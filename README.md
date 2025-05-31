# PIC16F877A Temperature and Humidity Measurement Using AHT10 Sensor

This project demonstrates how to interface the AHT10 temperature and humidity sensor with the PIC16F877A microcontroller via I2C communication. The measured values are displayed in real-time on a 16x2 LCD display using CCS C.

---

## 📌 Overview

The AHT10 is a modern, digital humidity and temperature sensor with a calibrated, I2C-based interface. This project uses a PIC16F877A microcontroller to:
- Communicate with the AHT10 sensor via I2C protocol
- Read and convert raw temperature and humidity data
- Display the results on an LCD display

---

## 🔧 Features

- 📡 I2C communication with AHT10 sensor  
- 📺 16x2 LCD display in 4-bit or I2C mode  
- 🌡️ Temperature in degrees Celsius (°C)  
- 💧 Relative humidity in percentage (%)  
- 📦 Modular CCS C codebase  
- 🧪 Proteus simulation ready (optional)

---

## 🛠️ Hardware Requirements

| Component                 | Quantity |
|--------------------------|----------|
| PIC16F877A MCU           | 1        |
| AHT10 Sensor (I2C)       | 1        |
| 16x2 LCD Display         | 1        |
| Potentiometer (10K)      | 1        |
| I2C Pull-up Resistors    | 2 (4.7kΩ)|
| Breadboard + Wires       | 1 set    |
| Power Supply (5V)        | 1        |

---

## 💻 Software Requirements

- CCS C Compiler
- MPLAB X IDE (or MPLAB 8)
- Proteus (for simulation, optional)
- GitHub Desktop / Git CLI (for version control)

---

## 🔌 Wiring Diagram

**I2C Connections:**
- AHT10 SDA → PIC16F877A RC4 (SDA)
- AHT10 SCL → PIC16F877A RC3 (SCL)
- 4.7kΩ pull-up resistors on SDA & SCL to Vcc

**LCD Connections:**
- Standard 4-bit mode to PORTD or use I2C LCD with PCF8574

Full schematic is available in the `schematics/` folder.

---

## 🧠 How It Works

1. The microcontroller initializes the I2C module.
2. AHT10 is sent a trigger command to start measurement.
3. The sensor responds with 6 bytes of raw data.
4. Raw bytes are processed into temperature (°C) and humidity (%) values.
5. LCD displays the results every 1 second in the main loop.

---

## 📂 Code Structure

