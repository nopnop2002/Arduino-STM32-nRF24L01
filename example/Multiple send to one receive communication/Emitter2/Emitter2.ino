//Transmitter program

#include "Mirf.h"

Nrf24l Mirf = Nrf24l(10, 9);
int value;

void setup()
{
  Serial.begin(115200);
  Mirf.spi = &MirfHardwareSpi;
  Mirf.init();
  //Set your own address (sender address) using 5 characters
  Mirf.setRADDR((byte *)"ABCDE");
  Mirf.payload = sizeof(value);
  Mirf.channel = 20;              //Set the channel used
  Mirf.config();
}

void loop()
{
  Mirf.setTADDR((byte *)"FGHIJ");           //Set the receiver address
  value = 200;                      //0-255 random number
  Mirf.send((byte *)&value);                //Send instructions, send random number value
  Serial.print("Wait for sending.....");
  //Test you send successfully
  if (Mirf.isSend()) {
    Serial.print("Send success:");
    Serial.println(value);
  } else {
    Serial.println("Send fail:");
  }
  delay(1000);
}
