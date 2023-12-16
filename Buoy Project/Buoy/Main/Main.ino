// Global Variables
struct Data {
  String GPS_Time;
  long GPS_Latitude;
  long GPS_Longitude;
  float Compass_Heading;
  long Destination_Latitude;
  long Destination_Longitude;
  float DistanceToDestination;
  float CourseToDestination;
  } Data;

struct Message_Receive {
  long Destination_Latitude;
  long Destination_Longitude;
} Message_Receive;

struct Message_Transmit {
  float Compass_Heading;
  float CourseToDestination;
  float DistanceToDestination;
} Message_Transmit;

struct Pins {
  const byte GPS_RX = 2;
  const byte GPS_TX = 3;
  const byte GPS_SDA = 4;
  const byte GPS_SCL = 5;
  const byte Relay_Lights = 8;
  const byte Radio_CE = 9;
  const byte Radio_CSN = 10;
  const byte Radio_MOSI = 11;
  const byte Radio_MISO = 12;
  const byte Radio_SCK = 13;
  const byte Relay_Motor_North = A0;
  const byte Relay_Motor_East = A1;
  const byte Relay_Motor_South = A2;
  const byte Relay_Motor_West = A3;
  } Pins;
  
void setup() {
  // Destination Variables for testing!!!!!!!!!
  Data.Destination_Latitude = 30.630197*1e7;
  Data.Destination_Longitude = -96.317825*1e7;
  
  //Set up other functions
  setup_GPS();
  setup_Compass();
  setup_Radio();
}
  
void loop() {
  //Lights
  ON_Lights();
  // Start Data Acquisition Loop
  data_GPS();
  data_Compass();
  // Update Variables
  Data.Destination_Latitude = Message_Receive.Destination_Latitude;
  Data.Destination_Longitude = Message_Receive.Destination_Longitude;
  Message_Transmit.Compass_Heading = Data.Compass_Heading;
  Message_Transmit.CourseToDestination = Data.CourseToDestination;
  Message_Transmit.DistanceToDestination = Data.DistanceToDestination;
  // Navigation
  Movement();
  // Radio receive
  receive_Radio();
  //Lights
  OFF_Lights();
  // Radio transmit
  transmit_Radio();
  // Turn off Motors
  Motor_Off();
}
