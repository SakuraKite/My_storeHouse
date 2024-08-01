# include "control.h"

#define MUTEX_ZT(mutex) mutex > RUNNING ? RUNNING : SUSPENDING;

extern SMART_HOME Smart_home;

SMART_HOME Smart_home = {{OFF, SUSPENDING}, {45.1, 1, 1, 1, 0, 0}, {OFF, SUSPENDING}, {OFF, SUSPENDING}, {OFF, SUSPENDING}};
 
void EXTI0_IRQHandler(void)
{
  

//	Smart_home._mutex = MUTEX_ZT();
//	Smart_home._key = !Smart_home._key;
	
	EXTI_ClearITPendingBit(EXTI_Line0);  //清除EXTI0线路挂起位
}

void TIM3_IRQHandler(void)   //TIM3中断 
{

	if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET) //检查指定的TIM中断发生与否:TIM 中断源 
		{
//			OneNet_SendData();
//			ESP8266_Clear();
			static int count = 0;
//			switch(count++)
			switch(count++)
			{
				case 0: 				break;
				case 1: 			break;
				case 2: break;
			}
			count %= 3;

			TIM_ClearITPendingBit(TIM3, TIM_IT_Update  );  //清除TIMx的中断待处理位:TIM 中断源 

		}
}
