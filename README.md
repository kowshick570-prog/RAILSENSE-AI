# 🚆 RAILSENSE AI
### AI-Powered Predictive Railway Track Health Monitoring System

> **Far Away 2026 Hackathon Submission**

![Status](https://img.shields.io/badge/status-prototype-yellow)
![Platform](https://img.shields.io/badge/platform-ESP32-blue)
![AI](https://img.shields.io/badge/AI-TensorFlow%20Lite-orange)
![Cost](https://img.shields.io/badge/cost-%3C%E2%82%B92000%2Fnode-success)

---

## 📖 Overview

Indian Railways manages over **67,000 km** of railway track, much of which still relies on manual inspection. This leaves a critical gap — faults often go undetected until they cause derailments, infrastructure damage, operational delays, or safety hazards.

**RAILSENSE AI** is an intelligent, edge-based monitoring system that combines multi-sensor fusion, on-device AI anomaly detection, and autonomous decision-making to **predict track failures before they happen** — at a cost low enough for mass deployment across the entire rail network.

---

##  Problem Statement

- 67,000+ km of track, largely dependent on manual/periodic inspection
- Delayed fault detection → derailments, damage, delays, safety risk
- No real-time, scalable, low-cost monitoring solution currently deployed at scale

---

##  Proposed Solution

RAILSENSE AI deploys low-cost sensor nodes along the track that continuously monitor vibration, temperature, current, and location data. A TensorFlow Lite model running directly on the ESP32 detects anomalies at the edge, a severity engine classifies the risk level, and the system autonomously sends alerts and maintenance recommendations via MQTT — enabling a **sense → think → decide → act** pipeline with minimal human intervention.

---

##  Hardware Components

| Component | Function |
|---|---|
| **ESP32 Microcontroller** | Edge processing, AI inference, MQTT communication |
| **MPU6050** (Accelerometer & Gyroscope) | Detects vibration anomalies & track deformation |
| **DS18B20** Temperature Sensor | Monitors thermal stress on rails |
| **ACS712** Current Sensor | Detects electrical/signal anomalies |
| **NEO-6M GPS Module** | Geo-locates faults precisely |
| **Solar Power Module** | Enables off-grid, sustainable deployment |

---

##  Working / Pipeline

1. **Sense** – Sensors continuously collect track condition data (vibration, temperature, current, location)
2. **Think** – ESP32 performs edge processing on incoming sensor streams
3. **Predict** – TensorFlow Lite model detects anomalies in real time
4. **Decide** – Severity engine classifies the risk level (Low / Medium / Critical)
5. **Act** – Autonomous alerts sent via MQTT + maintenance recommendations generated

```
[Sensors] → [ESP32 Edge Processing] → [TFLite Anomaly Detection]
                                              ↓
                              [Severity Classification Engine]
                                              ↓
                        [MQTT Alerts] + [Maintenance Recommendations]
```

---

## ✨ Key Features

-  Predictive maintenance (forecast failures before they occur)
- ⚡ Edge AI processing — no constant cloud dependency
-  Real-time monitoring via MQTT
-  GPS-based fault localization
-  Autonomous, tiered alert system
-  Extremely low-cost, scalable deployment

---

##  Estimated Cost

**< ₹2,000 per monitoring node** — enabling dense, network-wide deployment without massive capital investment.

---

##  Future Scope

-  LoRaWAN integration for long-range, low-power communication
-  Digital twin implementation of railway track segments
-  Centralized railway dashboard for zone-wide visibility
-  Large-scale deployment across all railway zones

---

##  Repository Structure

```
railsense-ai/
├── firmware/              # ESP32 source code
│   ├── sensors/           # Sensor driver modules
│   ├── ml_model/          # TFLite model + inference code
│   └── mqtt_comm/          # MQTT communication logic
├── ml/                    # Model training scripts & datasets
├── hardware/              # Circuit diagrams, BOM, wiring
├── docs/                  # Project documentation, abstract, presentation
├── dashboard/             # (Future) centralized monitoring dashboard
└── README.md
```

---

##  Team

**Far Away 2026 Hackathon Submission**

---

## 📄 License

This project is open for educational and research purposes. License details to be added.
