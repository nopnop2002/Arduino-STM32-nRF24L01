//Receiver program

#include "Mirf.h"

Nrf24l Mirf = Nrf24l(10, 9); // CE,CSN

byte value[4];

void setup()
{
  Serial.begin(115200);
  Mirf.spi = &MirfHardwareSpi;
  Mirf.init();
  Mirf.payload = sizeof(value);
  Mirf.channel = 90;             //Set the used channel
  Mirf.config();

  //Set your own address using 5 characters
  Mirf.setRADDR((byte *)"FGHIJ");

  Serial.println("Listening...");
}

void loop()
{
  while (Mirf.dataReady()) { //When the program is received, the received data is output from the serial port
    Mirf.getData(value);
    Serial.print("Got 4 byte data: ");
    Serial.print(value[0]);
    Serial.print("-");
    Serial.print(value[1]);
    Serial.print("-");
    Serial.print(value[2]);
    Serial.print("-");
    Serial.println(value[3]);
  }
}
