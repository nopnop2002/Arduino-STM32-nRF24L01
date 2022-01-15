//Transmitter program

#include "Mirf.h"

Nrf24l Mirf = Nrf24l(10, 9); // CE,CSN

byte value[4];

void setup()
{
  Serial.begin(115200);
  Mirf.spi = &MirfHardwareSpi;
  Mirf.init();
  Mirf.payload = sizeof(value);
  Mirf.channel = 90;              //Set the channel used
  Mirf.config();
  
  //Set the receiver address using 5 characters
  Mirf.setTADDR((byte *)"FGHIJ");
}

void loop()
{
  value[0] = 0;
  value[1] = 1;
  value[2] = 2;
  value[3] = random(255); //0-255 random number
  Mirf.send(value);
  Serial.print("Wait for sending.....");
  //Test you send successfully
  if (Mirf.isSend()) {
    Serial.print("Send success:");
    Serial.println(value[3]);
  } else {
    Serial.println("Send fail:");
  }
  delay(1000);
}
