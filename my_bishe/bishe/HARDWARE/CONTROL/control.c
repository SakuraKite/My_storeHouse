# include "control.h"

#define MUTEX_ZT(mutex) mutex > RUNNING ? RUNNING : SUSPENDING;

extern SMART_HOME Smart_home;

SMART_HOME Smart_home = {{OFF, SUSPENDING}, {45.1, 1, 1, 1, 0, 0}, {OFF, SUSPENDING}, {OFF, SUSPENDING}, {OFF, SUSPENDING}};
 
void EXTI0_IRQHandler(void)
{
  

//	Smart_home._mutex = MUTEX_ZT();
//	Smart_home._key = !Smart_home._key;
	
	EXTI_ClearITPendingBit(EXTI_Line0);  //���EXTI0��·����λ
}

void TIM3_IRQHandler(void)   //TIM3�ж� 
{

	if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET) //���ָ����TIM�жϷ������:TIM �ж�Դ 
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

			TIM_ClearITPendingBit(TIM3, TIM_IT_Update  );  //���TIMx���жϴ�����λ:TIM �ж�Դ 

		}
}
