//Include Libraries
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

// Create an RF24 object
RF24 radio(Pins.Radio_CE, Pins.Radio_CSN);  // CE, CSN

// Address through which two modules communicate.
const byte address[6] = "00001";

void setup_Radio() {
  radio.begin();
  radio.setPALevel(RF24_PA_MAX); 
  radio.setDataRate(RF24_250KBPS);
}

void transmit_Radio() {
  // Set the address
  radio.openWritingPipe(address);
  // Set module as transmitter
  radio.stopListening();
  // Send message to receiver
  long time = millis();
  while ((time+500)<500) {
    radio.write(&Message_Transmit, sizeof(Message_Transmit));
  }
}

void receive_Radio() {
  // Set the address
  radio.openReadingPipe(0, address);
  // Set module as receiver
  radio.startListening();
  // Check if data is available
  if (radio.available()) {
    // Collect message from transmitter
    long time = millis();
    while ((time+500)<500) {
      radio.read(&Message_Receive, sizeof(Message_Receive));
    }
  }
}
