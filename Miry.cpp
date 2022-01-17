/**
   Mirf

   Additional bug fixes and improvements
    11/03/2011:
     Switched spi library.
    07/13/2010:
     Added example to read a register
    11/12/2009:
     Fix dataReady() to work correctly
     Renamed keywords to keywords.txt ( for IDE ) and updated keyword list
     Fixed client example code to timeout after one second and try again
      when no response received from server
   By: Nathan Isburgh <nathan@mrroot.net>
   $Id: mirf.cpp 67 2010-07-13 13:25:53Z nisburgh $


   An Ardunio port of:
   http://www.tinkerer.eu/AVRLib/nRF24L01

   Significant changes to remove depencence on interupts and auto ack support.

   Aaron Shrimpton <aaronds@gmail.com>

*/

/*
    Copyright (c) 2007 Stefan Engelke <mbox@stefanengelke.de>

    Permission is hereby granted, free of charge, to any person
    obtaining a copy of this software and associated documentation
    files (the "Software"), to deal in the Software without
    restriction, including without limitation the rights to use, copy,
    modify, merge, publish, distribute, sublicense, and/or sell copies
    of the Software, and to permit persons to whom the Software is
    furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be
    included in all copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
    EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
    MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
    NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
    HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
    WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
    OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
    DEALINGS IN THE SOFTWARE.

    $Id: mirf.cpp 67 2010-07-13 13:25:53Z nisburgh $
*/

#include "Mirf.h"
// Defines for setting the MiRF registers for transmitting or receiving mode


Nrf24l::Nrf24l(uint8_t cs_pin, uint8_t csn_pin)
{
  cePin = cs_pin;
  csnPin = csn_pin;
  channel = 1;
  payload = 16;
  spi = NULL;
}

void Nrf24l::transferSync(uint8_t *dataout, uint8_t *datain, uint8_t len) {
  uint8_t i;
  for (i = 0; i < len; i++) {
    datain[i] = spi->transfer(dataout[i]);
  }
}

void Nrf24l::transmitSync(uint8_t *dataout, uint8_t len) {
  uint8_t i;
  for (i = 0; i < len; i++) {
    spi->transfer(dataout[i]);
  }
}

void Nrf24l::init()
// Initializes pins to communicate with the MiRF module
// Should be called in the early initializing phase at startup.
{
  pinMode(cePin, OUTPUT);
  pinMode(csnPin, OUTPUT);
  ceLow();
  csnHi();
  // Initialize spi module
  spi->begin();

}


void Nrf24l::config()
// Sets the important registers in the MiRF module and powers the module
// in receiving mode
// NB: channel and payload must be set now.
{
  // Set RF channel
  configRegister(RF_CH, channel);

  // Set length of incoming payload
  configRegister(RX_PW_P0, payload);
  configRegister(RX_PW_P1, payload);

  // Start receiver
  powerUpRx();
  flushRx();
}

void Nrf24l::setRADDR(uint8_t * adr)
// Sets the receiving address
{
  writeRegister(RX_ADDR_P1, adr, mirf_ADDR_LEN);
}

void Nrf24l::addRADDR(uint8_t pipe, uint8_t adr)
// Sets the receiving address
{
  uint8_t value;
  readRegister(EN_RXADDR, &value, 1);
  //Serial.print("EN_RXADDR(1)=0x");
  //Serial.println(value, HEX);
  //Serial.print("payload=");
  //Serial.println(payload);

  //Serial.print("adr=");
  //Serial.println(adr, HEX);
  if (pipe == 2) {
    configRegister(RX_PW_P2, payload);
    configRegister(RX_ADDR_P2, adr);
    value = value | 0x04;
    configRegister(EN_RXADDR, value);
  } else if (pipe == 3) {
    configRegister(RX_PW_P3, payload);
    configRegister(RX_ADDR_P3, adr);
    value = value | 0x08;
    configRegister(EN_RXADDR, value);
  } else if (pipe == 4) {
    configRegister(RX_PW_P4, payload);
    configRegister(RX_ADDR_P4, adr);
    value = value | 0x10;
    configRegister(EN_RXADDR, value);
  } else if (pipe == 5) {
    configRegister(RX_PW_P5, payload);
    configRegister(RX_ADDR_P5, adr);
    value = value | 0x20;
    configRegister(EN_RXADDR, value);
  }

  readRegister(EN_RXADDR, &value, 1);
  //Serial.print("EN_RXADDR(2)=0x");
  //Serial.println(value, HEX);

}

void Nrf24l::setTADDR(uint8_t * adr)
// Sets the transmitting address
{
  /*
     RX_ADDR_P0 must be set to the sending addr for auto ack to work.
  */

  writeRegister(RX_ADDR_P0, adr, mirf_ADDR_LEN);
  writeRegister(TX_ADDR, adr, mirf_ADDR_LEN);
}

extern bool Nrf24l::dataReady()
// Checks if data is available for reading
{
  // See note in getData() function - just checking RX_DR isn't good enough
  uint8_t status = getStatus();

  // We can short circuit on RX_DR, but if it's not set, we still need
  // to check the FIFO for any pending packets
  if ( status & (1 << RX_DR) ) return 1;
  return 0;
  //return !rxFifoEmpty();
}

uint8_t Nrf24l::getDataPipe() {
  uint8_t status = getStatus();
  //Serial.print("dataReady=0x");
  //Serial.println(status, HEX);
  return ((status & 0x0E) >> 1);
}

extern bool Nrf24l::rxFifoEmpty() {
  uint8_t fifoStatus;

  readRegister(FIFO_STATUS, &fifoStatus, sizeof(fifoStatus));
  return (fifoStatus & (1 << RX_EMPTY));
}



extern void Nrf24l::getData(uint8_t * data)
// Reads payload bytes into data array
{
  csnLow();                               // Pull down chip select
  spi->transfer( R_RX_PAYLOAD );            // Send cmd to read rx payload
  transferSync(data, data, payload); // Read payload
  csnHi();                               // Pull up chip select
  // NVI: per product spec, p 67, note c:
  //  "The RX_DR IRQ is asserted by a new packet arrival event. The procedure
  //  for handling this interrupt should be: 1) read payload through SPI,
  //  2) clear RX_DR IRQ, 3) read FIFO_STATUS to check if there are more
  //  payloads available in RX FIFO, 4) if there are more data in RX FIFO,
  //  repeat from step 1)."
  // So if we're going to clear RX_DR here, we need to check the RX FIFO
  // in the dataReady() function
#if 0
  uint8_t value;
  readRegister(RF_SETUP, &value, 1);
  //Serial.print("getData(1)=0x");
  //Serial.println(value, HEX);
  value = value | (1 << RX_DR);
  //Serial.print("getData(2)=0x");
  //Serial.println(value, HEX);
  //configRegister(STATUS, (1 << RX_DR)); // Reset status register
  configRegister(STATUS, value); // Reset status register
#endif
  configRegister(STATUS, (1 << RX_DR)); // Reset status register
}

void Nrf24l::configRegister(uint8_t reg, uint8_t value)
// Clocks only one byte into the given MiRF register
{
  csnLow();
  spi->transfer(W_REGISTER | (REGISTER_MASK & reg));
  spi->transfer(value);
  csnHi();
}

void Nrf24l::readRegister(uint8_t reg, uint8_t * value, uint8_t len)
// Reads an array of bytes from the given start position in the MiRF registers.
{
  csnLow();
  spi->transfer(R_REGISTER | (REGISTER_MASK & reg));
  transferSync(value, value, len);
  csnHi();
}

void Nrf24l::writeRegister(uint8_t reg, uint8_t * value, uint8_t len)
// Writes an array of bytes into inte the MiRF registers.
{
  csnLow();
  spi->transfer(W_REGISTER | (REGISTER_MASK & reg));
  transmitSync(value, len);
  csnHi();
}


void Nrf24l::send(uint8_t * value)
// Sends a data package to the default address. Be sure to send the correct
// amount of bytes as configured as payload on the receiver.
// After executing this function, confirm transmission completion with IsSending or IsSend.
{
  uint8_t status;
  status = getStatus();

  while (PTX) {
    status = getStatus();

    if ((status & ((1 << TX_DS)  | (1 << MAX_RT)))) {
      PTX = 0;
      break;
    }
  }                  // Wait until last paket is send

  ceLow();

  powerUpTx();       // Set to transmitter mode , Power up

  csnLow();                    // Pull down chip select
  spi->transfer( FLUSH_TX );     // Write cmd to flush tx fifo
  csnHi();                    // Pull up chip select

  csnLow();                    // Pull down chip select
  spi->transfer( W_TX_PAYLOAD ); // Write cmd to write payload
  transmitSync(value, payload);  // Write payload
  csnHi();                    // Pull up chip select

  ceHi();                     // Start transmission
}

/**
   isSending.

   Test if chip is still sending.
   When sending has finished return chip to listening.

*/

bool Nrf24l::isSending() {
  uint8_t status;
  if (PTX) {
    status = getStatus();
    //Serial.print("status:");
    //Serial.println(status,HEX);
    /*
        if sending successful (TX_DS) or max retries exceded (MAX_RT).
    */

    //Serial.println(((1 << TX_DS)  | (1 << MAX_RT)),HEX);
    if ((status & ((1 << TX_DS)  | (1 << MAX_RT)))) {
      //Serial.println("return false");
      powerUpRx();
      return false;
    }

    //Serial.println("return true");
    return true;
  }
  return false;
}

/**
   isSend.

   Test if Sending has finished or retry is over.
   When sending has finished return trur.
   When reach maximum number of TX retries return false.

*/

bool Nrf24l::isSend() {
  uint8_t status;
  if (PTX) {
    while(1) {
      status = getStatus();
      //Serial.print("status:0x");
      //Serial.println(status,HEX);
      /*
        if sending successful (TX_DS) or max retries exceded (MAX_RT).
      */

      if (status & (1 << TX_DS)) { // Data Sent TX FIFO interrup
        //Serial.println("TX_DS");
        powerUpRx();
        return true;
      }

      if (status & (1 << MAX_RT)) { // Maximum number of TX retries interrupt
        //Serial.println("MAX_RT");
        powerUpRx();
        return false;
      }
    }
  }
  return false;
}


uint8_t Nrf24l::getStatus() {
  uint8_t rv;
  readRegister(STATUS, &rv, 1);
  return rv;
}

void Nrf24l::powerUpRx() {
  PTX = 0;
  ceLow();
  configRegister(CONFIG, mirf_CONFIG | ( (1 << PWR_UP) | (1 << PRIM_RX) ) );
  ceHi();
  configRegister(STATUS, (1 << TX_DS) | (1 << MAX_RT));
}

void Nrf24l::flushRx() {
  csnLow();
  spi->transfer( FLUSH_RX );
  csnHi();
}

void Nrf24l::powerUpTx() {
  PTX = 1;
  configRegister(CONFIG, mirf_CONFIG | ( (1 << PWR_UP) | (0 << PRIM_RX) ) );
}

void Nrf24l::ceHi() {
  digitalWrite(cePin, HIGH);
}

void Nrf24l::ceLow() {
  digitalWrite(cePin, LOW);
}

void Nrf24l::csnHi() {
  digitalWrite(csnPin, HIGH);
}

void Nrf24l::csnLow() {
  digitalWrite(csnPin, LOW);
}

void Nrf24l::powerDown() {
  ceLow();
  configRegister(CONFIG, mirf_CONFIG );
}


void Nrf24l::setOutputRF_PWR(uint8_t val) //Set tx power : 0=-18dBm,1=-12dBm,2=-6dBm,3=0dBm,
{
  if (val > 3) return;

  //Serial.print("setOutputRF_PWR val=");
  //Serial.println(val);
  uint8_t value;
  readRegister(RF_SETUP, &value, 1);
  //Serial.print("setOutputRF_PWR(1)=0x");
  //Serial.println(value, HEX);

  value = value & 0xF9;
  value = value | (val<< RF_PWR);
  //Serial.print("setOutputRF_PWR(2)=0x");
  //Serial.println(value, HEX);

  //configRegister(RF_SETUP,	(val<< RF_PWR) );
  configRegister(RF_SETUP, value);
}

void Nrf24l::setSpeedDataRates(uint8_t val) //Select between the high speed data rates:0=1Mbps, 1=2Mbps, 2=250Kbps
{
  if (val > 2) return;

  //Serial.print("setSpeedDataRates val=");
  //Serial.println(val);
  uint8_t value;
  readRegister(RF_SETUP, &value, 1);
  //Serial.print("setSpeedDataRates(1)=0x");
  //Serial.println(value, HEX);

  if(val == 2)
  {
    value = value | 0x20;
    value = value & 0xF7;
    //Serial.print("setSpeedDataRates(2)=0x");
    //Serial.println(value, HEX);
    //configRegister(RF_SETUP,	(1 << RF_DR_LOW) );
    configRegister(RF_SETUP, value);
  }
  else
  {
    value = value & 0xD7;
    value = value | (val << RF_DR_HIGH);
    //Serial.print("setSpeedDataRates(2)=0x");
    //Serial.println(value, HEX);
    //configRegister(RF_SETUP,	(val << RF_DR_HIGH) );
    configRegister(RF_SETUP, value);
  }

}

void Nrf24l::setRetransmitDelay(uint8_t val) //Set Auto Retransmit Delay 0=250us, 1=500us, ... 15=4000us
{
  uint8_t value;
  readRegister(SETUP_RETR, &value, 1);
  //Serial.print("setRetransmitDelay(1)=0x");
  //Serial.println(value, HEX);
  value = value & 0x0F;
  value = value | (val << ARD);
  //Serial.print("setRetransmitDelay(2)=0x");
  //Serial.println(value, HEX);
  configRegister(SETUP_RETR, value);
}

void Nrf24l::setChannel(uint8_t val) //Set RF channel
{
  ceLow();
  configRegister(RF_CH, channel);
  ceHi();
}

void Nrf24l::printDetails()
{
  print_status(getStatus());
  print_address_register("RX_ADDR_P0-1", RX_ADDR_P0, 2);
  print_byte_register("RX_ADDR_P2-5", RX_ADDR_P2, 4);
  print_address_register("TX_ADDR\t", TX_ADDR, 1);
  print_byte_register("RX_PW_P0-6", RX_PW_P0, 6);
  print_byte_register("EN_AA\t", EN_AA, 1);
  print_byte_register("EN_RXADDR", EN_RXADDR, 1);
  print_byte_register("RF_CH\t", RF_CH, 1);
  print_byte_register("RF_SETUP", RF_SETUP, 1);
  print_byte_register("CONFIG\t", CONFIG, 1);
  print_byte_register("DYNPD/FEATURE", DYNPD, 2);
  //printf("getDataRate()=%d\n",getDataRate());
  uint8_t datarate = getDataRate();
  if (datarate == RF24_DR_1MBPS) {
    printf("Data Rate\t = 1MBPS \n");
  } else if (datarate == RF24_DR_2MBPS) {
    printf("Data Rate\t = 2MBPS \n");
  } else if (datarate == RF24_DR_250KBPS) {
    printf("Data Rate\t = 250KBPS \n");
  }
#if 0
  printf_P(PSTR("Model\t\t = "
  PRIPSTR
    "\r\n"),pgm_read_ptr(&rf24_model_e_str_P[isPVariant()]));
#endif
  //printf("getCRCLength()=%d\n",getCRCLength());
  uint8_t crclength = getCRCLength();
  if (crclength ==RF24_CRC_DISABLED) {
    printf("CRC Length\t = DISABLED\n");
  } else if (crclength == RF24_CRC_8) {
    printf("CRC Length\t = 8 bits\n");
  } else if (crclength == RF24_CRC_16) {
    printf("CRC Length\t = 16 bits\n");
  }
  //printf("getPALevel()=%d\n",getPALevel());
  uint8_t palevel = getPALevel();
  if (palevel == 0) {
    printf("PA Power\t = -18dBm\n");
  } else if (palevel == 1) {
    printf("PA Power\t = -12dBm\n");
  } else if (palevel == 2) {
    printf("PA Power\t = -6dBm\n");
  } else if (palevel == 3) {
    printf("PA Power\t = 0dBm\n");
  }
  //printf("getRetransmitDelay()=%d\n",getRetransmitDelay());
  uint8_t retransmit = getRetransmitDelay();
  int16_t delay = (retransmit+1)*250;
  printf("Retransmit\t = %d us\n", delay);

}


void Nrf24l::print_status(uint8_t status)
{
  printf("STATUS\t\t = 0x%02x RX_DR=%x TX_DS=%x MAX_RT=%x RX_P_NO=%x TX_FULL=%x\r\n", status, (status & _BV(RX_DR)) ? 1 : 0,
        (status & _BV(TX_DS)) ? 1 : 0, (status & _BV(MAX_RT)) ? 1 : 0, ((status >> RX_P_NO) & 0x07), (status & _BV(TX_FULL)) ? 1 : 0);
}


void Nrf24l::print_address_register(const char* name, uint8_t reg, uint8_t qty)
{
  printf("%s\t =",name);
  while (qty--) {
    //uint8_t buffer[addr_width];
    uint8_t buffer[5];
    readRegister(reg++, buffer, sizeof(buffer));

    printf(" 0x");
    uint8_t* bufptr = buffer + sizeof buffer;
    while (--bufptr >= buffer) {
      printf("%02x", *bufptr);
    }
  }
  printf("\r\n");
}

void Nrf24l::print_byte_register(const char* name, uint8_t reg, uint8_t qty)
{
  printf("%s\t =", name);
  while (qty--) {
    uint8_t buffer[1];
    readRegister(reg++, buffer, 1);
    printf(" 0x%02x", buffer[0]);
  }
  printf("\r\n");
}


uint8_t Nrf24l::getDataRate()
{
  uint8_t result;
  uint8_t dr;
  readRegister(RF_SETUP, &dr, sizeof(dr));
  //Serial.print("getDataRate(1)=0x");
  //Serial.println(dr, HEX);
  dr = dr & (_BV(RF_DR_LOW) | _BV(RF_DR_HIGH));
  //Serial.print("getDataRate(2)=0x");
  //Serial.println(dr, HEX);

  // switch uses RAM (evil!)
  // Order matters in our case below
  if (dr == _BV(RF_DR_LOW)) {
    // '10' = 250KBPS
    result = RF24_DR_250KBPS;
  } else if (dr == _BV(RF_DR_HIGH)) {
    // '01' = 2MBPS
    result = RF24_DR_2MBPS;
  } else {
    // '00' = 1MBPS
    result = RF24_DR_1MBPS;
  }
  return result;
}

uint8_t Nrf24l::getCRCLength()
{
  rf24_crclength_e result = RF24_CRC_DISABLED;
  
  uint8_t config;
  readRegister(CONFIG, &config, sizeof(config));
  //printf("CONFIG=%x\n",config);
  config = config & (_BV(CRCO) | _BV(EN_CRC));
  uint8_t AA;
  readRegister(EN_AA, &AA, sizeof(AA));

  if (config & _BV(EN_CRC) || AA) {
    if (config & _BV(CRCO)) {
      result = RF24_CRC_16;
    } else {
      result = RF24_CRC_8;
    }
  }
  return result;
}



uint8_t Nrf24l::getPALevel()
{
  uint8_t level;
  readRegister(RF_SETUP, &level, sizeof(level));
  //printf("RF_SETUP=%x\n",level);
  level = (level & (_BV(RF_PWR_LOW) | _BV(RF_PWR_HIGH))) >> 1;
  return (level);
}

uint8_t Nrf24l::getRetransmitDelay()
{
  uint8_t value;
  readRegister(SETUP_RETR, &value, 1);
  return (value >> 4);
}

