#ifndef _TJY_DEFINE_H_
#define _TJY_DEFINE_H_
#include <STC89C5xRC.H>
#define uint8_t unsigned char
#define uint16_t unsigned int
#define uint32_t unsigned long
#define OSC_M   	12000000UL			 /*ʹ��12M����*/
#define BAUD_RATE   4800UL		     /*�����ʶ���Ϊ9600*/
#define SERIAL_MAX_TX_BUFFER		64	//���崮�ڷ��ͻ�������С

//SPI Define//
sbit	SPI_MOSI 	= P1^0;     		//output
sbit	SPI_SCLK	= P1^1;     		//output
sbit	SPI_MISO 	= P1^2;       	//input

sbit	NRF_CSN	= P1^3;  			//output
sbit	NRF_CE  = P1^4;       //output
sbit	NRF_INT = P1^5;  			//input
#endif

