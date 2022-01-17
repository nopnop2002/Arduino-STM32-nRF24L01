//Transmitter program

#include "Mirf.h"

Nrf24l Mirf = Nrf24l(10, 9); // CE,CSN
int16_t value = 200;

void setup()
{
  Serial.begin(115200);
  Mirf.spi = &MirfHardwareSpi;
  Mirf.init();
  Mirf.payload = sizeof(value);
  Mirf.channel = 90; //Set the channel used
  Mirf.config();

  //Set the receiver address using 5 characters
  Mirf.setTADDR((byte *)"2RECV");
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
    if (value == 300) value=200;
  } else {
    Serial.println("Send fail:");
  }
  delay(1000);
}
