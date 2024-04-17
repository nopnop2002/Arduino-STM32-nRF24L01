# PingPong

```
Primary -----> Secondary
Primary <----- Secondary
```

# nRF24L01 Adress Register Setting
|Primary||||Secondary||||
|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|
|TX_ADDR<br>"FGHIJ"|RX_ADDR_P0<br>"FGHIJ"|RX_ADDR_P1<br>"ABCDE"||TX_ADDR<br>"ABCDE"|RX_ADDR_P0<br>"ABCDE"|RX_ADDR_P1<br>"FGHIJ"||
|(Send Data)|->|->|->|->|->|(Get Data)|Data to Secondary|
||(Get Ack)|<-|<-|<-|<-|(Send Ack)|Ack to Primary|
|||||||||
|||(Get Data)|<-|(Send Data)|||Data to Primary|
|||(Send Ack)|->|->|(Get Ack)||Ack to Secondary|

# Primary Register
![Register-Primary](https://github.com/nopnop2002/Arduino-STM32-nRF24L01/assets/6020549/9f0519e4-22e9-4552-b666-bd172f994fca)


# Secondary Register
![Register-Secondary](https://github.com/nopnop2002/Arduino-STM32-nRF24L01/assets/6020549/a70279d8-cd6b-4260-bcd2-15218ae0a4e8)

