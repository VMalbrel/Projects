#include <TinyGPSPlus.h>
#include <SoftwareSerial.h>

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
        Message_Transmit.Destination_Latitude = gps.location.lat()*1e7;
        Message_Transmit.Destination_Longitude = gps.location.lng()*1e7;
      }
    }
  }
}
