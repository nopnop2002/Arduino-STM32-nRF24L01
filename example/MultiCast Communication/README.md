# MultiCast communication
Multiple send to one receive communication.   
The nRF24L01 has 6 receive data pipes.   
In this library, the first datapipe is used for automatic ACK reception on transmission.   
The second to sixth data pipes are used for data reception.   
Therefore, it is possible to receive from a maximum of five transmitting sides.   
This example receive from 1RECV/2RECV/3RECV/4RECV/5RECV.   

![Slide0001](https://user-images.githubusercontent.com/6020549/132265362-1048a86a-f100-4e89-9fae-d0cc6766a8d8.jpg)

![MultiCast](https://user-images.githubusercontent.com/6020549/149721203-af8e69e3-dd5f-47bf-80e1-7fdcb72ed5dd.jpg)


