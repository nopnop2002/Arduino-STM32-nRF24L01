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

    $Id$
*/

#ifndef _NRF24L01_H_
#define _NRF24L01_H_

#include <Arduino.h>

#include "MirfHardwareSpiDriver.h"

// Nrf24l settings
/* Memory Map */
#define CONFIG      0x00
#define EN_AA       0x01
#define EN_RXADDR   0x02
#define SETUP_AW    0x03
#define SETUP_RETR  0x04
#define RF_CH       0x05
#define RF_SETUP    0x06
#define STATUS      0x07
#define OBSERVE_TX  0x08
#define CD          0x09
#define RX_ADDR_P0  0x0A
#define RX_ADDR_P1  0x0B
#define RX_ADDR_P2  0x0C
#define RX_ADDR_P3  0x0D
#define RX_ADDR_P4  0x0E
#define RX_ADDR_P5  0x0F
#define TX_ADDR     0x10
#define RX_PW_P0    0x11
#define RX_PW_P1    0x12
#define RX_PW_P2    0x13
#define RX_PW_P3    0x14
#define RX_PW_P4    0x15
#define RX_PW_P5    0x16
#define FIFO_STATUS 0x17

// nRF24l01+ stuff
#define DYNPD       0x1C
#define FEATURE     0x1D

/* Bit Mnemonics */
#define MASK_RX_DR  6
#define MASK_TX_DS  5
#define MASK_MAX_RT 4
#define EN_CRC      3
#define CRCO        2
#define PWR_UP      1
#define PRIM_RX     0
#define ENAA_P5     5
#define ENAA_P4     4
#define ENAA_P3     3
#define ENAA_P2     2
#define ENAA_P1     1
#define ENAA_P0     0
#define ERX_P5      5
#define ERX_P4      4
#define ERX_P3      3
#define ERX_P2      2
#define ERX_P1      1
#define ERX_P0      0
#define AW          0
#define ARD         4
#define ARC         0
#define RF_DR_LOW   5
#define PLL_LOCK    4
#define RF_DR_HIGH  3
#define RF_PWR_LOW  1
#define RF_PWR_HIGH 2
#define RF_PWR      1
#define LNA_HCURR   0
#define RX_DR       6
#define TX_DS       5
#define MAX_RT      4
#define RX_P_NO     1
#define TX_FULL     0
#define PLOS_CNT    4
#define ARC_CNT     0
#define TX_REUSE    6
#define FIFO_FULL   5
#define TX_EMPTY    4
#define RX_FULL     1
#define RX_EMPTY    0

/* Instruction Mnemonics */
#define R_REGISTER    0x00
#define W_REGISTER    0x20
#define REGISTER_MASK 0x1F
#define R_RX_PAYLOAD  0x61
#define W_TX_PAYLOAD  0xA0
#define FLUSH_TX      0xE1
#define FLUSH_RX      0xE2
#define REUSE_TX_PL   0xE3
#define NOP           0xFF

#define mirf_ADDR_LEN	5
#define mirf_CONFIG ((1<<EN_CRC) | (0<<CRCO) )


/**
 * Data rate.  How fast data moves through the air.
 *
 * For use with getDataRate()
 */
typedef enum {
    RF24_DR_1MBPS = 0,
    RF24_DR_2MBPS,
    RF24_DR_250KBPS
} rf24_datarate_e;

/**
 * CRC Length.  How big (if any) of a CRC is included.
 *
 * For use with setCRCLength()
 */
typedef enum {
    RF24_CRC_DISABLED = 0,
    RF24_CRC_8,
    RF24_CRC_16
} rf24_crclength_e;



class Nrf24l {
  public:
     Nrf24l(uint8_t cs_pin, uint8_t csn_pin);
    ~Nrf24l() {

    }
    //   Nrf24l(uint8_t CePin, uint8_t CsnPin);
    void init();
    void config();
    void send(uint8_t *value);
    void setRADDR(uint8_t * adr);
    void addRADDR(uint8_t pipe, uint8_t adr);
    void setTADDR(uint8_t * adr);
    bool dataReady();
    uint8_t getDataPipe();
    bool isSending();
    bool isSend();
    bool rxFifoEmpty();
    bool txFifoEmpty();
    void getData(uint8_t * data);
    uint8_t getStatus();

    void transmitSync(uint8_t *dataout, uint8_t len);
    void transferSync(uint8_t *dataout, uint8_t *datain, uint8_t len);
    void configRegister(uint8_t reg, uint8_t value);
    void readRegister(uint8_t reg, uint8_t * value, uint8_t len);
    void writeRegister(uint8_t reg, uint8_t * value, uint8_t len);
    void powerUpRx();
    void powerUpTx();
    void powerDown();
    void setOutputRF_PWR(uint8_t val);
    void setSpeedDataRates( uint8_t val);
    void setRetransmitDelay(uint8_t val);
    void setChannel(uint8_t val);
    void printDetails();
    void print_status(uint8_t status);
    void print_address_register(const char* name, uint8_t reg, uint8_t qty);
    void print_byte_register(const char* name, uint8_t reg, uint8_t qty);
    uint8_t getDataRate();
    uint8_t getCRCLength();
    uint8_t getPALevel();
    uint8_t getRetransmitDelay();


    void csnHi();
    void csnLow();

    void ceHi();
    void ceLow();
    void flushRx();

    /*
       In sending mode.
    */

    uint8_t PTX;

    /*
       CE Pin controls RX / TX, default 8.
    */

    uint8_t cePin;

    /*
       CSN Pin Chip Select Not, default 7.
    */

    uint8_t csnPin;

    /*
       Channel 0 - 127 or 0 - 84 in the US.
    */
    uint8_t channel;

    /*
       Payload width in bytes default 16 max 32.
    */

    uint8_t payload;

    /*
       Spi interface (must extend spi).
    */

    MirfHardwareSpiDriver *spi;
};

#endif /* _NRF24L01_H_ */
