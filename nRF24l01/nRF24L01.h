#ifndef _nRF24L01_H_
#define _nRF24L01_H_
#include "define.h"
#include "spi.h"

#define NRF_CSN_L() NRF_CSN = 0
#define NRF_CSN_H() NRF_CSN = 1
#define SPI1_RW 		spiReadWrite
uint8_t NRF_Check(void);

#endif
