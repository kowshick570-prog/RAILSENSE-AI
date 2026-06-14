# 🔌 Wiring / Pin Connection Guide - RAILSENSE AI Node

## ESP32 Pin Mapping

| Sensor | Pin on Sensor | Connects to ESP32 Pin | Notes |
|---|---|---|---|
| MPU6050 | VCC | 3.3V | |
| | GND | GND | |
| | SDA | GPIO21 | I2C Data |
| | SCL | GPIO22 | I2C Clock |
| DS18B20 | VCC | 3.3V | |
| | GND | GND | |
| | DATA | GPIO4 | Needs 4.7kΩ pull-up resistor to 3.3V |
| ACS712 | VCC | 5V (via VIN) | |
| | GND | GND | |
| | OUT | GPIO34 | ADC1 channel (input-only pin) |
| NEO-6M GPS | VCC | 3.3V / 5V (check module) | |
| | GND | GND | |
| | TX | GPIO16 (RX2) | |
| | RX | GPIO17 (TX2) | |
| Solar + Battery | Solar Panel → Charge Controller → Battery → ESP32 VIN/5V | | Ensure regulated 5V/3.3V output |

## Notes
- Use a logic-level safe ADC pin (GPIO32-39) for ACS712 — these are input-only on ESP32.
- I2C bus (SDA/SCL) can be shared if more I2C sensors are added later.
- Keep GPS antenna away from the ESP32 WiFi antenna to minimize interference.
- Add a TVS diode / decoupling capacitor near ACS712 output to reduce ADC noise.
