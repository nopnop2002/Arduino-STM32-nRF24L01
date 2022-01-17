//Receiver program

#include "Mirf.h"

Nrf24l Mirf = Nrf24l(10, 9); // CE,CSN
int16_t value;

void setup()
{
  Serial.begin(115200);
  Mirf.spi = &MirfHardwareSpi;
  Mirf.init();
  Mirf.payload = sizeof(value);
  Mirf.channel = 90; //Set the used channel
  Mirf.config();

  //Set your own address (receiver address) using 5 characters
  Mirf.setRADDR((byte *)"RECV1");  
  Serial.println("Listening...");
}

void loop()
{
  //When the program is received, the received data is output from the serial port
  if (Mirf.dataReady()) {
    Mirf.getData((byte *) &value);
    Serial.print("Receive1 got data is: ");
    Serial.println(value);
  }
}
