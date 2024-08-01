# include "timercontrol.h"



////占空比
//int PWM_L = qianjin_PWM_Left;
//int PWM_R = qianjin_PWM_Right;

//占空比
int PWM_L = qianjin_PWM_Left;
int PWM_R = qianjin_PWM_Right;

int qianjin_time = 0;
int Road_time = 0;
int Road_timee = 0;
int Road_timeer = 0;
int Road_timeeeer = 0;
int Road_timeeerr = 0;

int Road_Count = -7;//-3
int stop_time = 0;
int stop_time_r = 0;
int zhuang_time_r = 0;
int Grap_time = 0;
int Grap_N_time = 0;
int Hou_time = 0;
int Hou_timee = 0;
int Hou_timeee = 0;
int Close_XJ_time = 0;
int Close_XJ_timee = 0;
int BJ_fall_time = 0;
int BJ_fall_timee = 0;
int BJ_up_time = 0;
int BJ_up_timee = 0;
int Wukuai_grap_time = 0;
int Wukuai_release_time = 0;
int Mapan_zhuang_time = 0;
int P_time = 0;
int Forward_time = 0;
//int tiao_time = 0;


//标志位
char stop_flag = 0;
char qianjin_flag = 0;
char zhuangwang_flag = 0;
//char Road_flag = 0;
//char Zhuang_Xiang_flag = 0;

//输出4路pwm控制电机
// 注意 TIM2映射为完全映射，引脚都改变了。
void TIM2_PWM_Init(u32 arr, u32 psc)
{
		//GPIO_InitTypeDef GPIO_InitStruct;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
	TIM_OCInitTypeDef TIM_OCInitStruct;
	
//	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO | RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB, ENABLE);//重映射一定要开AFIO时钟
	
//	//引脚功能擦除
//	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);
//	GPIO_PinRemapConfig(GPIO_FullRemap_TIM2,    ENABLE);
//	
//	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;//复用推挽输出
//	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
//	
//	//PA15
//	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_15;
//	GPIO_Init(GPIOA, &GPIO_InitStruct);
//	
//	//PB3 PB10 PB11
//	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_3 | GPIO_Pin_10 | GPIO_Pin_11;
//	GPIO_Init(GPIOB, &GPIO_InitStruct);
	
	//pwm输出周期初始化
		TIM_TimeBaseStructInit(&TIM_TimeBaseInitStruct);
		TIM_TimeBaseInitStruct.TIM_Period = arr;
		TIM_TimeBaseInitStruct.TIM_Prescaler = psc;
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseInitStruct);
	
	//TIM2_CH1 TIM2_CH2 TIM2_CH3 TIM2_CH4通道初始化
		TIM_OCInitStruct.TIM_OCMode = TIM_OCMode_PWM1;//pwm输出方式为PWM1
		TIM_OCInitStruct.TIM_Pulse = 0;//初始脉冲0
		TIM_OCInitStruct.TIM_OCPolarity =TIM_OCPolarity_High;//输出极性高
		TIM_OCInitStruct.TIM_OutputState = TIM_OutputState_Enable;//输出使能
	
	TIM_OC1Init(TIM2, &TIM_OCInitStruct);
	TIM_OC2Init(TIM2, &TIM_OCInitStruct);
	TIM_OC3Init(TIM2, &TIM_OCInitStruct);
	TIM_OC4Init(TIM2, &TIM_OCInitStruct);
	
	TIM_OC1PreloadConfig(TIM2, TIM_OCPreload_Enable);//CH1预装载使能
	TIM_OC2PreloadConfig(TIM2, TIM_OCPreload_Enable);//CH2预装载使能
	TIM_OC3PreloadConfig(TIM2, TIM_OCPreload_Enable);//CH3预装载使能
	TIM_OC4PreloadConfig(TIM2, TIM_OCPreload_Enable);//CH4预装载使能
	
	TIM_ARRPreloadConfig(TIM2, ENABLE);//使能TIM2自动重装载寄存器
	
	TIM_Cmd(TIM2, ENABLE);//使能TIM2
}

/*
** function : 左轮编码器的定时器初始化函数
** discription: 输入引脚为PA6 PA7
*/
void TIM3_INT_Init(void)
{
	//GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	TIM_ICInitTypeDef TIM_ICInitStructure;
	
//	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
//	
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//浮空输入
//	
//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
//	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	//计数初始化
		TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
		TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up; // 向上计数
		TIM_TimeBaseInitStructure.TIM_Period = 65535;
		TIM_TimeBaseInitStructure.TIM_Prescaler = 0;
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseInitStructure);
	
	//捕获通道TIM3_IC1 TIM3_IC2初始化
		TIM_ICStructInit(&TIM_ICInitStructure);
		TIM_ICInitStructure.TIM_Channel = TIM_Channel_1 | TIM_Channel_2;
		TIM_ICInitStructure.TIM_ICFilter = 6;//滤波
	TIM_ICInit(TIM3, &TIM_ICInitStructure);
	
	/* 编码器  不反相：捕获发生在IC1的上升沿 */
	TIM_EncoderInterfaceConfig(TIM3, TIM_EncoderMode_TI12, TIM_ICPolarity_Rising, TIM_ICPolarity_Rising);
	
	TIM_ClearFlag(TIM3, TIM_FLAG_Update);//清除溢出标志位
	TIM_SetCounter(TIM3, 0);//设置定时器计数值
	TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);
	
	TIM_Cmd(TIM3, ENABLE);
	
}



/*
** function : 右轮编码器的定时器初始化函数
** discription: 输入引脚为PB6 PB7
*/
void TIM4_INT_Init(void)
{
//	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
//	GPIO_InitTypeDef GPIO_InitStruct;
//	TIM_ICInitTypeDef TIM_ICInitStruct;
//  
//	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4 ,ENABLE);  // 开启定时器时钟
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO,ENABLE); // 开启GPIO时钟
//	
//	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;    // 浮空输入
//	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;   // 编码器2:PB6/PB7
//	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
//	GPIO_Init(GPIOB ,&GPIO_InitStruct);	
//  
//	TIM_TimeBaseStructInit(&TIM_TimeBaseInitStruct);
//	TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1;      // 不分频
//	TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;  // 向上计数
//	TIM_TimeBaseInitStruct.TIM_Period = 65535;                    // 重装载值65535
//	TIM_TimeBaseInitStruct.TIM_Prescaler = 0;                     // 分频系数0
//	TIM_TimeBaseInit(TIM4,&TIM_TimeBaseInitStruct);
//  
//	// 编码器配置函数：定时器4，模式3，上升沿
//	TIM_EncoderInterfaceConfig(TIM4,TIM_EncoderMode_TI12,TIM_ICPolarity_Rising,TIM_ICPolarity_Rising);  
//  
//	TIM_ICStructInit(&TIM_ICInitStruct);
//	TIM_ICInitStruct.TIM_ICFilter = 10;       // 滤波器设置为10
//	TIM_ICInit(TIM4,&TIM_ICInitStruct);
//  
//	TIM_ClearFlag(TIM4,TIM_FLAG_Update);      // 清除定时器溢出更新标志位
//	TIM_ITConfig(TIM4,TIM_IT_Update,ENABLE);  // 定时器4，溢出更新，使能
//	TIM_SetCounter(TIM4,0);                   // 定时数据清零
//	TIM_Cmd(TIM4,ENABLE);                     // 定时器2使能
//	
	
//GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	TIM_ICInitTypeDef TIM_ICInitStructure;
	
//	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
//	
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//浮空输入
//	
//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
//	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	//计数初始化
		TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
		TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up; // 向上计数
		TIM_TimeBaseInitStructure.TIM_Period = 65535;
		TIM_TimeBaseInitStructure.TIM_Prescaler = 0;
	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseInitStructure);
	
	//捕获通道TIM4_IC1 TIM4_IC2初始化
		TIM_ICStructInit(&TIM_ICInitStructure);
		TIM_ICInitStructure.TIM_Channel = TIM_Channel_1 | TIM_Channel_2;
		TIM_ICInitStructure.TIM_ICFilter = 6;//滤波
	TIM_ICInit(TIM4, &TIM_ICInitStructure);
	
	/* 编码器  不反相：捕获发生在IC1的上升沿 */
	TIM_EncoderInterfaceConfig(TIM4, TIM_EncoderMode_TI12, TIM_ICPolarity_Rising, TIM_ICPolarity_Rising);
	
	TIM_ClearFlag(TIM4, TIM_FLAG_Update);//清除溢出标志位
	TIM_SetCounter(TIM4, 0);//设置定时器计数值
	TIM_ITConfig(TIM4, TIM_IT_Update, ENABLE);
	
	TIM_Cmd(TIM4, ENABLE);
}


//状态检测
void TIM5_Zt_Init(u32 arr, u32 psc)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
//	NVIC_InitTypeDef NVIC_InitStruct;
//	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE);

		TIM_TimeBaseInitStruct.TIM_Period    = arr;
		TIM_TimeBaseInitStruct.TIM_Prescaler = psc;
//		TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1;
//		TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM5, &TIM_TimeBaseInitStruct);
	
	TIM_ITConfig(TIM5, TIM_IT_Update, ENABLE);//使能更新中断
	
//	NVIC_InitStruct.NVIC_IRQChannel=TIM5_IRQn;                   
//		NVIC_InitStruct.NVIC_IRQChannelCmd=ENABLE;                   
//		NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority=0x02;      
//		NVIC_InitStruct.NVIC_IRQChannelSubPriority =0x02;            
//	NVIC_Init(&NVIC_InitStruct);
	
	TIM_Cmd(TIM5, ENABLE);

}


/*************************
//function：定时器
*************************/
void TIM6_Init(u32 arr, u32 psc)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
	
	//RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6, ENABLE);
	
		TIM_TimeBaseInitStruct.TIM_Period    = arr;
		TIM_TimeBaseInitStruct.TIM_Prescaler = psc;
	TIM_TimeBaseInit(TIM6, &TIM_TimeBaseInitStruct);
	
	TIM_ITConfig(TIM6, TIM_IT_Update, ENABLE);//使能更新中断
	
	TIM_Cmd(TIM6, ENABLE);
}

//const int Guang_Situation[][5] = 
//{
//	1, 1, 0, 1, 1,//直
//	
//	1, 1, 0, 0, 1,//左微偏
//	1, 1, 1, 0, 1,
//	1, 1, 1, 0, 0,//左中偏
//	1, 1, 1, 1, 0,//左大偏
//	
//	1, 0, 1, 1, 1,//右微偏
//	0, 0, 1, 1, 1,//右中偏
//	0, 1, 1, 1, 1,//右大偏
//	
//};

u8 Guang_Data = 0;

void Store_Guang_Zt(void)
{
	
	Guang_Data = 0;
	
	if (H_1 == BLACKs)
		Guang_Data |= 0x01;
	if (H_2 == BLACKs)
		Guang_Data |= 0x02;
	if (H_3 == BLACKs)
		Guang_Data |= 0x04;
	if (H_4 == BLACKs)
		Guang_Data |= 0x08;
	if (H_5 == BLACKs)
		Guang_Data |= 0x10;
	if (H_6 == BLACKs)
		Guang_Data |= 0x20;
	if (H_7 == BLACKs)
		Guang_Data |= 0x40;
	
	
	  //显示光电状态	
	if (get_G_1) 		table[0] = 1 + 0x30;
	else				table[0] = 0 + 0x30;
	if (get_G_2)		table[1] = 1 + 0x30;
	else				table[1] = 0 + 0x30;
	if (get_G_3) 		table[2] = 1 + 0x30;
	else				table[2] = 0 + 0x30;
	if (get_G_4)		table[3] = 1 + 0x30;
	else				table[3] = 0 + 0x30;
	if (get_G_5)		table[4] = 1 + 0x30;
	else				table[4] = 0 + 0x30;
	if (get_G_6)		table[5] = 1 + 0x30;
	else				table[5] = 0 + 0x30;
	if (get_G_7)		table[6] = 1 + 0x30;
	else				table[6] = 0 + 0x30;
	
}

char xiu_flag = 0;
int i = 0;


void time_fuzhi(int flag)
{
	switch(flag)
	{
		case 0://十字转弯停车
				stop_time = Stop_times;
				break;
		case 1://转弯成功后短暂的停车
				stop_time_r = Stop_timer;
				break;
		case 10://转弯延时
				zhuang_time_r = Zhuangwang_time;
				break;
//		case 11:
//				tiao_time = Tiao_timer;
//				break;
		case 2://路口计数延时
				Road_time = Road_times;
				break;
		case 3://到地点再启动关闭计数功能时间
				Road_timee = Road_timess;
				break;
		case 4://倒车后计数间隔
				Road_timeer = Road_timesss;
				break;
		case 5://在3-7和1-5轴上时计数延迟
				Road_timeeeer = Road_timessss;
				break;
		case 6://任务二第二问在（负x，1）上计数延时
				Road_timeeerr = Road_timeesss;
				break;
		case 20://抓动作执行时间
				Grap_time = Grap_times;
				break;
		case 21://打开手时间
				Grap_N_time = Grap_N_times;
				break;
		case 30://倒车时间
				Hou_time = Hou_times;
				break;
		case 31://短倒车
				Hou_timee = Hou_timess;
				break;
		case 32:
				Hou_timeee = Hou_timesss;
				break;
		case 33://任务二第一部分后退时间
				Hou_time = Hou_timees;
				break;
		case 50://识别完物块关闭寻迹时间
				Close_XJ_timee = Close_times;
				break;
		case 51://途经过空白圆关闭寻迹时间（隐含此处不停）
				Close_XJ_timee = Close_timess;
				break;	
		case 59://摞物块步进下降
				BJ_fall_timee = BJ_fall_timess;
				break;
		case 60://步进下降时间
				BJ_fall_time = BJ_fall_times;
				break;
		case 61://第一部分步进上升时间
				BJ_up_time = BJ_up_times;
				break;	
		case 62://第二部分步进上升时间
				BJ_up_timee = BJ_up_timess;
				break;
		case 66://5个舵机抓取时间
				Wukuai_grap_time = Wukuai_grap_times;
				break;
		case 67://5个舵机依次放下一个物块时间
				Wukuai_release_time = Wukuai_release_times;
				break;
		case 70://码盘转到下个待放物块shiji
				Mapan_zhuang_time = Mapan_zhuang_times;
				break;
		case 88:
				P_time = P_xiu_time;
				break;
		case 89://放物块前修一段 
				P_time = P_xiu_times;
				break;
		case 90://任务二第一部分前进时间
				Forward_time = qianjin_times;
				break;
		case 91://第二部分前进时间
				Forward_time = qianjin_timess;
				break;
		default:
				break;
	}
}


unsigned char table[7] = {'0'};
int P_flag = 1;//2代表左偏严重	3代表右偏严重
short Lun_Left_Count = 0; 
char flag_s = 0;
short Store_XJ = 1; // 100为开存物块寻迹 其他为关闭

void Xun_ji(void)
{
	if (P_flag != 1)
	{
		Lun_Left_Count -= (short)TIM3->CNT;//此处不能将TIM3->CNT值清零，否则将影响后面pid计算
	}
	else    Lun_Left_Count = 0; //为下次做准备
//-------------------------------------------------------------------------------------------------------	
	
	if ( ((X_now_pos == 1 && X_process[0] == 2) || (X_now_pos == -1 && X_process[0] == -2))  && Y_now_pos != 0) {Store_XJ = 100;}
		
//	if (X_process[0] != 0 && X_now_pos == 0 && get_G_7 == BLACK) 
//	{//经过空白圆圈
//		flag_s = 1;	
//	}
//	if (flag_s == 1 && get_G_3 == WHITE && get_G_4 == WHITE && (Y_now_pos > 1 && Y_now_pos != 7))	{P_flag = 4; flag_s = 0; time_fuzhi(50);}//短暂关闭寻迹)
//	
//	if (ZT_Flag != houtui)
//	{
	if (Close_XJ_timee == 0 && ZT_Flag != houtui)
	{
		if (((X_process[0] == 1 || X_process[0] == -1) || (X_process[0] > 0 && Y_now_pos == 7) || (X_process[0] < 0 && Y_now_pos == 1)) && P_time > 0)
		{
			if (get_G_3 == get_G_4)
			{
				PWM_L = 20; PWM_R = 20;
			}
			else if (get_G_3 == BLACK)
			{
				xiu_flag = 1;	PWM_L = -5; PWM_R = 20;
			}
			else 
			{
				xiu_flag = 1;	PWM_L = 20;	PWM_R = -5;
			}
		}
		else if (X_process[0] == 0 && P_time > 0)
		{
			if (get_G_2 == BLACK)
			{
				if (get_G_3 == BLACK)	{PWM_L = 25; PWM_R = 30;}
				else	{xiu_flag = 1;PWM_L = -10; PWM_R = 30;}
			}
			else if (get_G_5 == BLACK)	
			{
				if (get_G_4 == BLACK)	{PWM_L = 30; PWM_R = 25;}
				else	{xiu_flag = 1;PWM_L = 30; PWM_R = -10;}
			}
			else
			{
					if (get_G_4 == BLACK)	{xiu_flag = 1;PWM_L = 28; PWM_R = -8;}
					else if (get_G_3 == BLACK)	{xiu_flag = 1;PWM_L = -8; PWM_R = 28;}
					else if (get_G_1 == BLACK)	{xiu_flag = 1; PWM_L = 20; PWM_R = 40;}
					else if (get_G_6 == BLACK)	{xiu_flag = 1; PWM_L = 40; PWM_R = 20;}
					else {PWM_L = 30; PWM_R = 30;}
			}
			
		}
		else if (((X_process[0] == 2 || X_process[0] == -2) && Store_XJ == 100) || (force_XJ == 10))//存放物块时寻迹
		{
			if (get_G_2 == get_G_5)
			{
				if (get_G_3 == get_G_4)	{PWM_L = qianjin_PWM_Lefts; PWM_R = qianjin_PWM_Rights;}
				else if (get_G_3 == BLACK) {xiu_flag = 1; PWM_L = 22; PWM_R = 27;}
				else 		{xiu_flag = 1; PWM_L = 27; PWM_R = 22;}
			}
			else if (get_G_2 == BLACK)
			{
				if (get_G_3 == get_G_4){
					if (get_G_3 == BLACK)	{PWM_L = qianjin_PWM_Lefts; PWM_R = qianjin_PWM_Rights;}
					else 					{xiu_flag = 1; PWM_L = 22; PWM_R = 27;}
				}	
				else if (get_G_3 == BLACK)
				{
					xiu_flag = 1; PWM_L = 23; PWM_R = 32;
				}
				else {PWM_L = qianjin_PWM_Lefts; PWM_R = qianjin_PWM_Rights;}
			}
			else if (get_G_5 == BLACK)
			{
				if (get_G_3 == get_G_4){
					if (get_G_3 == BLACK)	{PWM_L = qianjin_PWM_Lefts; PWM_R = qianjin_PWM_Rights;}
					else 					{PWM_L = 27; PWM_R = 22;}
				}	
				else if (get_G_4 == BLACK)
				{
					xiu_flag = 1; PWM_L = 32; PWM_R = 23;
				}
				else {PWM_L = qianjin_PWM_Lefts; PWM_R = qianjin_PWM_Rights;}
			}
			else {PWM_L = qianjin_PWM_Lefts; PWM_R = qianjin_PWM_Rights;}
		}
		else 
		{
			if (get_G_2 == get_G_5)
			{
				if (get_G_3 == get_G_4)	{PWM_L = qianjin_PWM_Left; PWM_R = qianjin_PWM_Right;}
				else if (get_G_3 == BLACK) {xiu_flag = 1; PWM_L = 28; PWM_R = 32;}
				else 		{xiu_flag = 1; PWM_L = 32; PWM_R = 28;}
			}
			else if (get_G_2 == BLACK)
			{
				if (get_G_3 == get_G_4){
					if (get_G_3 == BLACK)	{PWM_L = qianjin_PWM_Left; PWM_R = qianjin_PWM_Right;}
					else 					{PWM_L = 28; PWM_R = 32;}
				}	
				else if (get_G_3 == BLACK)
				{
					xiu_flag = 1; PWM_L = 26; PWM_R = 32;
				}
				else {PWM_L = qianjin_PWM_Left; PWM_R = qianjin_PWM_Right;}
			}
			else if (get_G_5 == BLACK)
			{
				if (get_G_3 == get_G_4){
					if (get_G_3 == BLACK)	{PWM_L = qianjin_PWM_Left; PWM_R = qianjin_PWM_Right;}
					else 					{PWM_L = 32; PWM_R = 28;}
				}	
				else if (get_G_4 == BLACK)
				{
					xiu_flag = 1; PWM_L = 32; PWM_R = 26;
				}
				else {PWM_L = qianjin_PWM_Left; PWM_R = qianjin_PWM_Right;}
			}
			else {PWM_L = qianjin_PWM_Left; PWM_R = qianjin_PWM_Right;}
		}
	}
//	}
//	else	
//	{	if (ZT_Flag == houtui)
//		{
////			if (get_G_3 == BLACK || get_G_4 == BLACK)	{PWM_L = -20; PWM_R = -20;}
////			else if (get_G_2 == BLACK)	{PWM_L = -10; PWM_R = -25;}
////			else		{PWM_L = -25; PWM_R = -10;}
//			
//			PWM_L = -20; PWM_R = -20;
//			if (get_G_2 == get_G_5)
//			{
//				if (get_G_3 == get_G_4)	{PWM_L = -qianjin_PWM_Left; PWM_R = -qianjin_PWM_Right;}
//				else if (get_G_3 == BLACK) {PWM_L = -30; PWM_R = -40;}
//				else 		{PWM_L = -40; PWM_R = -30;}
//			}
//			else {
//				if (get_G_2 == BLACK)
//				{
//					if (get_G_3 == BLACK)	{PWM_L = 5; PWM_R = -20;}
//					else	{xiu_flag = 1;PWM_L = 5; PWM_R = -30;}
//				}
//				else if (get_G_5 == BLACK)	
//				{
//					if (get_G_4 == BLACK)	{PWM_L = -20; PWM_R = -5;}
//					else	{xiu_flag = 1;PWM_L = -30; PWM_R = 5;}
//				}
//				else
//				{
////					if (get_G_4 == BLACK)	{xiu_flag = 1;PWM_L = 55; PWM_R = 15;}
////					else if (get_G_3 == BLACK)	{xiu_flag = 1;PWM_L = 15; PWM_R = 55;}
////					else {PWM_L = qianjin_PWM_Left; PWM_R = qianjin_PWM_Right;}
////					PWM_L = qianjin_PWM_Left; PWM_R = qianjin_PWM_Right;
//				}
//			
//			}
			
//			if ((get_G_1 == BLACK && (get_G_6 == BLACK || get_G_5 == BLACK)) ||
//				((get_G_6 == BLACK) && (get_G_1 == BLACK || get_G_2 == BLACK)))
//			{
//				Hou_time = 0;
//			}
//		
//		}
		else 
		{
			PWM_L = 20; PWM_R = 20;
		}
		
		
			EXTI_InitTypeDef EXTI_InitStructure;
		
		
			if (Road_time == 0 && Road_timee == 0 && Road_timeer == 0 && Road_timeeeer == 0 && Road_timeeerr == 0 && ZT_Flag != houtui)
			{
				if (task_flagg != 10 && task_flagg!=0)
				{
				if( (X_now_pos == 1 && Y_now_pos>=4 && Y_now_pos <= 6) || 
				  (X_now_pos == -1 && Y_now_pos<4 && Y_now_pos >= 2) ||
				  (Y_now_pos == 7 && Road_timeeeer == 0 && X_now_pos == 1) ||
				  (Y_now_pos == 1 && Road_timeeeer == 0 && X_now_pos == -1) )
				{
					EXTI_InitStructure.EXTI_LineCmd = ENABLE;
					EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
					EXTI_InitStructure.EXTI_Line=EXTI_Line1;
					EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
					EXTI_Init(&EXTI_InitStructure);	  
				}
				else if (X_now_pos == 2 || X_now_pos == -2)
				{
					EXTI_InitStructure.EXTI_LineCmd = DISABLE;
					EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
					EXTI_InitStructure.EXTI_Line=EXTI_Line1;
					EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
					EXTI_Init(&EXTI_InitStructure);	  
				}
				}
				else
				{
					if (get_G_7 == BLACK && (X_now_pos == 1 || X_now_pos == -1))
					{
						if (X_process[0] == 2)
						X_now_pos = 2;
						else if (X_process[0] == -2)
							X_now_pos = -2;
					}
				}
		}
		
	
	
}

char k = 0;
char Line_Road = 0;

void Encounter_Road(void)
{

	
	if (ZT_Flag != zhuangwang && ZT_Flag != houtui && Road_time == 0 && Road_timee == 0 && Road_timeer == 0 && Road_timeeeer == 0 && Road_timeeerr == 0)
	{
		if (((X_now_pos - X_process[0] != 1) && (X_process[0] > 0)) 
			|| ((X_process[0] < 0) && (X_now_pos - X_process[0] != -1)) 
			|| ((X_now_pos - X_process[0] != -1) && (X_now_pos - X_process[0] != 1) && X_process[0] == 0))
		{
		  if (((get_G_1 == BLACK) && (get_G_6 == BLACK)) || (get_G_1 == BLACK && get_G_5 == BLACK) || (get_G_2 == BLACK && get_G_6 == BLACK))//可以计数
		  {
			  i++;
			  if (i == 1)
			  {
				if(Y_now_pos == 4 || Y_now_pos == 5 || Y_now_pos == 6 || (Y_now_pos == 7 && X_now_pos != 1))	X_now_pos++;
				else if (Y_now_pos == 0 || Y_now_pos == 2 || Y_now_pos == 3 || (Y_now_pos == 1 && X_now_pos != -1))     	X_now_pos--;
				  
				  if ((Y_now_pos == 7 || Y_now_pos == 4) && (X_now_pos > 0))
					time_fuzhi(5);
				  else if ((Y_now_pos == 1) && (X_now_pos < 0))
					  time_fuzhi(5);
				  else if  ((Y_now_pos == 5 || Y_now_pos ==0 ) && (X_now_pos < 0))
					time_fuzhi(6);
				  else time_fuzhi(2);
			  }
		  }
	   }
	   else 
	   {
		   
			if (get_G_1 == BLACK && get_G_2 == BLACK && get_G_5 == BLACK&& get_G_6 == BLACK)
			{
				X_now_pos = 0;
				time_fuzhi(2);
			}
	   }
	  
	  if ((get_G_1 == WHITE) && (get_G_6 == WHITE))
	  {
		i = 0;
	  }	

    }
}

