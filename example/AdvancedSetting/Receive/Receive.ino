//Receiver program

#include "Mirf.h"
#include "printf.h"

Nrf24l Mirf = Nrf24l(10, 9); // CE,CSN

union MYDATA_t {
  byte value[4];
  unsigned long now_time;
};


MYDATA_t mydata;
//uint8_t dataRate = 0; // 1MBps
uint8_t dataRate = 1; // 2MBps
//uint8_t dataRate = 2; // 250KBps

void setup()
{
  Serial.begin(115200);
  Mirf.spi = &MirfHardwareSpi;
  Mirf.init();
  Mirf.payload = sizeof(mydata.value); // Set the payload size
  Mirf.channel = 90;                   // Set the used channel
  Mirf.config();

  // Set my own address to RX_ADDR_P1
  Mirf.setRADDR((byte *)"FGHIJ"); 

  // Set RF Data Ratio
  // It must be the same value as the other party's value.
  Mirf.setSpeedDataRates(dataRate);

  // Print current settings
  printf_begin();
  Mirf.printDetails();

  // Clear RX FiFo
  while(1) {
    if (Mirf.dataReady() == false) break;
    Mirf.getData(mydata.value);
  }
  Serial.println("Listening...");
}

void loop()
{
  // Wait for received data
  if (Mirf.dataReady()) {
    Mirf.getData(mydata.value);
    Serial.print("Got string: ");
    Serial.println(mydata.now_time);
  }
}
