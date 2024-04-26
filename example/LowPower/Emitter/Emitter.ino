//Transmitter program
//Supports only STM32
//Don't work with PlatformIO

#include "Mirf.h"
#include "STM32LowPower.h" // https://github.com/stm32duino/STM32LowPower

Nrf24l Mirf = Nrf24l(PB0, PB1); // CE,CSN

/*
 * nRF24L01 STM32   UART
 * VCC      3.3V
 * CE       PB0
 * CSN      PB1
 * SCK      PA5
 * MOSI     PA7
 * MISO     PA6
 *          PA9     TX
 */
 
union MYDATA_t {
  byte value[32];
  char now_time[32];
};

MYDATA_t mydata;

volatile int wakeup = 1;

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
  sprintf(mydata.now_time,"wakeup is %d",wakeup);
  Mirf.send(mydata.value);
  Serial.print("Wait for sending.....");
  // Verify send was successfuly
  if (Mirf.isSend()) {
    Serial.print("Send success:");
    Serial.println(mydata.now_time);
    Serial.flush();
  } else {
    Serial.println("Send fail:");
    Serial.flush();
  }

  uint32_t sleepMS = 1000 * 10;  // DeepSleep 10 Seconds
  LowPower.deepSleep(sleepMS);
  wakeup++;
}
