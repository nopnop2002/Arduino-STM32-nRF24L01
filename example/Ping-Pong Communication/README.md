# Ping-Pong Communication

```
Primary -----> Secondary
Primary <----- Secondary
```

# nRF24L01 Address Register Setting
|Primary||||Secondary||||
|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|
|TX_ADDR<br>"FGHIJ"|RX_ADDR_P0<br>"FGHIJ"|RX_ADDR_P1<br>"ABCDE"||TX_ADDR<br>"ABCDE"|RX_ADDR_P0<br>"ABCDE"|RX_ADDR_P1<br>"FGHIJ"||
|(Send Data)|->|->|->|->|->|(Get Data)|Data to Secondary|
||(Get Ack)|<-|<-|<-|<-|(Send Ack)|Ack to Primary|
|||||||||
|||(Get Data)|<-|(Send Data)|||Data to Primary|
|||(Send Ack)|->|->|(Get Ack)||Ack to Secondary|

# Setting Register
The underlined address match on the sending and receiving sides.   

## Primary Register
![Register-Primary](https://github.com/nopnop2002/Arduino-STM32-nRF24L01/assets/6020549/71a00113-9de5-4fd2-8742-deebc6278a76)

# Secondary Register
![Register-Secondary](https://github.com/nopnop2002/Arduino-STM32-nRF24L01/assets/6020549/c2506c30-58a8-4aa0-9d07-c4225a2dae51)

