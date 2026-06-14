#ifndef MQTT_HANDLER_H
#define MQTT_HANDLER_H

#include <Arduino.h>
#include "../sensors/gps_module.h"

void connectMQTT();
void loopMQTT();
void publishAlert(String severity, float anomalyScore, GPSData location,
                  float temperature, float current);

#endif
