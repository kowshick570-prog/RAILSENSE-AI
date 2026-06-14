# RAILSENSE AI — Project Abstract

**RAILSENSE AI** addresses a critical gap in Indian Railways infrastructure
management — 67,000 km of track still inspected manually, leading to
undetected faults and derailments. The proposed system deploys a
multi-sensor fusion node (MPU6050, DS18B20, ACS712, NEO-6M GPS) on an
ESP32 microcontroller, running a TensorFlow Lite anomaly detection model
at the edge to predict track failures before they occur.

Unlike reactive monitoring systems, RAILSENSE AI implements a fully
autonomous **sense → think → decide → act** pipeline, where a severity
scoring engine independently classifies fault criticality and executes
tiered responses — from maintenance work order generation to emergency
MQTT alerts and train speed restriction triggers — without human
intervention.

Designed for solar-powered, off-grid deployment at under ₹2,000 per node,
RAILSENSE AI offers a scalable and immediately deployable path toward
nationwide predictive railway track health monitoring.
