//Transmitter program

#include "Mirf.h"

Nrf24l Mirf = Nrf24l(10, 9);

union MYDATA_t {
  byte value[4];
  unsigned long now_time;
};


MYDATA_t mydata;

void setup()
{
  Serial.begin(115200);
  Mirf.spi = &MirfHardwareSpi;
  Mirf.init();
  //Set your own address (sender address) using 5 characters
  Mirf.setRADDR((byte *)"ABCDE");         //Set your own address (receiver address) using 5 characters
  Mirf.payload = sizeof(mydata.value);
  Mirf.channel = 90;                      //Set the channel used
  Mirf.config();
}

void loop()
{
  Mirf.setTADDR((byte *)"FGHIJ");         //Set Destination address
  mydata.now_time = micros();;            //0-255 random number
  Mirf.send(mydata.value);                //Send instructions, send random number value
  Serial.print("Wait for sending.....");
  //Test you send successfully
  if (Mirf.isSend()) {
    Serial.print("Send success:");
    Serial.println(mydata.now_time);
  } else {
    Serial.println("Send fail:");
  }
  delay(1000);
}
