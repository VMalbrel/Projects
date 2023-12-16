#include <TinyGPSPlus.h>
#include <SoftwareSerial.h>

static const int RXPin = 3, TXPin = 2;
static const uint32_t GPSBaud = 9600;

// The TinyGPSPlus object
TinyGPSPlus gps;

// The serial connection to the GPS device
SoftwareSerial ss(RXPin, TXPin);

void setup_GPS()
{
  Serial.begin(9600);
  ss.begin(GPSBaud);
}

void get_GPS_data()
{
  // Read data from GPS
  while (ss.available() > 0)
    if (gps.encode(ss.read()))
      if (gps.location.isValid())
        {
        //Location
        Data.GPS_Latitude = gps.location.lat();
        Data.GPS_Longitude = gps.location.lng();
      
        //Time
        String Time = "";
        if (int(gps.time.hour())+18 < 10) Time+="0";
        Time+=int(gps.time.hour())+18;
        Time+=F(":");
        if (gps.time.minute() < 10) Time+="0";
        Time+=gps.time.minute();
        Time+=F(":");
        if (gps.time.second() < 10) Time+="0";
        Time+=gps.time.second();
        Data.GPS_Time = Time;
        }
}
