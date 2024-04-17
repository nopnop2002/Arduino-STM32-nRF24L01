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

  // Set destination address to TX_ADDR
  // Set ACK waiting address to RX_ADDR_P0
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
  // Verify send was successfuly
  if (Mirf.isSend()) {
    Serial.print("Send success: b=");
    Serial.print(mydata.pack.b);
    Serial.print(" i=");
    Serial.print(mydata.pack.i);
    Serial.print(" l=");
    Serial.print(mydata.pack.l);
    Serial.print(" f=");
    Serial.print(mydata.pack.f);
    Serial.print(" d=");
    Serial.println(mydata.pack.d);
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
