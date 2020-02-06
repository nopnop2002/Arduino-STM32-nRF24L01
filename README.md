# Arduino-STM32-nRF24L01
Arduino stm32 support files for nRF24L01 RF modules


Arduino_Core_STM32 supports SPI library, but only works in Transaction SPI Mode.

Legacy SPI Mode
```
SPI.begin()
SPI.setClockDivider(divider)
SPI.setDataMode(mode)
SPI.setBitOrder(order)
SPI.transfer(data);
```

Transaction SPI Mode
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

---

# Tested board

- Arduino UNO
```
Nrf24l Mirf = Nrf24l(10, 9);
 * VCC  3.3V
 * MISO 12
 * MOSI 11
 * SCK  13
 * CE   10
 * CSN  9
```

Serial.print is output to Arduino Serial Monitor.


- Arduino MEGA
```
Nrf24l Mirf = Nrf24l(10, 9);
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
Nrf24l Mirf = Nrf24l(10, 9);
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
Nrf24l Mirf = Nrf24l(10, 9);
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
Nrf24l Mirf = Nrf24l(PC6, PC7);
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
Nrf24l Mirf = Nrf24l(PB0, PB1);
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
Nrf24l Mirf = Nrf24l(PB0, PB1);
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
Nrf24l Mirf = Nrf24l(PB0, PB1);
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
Nrf24l Mirf = Nrf24l(PB8, PB9);
 * VCC  3.3V
 * MISO PB14
 * MOSI PB15
 * SCK  PB13
 * CE   PB8
 * CSN  PB9
```

Serial.print is output to PB10.


- Generic STM32F407(DIYMORE/BlackF407/etc)
```
Nrf24l Mirf = Nrf24l(PB0, PB1);
 * VCC  3.3V
 * MISO PB4
 * MOSI PB5
 * SCK  PB3
 * CE   PB0
 * CSN  PB1
```

Serial.print is output to PA9.


- ESP8266
```
Nrf24l Mirf = Nrf24l(15, 16);
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

# Important point
When changing the settings of the nRF24L01, it is necessary to power cycle the nRF24L01 before executing.   
Because nRF24L01 remembers the previous setting.   
nRF24L01 does not have Software Reset function.   
