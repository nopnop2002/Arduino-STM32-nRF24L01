//Transmitter program

#include "Mirf.h"

Nrf24l Mirf = Nrf24l(PB0, PB1); // CE,CSN

/*
 * nRF24L01 STM   UART
 * VCC      3.3V
 * CE       PB0
 * CSN      PB1
 * SCK      PA5
 * MOSI     PA7
 * MISO     PA6
 *          PA9   TX
 */
 
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
  Mirf.payload = sizeof(mydata.value); // Set the payload size
  Mirf.channel = 90;                   // Set the used channel
  Mirf.config();

  // Set my own address to RX_ADDR_P1
  Mirf.setRADDR((byte *)"FGHIJ");

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
