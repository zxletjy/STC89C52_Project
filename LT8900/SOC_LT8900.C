#include "GLOBAL.H"

/*参数定义*/

U8 RegH, RegL;
U8 SYNC_H,SYNC_L;


void SYNC_SET(void)	    //SYNC 定码
{
	if(IAPRead(0)!=0x55)	//判断遥控是否定码   0x55表示遥控已经定码
	{
	  IAPWrite(0x55,0);                //将遥控定码标志位写到EEPROM的0x0F00  0x55表示遥控已经定码
	  IAPWrite(RANKDOM_CNT&0x00FF,1);  //将码值低位写到EEPROM的0x0F01
	  IAPWrite(RANKDOM_CNT>>8,2);      //将码值高位写到EEPROM的0x0F02
	}
}

void SYNC_INIT(void)	//SYNC初始化
{
    SYNC_H=IAPRead(2);	//读EEPROM中的SYNC码值
	SYNC_L=IAPRead(1);		
}

//----------------------------------------------------------------------------

U8 spiReadWrite(U8 Byte)	  //SPI写操作
{										    
    unsigned char i;						

	EA = 0;
    for (i = 0; i < 8; i++)
    {
        MOSI = (Byte & 0x80);
		SCLK = 1;			  //一个上升沿传送数据
		Delay10us();
        Byte <<= 1;
        Byte |= MISO;
        SCLK = 0;
		Delay10us();
    }
	EA = 1;    

    return (Byte);
}

//----------------------------------------------------------------------------
void spiReadreg(U8 reg)		  //读寄存器操作
{
	SS = 0;
    spiReadWrite(READ | reg);
    RegH = spiReadWrite(0x00);
    RegL = spiReadWrite(0x00);
	SS = 1;
}

//----------------------------------------------------------------------------
void spiWriteReg(U8 reg, U8 byteH, U8 byteL)   //写寄存器操作
{
	SS = 0;
    spiReadWrite(WRITE & reg);
    spiReadWrite(byteH);
    spiReadWrite(byteL);
	SS = 1;
}

//----------------------------------------------------------------------------
void InitLT8900(void)
{
    RESET_N = 0;
    delayMs(100);
    RESET_N = 1;
    delayMs(200);
    SCLK = 0;
   
    spiWriteReg(0, 0x6f, 0xe0);
    spiWriteReg(1, 0x56, 0x81);
    spiWriteReg(2, 0x66, 0x17);
    spiWriteReg(4, 0x9c, 0xc9);
    spiWriteReg(5, 0x66, 0x37);
    spiWriteReg(7, 0x00, 0x00);
    spiWriteReg(8, 0x6c, 0x90);
    spiWriteReg(9, 0x48, 0x00);	  	 // 5.5dBm
    spiWriteReg(10, 0x7f, 0xfd);
    spiWriteReg(11, 0x00, 0x08);
    spiWriteReg(12, 0x00, 0x00);
    spiWriteReg(13, 0x48, 0xbd);
    
    spiWriteReg(22, 0x00, 0xff);
    spiWriteReg(23, 0x80, 0x05);
    spiWriteReg(24, 0x00, 0x67);
    spiWriteReg(25, 0x16, 0x59);
    spiWriteReg(26, 0x19, 0xe0);
    spiWriteReg(27, 0x13, 0x00);
    spiWriteReg(28, 0x18, 0x00);
    
    spiWriteReg(32, 0x50, 0x00);	 //SYNC LENGTH
    spiWriteReg(33, 0x3f, 0xc7);
    spiWriteReg(34, 0x20, 0x00);
    spiWriteReg(35, 0x43, 0x00);
   	//REG36~39:Choose unique sync words 
	//for each over-the-air network. 
	//Similar to a MAC address.
    spiWriteReg(36, 0x03, 0x80);
    spiWriteReg(37, 0x03, 0x80);
    spiWriteReg(38, 0x5a, 0x5a);
    spiWriteReg(39, 0x03, 0x80);
    //REG40:Configure FIFO flag, 4BIT sync threshold
	spiWriteReg(40, 0x44, 0x01);
    
	spiWriteReg(41, 0xB0, 0x00);  //crc on scramble off ,1st byte packet length ,auto ack off 
    spiWriteReg(42, 0xfd, 0xb0);  //
    spiWriteReg(43, 0x00, 0x0f);
    spiWriteReg(50, 0x00, 0x00);
	delayMs(200);
	
    spiWriteReg(7, 0x01, 0x00);
	delayMs(2);
    spiWriteReg(7, 0x00, 0x30);
}



void NOP_Delay(void)       //1us延时函数
  {
   _nop_();  //
  }

void Delay10us(void)       //N us延时函数
  {
   U16 i=0;
   for (i=0;i<10;i++)
   NOP_Delay();
  }
  
void Delay_1ms(void)       //1ms延时函数
  {
   U16 i;
   for (i=0;i<1140;i++);
  }
  
void delayMs(U16 n)        //N ms延时函数
  {
   U16 i=0;
   for (i=0;i<n;i++)
   Delay_1ms();
  }