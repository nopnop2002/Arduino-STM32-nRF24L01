//Receiver program

#include "Mirf.h"

Nrf24l Mirf = Nrf24l(10, 9); // CE,CSN
int16_t value;

void setup()
{
  Serial.begin(115200);
  Mirf.spi = &MirfHardwareSpi;
  Mirf.init();
  Mirf.payload = sizeof(value); // Set the payload size
  Mirf.channel = 90;            // Set the used channel
  Mirf.config();

  // Set my own address to RX_ADDR_P1
  Mirf.setRADDR((byte *)"RECV0");  

  // Clear RX FiFo
  while(1) {
    if (Mirf.dataReady() == false) break;
    Mirf.getData((byte *) &value);
  }
  Serial.println("Listening...");  
}

void loop()
{
  // Wait for received data
  if (Mirf.dataReady()) {
    Mirf.getData((byte *) &value);
    Serial.print("Receive1 got int16 data: ");
    Serial.println(value);
  }
}
