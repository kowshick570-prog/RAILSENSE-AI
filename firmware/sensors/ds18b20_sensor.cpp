#include "ds18b20_sensor.h"
#include <OneWire.h>
#include <DallasTemperature.h>

#define ONE_WIRE_BUS 4   // GPIO4 on ESP32

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature tempSensor(&oneWire);

void initTempSensor() {
  tempSensor.begin();
  Serial.println("DS18B20 initialized.");
}

float readTemperature() {
  tempSensor.requestTemperatures();
  return tempSensor.getTempCByIndex(0);
}
