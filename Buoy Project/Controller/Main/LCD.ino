#include <Arduino.h>
#include <U8g2lib.h>
#ifdef U8X8_HAVE_HW_SPI
#include <SPI.h>
#endif
#ifdef U8X8_HAVE_HW_I2C
#include <Wire.h>
#endif

#define DEG_TO_RAD 0.017453292519943295769236907684886

U8G2_SSD1306_128X64_NONAME_2_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);

float angle(float angle_deg) {
  float value = DEG_TO_RAD * (90 + angle_deg);
  return value;
}

void u8g2_prepare(void) {
  u8g2.setFontRefHeightExtendedText();
  u8g2.setDrawColor(1);
  u8g2.setFontPosTop();
  u8g2.setFontDirection(0);
}

void u8g2_compass() {
  u8g2.setFont(u8g2_font_6x10_tf);
  float bearing_deg = Message_Receive.Compass_Heading; // Angle of Buoy in degrees Compass System
  float course_deg = Message_Receive.CourseToDestination; // Angle of Waypoint in degrees Compass System
  float distance = Message_Receive.DistanceToDestination;
  int radius_Compass = 30;
  int radius_Pointer = 2;
  int center_compass_x = 128 - radius_Compass - 3;
  int center_compass_y = 32;
  String bearing_txt = String(bearing_deg,3) + "\xB0";
  String course_txt = String(course_deg,3) + "\xB0";
  String distance_txt = String(distance,3) + " m";
  u8g2.drawStr(0, 0, "Bearing");
  u8g2.drawStr(0, 10, bearing_txt.c_str());
  u8g2.drawStr(0, 22, "Course");
  u8g2.drawStr(0, 32, course_txt.c_str());
  u8g2.drawStr(0, 44, "Distance");
  u8g2.drawStr(0, 54, distance_txt.c_str());
  u8g2.drawCircle(center_compass_x, center_compass_y, radius_Compass);
  u8g2.drawLine(center_compass_x, center_compass_y, center_compass_x - (radius_Compass - 4)*cos(angle(bearing_deg)), center_compass_y - (radius_Compass - 4)*sin(angle(bearing_deg)));
  u8g2.drawDisc(center_compass_x - (radius_Compass)*cos(angle(course_deg)), center_compass_y - (radius_Compass)*sin(angle(course_deg)), radius_Pointer);
  u8g2.drawStr(-3 + center_compass_x - (radius_Compass - 6)*cos(angle(0)), -5 + center_compass_y - (radius_Compass - 6)*sin(angle(0)), "N");
  u8g2.drawStr(-3 + center_compass_x - (radius_Compass - 6)*cos(angle(90)), -5 + center_compass_y - (radius_Compass - 6)*sin(angle(90)), "E");
  u8g2.drawStr(-3 + center_compass_x - (radius_Compass - 6)*cos(angle(180)), -5 + center_compass_y - (radius_Compass - 6)*sin(angle(180)), "S");
  u8g2.drawStr(-3 + center_compass_x - (radius_Compass - 6)*cos(angle(270)), -5 + center_compass_y - (radius_Compass - 6)*sin(angle(270)), "W");
}

void u8g2_gps() {
  u8g2.setFont(u8g2_font_9x15_tf);
  float Destination_Latitude = Message_Transmit.Destination_Latitude/1e7; // Angle of Buoy in degrees Compass System
  float  Destination_Longitude = Message_Transmit.Destination_Longitude/1e7; // Angle of Waypoint in degrees Compass System
  String Latitude_txt = String(Destination_Latitude,3) + "\xB0";
  String Longitude_txt = String(Destination_Longitude,3) + "\xB0";
  u8g2.drawStr(0, 0, "Latitude");
  u8g2.drawStr(0, 10, Latitude_txt.c_str());
  u8g2.drawStr(0, 22, "Longitude");
  u8g2.drawStr(0, 32, Longitude_txt.c_str());
}

void setup_Display() {
  u8g2.begin();
}

void Display() { 
  u8g2.firstPage();
  do {
    u8g2_prepare();
    u8g2_compass();
  } while ( u8g2.nextPage() );
}

void Display_GPS() { 
  u8g2.firstPage();
  do {
    u8g2_prepare();
    u8g2_gps();
  } while ( u8g2.nextPage() );
}