//Transmitter program
//Supports only STM32
//Don't work with PlatformIO

#include "Mirf.h"
#include "STM32LowPower.h" // https://github.com/stm32duino/STM32LowPower

Nrf24l Mirf = Nrf24l(PB0, PB1); // CE,CSN

/*
 * Generic STM32F103(BluePill/BlackPill/etc)
 * VCC  3.3V
 * MISO PA6
 * MOSI PA7
 * SCK  PA5
 * CE   PB0
 * CSN  PB1
 */
 
union MYDATA_t {
  byte value[4];
  unsigned long counter;
};


MYDATA_t mydata;

void setup()
{
  Serial.begin(115200);
  Mirf.spi = &MirfHardwareSpi;
  Mirf.init();
  Mirf.payload = sizeof(mydata.value);
  Mirf.channel = 90; //Set the channel used
  Mirf.config();

  //Set the receiver address using 5 characters
  Mirf.setTADDR((byte *)"FGHIJ");
  mydata.counter = 0;
}

void loop()
{
  mydata.counter++;
  Mirf.send(mydata.value);
  Serial.print("Wait for sending.....");
  //Test you send successfully
  if (Mirf.isSend()) {
    Serial.print("Send success:");
    Serial.println(mydata.counter);
    Serial.flush();
  } else {
    Serial.println("Send fail:");
    Serial.flush();
  }
  //delay(10000);
  for(int i=0;i<10;i++) {
    LowPower.deepSleep(1000); // DeepSleep 1000 MilllSec
  }
}
