#include "SystemTick.h"

static u16 cnt;

void SystemTick_init(void)//@22.1184 for 10ms
{
    TMOD |= 0x01;
    TH0 = 0x0B8;
    TL0 = 0x00;

    ET0 = 1;
    TR0 = 1;
}
void set_delay(u16 _10ms)
{
	cnt=_10ms;
	SystemTick_init();
}

u8 Is_Time_up(void)
{
	if(cnt==0) return 1;
	else return 0;
}
void Timer0Interrupt(void) interrupt 1
{
    TH0 = 0x0B8;
    TL0 = 0x00;
    
	if(cnt!=0) cnt--;
	else TR0 = 0; //stop timer0
	
}
