#include "pt.h"
#include "Uart.h"
#include "SystemTick.h"
#include "intrins.h"
void delay1s(void)   //误差 -0.000000000125us
{
    unsigned char a,b,c,n;
    for(c=169;c>0;c--)
        for(b=228;b>0;b--)
            for(a=142;a>0;a--);
    for(n=5;n>0;n--);
    _nop_();  //if Keil,require use intrins.h
}
sfr IAP_CONTR=0xc7;
u8 temp;
PT_THREAD(shell(struct pt *pt))
{ 
	PT_BEGIN(pt);
	Uart_init();
	SendStr("\r\n\r\nCommand List:\r\n");
	SendStr("v:get Protothreads Version\r\n");
	SendStr("r:reset cpu\r\n");
	while(1)
	{
		PT_WAIT_UNTIL(pt,GetByte_NoWait(&temp)==0); 
		switch(temp)
		{
			case 'v':
			case 'V':
			SendStr("Protothreads V1.4\r\n");
				break;
			case 'd'://使用自定义下载
			case 'D':	
			delay1s();
			IAP_CONTR=0x60; //soft reset system to run ISP monitor
				break;
			case 'r':
			case 'R':
				SendStr("Reset broad ...\r\n");
				((void (code *) (void)) 0x0000) ();
				break;
		}
		
	}
	PT_END(pt);
}

#define led P1

PT_THREAD(leds(struct pt *pt))
{
	PT_BEGIN(pt);
	
	while(1)
	{
		P0^=0x0F;
		P1^=0x0F;
		P2^=0x0F;
		set_delay(DELAY_1S);
		PT_WAIT_UNTIL(pt,Is_Time_up());
	}
	PT_END(pt);
}

struct pt pt1,pt2;
 
void main(void)
{
	EA=1;
	PT_INIT(&pt1);
	PT_INIT(&pt2);
	
	while(1)
	{
		shell(&pt1);
		leds(&pt2);
	}
}










