#include "stdio.h"
#include "uart.h"
#include "delay.h"
#include "adc.h"
#include "time.h"
#include "control.h"

float watch_dog = 0;

extern struct DEMO Smart_home;
extern uint8_t g_TFminiPlus_flag;

char *qqq;
 int main(void)
 {	
	 int adcx = 0;
	 float temp = 0.0;
	 unsigned char *dataPtr = NULL;	
	 
	 delay_init();	    	 //延时函数初始化
	 NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);// 设置中断优先级分组2
	 uart_init(115200);
	 
	 ESP8266_Init();	 
 
	while(OneNet_DevLink())			//接入OneNET
	delay_ms(500);	
	 
	TIM_PWM_Init(199, 7199);//20ms
//	TIM3_Int_Init(9999,7199);//1s
//	MqttOnenet_Savedata(qqq);
		  USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);//开启串口接受中断
	  USART_Cmd(USART1, ENABLE);                    //使能串口1 
	
	while (1)
	{
//g_TFminiPlus_flag = 1;
		if (g_TFminiPlus_flag == 1)
		{
			OneNet_SendData();
			ESP8266_Clear();
			g_TFminiPlus_flag = 0;//为下次接收数据做准备
		}

	}
	 
	while(1);
 }

 
 
 /*
 onenet 云平台开发时 ，上传的数据一定要符合云平台定义的步长
 onenet平台现在不能下发数据，平台bug
 */
