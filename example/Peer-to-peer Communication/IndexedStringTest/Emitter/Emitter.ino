//Transmitter program

#include "Mirf.h"

Nrf24l Mirf = Nrf24l(10, 9); // CE,CSN

struct Pack {
  byte index;
  char payload[31];
};

#define PackSize sizeof(Pack)

union MYDATA_t {
  byte value[PackSize];
  struct Pack pack;
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
  Serial.print("PackSize=");
  Serial.println(PackSize);
  
  //Set the receiver address using 5 characters
  Mirf.setTADDR((byte *)"FGHIJ");

}

void loop()
{
  static int index = 0x41; // 'A'
  mydata.pack.index = index;
  for (int i=0;i<30;i++) {
    mydata.pack.payload[i] = index;
  }
  mydata.pack.payload[30] = 0;
  index++;
  if(index == 0x7e) {
    index = 0x41;
  }
  Mirf.send(mydata.value);
  Serial.print("Wait for sending.....");
  //Test you send successfully
  if (Mirf.isSend()) {
    Serial.println("Send success:");
  } else {
    Serial.println("Send fail:");
  }
  delay(1000);
}
