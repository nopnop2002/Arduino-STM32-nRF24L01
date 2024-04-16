//Transmitter program

#include "Mirf.h"

Nrf24l Mirf = Nrf24l(10, 9); // CE,CSN

struct Pack {
  byte b;   /* 1 */
  int i;    /* 2 */
  long l;   /* 4 */
  float f;  /* 4 */
  double d; /* 4 */
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

  //Set the receiver address using 5 characters
  Mirf.setTADDR((byte *)"FGHIJ");

  mydata.pack.b = 0;
  mydata.pack.i = 0;
  mydata.pack.l = 0;
  mydata.pack.f = 0.0;
  mydata.pack.d = 0.0;
}

void loop()
{
  Mirf.send(mydata.value);
  Serial.print("Wait for sending.....");
  //Test you send successfully
  if (Mirf.isSend()) {
    Serial.print("Send success:");
    Serial.println(mydata.pack.b);
    mydata.pack.b++;
    mydata.pack.i--;
    mydata.pack.l++;
    mydata.pack.f+=1.0;
    mydata.pack.d-=1.0;
  } else {
    Serial.println("Send fail:");
  }
  delay(1000);
}
