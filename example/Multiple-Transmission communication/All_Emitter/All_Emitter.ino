//Transmitter program

#include "Mirf.h"

Nrf24l Mirf = Nrf24l(10, 9);
int16_t value;

void setup()
{
  Serial.begin(115200);
  Mirf.spi = &MirfHardwareSpi;
  Mirf.init();
  Mirf.payload = sizeof(value); // Set the payload size
  Mirf.channel = 90;            // Set the channel used
  Mirf.config();
  value = 100;
}

void loop()
{
  static int sequence = 0;
  byte address[5];
  strcpy((char*)address, "RECV0");
  address[4] = address[4] + sequence;
  Serial.print("RECV");
  Serial.print(address[4]-'0');

  // Set destination address to TX_ADDR
  // Set ACK waiting address to RX_ADDR_P0  
  Mirf.setTADDR(address);
  Mirf.send((byte *)&value);
  // Verify send was successfuly
  if (Mirf.isSend()) {
    //Serial.print("address:");
    //Serial.print(address[4]-'0');
    Serial.print(" Send success:");
    Serial.println(value);
  } else {
    Serial.println();
  }

  sequence++;
  if (sequence == 10) {
    value++;
    sequence=0;
  }
  delay(100);
}
