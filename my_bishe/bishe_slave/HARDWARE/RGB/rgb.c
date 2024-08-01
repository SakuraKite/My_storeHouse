#include "stm32f10x.h"
#include "rgb.h"
#include "delay.h"

extern uint8_t RGB_Data[24*3]={0};

void Delay_L(void)
{	
	__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();//__NOP();__NOP();
//	__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();
//	__NOP();__NOP();__NOP();__NOP();__NOP();
	
}
void Delay_H(void)
{
	__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();
	__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();
	__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();
	__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();
	__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();
	__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();
	__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();
//	__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();
//	__NOP();	
}
void WS_0(void)
{
	GPIOB->BSRR = GPIO_Pin_1;
	Delay_L();
	GPIOB->BRR = GPIO_Pin_1;
	Delay_H();
}
void WS_1(void)
{
	GPIOB->BSRR = GPIO_Pin_1;
	Delay_H();
	GPIOB->BRR = GPIO_Pin_1;
	Delay_L();
}
void WS_RESET(void)
{
	delay_us(180);
}
void WS2812_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;                             
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	delay_ms(100);
	LED_OFF();
	delay_ms(100);
}
//GRB高位先发
void WS_SetRGB(uint8_t W_i,uint8_t W_r,uint8_t W_g,uint8_t W_b)
{
	RGB_Data[(W_i-1)*3]=W_g;
	RGB_Data[(W_i-1)*3+1]=W_r;
	RGB_Data[(W_i-1)*3+2]=W_b;
}
void Send_RGBData(void)
{
	uint8_t i;
	for(i=0;i<24*3;i++)
	{		
		if(RGB_Data[i]&(0x80)!=0)WS_1();else WS_0();
		if(RGB_Data[i]&(0x40)!=0)WS_1();else WS_0();
		if(RGB_Data[i]&(0x20)!=0)WS_1();else WS_0();
		if(RGB_Data[i]&(0x10)!=0)WS_1();else WS_0();
		if(RGB_Data[i]&(0x08)!=0)WS_1();else WS_0();
		if(RGB_Data[i]&(0x04)!=0)WS_1();else WS_0();
		if(RGB_Data[i]&(0x02)!=0)WS_1();else WS_0();
		if(RGB_Data[i]&(0x01)!=0)WS_1();else WS_0();
	}
	WS_RESET();
}
void Reset_RGBData(void)
{
	for(uint8_t i=0;i<24*3;i++)
	{
		RGB_Data[i]=0;
	}
	Send_RGBData();
}
void LED_Set(uint8_t Num,uint8_t colour,uint16_t time)
{
	if(colour>6)
	{
		colour=colour-6;
	}
	switch(colour)
	{
		case 1:	WS_SetRGB(Num,255,0,0);	
				Send_RGBData();
				delay_ms(time);
				break;			
		case 2: WS_SetRGB(Num,255,255,0);	
				Send_RGBData();
				delay_ms(time);
				break;	
		case 3: WS_SetRGB(Num,0,255,0);	
				Send_RGBData();
				delay_ms(time);
				break;
		case 4: WS_SetRGB(Num,0,255,255);
				Send_RGBData();
				delay_ms(time);
				break;
		case 5:	WS_SetRGB(Num,0,0,255);	
				Send_RGBData();
				delay_ms(time);
				break;
		case 6: WS_SetRGB(Num,255,0,255);	
				Send_RGBData();
				delay_ms(time);
				break;
	}		
}



void LED_Red(void)
{
	WS_0();//g
	WS_0();
	WS_0();
	WS_0();
	WS_0();
	WS_0();
	WS_0();
	WS_0();
	//g+r=??
	WS_1();//r
	WS_1();
	WS_1();
	WS_1();
	WS_1();
	WS_1();
	WS_1();
	WS_1();
	//r+b=×? 
	WS_0();//b
	WS_0();
	WS_0();
	WS_0();
	WS_0();
	WS_0();
	WS_0();
	WS_0();
	//g+b=?à
	
}
void LED_Green(void)
{
	WS_1();//g
	WS_1();
	WS_1();
	WS_1();
	WS_1();
	WS_1();
	WS_1();
	WS_1();
	//g+r=??
	WS_0();//r
	WS_0();
	WS_0();
	WS_0();
	WS_0();
	WS_0();
	WS_0();
	WS_0();
	//r+b=×? 
	WS_0();//b
	WS_0();
	WS_0();
	WS_0();
	WS_0();
	WS_0();
	WS_0();
	WS_0();
	//g+b=?à
	
}
void LED_Blue(void)
{
	WS_0();//g
	WS_0();
	WS_0();
	WS_0();
	WS_0();
	WS_0();
	WS_0();
	WS_0();
	//g+r=??
	WS_0();//r
	WS_0();
	WS_0();
	WS_0();
	WS_0();
	WS_0();
	WS_0();
	WS_0();
	//r+b=×? 
	WS_1();//b
	WS_1();
	WS_1();
	WS_1();
	WS_1();
	WS_1();
	WS_1();
	WS_1();
	//g+b=?à
	
}
void LED_Yellow(void)
{
	WS_1();//g
	WS_1();
	WS_1();
	WS_1();
	WS_1();
	WS_1();
	WS_1();
	WS_1();
	//g+r=??
	WS_1();//r
	WS_1();
	WS_1();
	WS_1();
	WS_1();
	WS_1();
	WS_1();
	WS_1();
	//r+b=×? 
	WS_0();//b
	WS_0();
	WS_0();
	WS_0();
	WS_0();
	WS_0();
	WS_0();
	WS_0();
	//g+b=?à
	
}
void LED_Purple(void)
{
	WS_0();//g
	WS_0();
	WS_0();
	WS_0();
	WS_0();
	WS_0();
	WS_0();
	WS_0();
	//g+r=??
	WS_1();//r
	WS_1();
	WS_1();
	WS_1();
	WS_1();
	WS_1();
	WS_1();
	WS_1();
	//r+b=×? 
	WS_1();//b
	WS_1();
	WS_1();
	WS_1();
	WS_1();
	WS_1();
	WS_1();
	WS_1();
	//g+b=?à
	
}
void LED_Cyan(void)
{
	WS_1();//g
	WS_1();
	WS_1();
	WS_1();
	WS_1();
	WS_1();
	WS_1();
	WS_1();
	//g+r=??
	WS_0();//r
	WS_0();
	WS_0();
	WS_0();
	WS_0();
	WS_0();
	WS_0();
	WS_0();
	//r+b=×? 
	WS_1();//b
	WS_1();
	WS_1();
	WS_1();
	WS_1();
	WS_1();
	WS_1();
	WS_1();
	//g+b=?à
	
}
void LED_OFF(void)
{
	WS_0();
	WS_0();
	WS_0();
	WS_0();
	WS_0();
	WS_0();
	WS_0();
	WS_0();
	
	WS_0();
	WS_0();
	WS_0();
	WS_0();
	WS_0();
	WS_0();
	WS_0();
	WS_0();
	
	WS_0();
	WS_0();
	WS_0();
	WS_0();
	WS_0();
	WS_0();
	WS_0();
	WS_0();
}

void LED_Switch(uint8_t Colour,uint8_t Switch)
{
	if(Switch==1)
	{
		switch(Colour)
		{
			case 1:LED_Red();break;//oì
			case 2:LED_Green();break;//?ì
			case 3:LED_Blue();break;//à?
			case 4:LED_Yellow();break;//??
			case 5:LED_Purple();break;//×?
			case 6:LED_Cyan();break;//?à
		}
	}
	else
	{
		LED_OFF();
	}

}
void LED_Mode1(uint16_t time)
{
	for(uint8_t i=0;i<4;i++)
	{		
		WS_SetRGB(1+i*6,255,0,0);	
		Send_RGBData();
		delay_ms(time);
		WS_SetRGB(2+i*6,255,255,0);	
		Send_RGBData();
		delay_ms(time);
		WS_SetRGB(3+i*6,0,255,0);	
		Send_RGBData();
		delay_ms(time);
		WS_SetRGB(4+i*6,0,255,255);	
		Send_RGBData();
		delay_ms(time);
		WS_SetRGB(5+i*6,0,0,255);	
		Send_RGBData();
		delay_ms(time);
		WS_SetRGB(6+i*6,255,0,255);	
		Send_RGBData();
		delay_ms(time);
	}
	for(uint8_t i=0;i<4;i++)
	{		
		WS_SetRGB(1+i*6,255,255,0);	
		Send_RGBData();
		delay_ms(time);
		WS_SetRGB(2+i*6,0,255,0);	
		Send_RGBData();
		delay_ms(time);
		WS_SetRGB(3+i*6,0,255,255);	
		Send_RGBData();
		delay_ms(time);
		WS_SetRGB(4+i*6,0,0,255);	
		Send_RGBData();
		delay_ms(time);
		WS_SetRGB(5+i*6,255,0,255);	
		Send_RGBData();
		delay_ms(time);
		WS_SetRGB(6+i*6,255,0,0);	
		Send_RGBData();
		delay_ms(time);
	}
	for(uint8_t i=0;i<4;i++)
	{		
		
		WS_SetRGB(1+i*6,0,255,0);	
		Send_RGBData();
		delay_ms(time);
		WS_SetRGB(2+i*6,0,255,255);	
		Send_RGBData();
		delay_ms(time);
		WS_SetRGB(3+i*6,0,0,255);	
		Send_RGBData();
		delay_ms(time);
		WS_SetRGB(4+i*6,255,0,255);	
		Send_RGBData();
		delay_ms(time);
		WS_SetRGB(5+i*6,255,0,0);	
		Send_RGBData();
		delay_ms(time);
		WS_SetRGB(6+i*6,255,255,0);	
		Send_RGBData();
		delay_ms(time);
	}
	for(uint8_t i=0;i<4;i++)
	{				
		WS_SetRGB(1+i*6,0,255,255);	
		Send_RGBData();
		delay_ms(time);
		WS_SetRGB(2+i*6,0,0,255);	
		Send_RGBData();
		delay_ms(time);
		WS_SetRGB(3+i*6,255,0,255);	
		Send_RGBData();
		delay_ms(time);
		WS_SetRGB(4+i*6,255,0,0);	
		Send_RGBData();
		delay_ms(time);
		WS_SetRGB(5+i*6,255,255,0);	
		Send_RGBData();
		delay_ms(time);
		WS_SetRGB(6+i*6,0,255,0);	
		Send_RGBData();
		delay_ms(time);
	}
	for(uint8_t i=0;i<4;i++)
	{						
		WS_SetRGB(1+i*6,0,0,255);	
		Send_RGBData();
		delay_ms(time);
		WS_SetRGB(2+i*6,255,0,255);	
		Send_RGBData();
		delay_ms(time);
		WS_SetRGB(3+i*6,255,0,0);	
		Send_RGBData();
		delay_ms(time);
		WS_SetRGB(4+i*6,255,255,0);	
		Send_RGBData();
		delay_ms(time);
		WS_SetRGB(5+i*6,0,255,0);	
		Send_RGBData();
		delay_ms(time);
		WS_SetRGB(6+i*6,0,255,255);	
		Send_RGBData();
		delay_ms(time);
	}
}
void LED_Mode2(uint16_t time)
{
	for(uint8_t i=0;i<4;i++)
	{		
		WS_SetRGB(1+i*6,255,0,0);	
		Send_RGBData();
		delay_ms(time);
		WS_SetRGB(2+i*6,255,255,0);	
		Send_RGBData();
		delay_ms(time);
		WS_SetRGB(3+i*6,0,255,0);	
		Send_RGBData();
		delay_ms(time);
		WS_SetRGB(4+i*6,0,255,255);	
		Send_RGBData();
		delay_ms(time);
		WS_SetRGB(5+i*6,0,0,255);	
		Send_RGBData();
		delay_ms(time);
		WS_SetRGB(6+i*6,255,0,255);	
		Send_RGBData();
		delay_ms(time);
	}
}
void LED_Mode3(uint16_t time)
{
	for(uint8_t i=0;i<6;i++)
	{
		LED_Set(1,1+i,time);
		LED_Set(2,2+i,time);
		LED_Set(3,3+i,time);
		LED_Set(4,4+i,time);
		LED_Set(5,5+i,time);
		LED_Set(6,6+i,time);
		LED_Set(7,1+i,time);
		LED_Set(8,2+i,time);
		LED_Set(9,3+i,time);
		LED_Set(10,4+i,time);
		LED_Set(11,5+i,time);
		LED_Set(12,6+i,time);
		LED_Set(13,1+i,time);
		LED_Set(14,2+i,time);
		LED_Set(15,3+i,time);
		LED_Set(16,4+i,time);
		LED_Set(17,5+i,time);
		LED_Set(18,6+i,time);
		LED_Set(19,1+i,time);
		LED_Set(20,2+i,time);
		LED_Set(21,3+i,time);
		LED_Set(22,4+i,time);
		LED_Set(23,5+i,time); 
		LED_Set(24,6+i,time);
	}	
}
void LED_Mode4(uint16_t time)
{
	LED_Set(1,1,time);
}










