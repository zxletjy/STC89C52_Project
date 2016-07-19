#ifndef _LT8900_H_
#define _LT8900_H_


#define WRITE		0x7F	  //���λ�������Ҫд����
#define READ		0x80	  //���λ��һ����Ҫ������


//SPI Define//	 6��SPIͨ�ţ��˴���ָ����IO����
sbit	RESET_N	= P3^4;  			//output
sbit	SS 		= P1^6;       		//output
sbit	MOSI 	= P3^2;     		//output
sbit	SCLK	= P1^4;     		//output
sbit	PKT 	= P1^7;  			//input
sbit	MISO 	= P3^3;       		//input


extern U8 RegH, RegL;
extern U8 SYNC_L,SYNC_H;

U8 spiReadWrite(U8 Byte); 
void spiReadreg(U8 reg);	 
void spiWriteReg(U8 reg, U8 byteH, U8 byteL);
void InitLT8900(void);

void SYNC_INIT(void);
void SYNC_SET(void);

void NOP_Delay(void);
void Delay10us(void);
void Delay_1ms(void);
void delayMs(U16 n);


#endif