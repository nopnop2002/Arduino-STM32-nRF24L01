//Transmitter program

#include "Mirf.h"

Nrf24l Mirf = Nrf24l(10, 9); // CE,CSN
int value = 100;

void setup()
{
  Serial.begin(115200);
  Mirf.spi = &MirfHardwareSpi;
  Mirf.init();
  Mirf.payload = sizeof(value);
  Mirf.channel = 90; //Set the channel used
  Mirf.config();

  //Set the receiver address using 5 characters
  Mirf.setTADDR((byte *)"1RECV");
}

void loop()
{
  Mirf.send((byte *)&value);
  Serial.print("Wait for sending.....");
  //Test you send successfully
  if (Mirf.isSend()) {
    Serial.print("Send success:");
    Serial.println(value);
    value++;
    if (value == 200) value=100;
  } else {
    Serial.println("Send fail:");
  }
  delay(1000);
}
