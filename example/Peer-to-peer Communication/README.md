# Peer-to-peer Communication

The following parameters must match on the sender and receiver.   

## Payload size & channel
```
  Mirf.payload = sizeof(mydata.value); // Set the payload size
  Mirf.channel = 90;                   // Set the channel used
```

## Sender side
```
  // Set destination address to TX_ADDR
  // Set ACK waiting address to RX_ADDR_P0
  Mirf.setTADDR((byte *)"FGHIJ");
```

## Receiver side
```
  // Set my own address to RX_ADDR_P1
  Mirf.setRADDR((byte *)"FGHIJ");

```

# nRF24L01 Address Register Setting
|Emitter||||Receiver||||
|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|
|TX_ADDR<br>"FGHIJ"|RX_ADDR_P0<br>"FGHIJ"|RX_ADDR_P1<br>NONE||TX_ADDR<br>NONE|RX_ADDR_P0<br>NONE|RX_ADDR_P1<br>"FGHIJ"||
|(Send Data)|->|->|->|->|->|(Get Data)|Data to Receiver|
||(Get Ack)|<-|<-|<-|<-|(Send Ack)|Ack to Emitter|

# Sender Register
![Register-Sender](https://github.com/nopnop2002/Arduino-STM32-nRF24L01/assets/6020549/472a41e0-ebad-4074-8b4b-5832116ddf96)

# Receiver Register
![Register-Receiver](https://github.com/nopnop2002/Arduino-STM32-nRF24L01/assets/6020549/1135e312-4e72-4990-b059-6bc7849928ee)
