# Arduino-STM32-nRF24L01
Arduino stm32 support files for nRF24L01 RF modules


Arduino_Core_STM32 supports SPI library, but only works in Transaction SPI Mode.

- Legacy SPI Mode   
SPI speed depends on the CPU frequency.   
STM32 does not work because it has various CPU frequencies.
```
SPI.begin()
SPI.setClockDivider(divider)
SPI.setDataMode(mode)
SPI.setBitOrder(order)
SPI.transfer(data);
```

- Transaction SPI Mode   
SPI speed NOT depends on the CPU frequency.   
Therefore, it works correctly with STM32.
```
SPI.begin()
SPI.beginTransaction(SPISettings(speed, order, mode))
SPI.transfer(data);
SPI.endTransaction()
```

This repository works with Transaction SPI Mode.

---

# Memory usage

- Transmitter
```
Sketch uses 3054 bytes (9%) of program storage space. Maximum is 32256 bytes.
Global variables use 272 bytes (13%) of dynamic memory, leaving 1776 bytes for local variables. Maximum is 2048 bytes.
```

- Receiver
```
Sketch uses 2796 bytes (8%) of program storage space. Maximum is 32256 bytes.
Global variables use 248 bytes (12%) of dynamic memory, leaving 1800 bytes for local variables. Maximum is 2048 bytes.
```

---

# Important
When changing the settings of the nRF24L01, it is necessary to power cycle the nRF24L01 before executing.   
Because nRF24L01 remembers the previous setting.   
nRF24L01 does not have Software Reset function.   

---

# Tested board

- Arduino UNO
```
Nrf24l Mirf = Nrf24l(10, 9); // CE,CSN
 * VCC  3.3V
 * MISO 12
 * MOSI 11
 * SCK  13
 * CE   10
 * CSN  9
```

Serial.print is output to Arduino Serial Monitor.   


__Note__   
UNO's 3.3V output can only supply 50mA.   
In addition, the output current capacity of UNO-compatible devices is smaller than that of official products.   
__So this module may not work normally when supplied from the on-board 3v3.__   




- Arduino MEGA
```
Nrf24l Mirf = Nrf24l(10, 9); // CE,CSN
 * VCC  3.3V
 * MISO 50
 * MOSI 51
 * SCK  52
 * CE   10
 * CSN  9
```

Serial.print is output to Arduino Serial Monitor.


- Arduino DUE
```
Nrf24l Mirf = Nrf24l(10, 9); // CE,CSN
 * VCC  3.3V
 * MISO A.25
 * MOSI A.26
 * SCK  A.27
 * CE   D10
 * CSN  D9
```

Serial.print is output to Arduino Serial Monitor.


- STM32 NUCLEO
```
Nrf24l Mirf = Nrf24l(10, 9); // CE,CSN
 * VCC  3.3V
 * MISO D12(=PA6)
 * MOSI D11(=PA7)
 * SCK  D13(=PA5)
 * CE   D10(=PB6)
 * CSN  D9(=PC7)
```

Serial.print is output to Arduino Serial Monitor.


- STM32 F4-Discovery
```
Nrf24l Mirf = Nrf24l(PC6, PC7); // CE,CSN
 * VCC  3.3V
 * MISO PA6
 * MOSI PA7
 * SCK  PA5
 * CE   PC6
 * CSN  PC7
```

Serial.print is output to PA2.


- Generic STM32F103(BluePill/BlackPill/etc)
```
Nrf24l Mirf = Nrf24l(PB0, PB1); // CE,CSN
 * VCC  3.3V
 * MISO PA6
 * MOSI PA7
 * SCK  PA5
 * CE   PB0
 * CSN  PB1
```

Serial.print is output to PA9.


- Generic STM32F303(BackPill F303CC)
```
Nrf24l Mirf = Nrf24l(PB0, PB1); // CE,CSN
 * VCC  3.3V
 * MISO PA6
 * MOSI PA7
 * SCK  PA5
 * CE   PB0
 * CSN  PB1
```

Serial.print is output to PA9.


- Generic STM32F401(BlackPill F401CC)
```
Nrf24l Mirf = Nrf24l(PB0, PB1); // CE,CSN
 * VCC  3.3V
 * MISO PA6
 * MOSI PA7
 * SCK  PA5
 * CE   PB0
 * CSN  PB1
```

Serial.print is output to PA9.


- Generic STM32F405(Adafruit Feather STM32F405 Express)
```
Nrf24l Mirf = Nrf24l(PB8, PB9); // CE,CSN
 * VCC  3.3V
 * MISO PB14
 * MOSI PB15
 * SCK  PB13
 * CE   PB8
 * CSN  PB9
```

Serial.print is output to PB10.


- Generic STM32F407(DIYMORE)
```
Nrf24l Mirf = Nrf24l(PB0, PB1); // CE,CSN
 * VCC  3.3V
 * MISO PB4
 * MOSI PB5
 * SCK  PB3
 * CE   PB0
 * CSN  PB1
```

Serial.print is output to PA9.


- Generic STM32F407(BLACK F407VE)   
These boards share SPI with NRF24 connector and on board flash.    
```
NRF24L01 (JP2)
1 GND
2 3V3
3 PB6 NRF_CE
4 PB7 NRF_CS
5 PB3 SPI1_SCK
6 PB5 SPI1_MOSI
7 PB4 SPI1_MISO
8 PB8 NRF_IRQ

SPI Flash W25Q16 (U3)
1 PB0 F_CS
2 PB4 SPI1_MISO
3 WP 3V3
4 GND
5 PB5 SPI1_MOSI
6 PB3 SPI1_SCK
7 HOLD 3V3
8 VCC 3V3 
```

It is necessary to remap SPI and separate NRF24 and on board flash.
```
void setup()
{
  SPI.setMOSI(PB15);
  SPI.setMISO(PB14);
  SPI.setSCLK(PB13);
  SPI.setSSEL(PB12);
```

The following works when you remap SPI.

```
Nrf24l Mirf = Nrf24l(PB0, PB1); // CE,CSN
 * VCC  3.3V
 * MISO PB14
 * MOSI PB15
 * SCK  PB13
 * CE   PB0
 * CSN  PB1
```

Serial.print is output to PA9.


- ESP8266
```
Nrf24l Mirf = Nrf24l(15, 16); // CE,CSN
 * VCC  3.3V
 * MISO IO12(D6)
 * MOSI IO13(D7)
 * SCK  IO14(D5)
 * CE   IO15(D8)
 * CSN  IO16(D0)
```

Serial.print is output to IO1.


- ESP8285
```
Nrf24l Mirf = Nrf24l(15, 16); // CE,CSN
 * VCC  3.3V
 * MISO IO12(D6)
 * MOSI IO13(D7)
 * SCK  IO14(D5)
 * CE   IO15(D8)
 * CSN  IO16(D0)
```

Serial.print is output to IO1.


- Raspberry Pi   
This library can communicate with [this](https://github.com/nopnop2002/Raspberry-Mirf).


- esp-idf(esp32)   
This library can communicate with [this](https://github.com/nopnop2002/esp-idf-mirf).

