#include "mqtt_handler.h"
#include <WiFi.h>
#include <PubSubClient.h>

// ---------- WiFi & MQTT Configuration ----------
const char* WIFI_SSID     = "YOUR_WIFI_SSID";
const char* WIFI_PASSWORD = "YOUR_WIFI_PASSWORD";

const char* MQTT_BROKER   = "broker.hivemq.com";
const int   MQTT_PORT     = 1883;
const char* MQTT_TOPIC    = "railsense/track_health";
const char* DEVICE_ID     = "RAILSENSE_NODE_01";

WiFiClient espClient;
PubSubClient mqttClient(espClient);

void connectWiFi() {
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi connected.");
}

void connectMQTT() {
  connectWiFi();
  mqttClient.setServer(MQTT_BROKER, MQTT_PORT);

  while (!mqttClient.connected()) {
    Serial.print("Connecting to MQTT broker...");
    if (mqttClient.connect(DEVICE_ID)) {
      Serial.println("connected.");
    } else {
      Serial.print("failed, rc=");
      Serial.print(mqttClient.state());
      Serial.println(" retrying in 2s");
      delay(2000);
    }
  }
}

void loopMQTT() {
  if (!mqttClient.connected()) {
    connectMQTT();
  }
  mqttClient.loop();
}

void publishAlert(String severity, float anomalyScore, GPSData location,
                   float temperature, float current) {
  String payload = "{";
  payload += "\"device_id\":\"" + String(DEVICE_ID) + "\",";
  payload += "\"severity\":\"" + severity + "\",";
  payload += "\"anomaly_score\":" + String(anomalyScore, 3) + ",";
  payload += "\"temperature_c\":" + String(temperature, 2) + ",";
  payload += "\"current_a\":" + String(current, 2) + ",";
  payload += "\"latitude\":" + String(location.latitude, 6) + ",";
  payload += "\"longitude\":" + String(location.longitude, 6);
  payload += "}";

  mqttClient.publish(MQTT_TOPIC, payload.c_str());

  // Tiered autonomous response based on severity
  if (severity == "CRITICAL") {
    mqttClient.publish("railsense/alerts/emergency", payload.c_str());
    mqttClient.publish("railsense/speed_restriction", "RESTRICT_SPEED");
  } else if (severity == "MEDIUM") {
    mqttClient.publish("railsense/maintenance/work_order", payload.c_str());
  }
}
