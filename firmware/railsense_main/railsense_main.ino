/*
  RAILSENSE AI - Main Firmware
  AI-Powered Predictive Railway Track Health Monitoring System
  Board: ESP32

  Pipeline:
  1. SENSE  - Read MPU6050, DS18B20, ACS712, NEO-6M GPS
  2. THINK  - Build feature vector from sensor readings
  3. PREDICT- Run TFLite Micro anomaly detection on-device
  4. DECIDE - Severity classification engine
  5. ACT    - Publish MQTT alerts + maintenance recommendations

  NOTE: Required libraries (install via Arduino Library Manager):
  - Adafruit MPU6050 + Adafruit Unified Sensor + Adafruit BusIO
  - OneWire + DallasTemperature (for DS18B20)
  - TinyGPSPlus
  - PubSubClient
  - TensorFlowLite_ESP32
*/

#include "sensors/mpu6050_sensor.h"
#include "sensors/ds18b20_sensor.h"
#include "sensors/acs712_sensor.h"
#include "sensors/gps_module.h"
#include "ml_model/inference.h"
#include "mqtt_comm/mqtt_handler.h"

// ---------- Configuration ----------
const unsigned long SENSOR_READ_INTERVAL_MS = 5000;   // Read every 5 seconds
unsigned long lastReadTime = 0;

// ---------- Severity Thresholds (tune after calibration) ----------
const float THRESHOLD_LOW    = 0.30;
const float THRESHOLD_MEDIUM = 0.60;
const float THRESHOLD_HIGH   = 0.85;

void setup() {
  Serial.begin(115200);
  Serial.println("RAILSENSE AI - Booting up...");

  initMPU6050();
  initTempSensor();
  initCurrentSensor();
  initGPS();
  initModel();          // Load TFLite anomaly detection model
  connectMQTT();        // Connect to WiFi + MQTT broker

  Serial.println("RAILSENSE AI - System Ready.");
}

void loop() {
  unsigned long now = millis();

  if (now - lastReadTime >= SENSOR_READ_INTERVAL_MS) {
    lastReadTime = now;

    // ---------- 1. SENSE ----------
    VibrationData vib   = readVibration();
    float temperature   = readTemperature();
    float current       = readCurrent();
    GPSData location    = getLocation();

    // ---------- 2. THINK (feature vector) ----------
    float features[8] = {
      vib.accelX, vib.accelY, vib.accelZ,
      vib.gyroX,  vib.gyroY,  vib.gyroZ,
      temperature, current
    };

    // ---------- 3. PREDICT (edge AI inference) ----------
    float anomalyScore = runInference(features);

    // ---------- 4. DECIDE (severity classification) ----------
    String severity = classifySeverity(anomalyScore);

    // ---------- 5. ACT (publish alert) ----------
    publishAlert(severity, anomalyScore, location, temperature, current);

    Serial.printf("Anomaly: %.2f | Severity: %s | Lat: %.6f Lon: %.6f | Temp: %.1fC | Curr: %.2fA\n",
                   anomalyScore, severity.c_str(), location.latitude, location.longitude,
                   temperature, current);
  }

  loopMQTT();  // keep MQTT connection alive
}

// ---------- Severity Classification Engine ----------
String classifySeverity(float score) {
  if (score < THRESHOLD_LOW)         return "NORMAL";
  else if (score < THRESHOLD_MEDIUM) return "LOW";
  else if (score < THRESHOLD_HIGH)   return "MEDIUM";
  else                                return "CRITICAL";
}
