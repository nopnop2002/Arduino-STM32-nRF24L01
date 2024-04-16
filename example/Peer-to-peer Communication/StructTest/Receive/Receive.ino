//Receiver program

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
  Mirf.channel = 90;                   // Set the used channel
  Mirf.config();

  //Set your own address using 5 characters
  Mirf.setRADDR((byte *)"FGHIJ");

  Serial.println("Listening...");
}

void loop()
{
  if (Mirf.dataReady()) { //When the program is received, the received data is output from the serial port
    Mirf.getData(mydata.value);
    Serial.print("Got pack: b=");
    Serial.print(mydata.pack.b);
    Serial.print(" i=");
    Serial.print(mydata.pack.i);
    Serial.print(" l=");
    Serial.print(mydata.pack.l);
    Serial.print(" f=");
    Serial.print(mydata.pack.f);
    Serial.print(" d=");
    Serial.println(mydata.pack.d);
  }
}
