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
  //Set your own address (sender address) using 5 characters
  Mirf.payload = sizeof(mydata.value);
  Mirf.channel = 90;              //Set the channel used
  Mirf.config();

  //Set your own address using 5 characters
  Mirf.setRADDR((byte *)"ABCDE");

  //Set the receiver address using 5 characters
  Mirf.setTADDR((byte *)"FGHIJ");

  // Set RF output power in TX mode
  Mirf.setOutputRF_PWR(2);

  // Set RF Data Ratio
  // It must be the same value as the other party's value.
  Mirf.setSpeedDataRates(0);

  // Set Auto Retransmit Delay
  Mirf.setRetransmitDelay(0x1);

  // Print current settings
  printf_begin();
  Mirf.printDetails();
}

void loop()
{
  sprintf(mydata.now_time,"now is %lu",micros());                      //0-255 random number
  Mirf.send(mydata.value);                //Send instructions, send random number value
  Serial.print("Wait for sending.....");
  //Test you send successfully
  if (Mirf.isSend()) {
    Serial.print("Send success:");
    Serial.println(mydata.now_time);
  } else {
    Serial.println("Send fail:");
  }
  delay(1000);
}
