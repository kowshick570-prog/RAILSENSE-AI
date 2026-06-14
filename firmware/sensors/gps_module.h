#ifndef GPS_MODULE_H
#define GPS_MODULE_H

struct GPSData {
  double latitude;
  double longitude;
  bool fixValid;
};

void initGPS();
GPSData getLocation();

#endif
