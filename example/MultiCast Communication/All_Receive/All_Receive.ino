//Receiver program

#include "Mirf.h"
#include "printf.h"

Nrf24l Mirf = Nrf24l(10, 9); // CE,CSN

int value;

void setup()
{
  Serial.begin(115200);
  Mirf.spi = &MirfHardwareSpi;
  Mirf.init();
  Mirf.payload = sizeof(value);
  Mirf.channel = 90; //Set the default channel
  Mirf.config();

  //Set your own address using 5 characters
  Mirf.setRADDR((byte *)"1RECV");

  //Add your own address using 1 characters
  Mirf.addRADDR(2, '2'); // 2RECV
  Mirf.addRADDR(3, '3'); // 3RECV
  Mirf.addRADDR(4, '4'); // 4RECV
  Mirf.addRADDR(5, '5'); // 5RECV

  // Print current settings
  printf_begin();
  Mirf.printDetails();
  Serial.println("Listening...");
}

void loop()
{
  //When the program is received, the received data is output from the serial port
  if (Mirf.dataReady()) {
    uint8_t pipe = Mirf.getDataPipe();
    Mirf.getData((byte *) &value);
    Serial.print("Got data pipe(");
    Serial.print(pipe);
    Serial.print(") is: ");
    Serial.println(value);
  }
  delay(1);
}
