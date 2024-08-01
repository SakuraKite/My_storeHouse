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
	 
	 delay_init();	    	 //��ʱ������ʼ��
	 NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);// �����ж����ȼ�����2
	 uart_init(115200);
	 
	 ESP8266_Init();	 
 
	while(OneNet_DevLink())			//����OneNET
	delay_ms(500);	
	 
	TIM_PWM_Init(199, 7199);//20ms
//	TIM3_Int_Init(9999,7199);//1s
//	MqttOnenet_Savedata(qqq);
		  USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);//�������ڽ����ж�
	  USART_Cmd(USART1, ENABLE);                    //ʹ�ܴ���1 
	
	while (1)
	{
//g_TFminiPlus_flag = 1;
		if (g_TFminiPlus_flag == 1)
		{
			OneNet_SendData();
			ESP8266_Clear();
			g_TFminiPlus_flag = 0;//Ϊ�´ν���������׼��
		}

	}
	 
	while(1);
 }

 
 
 /*
 onenet ��ƽ̨����ʱ ���ϴ�������һ��Ҫ������ƽ̨����Ĳ���
 onenetƽ̨���ڲ����·����ݣ�ƽ̨bug
 */
