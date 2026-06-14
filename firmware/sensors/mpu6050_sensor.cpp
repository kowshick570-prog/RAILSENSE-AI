#include "mpu6050_sensor.h"
#include <Wire.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>

Adafruit_MPU6050 mpu;

void initMPU6050() {
  if (!mpu.begin()) {
    Serial.println("ERROR: MPU6050 not found! Check wiring (SDA/SCL).");
    while (1) delay(10);
  }
  mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
  mpu.setGyroRange(MPU6050_RANGE_500_DEG);
  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);
  Serial.println("MPU6050 initialized.");
}

VibrationData readVibration() {
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);

  VibrationData data;
  data.accelX = a.acceleration.x;
  data.accelY = a.acceleration.y;
  data.accelZ = a.acceleration.z;
  data.gyroX  = g.gyro.x;
  data.gyroY  = g.gyro.y;
  data.gyroZ  = g.gyro.z;
  return data;
}
