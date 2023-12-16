#include <Arduino.h>
#include <U8g2lib.h>
#ifdef U8X8_HAVE_HW_SPI
#include <SPI.h>
#endif
#ifdef U8X8_HAVE_HW_I2C
#include <Wire.h>
#endif

#define DEG_TO_RAD 0.017453292519943295769236907684886

U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);

void u8g2_prepare(void) {
  u8g2.setFont(u8g2_font_6x10_tf);
  u8g2.setFontRefHeightExtendedText();
  u8g2.setDrawColor(1);
  u8g2.setFontPosTop();
  u8g2.setFontDirection(0);
}

float angle(float angle_deg) {
  float value = DEG_TO_RAD * (90 + angle_deg);
  return value;
}

void u8g2_compass(uint8_t a) {
  float bearing_deg = 45*a; // Angle of Buoy in degrees Compass System
  float course_deg = 45*a; // Angle of Waypoint in degrees Compass System
  float bearing = angle(bearing_deg); // Angle in radians Normal System
  float course = angle(course_deg); // Angle in radians Normal System
  float radius_Compass = 31;
  int radius_Pointer = 2;
  int center_compass_x = 128 - radius_Compass - 1;
  int center_compass_y = 32;
  String bearing_txt = String(bearing_deg,0) + "\xB0";
  String course_txt = String(course_deg,0) + "\xB0";
  u8g2.drawStr(0, 0, "Bearing:");
  u8g2.drawStr(0, 10, bearing_txt.c_str());
  u8g2.drawStr(0, 25, "Course");
  u8g2.drawStr(0, 35, course_txt.c_str());
  u8g2.drawCircle(center_compass_x, center_compass_y, radius_Compass);
  u8g2.drawLine(center_compass_x, center_compass_y, center_compass_x - (radius_Compass - 4)*cos(bearing), center_compass_y - (radius_Compass - 4)*sin(bearing));
  //u8g2.drawDisc(center_compass_x - (radius_Compass - 2)*cos(angle), center_compass_y - (radius_Compass - 2)*sin(angle), radius_Pointer);
}

uint8_t draw_state = 0;

void draw(void) {
  u8g2_prepare();
  switch(draw_state >> 3) {
    case 0: u8g2_compass(draw_state&7); break;
  }
}


void setup(void) {
  u8g2.begin();
}

void loop(void) {
  // picture loop  
  u8g2.clearBuffer();
  draw();
  u8g2.sendBuffer();
  
  // increase the state
  draw_state++;
  if ( draw_state >= 1*8 )
    draw_state = 0;

  // delay between each page
  delay(100);
}
