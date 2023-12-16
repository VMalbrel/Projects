// Global Variables
struct Message_Transmit {
  long Destination_Latitude;
  long Destination_Longitude;
} Message_Transmit;

struct Message_Receive {
  float Compass_Heading;
  float CourseToDestination;
  float DistanceToDestination;
} Message_Receive;

struct Pins {
  const byte GPS_RX = 2;
  const byte GPS_TX = 3;
  const byte GPS_SDA = 4;
  const byte GPS_SCL = 5;
  const byte Radio_CE = 9;
  const byte Radio_CSN = 10;
  const byte Radio_MOSI = 11;
  const byte Radio_MISO = 12;
  const byte Radio_SCK = 13;
  const byte Switch = A0;
  const byte Display_SDA = A4;
  const byte Display_SCL = A5;
} Pins;
  
void setup() {
  setup_Display();
  setup_Radio();
  setup_GPS();
}
  
void loop() {
  // Data Transmission
  receive_Radio();
  // Send Location 
  if (digitalRead(Pins.Switch) == HIGH) {
    data_GPS();
    transmit_Radio();
    Display_GPS();
  }
  // Display data
  Display();
}
