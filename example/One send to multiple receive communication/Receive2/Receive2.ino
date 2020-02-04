//Receiver program

#include "Mirf.h"

Nrf24l Mirf = Nrf24l(10, 9);

byte value[2];

void setup()
{
  Serial.begin(115200);
  Mirf.spi = &MirfHardwareSpi;
  Mirf.init();
  Mirf.setRADDR((byte *)"KLMNO"); //Set your own address (receiver address) using 5 characters
  Mirf.payload = sizeof(value);
  Mirf.channel = 20;             //Set the used channel
  Mirf.config();
  Serial.println("Listening...");  //Start listening to received data
}

void loop()
{    
  //Mirf.ceLow();
  //Mirf.configRegister(RF_CH, 20);  //switch channel 20
  //Mirf.ceHi();
  if (Mirf.dataReady()) {
    //When the program is received, the received data is output from the serial port
    Mirf.getData(value);
    Serial.print("Receive2 got data is: ");
    Serial.print(value[0]);
    Serial.print("-");
    Serial.println(value[1]);
  }
  //delay(1000);
}
