//Transmitter program

#include "Mirf.h"

Nrf24l Mirf = Nrf24l(10, 9);
byte value1[2] = {0};
byte value2[2] = {0};

void setup()
{
    Serial.begin(115200);
    Mirf.spi = &MirfHardwareSpi;
    Mirf.init();
    //Set your own address (sender address) using 5 characters
    Mirf.setRADDR((byte *)"ABCDE"); 
}

void loop()
{
  Mirf.payload = sizeof(value1);
  Mirf.channel = 10;                 //Set the channel used
  Mirf.config();
  Mirf.setTADDR((byte *)"FGHIJ");    //Set the receiver address
  value1[0] = 100;
  value1[1]++;
  Mirf.send(value1);                 //Send instructions, send random number value
  Serial.print("Wait for sending.....");
  //Test you send successfully
  if (Mirf.isSend()) {
    Serial.print("Send success:");
    Serial.print(value1[0]);
    Serial.print("-");
    Serial.println(value1[1]);
  } else {
    Serial.println("Send fail:");
  }
  delay(500);

  
  Mirf.payload = sizeof(value2);
  Mirf.channel = 20;                 //Set the channel used
  Mirf.config();
  Mirf.setTADDR((byte *)"KLMNO");    //Set the receiver address
  value2[0] = 200;
  value2[1]++;
  Mirf.send(value2);                 //Send instructions, send random number value
  Serial.print("Wait for sending.....");
  //Test you send successfully
  if (Mirf.isSend()) {
    Serial.print("Send success:");
    Serial.print(value2[0]);
    Serial.print("-");
    Serial.println(value2[1]);
  } else {
    Serial.println("Send fail:");
  }
  delay(500);
}
