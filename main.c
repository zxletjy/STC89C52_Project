#include "define.h"
#include "Serial.h"
#include <stdio.h>
#include "spi.h"
#include "nRF24L01.h"
//Èí¼şÑÓÊ±º¯Êı
void delay_ms(unsigned long i)
{
	unsigned long x,y;
	for (x=0; x<i; x++)
		for (y=0; y<20; y++);
}
void Setup(void)
{
	EA=0;
	Serial_Setup();
	EA=1;
}
void main()
{
	Setup();
	if (NRF_Check() == 1)
	{
		printf("Fuck Yeah!!!");
	}
	while(1)
	{
    
		delay_ms(1000);
	}
}

