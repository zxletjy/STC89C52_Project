#include "Serial.h"
#include <string.h>
#include <stdio.h>  
#include <stdarg.h> 

unsigned int Serial_Tx_Length;//���ͳ���
unsigned int Serial_Tx_Count;//���ͼ���
uint8_t Serial_Tx_Buffer[SERIAL_MAX_TX_BUFFER];	 //���ͻ�����
uint8_t Serial_Tx_Done;		//������ɱ�־λ

void Serial_Setup(void)
{
	TMOD&=0x0F;  	//��ʱ��1ģʽ�����ڸ�4λ
	TMOD|=0x20;    //��ʱ��1������ģʽ2���Զ���װģʽ
	SCON=0x50;     //���ڹ�����ģʽ1
	TH1=256-OSC_M/(BAUD_RATE*12*16);  //���㶨ʱ����װֵ
	TL1=256-OSC_M/(BAUD_RATE*12*16);
	PCON|=0x80;    //���ڲ����ʼӱ�
	ES=1;         //�����ж�����
	TR1=1;        //������ʱ��1
	REN=1;        //������� 
}

void SendByte(unsigned char d)		  //����һ���ֽڵ����ݣ��β�d��Ϊ���������ݡ�
{
	SBUF=d; //������д�뵽���ڻ���
	while(TI == 0);
	TI=0;
}
uint8_t SendString(unsigned char *p, int length)		  //����һ���ֽڵ����ݣ��β�d��Ϊ���������ݡ�
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
//�����ж�����������   
void Serial_IRQ(void) interrupt 4		 //���ڷ����ж�
{
	if(RI)    //�յ�����
	{
		RI=0;   //���ж�����
	}
	else      //������һ�ֽ�����
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