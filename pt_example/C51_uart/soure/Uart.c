#include "Uart.h"

void Uart_init(void)
{
    TMOD = 0x20;
    SCON = 0x50;
    TH1 = 0xFA;
    TL1 = TH1;
    PCON = 0x00;
    //EA = 1;
    //ES = 1;
    TR1 = 1;
}

void SendByte(u8 c)
{
    SBUF = c;
    while(TI==0);
    TI = 0;
}

void SendStr(u8 *pStr)
{
	while(*pStr)
	{
		SendByte(*pStr++);
	}
}

u8 GetByte(void)
{
	while(RI);
	RI=0;
	return SBUF;
}

u8 GetByte_NoWait(u8 *pOutput)
{
	if(RI==1)
	{
		*pOutput=SBUF;
		RI=0;
		return 0;
	}
	
	return 1;
}