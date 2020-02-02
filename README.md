# Arduino-STM32-nRF24L01
Arduino stm32 support files for nRF24L01 RF modules


Arduino_Core_STM32 supports SPI library, but only works in Transaction SPI Mode.

Legacy Mode
```
SPI.begin()
SPI.setClockDivider(divider)
SPI.setDataMode(mode)
SPI.setBitOrder(order)
SPI.transfer(data);
```

Transaction Mode
```
SPI.begin()
SPI.beginTransaction(SPISettings(speed, order, mode))
SPI.transfer(data);
SPI.endTransaction()
```

This repository works with Transaction Mode.

----

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

