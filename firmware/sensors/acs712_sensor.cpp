#include "acs712_sensor.h"
#include <Arduino.h>

#define ACS712_PIN 34              // ESP32 ADC1 pin
#define ACS712_SENSITIVITY 0.066   // V/A for 30A module
#define ADC_VREF 3.3
#define ADC_RESOLUTION 4095.0

float acs712Zero = 1.65;  // Zero-current voltage, calibrated at startup

void initCurrentSensor() {
  long sum = 0;
  for (int i = 0; i < 50; i++) {
    sum += analogRead(ACS712_PIN);
    delay(2);
  }
  float avgRaw = sum / 50.0;
  acs712Zero = (avgRaw / ADC_RESOLUTION) * ADC_VREF;
  Serial.println("ACS712 initialized. Zero offset calibrated.");
}

float readCurrent() {
  int raw = analogRead(ACS712_PIN);
  float voltage = (raw / ADC_RESOLUTION) * ADC_VREF;
  float current = (voltage - acs712Zero) / ACS712_SENSITIVITY;
  return current;
}
