#include "gps_module.h"
#include <TinyGPSPlus.h>
#include <HardwareSerial.h>

#define GPS_RX_PIN 16
#define GPS_TX_PIN 17

TinyGPSPlus gps;
HardwareSerial gpsSerial(2);  // UART2

void initGPS() {
  gpsSerial.begin(9600, SERIAL_8N1, GPS_RX_PIN, GPS_TX_PIN);
  Serial.println("NEO-6M GPS initialized.");
}

GPSData getLocation() {
  GPSData loc = {0.0, 0.0, false};

  while (gpsSerial.available() > 0) {
    gps.encode(gpsSerial.read());
  }

  if (gps.location.isValid()) {
    loc.latitude  = gps.location.lat();
    loc.longitude = gps.location.lng();
    loc.fixValid  = true;
  }
  return loc;
}
