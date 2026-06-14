#ifndef MPU6050_SENSOR_H
#define MPU6050_SENSOR_H

struct VibrationData {
  float accelX, accelY, accelZ;
  float gyroX, gyroY, gyroZ;
};

void initMPU6050();
VibrationData readVibration();

#endif
