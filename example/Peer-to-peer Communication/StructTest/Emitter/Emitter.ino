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
  } else {
    Serial.println("Send fail:");
  }
  delay(1000);
}
