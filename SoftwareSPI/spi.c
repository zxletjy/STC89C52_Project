#include "spi.h"
#include <intrins.h> 
void NOP_Delay(void)
{
	_nop_();
}
void Delay10us(void) 
{
	 uint16_t i=0;
	 for (i=0;i<10;i++)
	 NOP_Delay();
}
uint8_t spiReadWrite(uint8_t Byte)
{										    
  uint8_t i;						
	EA = 0;
	for (i = 0; i < 8; i++)
	{
		SPI_MOSI = (Byte & 0x80);
		SPI_SCLK = 1;	
		Delay10us();
		Byte <<= 1;
		Byte |= SPI_MISO;
		SPI_SCLK = 0;
		Delay10us();
	}
	EA = 1;    
  return (Byte);
}