#ifndef _UART_H_BAB
#define _UART_H_BAB

#include "BaseType.h"

void Uart_init(void);
void SendByte(u8 c);
void SendStr(u8 *pStr);
u8 GetByte(void);
u8 GetByte_NoWait(u8 *Output);
#endif
