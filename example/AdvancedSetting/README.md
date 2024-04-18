# AdvancedSetting
nRF24L01 has "Enhanced ShockBurst" features.   
"Enhanced ShockBurst" automatically sets the PTX(=Transmitter) in receive mode to wait for the ACK packet from PRX(=Receiver).   

## Transmission Successful   
|ESP32||nRF24L01[PTX]||nRF24L01[PRX]||ESP32|
|:-:|:-:|:-:|:-:|:-:|:-:|:-:|
|ESP32|-->|nRF24L01|||||
|||nRF24L01|--(Payload)-->|nRF24L01|||||
||||wait 250uS||||||
|||nRF24L01|<--(Ack Packet)--|nRF24L01|||||
|ESP32|<--|nRF24L01|||||||
|||||nRF24L01|-->|ESP32|

## Transmission Failure   
PTX waits for an ACK packet for 250uS and retransmits 3 times.   
|ESP32||nRF24L01[PTX]||nRF24L01[PRX]||ESP32|
|:-:|:-:|:-:|:-:|:-:|:-:|:-:|
|ESP32|-->|nRF24L01|||||
|||nRF24L01|--(Payload)-->|nRF24L01|||||
||||wait 250uS||||||
|||nRF24L01|--(Payload)-->|nRF24L01|||||
||||wait 250uS||||||
|||nRF24L01|--(Payload)-->|nRF24L01|||||
||||wait 250uS||||||
|ESP32|<--|nRF24L01|||||||


Using a data rate of 250KBps extends the range of radio waves.   
However, it takes time to send PAYLOAD and receive ACK PACKET.   
Therefore, the delay time for automatic retransmission should be longer than 250uS.   
If the delay of automatic retransmission is not increased, it is considered as a transmission failure.   
|ESP32||nRF24L01[PTX]||nRF24L01[PRX]||ESP32|
|:-:|:-:|:-:|:-:|:-:|:-:|:-:|
|ESP32|-->|nRF24L01|||||
|||nRF24L01|--(Payload)-->|nRF24L01|||||
||||Over 250uS||||||
|||nRF24L01|<--(Ack Packet)--|nRF24L01|||||
|ESP32|<--|nRF24L01|||||||
|||||nRF24L01|-->|ESP32|

See the data sheet for details on Enhanced ShockBurst.   

# About antena
Standard PCB antenna is designed for 2MBps frequency.   
If you want to change the frequency, you need to use an IPEX antenna type module and use an IPEX antenna that matches the frequency.   
