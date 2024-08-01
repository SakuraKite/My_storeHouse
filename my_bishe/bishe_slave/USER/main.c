#include "stdio.h"
#include "uart.h"
#include "esp8266.h"
#include "onenet.h"
#include "delay.h"
#include "adc.h"
#include "time.h"
#include "control.h"
#include "OLED.h"
#include "rgb.h"
#include "bj.h"
#include "wendu.h"

float watch_dog = 0;

extern SMART_HOME Smart_home;

#define OPEN_FAN GPIO_SetBits(GPIOB,GPIO_Pin_11)
#define OFF_FAN GPIO_ResetBits(GPIOB,GPIO_Pin_11)
//从机

void GPIO_Init_Part(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_11;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; //设置为推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
 	GPIO_Init(GPIOB, &GPIO_InitStructure);//初始化GPIOBA	
	GPIO_ResetBits(GPIOB,GPIO_Pin_11);				 
}

char *qqq;
//float temperature = 0;
//	 u8 humidity = 0;
 int main(void)
 {	
	 int adcx = 0;
	 float temp = 0.0;
	 int _guangqiang = 0;
	 
	 
	 
	 delay_init();	    	 //延时函数初始化
	 NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);// 设置中断优先级分组2
	 GPIO_Init_Part();
	 uart_init(115200);
	
	Adc_Init();
	 
	TIM_PWM_Init(199, 7199);//20ms   舵机
	
	TIM3_Int_Init(9999,7199);//1s
//	 
//	 delay_ms(1000);
	OLED_Init();
//	 delay_ms(1000);

	WS2812_Init();
//	 LED_Mode1(100);
	 stepper_init();
//	 conter_stepper1(3200, 360*2, 800, 1);
	 AHT10Init();
	 
	
	 
	 OLED_ShowString(0,0, (char *)("Window_ZT: "), OLED_6X8);
	OLED_ShowString(0,8, (char *)("humdity: "), OLED_6X8);
	OLED_ShowString(0,16, (char *)("wendu: "), OLED_6X8);
	OLED_ShowString(0,24, (char *)("chaunglian: "), OLED_6X8);
	OLED_ShowString(0,32, (char *)("fan: "), OLED_6X8);
	OLED_ShowString(0,40, (char *)("tu_humdity: "), OLED_6X8);
	OLED_ShowString(0,48, (char *)("WS2812: "), OLED_6X8);
OLED_Update();

//	while (1)
//	{
//	OLED_ShowString(80, 0, (char *)"OPEN", OLED_6X8);
//			OLED_UpdateArea(80, 0, 30, 6);
//		OLED_ShowString(80, 8, (char *)"OPEN ", OLED_6X8);
//			OLED_UpdateArea(80, 8, 30, 6);
//		delay_ms(1000);
//		OLED_ShowString(80, 0, (char *)"OFF ", OLED_6X8);
//			OLED_UpdateArea(80, 0, 30, 6);
//		OLED_ShowString(80, 8, (char *)"OFF ", OLED_6X8);
//			OLED_UpdateArea(80, 8, 30, 6);
//		delay_ms(1000);
//		
//	}
	
	
	while (1)
	{
		adcx=Get_Adc_Average(ADC_Channel_1,10);
		temp=(float)adcx*(3.3/4096);
		
		watch_dog = temp;
		
		
		
		
		if (g_oledflg == 1){
			g_oledflg = 0;
			AHT10ReadData(&Smart_home._data.temperature_one, &Smart_home._data.humidity_zero);
			OLED_ShowFloatNum(80, 40, temp, 2, 1, OLED_6X8);
			OLED_UpdateArea(80, 40, 30, 6);
			OLED_ShowFloatNum(80, 16, Smart_home._data.temperature_one, 2, 1, OLED_6X8);
			OLED_UpdateArea(80, 16, 30, 6);
			OLED_ShowNum(80, 8, Smart_home._data.humidity_zero, 2, OLED_6X8);
			OLED_UpdateArea(80, 8, 30, 6);
		}
		
//		if (_guangqiang != GUANGMING_ZT)
//		{
//			_guangqiang = GUANGMING_ZT;
//			//光强太强，之后干什么，关窗，或者关窗帘
//		}
		//窗户
		if (Smart_home.window._key == OPEN && Smart_home.window._mutex == RUNNING)
		{
			Smart_home._data.window_ZT_zero = 1;
			Smart_home.window._mutex = SUSPENDING;
			TIM_SetCompare3(TIM4, 15);
			delay_ms(500);
			OLED_ShowString(80, 0, (char *)"OPEN", OLED_6X8);
			OLED_UpdateArea(80, 0, 30, 6);
		}
		else if (Smart_home.window._key == OFF && Smart_home.window._mutex == RUNNING)
		{
			Smart_home._data.window_ZT_zero = 0;
			Smart_home.window._mutex = SUSPENDING;
			TIM_SetCompare3(TIM4, 5);
			delay_ms(500);
			OLED_ShowString(80, 0, (char *)"OFF ", OLED_6X8);
			OLED_UpdateArea(80, 0, 30, 6);
		}
		//窗帘
		if (Smart_home.chuanglian._key == OPEN && Smart_home.chuanglian._mutex == RUNNING){
			Smart_home._data.chuanglian_ZT_zero = 1;
			Smart_home.chuanglian._mutex = SUSPENDING;
			conter_stepper1(3200, 360*2, 800, 1);
			OLED_ShowString(80, 24, (char *)"OPEN", OLED_6X8);
			OLED_UpdateArea(80, 24, 30, 6);
		}else if (Smart_home.chuanglian._key == OFF && Smart_home.chuanglian._mutex == RUNNING){
			Smart_home._data.chuanglian_ZT_zero = 0;
			Smart_home.chuanglian._mutex = SUSPENDING;
			conter_stepper1(3200, 360*2, 800, 0);
			OLED_ShowString(80, 24, (char *)"OFF ", OLED_6X8);
			OLED_UpdateArea(80, 24, 30, 6);
		}
		//风扇
		if (Smart_home.fan._key == OPEN && Smart_home.fan._mutex == RUNNING){
			Smart_home._data.fan_ZT_zero = 1;
			Smart_home.fan._mutex = SUSPENDING;
			OPEN_FAN;
			OLED_ShowString(80, 32, (char *)"OPEN", OLED_6X8);
			OLED_UpdateArea(80, 32, 30, 6);
		}else if (Smart_home.fan._key == OFF && Smart_home.fan._mutex == RUNNING){
			Smart_home._data.fan_ZT_zero = 0;
			Smart_home.fan._mutex = SUSPENDING;
			OFF_FAN;
			OLED_ShowString(80, 32, (char *)"OFF ", OLED_6X8);
			OLED_UpdateArea(80, 32, 30, 6);
		}
		//LED
		if (Smart_home.led._key == OPEN && Smart_home.led._mutex == RUNNING){
			Smart_home._data.led_ZT_zero = 1;
			Smart_home.led._mutex = SUSPENDING;
			LED_Mode1(100);
			OLED_ShowString(80, 48, (char *)"OPEN", OLED_6X8);
			OLED_UpdateArea(80, 48, 30, 6);
		}else if (Smart_home.led._key == OFF && Smart_home.led._mutex == RUNNING){
			Smart_home._data.led_ZT_zero = 0;
			Smart_home._data.chuanglian_ZT_zero = 0;
			Smart_home._data.window_ZT_zero = 0;
			Smart_home.window._key = OFF, Smart_home.window._mutex = SUSPENDING;
			Smart_home.chuanglian._key = OFF, Smart_home.chuanglian._mutex = SUSPENDING;
			Smart_home.led._key = OFF, Smart_home.led._mutex = SUSPENDING;

			Reset_RGBData();
			conter_stepper1(3200, 360*2, 800, 0);
			TIM_SetCompare3(TIM4, 5);
			delay_ms(500);
			
			OLED_ShowString(80, 48, (char *)"OFF ", OLED_6X8);
			OLED_UpdateArea(80, 48, 30, 6);
			OLED_ShowString(80, 24, (char *)"OFF ", OLED_6X8);
			OLED_UpdateArea(80, 24, 30, 6);
			OLED_ShowString(80, 0, (char *)"OFF ", OLED_6X8);
			OLED_UpdateArea(80, 0, 30, 6);
		}
	}
	 
	while(1);
 }

 
 
 /*
 onenet 云平台开发时 ，上传的数据一定要符合云平台定义的步长
 
 */
