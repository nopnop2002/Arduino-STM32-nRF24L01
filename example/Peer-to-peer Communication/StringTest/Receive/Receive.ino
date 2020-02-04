//Receiver program

#include "Mirf.h"

Nrf24l Mirf = Nrf24l(10, 9);

union MYDATA_t {
  byte value[32];
  char now_time[32];
};

MYDATA_t mydata;

void setup()
{
  Serial.begin(115200);
  Mirf.spi = &MirfHardwareSpi;
  Mirf.init();
  Mirf.setRADDR((byte *)"FGHIJ"); //Set your own address (receiver address) using 5 characters
  Mirf.payload = sizeof(mydata.value);
  Mirf.channel = 90;             //Set the used channel
  Mirf.config();
  Serial.println("Listening...");  //Start listening to received data
}

void loop()
{
  if (Mirf.dataReady()) { //When the program is received, the received data is output from the serial port
    Mirf.getData(mydata.value);
    Serial.print("Got string: ");
    Serial.println(mydata.now_time);
  }
}
