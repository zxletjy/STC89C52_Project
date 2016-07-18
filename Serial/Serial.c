#include "Serial.h"
#include <string.h>
#include <stdio.h>  
#include <stdarg.h> 

unsigned int Serial_Tx_Length;//发送长度
unsigned int Serial_Tx_Count;//发送计数
uint8_t Serial_Tx_Buffer[SERIAL_MAX_TX_BUFFER];	 //发送缓冲区
uint8_t Serial_Tx_Done;		//发送完成标志位

void Serial_Setup(void)
{
	TMOD&=0x0F;  	//定时器1模式控制在高4位
	TMOD|=0x20;    //定时器1工作在模式2，自动重装模式
	SCON=0x50;     //串口工作在模式1
	TH1=256-OSC_M/(BAUD_RATE*12*16);  //计算定时器重装值
	TL1=256-OSC_M/(BAUD_RATE*12*16);
	PCON|=0x80;    //串口波特率加倍
	ES=1;         //串行中断允许
	TR1=1;        //启动定时器1
	REN=1;        //允许接收 
}

void SendByte(unsigned char d)		  //发送一个字节的数据，形参d即为待发送数据。
{
	SBUF=d; //将数据写入到串口缓冲
	while(TI == 0);
	TI=0;
}
uint8_t SendString(unsigned char *p, int length)		  //发送一个字节的数据，形参d即为待发送数据。
{	  
	uint8_t flag=0;
    if (Serial_Tx_Done == 0)
    {
        Serial_Tx_Done = 1;
        Serial_Tx_Count=0;
        memcpy(Serial_Tx_Buffer, p, length);
        Serial_Tx_Length = length;
        SBUF = Serial_Tx_Buffer[Serial_Tx_Count++];
        flag = 1;
    }
    else 
    {
        flag = 0;
    }
    return flag;
}

uint8_t Serial_printf(const char *fmt,...)  
{  
	uint8_t flag=0;
	va_list ap; 
	if (Serial_Tx_Done == 0)
	{
			Serial_Tx_Done = 1;
      Serial_Tx_Count=0;
			va_start(ap,fmt);
			Serial_Tx_Length = vsprintf(Serial_Tx_Buffer,fmt,ap);
      SBUF = Serial_Tx_Buffer[Serial_Tx_Count++];
			va_end(ap);
			flag = 1;
	}
	else 
	{
			flag = 0;
	}
	return flag;
}  
//利用中断来发送数据   
void Serial_IRQ(void) interrupt 4		 //串口发送中断
{
	if(RI)    //收到数据
	{
		RI=0;   //清中断请求
	}
	else      //发送完一字节数据
	{
    	TI=0;
        if ((Serial_Tx_Done == 1) && (Serial_Tx_Count < Serial_Tx_Length) && (Serial_Tx_Length != 0))
        {
           SBUF = Serial_Tx_Buffer[Serial_Tx_Count++]; 
        }
        else if (Serial_Tx_Count >= Serial_Tx_Length)
        {
           Serial_Tx_Done = 0;
           Serial_Tx_Length = 0;
        }
	}
}