//Transmitter program

#include "Mirf.h"

// for ATMega328
Nrf24l Mirf = Nrf24l(10, 9); // CE,CSN

// for RF-Nano
//Nrf24l Mirf = Nrf24l(9, 10); // CE,CSN

// for STM32
//Nrf24l Mirf = Nrf24l(PB0, PB1); // CE,CSN
 
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
  Mirf.channel = 90;                   // Set the channel used
  Mirf.config();

  // Set destination address to TX_ADDR
  // Set ACK waiting address to RX_ADDR_P0
  Mirf.setTADDR((byte *)"FGHIJ");
}

void loop()
{
  sprintf(mydata.now_time,"now is %lu",micros());
  Mirf.send(mydata.value);
  Serial.print("Wait for sending.....");
  // Verify send was successfuly
  if (Mirf.isSend()) {
    Serial.print("Send success:");
    Serial.println(mydata.now_time);
  } else {
    Serial.println("Send fail:");
  }
  delay(1000);
}
