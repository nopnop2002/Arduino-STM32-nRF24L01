//Receiver program

#include "Mirf.h"

Nrf24l Mirf = Nrf24l(10, 9); // CE,CSN

byte value[4];

void setup()
{
  Serial.begin(115200);
  Mirf.spi = &MirfHardwareSpi;
  Mirf.init();
  Mirf.payload = sizeof(value); // Set the payload size
  Mirf.channel = 90;            // Set the used channel
  Mirf.config();

  // Set my own address to RX_ADDR_P1
  Mirf.setRADDR((byte *)"FGHIJ");

  // Clear RX FiFo
  while(1) {
    if (Mirf.dataReady() == false) break;
    Mirf.getData(value);
  }
  Serial.println("Listening...");
}

void loop()
{
  // Wait for received data
  while (Mirf.dataReady()) {
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
