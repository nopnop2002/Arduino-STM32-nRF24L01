//Transmitter program

#include "Mirf.h"

Nrf24l Mirf = Nrf24l(10, 9); // CE,CSN
byte value;

void setup()
{
  Serial.begin(115200);
  Mirf.spi = &MirfHardwareSpi;
  Mirf.init();
  Mirf.payload = sizeof(value); // Set the payload size
  Mirf.channel = 90;            // Set the channel used
  Mirf.config();

  // Set destination address to TX_ADDR
  // Set ACK waiting address to RX_ADDR_P0
  Mirf.setTADDR((byte *)"FGHIJ");

  value = 0;
}

void loop()
{
  Mirf.send(&value);
  Serial.print("Wait for sending.....");
  // Verify send was successful
  if (Mirf.isSend()) {
    Serial.print("Send success:");
    Serial.println(value);
    value++;
  } else {
    Serial.println("Send fail:");
  }
  delay(1000);
}
