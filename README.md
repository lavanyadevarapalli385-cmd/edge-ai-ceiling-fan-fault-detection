# Edge AI Based Smart Fault Detection in Ceiling Fans

## 📌 Project Overview

This project presents an Edge AI based smart fault detection system designed for ceiling fans. The system uses an ESP32 controller along with temperature, vibration, current, and voltage sensors to continuously monitor fan operating conditions.

A Random Forest machine learning model is used to analyze the collected sensor parameters and classify abnormal operating conditions. When a fault is detected, the system can initiate safety actions such as power cut-off and alert generation.

## 🎯 Objectives

- Continuously monitor ceiling fan operating parameters.
- Detect abnormal conditions at an early stage.
- Use Edge AI for real-time fault classification.
- Reduce dependency on cloud-based processing.
- Improve electrical and mechanical safety.
- Provide alerts when a fault condition is detected.

## ⚙️ Hardware Components

- ESP32 Microcontroller
- Temperature Sensor
- Vibration Sensor
- Current Sensor
- Voltage Sensor
- Relay Module
- Buzzer / Voice Alert Module

## 🧠 Machine Learning

The system uses a **Random Forest classification algorithm** for fault detection.

Sensor parameters such as:

- Temperature
- Vibration
- Current
- Voltage

are used as input features for the machine learning model.

The trained model is intended to be deployed on the ESP32 for Edge AI based inference.

## 🔄 System Workflow

```text
Power ON
   ↓
Initialize ESP32 and Sensors
   ↓
Acquire Sensor Data
   ↓
Data Preprocessing
   ↓
Random Forest Inference
   ↓
Fault Detection
   ↓
┌─────────────────────┐
│                     │
No Fault            Fault
│                     │
↓                     ↓
Continue            Classify Fault
Monitoring              ↓
                  Activate Relay
                        ↓
                  Generate Alert
                        ↓
                  Log Fault Data
## 🚨 Fault Categories

The system is designed to classify abnormal ceiling fan conditions into:

- Electrical Fault
- Mechanical Fault
- Overload Condition

## 🛠️ Technologies Used

- ESP32
- Embedded C/C++
- Arduino IDE
- Machine Learning
- Random Forest
- Python / Scikit-learn

## 🛡️ Safety Features

When a fault is detected, the system can activate the relay to disconnect the fan supply and generate an alert.

## 🔮 Future Enhancements

- Mobile application integration
- Remote monitoring
- Larger fault datasets
- Predictive maintenance
- Historical fault analysis
