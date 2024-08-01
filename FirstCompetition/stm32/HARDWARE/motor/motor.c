# include "motor.h"


void ALL_RCC_GPIO_Init(void)
{
	    GPIO_InitTypeDef GPIO_InitStructure;
     //SCL  D0
	 RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2 | RCC_APB1Periph_TIM3 | RCC_APB1Periph_TIM4 | RCC_APB1Periph_TIM5 | RCC_APB1Periph_TIM6, ENABLE);
     RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOC | RCC_APB2Periph_AFIO, ENABLE);
	
	 GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);
	 GPIO_PinRemapConfig(GPIO_FullRemap_TIM2 , ENABLE);
	
     GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
     GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	
		GPIO_InitStructure.GPIO_Pin = SCL_GPIO_Pin;
     GPIO_Init(SCL_GPIO,&GPIO_InitStructure);    
		GPIO_SetBits(SCL_GPIO,SCL_GPIO_Pin);
     //SDA  D1
	
		GPIO_InitStructure.GPIO_Pin = SDA_GPIO_Pin;
    GPIO_Init(SDA_GPIO,&GPIO_InitStructure);    
		GPIO_SetBits(SDA_GPIO,SDA_GPIO_Pin);
	
  //TIM2
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;//复用推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	
	//PA2 PA3 PA15
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	//PB3
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3 | GPIO_Pin_10 | GPIO_Pin_11;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
  //TIM3
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//浮空输入
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
  //TIM4
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
  //光电
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//浮空输入
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5;
	GPIO_Init(GPIOC, &GPIO_InitStructure);
	GPIO_ResetBits(GPIOC, GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5);
	
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOC,GPIO_PinSource1);
		
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	GPIO_ResetBits(GPIOA, GPIO_Pin_0);
}


/*
** discritpion: 限幅函数
*/
void Limit(float *motoA, float *motoB)
{
	if (*motoA > PWM_MAX) *motoA = PWM_MAX;
	if (*motoA < PWM_MIN) *motoA = PWM_MIN;
	
	if (*motoB > PWM_MAX) *motoB = PWM_MAX;
	if (*motoB < PWM_MIN) *motoB = PWM_MIN;
}



/*
** discription: 装载函数
** moto1 左电机 moto2 右电机
** 入口参数为PID运算完后的最终PWM值
*/
void Load(float moto1, float moto2)
{
	/**********左轮************/
	if (moto1 >= 0)
	{
		TIM_SetCompare1(TIM2, 0);
		TIM_SetCompare2(TIM2, (int)moto1);
	}
	else
	{
		TIM_SetCompare1(TIM2, -(int)moto1);
		TIM_SetCompare2(TIM2, 0);
	}
	
	/***********右轮***************/
	if (moto2 >= 0)
	{
		TIM_SetCompare3(TIM2, 0);
		TIM_SetCompare4(TIM2, (int)moto2);
	}
	else
	{
		TIM_SetCompare3(TIM2,  -(int)moto2);
		TIM_SetCompare4(TIM2, 0);

	}
	
	
}
