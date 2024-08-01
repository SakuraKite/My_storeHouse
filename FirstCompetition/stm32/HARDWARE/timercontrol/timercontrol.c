# include "timercontrol.h"



////ռ�ձ�
//int PWM_L = qianjin_PWM_Left;
//int PWM_R = qianjin_PWM_Right;

//ռ�ձ�
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


//��־λ
char stop_flag = 0;
char qianjin_flag = 0;
char zhuangwang_flag = 0;
//char Road_flag = 0;
//char Zhuang_Xiang_flag = 0;

//���4·pwm���Ƶ��
// ע�� TIM2ӳ��Ϊ��ȫӳ�䣬���Ŷ��ı��ˡ�
void TIM2_PWM_Init(u32 arr, u32 psc)
{
		//GPIO_InitTypeDef GPIO_InitStruct;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
	TIM_OCInitTypeDef TIM_OCInitStruct;
	
//	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO | RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB, ENABLE);//��ӳ��һ��Ҫ��AFIOʱ��
	
//	//���Ź��ܲ���
//	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);
//	GPIO_PinRemapConfig(GPIO_FullRemap_TIM2,    ENABLE);
//	
//	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;//�����������
//	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
//	
//	//PA15
//	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_15;
//	GPIO_Init(GPIOA, &GPIO_InitStruct);
//	
//	//PB3 PB10 PB11
//	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_3 | GPIO_Pin_10 | GPIO_Pin_11;
//	GPIO_Init(GPIOB, &GPIO_InitStruct);
	
	//pwm������ڳ�ʼ��
		TIM_TimeBaseStructInit(&TIM_TimeBaseInitStruct);
		TIM_TimeBaseInitStruct.TIM_Period = arr;
		TIM_TimeBaseInitStruct.TIM_Prescaler = psc;
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseInitStruct);
	
	//TIM2_CH1 TIM2_CH2 TIM2_CH3 TIM2_CH4ͨ����ʼ��
		TIM_OCInitStruct.TIM_OCMode = TIM_OCMode_PWM1;//pwm�����ʽΪPWM1
		TIM_OCInitStruct.TIM_Pulse = 0;//��ʼ����0
		TIM_OCInitStruct.TIM_OCPolarity =TIM_OCPolarity_High;//������Ը�
		TIM_OCInitStruct.TIM_OutputState = TIM_OutputState_Enable;//���ʹ��
	
	TIM_OC1Init(TIM2, &TIM_OCInitStruct);
	TIM_OC2Init(TIM2, &TIM_OCInitStruct);
	TIM_OC3Init(TIM2, &TIM_OCInitStruct);
	TIM_OC4Init(TIM2, &TIM_OCInitStruct);
	
	TIM_OC1PreloadConfig(TIM2, TIM_OCPreload_Enable);//CH1Ԥװ��ʹ��
	TIM_OC2PreloadConfig(TIM2, TIM_OCPreload_Enable);//CH2Ԥװ��ʹ��
	TIM_OC3PreloadConfig(TIM2, TIM_OCPreload_Enable);//CH3Ԥװ��ʹ��
	TIM_OC4PreloadConfig(TIM2, TIM_OCPreload_Enable);//CH4Ԥװ��ʹ��
	
	TIM_ARRPreloadConfig(TIM2, ENABLE);//ʹ��TIM2�Զ���װ�ؼĴ���
	
	TIM_Cmd(TIM2, ENABLE);//ʹ��TIM2
}

/*
** function : ���ֱ������Ķ�ʱ����ʼ������
** discription: ��������ΪPA6 PA7
*/
void TIM3_INT_Init(void)
{
	//GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	TIM_ICInitTypeDef TIM_ICInitStructure;
	
//	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
//	
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//��������
//	
//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
//	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	//������ʼ��
		TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
		TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up; // ���ϼ���
		TIM_TimeBaseInitStructure.TIM_Period = 65535;
		TIM_TimeBaseInitStructure.TIM_Prescaler = 0;
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseInitStructure);
	
	//����ͨ��TIM3_IC1 TIM3_IC2��ʼ��
		TIM_ICStructInit(&TIM_ICInitStructure);
		TIM_ICInitStructure.TIM_Channel = TIM_Channel_1 | TIM_Channel_2;
		TIM_ICInitStructure.TIM_ICFilter = 6;//�˲�
	TIM_ICInit(TIM3, &TIM_ICInitStructure);
	
	/* ������  �����ࣺ��������IC1�������� */
	TIM_EncoderInterfaceConfig(TIM3, TIM_EncoderMode_TI12, TIM_ICPolarity_Rising, TIM_ICPolarity_Rising);
	
	TIM_ClearFlag(TIM3, TIM_FLAG_Update);//��������־λ
	TIM_SetCounter(TIM3, 0);//���ö�ʱ������ֵ
	TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);
	
	TIM_Cmd(TIM3, ENABLE);
	
}



/*
** function : ���ֱ������Ķ�ʱ����ʼ������
** discription: ��������ΪPB6 PB7
*/
void TIM4_INT_Init(void)
{
//	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
//	GPIO_InitTypeDef GPIO_InitStruct;
//	TIM_ICInitTypeDef TIM_ICInitStruct;
//  
//	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4 ,ENABLE);  // ������ʱ��ʱ��
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO,ENABLE); // ����GPIOʱ��
//	
//	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;    // ��������
//	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;   // ������2:PB6/PB7
//	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
//	GPIO_Init(GPIOB ,&GPIO_InitStruct);	
//  
//	TIM_TimeBaseStructInit(&TIM_TimeBaseInitStruct);
//	TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1;      // ����Ƶ
//	TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;  // ���ϼ���
//	TIM_TimeBaseInitStruct.TIM_Period = 65535;                    // ��װ��ֵ65535
//	TIM_TimeBaseInitStruct.TIM_Prescaler = 0;                     // ��Ƶϵ��0
//	TIM_TimeBaseInit(TIM4,&TIM_TimeBaseInitStruct);
//  
//	// ���������ú�������ʱ��4��ģʽ3��������
//	TIM_EncoderInterfaceConfig(TIM4,TIM_EncoderMode_TI12,TIM_ICPolarity_Rising,TIM_ICPolarity_Rising);  
//  
//	TIM_ICStructInit(&TIM_ICInitStruct);
//	TIM_ICInitStruct.TIM_ICFilter = 10;       // �˲�������Ϊ10
//	TIM_ICInit(TIM4,&TIM_ICInitStruct);
//  
//	TIM_ClearFlag(TIM4,TIM_FLAG_Update);      // �����ʱ��������±�־λ
//	TIM_ITConfig(TIM4,TIM_IT_Update,ENABLE);  // ��ʱ��4��������£�ʹ��
//	TIM_SetCounter(TIM4,0);                   // ��ʱ��������
//	TIM_Cmd(TIM4,ENABLE);                     // ��ʱ��2ʹ��
//	
	
//GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	TIM_ICInitTypeDef TIM_ICInitStructure;
	
//	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
//	
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//��������
//	
//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
//	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	//������ʼ��
		TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
		TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up; // ���ϼ���
		TIM_TimeBaseInitStructure.TIM_Period = 65535;
		TIM_TimeBaseInitStructure.TIM_Prescaler = 0;
	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseInitStructure);
	
	//����ͨ��TIM4_IC1 TIM4_IC2��ʼ��
		TIM_ICStructInit(&TIM_ICInitStructure);
		TIM_ICInitStructure.TIM_Channel = TIM_Channel_1 | TIM_Channel_2;
		TIM_ICInitStructure.TIM_ICFilter = 6;//�˲�
	TIM_ICInit(TIM4, &TIM_ICInitStructure);
	
	/* ������  �����ࣺ��������IC1�������� */
	TIM_EncoderInterfaceConfig(TIM4, TIM_EncoderMode_TI12, TIM_ICPolarity_Rising, TIM_ICPolarity_Rising);
	
	TIM_ClearFlag(TIM4, TIM_FLAG_Update);//��������־λ
	TIM_SetCounter(TIM4, 0);//���ö�ʱ������ֵ
	TIM_ITConfig(TIM4, TIM_IT_Update, ENABLE);
	
	TIM_Cmd(TIM4, ENABLE);
}


//״̬���
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
	
	TIM_ITConfig(TIM5, TIM_IT_Update, ENABLE);//ʹ�ܸ����ж�
	
//	NVIC_InitStruct.NVIC_IRQChannel=TIM5_IRQn;                   
//		NVIC_InitStruct.NVIC_IRQChannelCmd=ENABLE;                   
//		NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority=0x02;      
//		NVIC_InitStruct.NVIC_IRQChannelSubPriority =0x02;            
//	NVIC_Init(&NVIC_InitStruct);
	
	TIM_Cmd(TIM5, ENABLE);

}


/*************************
//function����ʱ��
*************************/
void TIM6_Init(u32 arr, u32 psc)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
	
	//RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6, ENABLE);
	
		TIM_TimeBaseInitStruct.TIM_Period    = arr;
		TIM_TimeBaseInitStruct.TIM_Prescaler = psc;
	TIM_TimeBaseInit(TIM6, &TIM_TimeBaseInitStruct);
	
	TIM_ITConfig(TIM6, TIM_IT_Update, ENABLE);//ʹ�ܸ����ж�
	
	TIM_Cmd(TIM6, ENABLE);
}

//const int Guang_Situation[][5] = 
//{
//	1, 1, 0, 1, 1,//ֱ
//	
//	1, 1, 0, 0, 1,//��΢ƫ
//	1, 1, 1, 0, 1,
//	1, 1, 1, 0, 0,//����ƫ
//	1, 1, 1, 1, 0,//���ƫ
//	
//	1, 0, 1, 1, 1,//��΢ƫ
//	0, 0, 1, 1, 1,//����ƫ
//	0, 1, 1, 1, 1,//�Ҵ�ƫ
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
	
	
	  //��ʾ���״̬	
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
		case 0://ʮ��ת��ͣ��
				stop_time = Stop_times;
				break;
		case 1://ת��ɹ�����ݵ�ͣ��
				stop_time_r = Stop_timer;
				break;
		case 10://ת����ʱ
				zhuang_time_r = Zhuangwang_time;
				break;
//		case 11:
//				tiao_time = Tiao_timer;
//				break;
		case 2://·�ڼ�����ʱ
				Road_time = Road_times;
				break;
		case 3://���ص��������رռ�������ʱ��
				Road_timee = Road_timess;
				break;
		case 4://������������
				Road_timeer = Road_timesss;
				break;
		case 5://��3-7��1-5����ʱ�����ӳ�
				Road_timeeeer = Road_timessss;
				break;
		case 6://������ڶ����ڣ���x��1���ϼ�����ʱ
				Road_timeeerr = Road_timeesss;
				break;
		case 20://ץ����ִ��ʱ��
				Grap_time = Grap_times;
				break;
		case 21://����ʱ��
				Grap_N_time = Grap_N_times;
				break;
		case 30://����ʱ��
				Hou_time = Hou_times;
				break;
		case 31://�̵���
				Hou_timee = Hou_timess;
				break;
		case 32:
				Hou_timeee = Hou_timesss;
				break;
		case 33://�������һ���ֺ���ʱ��
				Hou_time = Hou_timees;
				break;
		case 50://ʶ�������ر�Ѱ��ʱ��
				Close_XJ_timee = Close_times;
				break;
		case 51://;�����հ�Բ�ر�Ѱ��ʱ�䣨�����˴���ͣ��
				Close_XJ_timee = Close_timess;
				break;	
		case 59://����鲽���½�
				BJ_fall_timee = BJ_fall_timess;
				break;
		case 60://�����½�ʱ��
				BJ_fall_time = BJ_fall_times;
				break;
		case 61://��һ���ֲ�������ʱ��
				BJ_up_time = BJ_up_times;
				break;	
		case 62://�ڶ����ֲ�������ʱ��
				BJ_up_timee = BJ_up_timess;
				break;
		case 66://5�����ץȡʱ��
				Wukuai_grap_time = Wukuai_grap_times;
				break;
		case 67://5��������η���һ�����ʱ��
				Wukuai_release_time = Wukuai_release_times;
				break;
		case 70://����ת���¸��������shiji
				Mapan_zhuang_time = Mapan_zhuang_times;
				break;
		case 88:
				P_time = P_xiu_time;
				break;
		case 89://�����ǰ��һ�� 
				P_time = P_xiu_times;
				break;
		case 90://�������һ����ǰ��ʱ��
				Forward_time = qianjin_times;
				break;
		case 91://�ڶ�����ǰ��ʱ��
				Forward_time = qianjin_timess;
				break;
		default:
				break;
	}
}


unsigned char table[7] = {'0'};
int P_flag = 1;//2������ƫ����	3������ƫ����
short Lun_Left_Count = 0; 
char flag_s = 0;
short Store_XJ = 1; // 100Ϊ�������Ѱ�� ����Ϊ�ر�

void Xun_ji(void)
{
	if (P_flag != 1)
	{
		Lun_Left_Count -= (short)TIM3->CNT;//�˴����ܽ�TIM3->CNTֵ���㣬����Ӱ�����pid����
	}
	else    Lun_Left_Count = 0; //Ϊ�´���׼��
//-------------------------------------------------------------------------------------------------------	
	
	if ( ((X_now_pos == 1 && X_process[0] == 2) || (X_now_pos == -1 && X_process[0] == -2))  && Y_now_pos != 0) {Store_XJ = 100;}
		
//	if (X_process[0] != 0 && X_now_pos == 0 && get_G_7 == BLACK) 
//	{//�����հ�ԲȦ
//		flag_s = 1;	
//	}
//	if (flag_s == 1 && get_G_3 == WHITE && get_G_4 == WHITE && (Y_now_pos > 1 && Y_now_pos != 7))	{P_flag = 4; flag_s = 0; time_fuzhi(50);}//���ݹر�Ѱ��)
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
		else if (((X_process[0] == 2 || X_process[0] == -2) && Store_XJ == 100) || (force_XJ == 10))//������ʱѰ��
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
		  if (((get_G_1 == BLACK) && (get_G_6 == BLACK)) || (get_G_1 == BLACK && get_G_5 == BLACK) || (get_G_2 == BLACK && get_G_6 == BLACK))//���Լ���
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

