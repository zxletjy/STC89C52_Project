#include "define.h"
#include "Serial.h"
#include "stdio.h"
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
	while(1)
	{
    Serial_printf("what the fuck!!!\r\n");
		delay_ms(1000);
	}
}

