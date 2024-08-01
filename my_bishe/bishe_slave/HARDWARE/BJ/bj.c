#include "bj.h"

void stepper_init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	
	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Pin= 	GPIO_Pin_7
							  | GPIO_Pin_9;
	GPIO_InitStruct.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStruct);
	
	
	
	//¹âÃôµÄ
	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_IN_FLOATING;
	GPIO_InitStruct.GPIO_Pin= 	GPIO_Pin_10;
	GPIO_Init(GPIOB,&GPIO_InitStruct);
	
}


void conter_stepper1(int tim,float angle,float xifen,int dir)
{
	int i,n;
	n=(int)(angle*(xifen/360));

	DIR1=dir;
//	ENA1=1;
	for(i=n;i>0;i--)
{

		PUL1=1;
		delay_us(tim/2);
		PUL1=0;
		delay_us(tim/2);
}		
//	ENA1=0;
	
}



