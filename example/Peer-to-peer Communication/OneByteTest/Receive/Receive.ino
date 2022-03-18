//Receiver program

#include "Mirf.h"

Nrf24l Mirf = Nrf24l(10, 9); // CE,CSN

byte value;

void setup()
{
  Serial.begin(115200);
  Mirf.spi = &MirfHardwareSpi;
  Mirf.init();
  Mirf.payload = sizeof(value); // Set the payload size
  Mirf.channel = 90;            // Set the used channel
  Mirf.config();

  //Set your own address using 5 characters
  Mirf.setRADDR((byte *)"FGHIJ");
  
  Serial.println("Listening...");
}

void loop()
{
  if (Mirf.dataReady()) { //When the program is received, the received data is output from the serial port
    Mirf.getData(&value);
    Serial.print("Got MotorDrive data: ");
    Serial.println(value);
  }
}
