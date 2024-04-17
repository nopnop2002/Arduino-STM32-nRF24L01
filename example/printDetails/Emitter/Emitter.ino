//Transmitter program

#include "Mirf.h"
#include "printf.h"

Nrf24l Mirf = Nrf24l(10, 9); // CE,CSN

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

  // Set RF output power in TX mode
  Mirf.setOutputRF_PWR(2);

  // Set RF Data Ratio
  // It must be the same value as the other party's value.
  Mirf.setSpeedDataRates(1); // 2MBps

  // Set Auto Retransmit Delay
  // 2 or more at 250KBps
  Mirf.setRetransmitDelay(2);

  // Print current settings
  printf_begin();
  Mirf.printDetails();
}

void loop()
{
  sprintf(mydata.now_time,"now is %lu",micros());
  Mirf.send(mydata.value);
  Serial.print("Wait for sending.....");
  // Verify send was successful
  if (Mirf.isSend()) {
    Serial.print("Send success:");
    Serial.println(mydata.now_time);
  } else {
    Serial.println("Send fail:");
  }
  delay(1000);
}
