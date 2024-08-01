# include "control.h"

#define MUTEX_ZT(mutex) mutex > RUNNING ? RUNNING : SUSPENDING;

extern SMART_HOME Smart_home;

SMART_HOME Smart_home = {{OFF, SUSPENDING}, {36.1, 1, 0, 1, 1, 1}, {OFF, SUSPENDING}, {OFF, SUSPENDING}, {OFF, SUSPENDING}};
 
void EXTI0_IRQHandler(void)
{

	Smart_home.window._mutex= MUTEX_ZT(Smart_home.window._mutex);
	Smart_home.window._key = !Smart_home.window._key;

	EXTI_ClearITPendingBit(EXTI_Line0);  //清除EXTI0线路挂起位
}

void EXTI9_5_IRQHandler(void)
{
	if(EXTI_GetITStatus(EXTI_Line9)!=RESET){
		Smart_home.chuanglian._mutex= MUTEX_ZT(Smart_home.chuanglian._mutex);
		Smart_home.chuanglian._key = !Smart_home.chuanglian._key;
		EXTI_ClearITPendingBit(EXTI_Line9);
	}else if (EXTI_GetITStatus(EXTI_Line7)!=RESET){
		Smart_home.fan._mutex= MUTEX_ZT(Smart_home.fan._mutex);
		Smart_home.fan._key = !Smart_home.fan._key;
		EXTI_ClearITPendingBit(EXTI_Line7);
	}else if (EXTI_GetITStatus(EXTI_Line8)!=RESET){
		Smart_home.led._mutex= MUTEX_ZT(Smart_home.led._mutex);
		Smart_home.led._key = !Smart_home.led._key;
		EXTI_ClearITPendingBit(EXTI_Line8);
	}
	
}

char g_oledflg = 0;


void TIM3_IRQHandler(void)   //TIM3中断 
	//用于获取sensor数据、放大sensor数据
{
//	unsigned char read_O2[]={0x01,0x03,0x00,0x00,0x00,0x06,0xc5,0xc8};
//	unsigned char read_N_N[]={0x02,0x03,0x00,0x00,0x00,0x01,0x84,0x39};	
//	unsigned char read_PH_TEMP[]={0x03,0x03,0x00,0x00,0x00,0x02,0xc5,0xe9};
	if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET) //检查指定的TIM中断发生与否:TIM 中断源 
		{
			Wireless_Send(Smart_home._data);
			static int count = 0;
//			switch(count++)
			switch(count++)
			{
				case 0: 		g_oledflg = 1;		break;
				case 1: 			break;
				case 2: break;
			}
			count %= 3;

			TIM_ClearITPendingBit(TIM3, TIM_IT_Update  );  //清除TIMx的中断待处理位:TIM 中断源 

		}
}



