#ifndef __UART_H
#define __UART_H	

#include "sys.h"
#include "delay.h"
#include "string.h"
  
/***函数声明***/	
void uart_init(u32 bound);
unsigned char color_Update(void); //跟新数据
void USART1_Send_Str(unsigned char *s);



#endif
