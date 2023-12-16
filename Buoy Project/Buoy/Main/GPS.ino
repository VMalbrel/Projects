#include <TinyGPSPlus.h>
#include <SoftwareSerial.h>
#define DEG_TO_RAD 0.017453292519943295769236907684886
#define RAD_TO_DEG 57.295779513082320876798154814105

// The TinyGPSPlus object
TinyGPSPlus gps;

// The serial connection to the GPS device
SoftwareSerial ss(Pins.GPS_RX, Pins.GPS_TX);

void setup_GPS() {
  Serial.begin(9600);
  ss.begin(9600);
}

void data_GPS() {
  // Read data from GPS
  while (ss.available() > 0) {
    if (gps.encode(ss.read())) {
      if (gps.location.isValid()) {
        //Location
        Data.GPS_Latitude = gps.location.lat()*1e7;
        Data.GPS_Longitude = gps.location.lng()*1e7;

        // Time
        String Time = "";
        // Hours
        if (int(gps.time.hour())+18 < 10) Time+="0";
        Time+=(int(gps.time.hour())+18)%24;
        // Minutes
        if (gps.time.minute() < 10) Time+="0";
        Time+=gps.time.minute();
        // Seconds
        if (gps.time.second() < 10) Time+="0";
        Time+=gps.time.second();
        Data.GPS_Time = Time;
        
        // Distance and bearing
        float dlam,dphi,radius = 6371000.0;
        dphi = DEG_TO_RAD *(gps.location.lat() + Data.Destination_Latitude)*0.5e-6; //average latitude in radians
        float cphi = cos(dphi);
        dphi = DEG_TO_RAD*(Data.Destination_Latitude - gps.location.lat())*1.0e-6; //differences in degrees (to radians)
        dlam = DEG_TO_RAD*(Data.Destination_Longitude - gps.location.lng())*1.0e-6;
        dlam *= cphi;  //correct for latitude
        Data.CourseToDestination = RAD_TO_DEG * atan2(dlam,dphi);
        if(Data.CourseToDestination<0) Data.CourseToDestination+=360.0;
        Data.DistanceToDestination = float(radius * sqrt(dphi*dphi + dlam*dlam));
      }
    }
  }
}
