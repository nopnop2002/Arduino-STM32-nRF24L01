# Multiple received communication   
The nRF24L01 has 6 receive data pipes.   
In this library, the first datapipe is used for automatic ACK reception on transmission.   
The second to sixth data pipes are used for data reception.   
Therefore, it is possible to receive from a maximum of five transmitting sides.   
This example receive from 1RECV/2RECV/3RECV/4RECV/5RECV.   

![MultiCast](https://github.com/nopnop2002/Arduino-STM32-nRF24L01/assets/6020549/8cdb34a7-8508-4b67-b4da-16eb52cd8e71)

![MultiReceiver](https://github.com/nopnop2002/Arduino-STM32-nRF24L01/assets/6020549/bc2534f3-3951-4846-bdf6-10164017e081)
