#include "MirfHardwareSpiDriver.h"
uint8_t MirfHardwareSpiDriver::transfer(uint8_t data) {
#if defined(SPI_HAS_TRANSACTION)
  SPI.beginTransaction(spiSettings);
#endif
  uint8_t value =SPI.transfer(data);
  //return SPI.transfer(data);
#if defined(SPI_HAS_TRANSACTION)
  SPI.endTransaction();
#endif
  return value;
}

void MirfHardwareSpiDriver::begin() {
  SPI.begin();
#if defined(SPI_HAS_TRANSACTION)
  //Serial.println("SPI_HAS_TRANSACTION");
  spiSettings = SPISettings(RF24_SPI_SPEED, MSBFIRST, SPI_MODE0);
#else
  //Serial.println("SPI_HAS_NO_TRANSACTION");
  SPI.setDataMode(SPI_MODE0);
  SPI.setClockDivider(SPI_2XCLOCK_MASK);
#endif
}

void MirfHardwareSpiDriver::end() {
}

MirfHardwareSpiDriver MirfHardwareSpi;
