# Multiple received communication   
The nRF24L01 has 6 receive data pipes (RX_ADDR_P0-P6).   
In this library, the first data pipe(RX_ADDR_P0) is used for automatic ACK reception on transmission.   
The second(RX_ADDR_P1) to sixth(RX_ADDR_P5) data pipes are used for data reception.   
Therefore, it is possible to receive from a maximum of five transmitting sides.   
This example receive from ```1RECV/2RECV/3RECV/4RECV/5RECV```.   

# nRF24L01 Address Register Setting
|Sender|||||Receiver||||||
|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|
|#1|TX_ADDR<br>"1RECV"|RX_ADDR_P0<br>"1RECV"|RX_ADDR_P1<br>NONE||TX_ADDR<br>NONE|RX_ADDR_P0<br>NONE|RX_ADDR_P1<br>"1RECV"|RX_ADDR_P2<br>"2RECV"|RX_ADDR_P5<br>"5RECV"||
||(Send Data)|->|->|->|->|->|(Get Data)|||Data to Receiver|
|||(Get Ack)|<-|<-|<-|<-|(Send Ack)|||Ack to Sender|
|#2|TX_ADDR<br>"2RECV"|RX_ADDR_P0<br>"2RECV"|RX_ADDR_P1<br>NONE||TX_ADDR<br>NONE|RX_ADDR_P0<br>NONE|RX_ADDR_P1<br>"1RECV"|RX_ADDR_P2<br>"2RECV"|RX_ADDR_P5<br>"5RECV"||
||(Send Data)|->|->|->|->|->|->|(Get Data)||Data to Receiver|
|||(Get Ack)|<-|<-|<-|<-|<-|(Send Ack)||Ack to Sender|
|#5|TX_ADDR<br>"5RECV"|RX_ADDR_P0<br>"5RECV"|RX_ADDR_P1<br>NONE||TX_ADDR<br>NONE|RX_ADDR_P0<br>NONE|RX_ADDR_P1<br>"1RECV"|RX_ADDR_P2<br>"2RECV"|RX_ADDR_P5<br>"5RECV"||
||(Send Data)|->|->|->|->|->|->|->|(Get Data)|Data to Receiver|
|||(Get Ack)|<-|<-|<-|<-|<-|<-|(Send Ack)|Ack to Sender|


# Receiver Register
RX_ADDR_P1 is 0x5643455231.   
RX_ADDR_P2 will be 0x5643455232. The same value is used for the first 4 bytes.   
![Register-Receiver](https://github.com/nopnop2002/Arduino-STM32-nRF24L01/assets/6020549/d2141577-7cf4-46a6-aec9-34266f6cd38c)

# Receiver ScreenShot
![MultiReceiver](https://github.com/nopnop2002/Arduino-STM32-nRF24L01/assets/6020549/5a7a4278-7890-48c5-aa42-45c886f7ed84)
