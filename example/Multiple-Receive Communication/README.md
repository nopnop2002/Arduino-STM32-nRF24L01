# Multiple received communication   
The nRF24L01 has 6 receive data pipes (RX_ADDR_P0-P6).   
In this library, the first data pipe(RX_ADDR_P0) is used for automatic ACK reception on transmission.   
The second(RX_ADDR_P1) to sixth(RX_ADDR_P5) data pipes are used for data reception.   
Therefore, it is possible to receive from a maximum of five transmitting sides.   
This example receive from 1RECV/2RECV/3RECV/4RECV/5RECV.   

# nRF24L01 Adress Register Setting
|Emitter|||||Receiver||||||
|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|
|#1|TX_ADDR<br>"1RECV"|RX_ADDR_P0<br>"1RECV"|RX_ADDR_P1<br>NONE||TX_ADDR<br>NONE|RX_ADDR_P0<br>NONE|RX_ADDR_P1<br>"1RECV"|RX_ADDR_P2<br>"2RECV"|RX_ADDR_P5<br>"5RECV"||
||(Send Data)|->|->|->|->|->|(Get Data)|||Data to Receiver|
|||(Get Ack)|<-|<-|<-|<-|(Send Ack)|||Ack to Emitter|
|#2|TX_ADDR<br>"1RECV"|RX_ADDR_P0<br>"1RECV"|RX_ADDR_P1<br>NONE||TX_ADDR<br>NONE|RX_ADDR_P0<br>NONE|RX_ADDR_P1<br>"1RECV"|RX_ADDR_P2<br>"2RECV"|RX_ADDR_P5<br>"5RECV"||
||(Send Data)|->|->|->|->|->|->|(Get Data)||Data to Receiver|
|||(Get Ack)|<-|<-|<-|<-|<-|(Send Ack)||Ack to Emitter|
|#5|TX_ADDR<br>"1RECV"|RX_ADDR_P0<br>"1RECV"|RX_ADDR_P1<br>NONE||TX_ADDR<br>NONE|RX_ADDR_P0<br>NONE|RX_ADDR_P1<br>"1RECV"|RX_ADDR_P2<br>"2RECV"|RX_ADDR_P5<br>"5RECV"||
||(Send Data)|->|->|->|->|->|->|->|(Get Data)|Data to Receiver|
|||(Get Ack)|<-|<-|<-|<-|<-|<-|(Send Ack)|Ack to Emitter|


# Receiver Register
![Register-Receiver](https://github.com/nopnop2002/Arduino-STM32-nRF24L01/assets/6020549/5bf35e2c-22a7-4c5b-8de7-b945cbfeb28b)

# Receiver ScreenShot
![MultiReceiver](https://github.com/nopnop2002/Arduino-STM32-nRF24L01/assets/6020549/5a7a4278-7890-48c5-aa42-45c886f7ed84)
