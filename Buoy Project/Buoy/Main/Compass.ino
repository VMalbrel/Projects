#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_HMC5883_U.h>

// Assign a unique ID to this sensor at the same time
Adafruit_HMC5883_Unified mag = Adafruit_HMC5883_Unified(12345);

void setup_Compass() {
  Serial.begin(9600);
}

void data_Compass() {
  // Start Compass 
  sensors_event_t event; 
  mag.getEvent(&event);
  float heading = atan2(event.magnetic.y, event.magnetic.x);
  float declinationAngle = -0.02618;
  heading += declinationAngle;
  
  // Correct for when signs are reversed
  if(heading < 0)
    heading += 2*PI;
    
  // Check for wrap due to addition of declination
  if(heading > 2*PI)
    heading -= 2*PI;

  // Convert radians to degrees
  Data.Compass_Heading = heading * 180/M_PI; 
}
