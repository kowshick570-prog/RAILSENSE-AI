# ⚙️ Setup Guide - RAILSENSE AI

## 1. Arduino IDE Setup
1. Install [Arduino IDE](https://www.arduino.cc/en/software) (v2.x recommended).
2. Add ESP32 board support:
   - File → Preferences → Additional Board Manager URLs:
     `https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json`
   - Tools → Board → Boards Manager → search "esp32" → Install
3. Install required libraries via Library Manager:
   - `Adafruit MPU6050`
   - `Adafruit Unified Sensor`
   - `Adafruit BusIO`
   - `OneWire`
   - `DallasTemperature`
   - `TinyGPSPlus`
   - `PubSubClient`
   - `TensorFlowLite_ESP32`

## 2. Configure Credentials
Edit `firmware/mqtt_comm/mqtt_handler.cpp`:
- Set `WIFI_SSID` and `WIFI_PASSWORD`
- Set `MQTT_BROKER` (use your own broker or HiveMQ public broker for testing)

## 3. Train & Convert the AI Model
```bash
cd ml
pip install -r requirements.txt
python train_model.py
xxd -i railsense_anomaly_model.tflite > ../firmware/ml_model/anomaly_model.h
```
Then rename the generated array/length variables inside `anomaly_model.h` to:
- `railsense_anomaly_model_tflite`
- `railsense_anomaly_model_tflite_len`

## 4. Flash the ESP32
1. Open `firmware/railsense_main/railsense_main.ino` in Arduino IDE.
2. Select Board: **ESP32 Dev Module**, correct COM port.
3. Click Upload.
4. Open Serial Monitor (115200 baud) to view live sensor + severity output.

## 5. Verify MQTT Alerts
Subscribe to the topics below using an MQTT client (e.g., MQTT Explorer):
- `railsense/track_health`
- `railsense/alerts/emergency`
- `railsense/maintenance/work_order`
- `railsense/speed_restriction`
