# include "NVIC.h"

char ZT_Flag = qianjin;


char houtui_flag = 0;
int Pos_flag = 0;

/* TIM6中pid有关变量 */
float Car_L_Speed = 0;
float Car_R_Speed = 0;
float Car_PWM_L = 0;
float Car_PWM_R = 0;

void my_delay(int num )
{
	int i,j;
	for(j=num;j>0;j--)
for(i=200;i>0;i--);

}

void NVIC_ALL_Init(void)
{
	NVIC_InitTypeDef NVIC_InitStruct;
	
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	
	//TIM3中断初始化
		NVIC_InitStruct.NVIC_IRQChannel=TIM3_IRQn;                   
		NVIC_InitStruct.NVIC_IRQChannelCmd=ENABLE;                   
		NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority=0x02;      
		NVIC_InitStruct.NVIC_IRQChannelSubPriority =0x02;            
	NVIC_Init(&NVIC_InitStruct);
	
	//TIM4中断初始化
		NVIC_InitStruct.NVIC_IRQChannel=TIM4_IRQn;                   
		NVIC_InitStruct.NVIC_IRQChannelCmd=ENABLE;                   
		NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority=0x02;      
		NVIC_InitStruct.NVIC_IRQChannelSubPriority =0x02;            
	NVIC_Init(&NVIC_InitStruct);
	
	//TIM5中断初始化
		NVIC_InitStruct.NVIC_IRQChannel=TIM5_IRQn;                   
		NVIC_InitStruct.NVIC_IRQChannelCmd=ENABLE;                   
		NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority=0x01;      
		NVIC_InitStruct.NVIC_IRQChannelSubPriority =0x01;            
	NVIC_Init(&NVIC_InitStruct);
	
	//TIM6中断初始化
		NVIC_InitStruct.NVIC_IRQChannel=TIM6_IRQn;                   
		NVIC_InitStruct.NVIC_IRQChannelCmd=ENABLE;                   
		NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority=0x01;      
		NVIC_InitStruct.NVIC_IRQChannelSubPriority =0x01;            
	NVIC_Init(&NVIC_InitStruct);
	
	//光电外部中断
//	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
//		EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
//		EXTI_InitStructure.EXTI_Line=EXTI_Line1;
//  	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
//		EXTI_Init(&EXTI_InitStructure);	  
	NVIC_InitStruct.NVIC_IRQChannel = EXTI1_IRQn;			//使能按键KEY1所在的外部中断通道
  	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0x01;	//抢占优先级2 
  	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0x01;					//子优先级1 
  	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;								//使能外部中断通道
  	NVIC_Init(&NVIC_InitStruct);  	  //根据NVIC_InitStruct中指定的参数初始化外设NVIC寄存器
	
}

void TIM3_IRQHandler(void)
{
	if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET)
	{
		TIM_ClearITPendingBit(TIM3, TIM_IT_Update);	// 清除TIM3更新中断标志位
	}
	
}

void TIM4_IRQHandler(void)
{
	if (TIM_GetITStatus(TIM4, TIM_IT_Update) != RESET)
	{
		TIM_ClearITPendingBit(TIM4, TIM_IT_Update);	// 清除TIM3更新中断标志位
	}
	
}

void EXTI1_IRQHandler(void)
{
		if ((Y_now_pos >=4 && Y_now_pos <=7)  && X_now_pos == 1)
		X_now_pos = 2;
		else if (Y_now_pos >= 0 && Y_now_pos <= 3  && X_now_pos == -1)
		X_now_pos = -2;
	EXTI_ClearITPendingBit(EXTI_Line1);  //清除EXTI0线路挂起位
}

//function:滤波Yaw值
float fas(float *p, int len)
{
	float Min = 100000;
	float Max = 0;
	float average = 0;
	float sum = 0;
	int i = 0;

	for ( i=0; i<len; i++)
	{
		if (*p > Max)
		{
			Max = *p;
		}
		
		if (*p < Min)
		{
			Min = *p;
		}
		
		sum += *p;
		p++;
	}
	
//	printf("Max = %f\n", Max);
//	printf("Min = %f\n", Min);
//	printf("len = %d\n", len);
//	printf("sum = %f\n", sum);

	average = (sum - Max - Min) / (len-2);

	//printf("average = %f\n", average);
	return average;
}


unsigned char cnt = 0;
unsigned char ARR = 0;
void TIM5_IRQHandler(void)
{
	if (TIM_GetITStatus(TIM5, TIM_IT_Update) != RESET)
	{
//		TIM_ClearITPendingBit(TIM5, TIM_IT_Update);	// 清除TIM3更新中断标志位	

//		Store_Guang_Zt();	
//		Jisuan_Target_Pos();		
//		Xun_ji();
			
		ZT_Flag = qianjin;
				
		if(cnt == 0)
		{										//寻迹和计数分开写
			switch (ZT_Flag)
			{
				
				case stop: 
									//PID_I_clear();
									#if Test//此处需要注意，如果是调试转弯模块时不能用停止pid，因为坐标运算没有直接转弯时的运算，这种										
									Load(0, 0);//想法在实际工程中并不需。
									#else
									Stop_Pid();
									//Load(0, 0);
									#endif
									PID_I_clear();
									break;
				
				case zhuangwang:
									Zhuang_Su();
									Zi_Zhuang_Pid();
									Zhuangdu(do_advance[0]);
									break;
				
				case grap:			UART_IT_Puts(LSC_Grap, sizeof(LSC_Grap));break;//触手
				
				case graps:			UART_IT_Puts(LSC_L_Grap, sizeof(LSC_L_Grap));break;//任务二摞时抓
				
				case collect_grap:	UART_IT_Puts(LSC_Collect, sizeof(LSC_Collect));	break;
				
				case grap_N:		UART_IT_Puts(LSC_Release, sizeof(LSC_Release));Load(0, 0);break;//触手big开度
				
				case grap_Ns:		UART_IT_Puts(LSC_Releases, sizeof(LSC_Releases)); break;//任务二触手开度刚好夹住5个物块
				
				case left_grap:		UART_IT_Puts(LSC_Zuo, sizeof(LSC_Zuo));break;
				
				case right_grap:	UART_IT_Puts(LSC_Right, sizeof(LSC_Right));Load(0, 0);break;
				
				case mapan_zhuang:	UART_IT_Puts(Copy_now_action, sizeof(Copy_now_action));	break;
				
				case bj_grap:		UART_IT_Puts(Copy_now_action, sizeof(Copy_now_action));	break;//4个物块
				
				case bj_release:	UART_IT_Puts(Copy_now_action, sizeof(Copy_now_action));	break;
				
				case bj_WZ_1:		Locate_Abs(0, 2000);				Load(0, 0);				    break;
				
				case bj_WZ_2:		Locate_Abs(0, 2000);				Load(0, 0);					break;	
				
				case bj_WZ_3:		Locate_Abs(0, 2000);				Load(0, 0);					break;//摞物块
				
				case bj_WZ_4:		Locate_Abs(-1600*6.7, 2500);		Load(0, 0);					break;
				
				case houtui:		houtui_Pid();									break;
				
				case qianjin:		qian_Pid();										break;
				
				
				default:
									break;
			}
		}
			TIM_ClearITPendingBit(TIM5, TIM_IT_Update);	// 清除TIM3更新中断标志位	
	}
	
}

int zi = 0;
int d = 0;
int oled_time = oled_time_s;

void qian_Pid(void)
{

	Car_L_Speed = (float)Read_Speed(3);
	Car_R_Speed = (float)Read_Speed(4);
	if (!xiu_flag)//直走
	{
			Car_PWM_L = Z_PID_AbsoluteMode_L(Car_L_Speed);
			Car_PWM_R = Z_PID_AbsoluteMode_R(Car_R_Speed);
	}
	else//微调
	{
			Car_PWM_L = T_PID_AbsoluteMode_L(Car_L_Speed);
			Car_PWM_R = T_PID_AbsoluteMode_R(Car_R_Speed);
			xiu_flag = 0;
	}
			
			
	Limit(&Car_PWM_L, &Car_PWM_R);
	Load(Car_PWM_L, Car_PWM_R);
	my_delay(1000);
}
//int q = 0;
//int w = 0;

void houtui_Pid(void)
{
	Car_L_Speed = (float)Read_Speed(3);
	Car_R_Speed = (float)Read_Speed(4);
	
//	if (!xiu_flag)//直走
//	{
			Car_PWM_L = D_PID_AbsoluteMode_L((float)Car_L_Speed);
			Car_PWM_R = D_PID_AbsoluteMode_R((float)Car_R_Speed);
//	}
//	else//微调
//	{
//			Car_PWM_L = DT_PID_AbsoluteMode_L((float)Car_L_Speed);
//			Car_PWM_R = DT_PID_AbsoluteMode_R((float)Car_R_Speed);
//			xiu_flag = 0;
//	}
			
			
	Limit(&Car_PWM_L, &Car_PWM_R);
	Load(Car_PWM_L, Car_PWM_R);
	my_delay(1000);
}

void Zhuang_Su(void)
{
	if (do_advance[0] > 0 && do_advance[0] != 180)
	{
		PWM_L = Zhuang_PWM_Left_Z;
		PWM_R = Zhuang_PWM_Right_Z;
	}
	else if (do_advance[0] < 0)
	{	
		PWM_L = Zhuang_PWM_Left_Y;
		PWM_R = Zhuang_PWM_Right_Y;
	}
	else if (do_advance[0] == 180)
	{
		PWM_L = Zhuang_PWM_Left_180;
		PWM_R = Zhuang_PWM_Right_180;
	}
	else
	{
		PWM_L = 0;
		PWM_R = 0;
	}
}

//int k = 0;
void Zi_Zhuang_Pid(void)
{
//	k += (short)TIM4->CNT;
//	TIM4->CNT = 0;
	Car_L_Speed = (float)Read_Speed(3);
	Car_R_Speed = (float)Read_Speed(4);
	
		Car_PWM_L = W_PID_AbsoluteMode_L((float)Car_L_Speed);
		Car_PWM_R = W_PID_AbsoluteMode_R((float)Car_R_Speed);

			Limit(&Car_PWM_L, &Car_PWM_R);
			Load(Car_PWM_L, Car_PWM_R);//这里还可以改为-装载值
		my_delay(1000);
	
}

void Stop_Pid(void)
{
	Car_L_Speed = (float)Read_Speed(3);
	Car_R_Speed = (float)Read_Speed(4);
	
	Car_PWM_L = Stop_PID_L((float)Car_L_Speed);
	Car_PWM_R = Stop_PID_R((float)Car_R_Speed);
	
	Limit(&Car_PWM_L, &Car_PWM_R);
		Load(Car_PWM_L, Car_PWM_R);
	my_delay(1000);
		
}

int g = 0;

void TIM6_IRQHandler(void)
{
	if (TIM_GetITStatus(TIM6, TIM_IT_Update) != RESET)//产生一个定时周期中断
	{
		unsigned char str[25], str_1[25] = {0}, str_2[25] = {0}, str_3[25] = {0};
		
		if (oled_time > 0)
		{
			oled_time--;
		}
		else
		{
			oled_time = oled_time_s;
			OLED_Clear();
		}
	
		if (stop_time_r >= 1)	stop_time_r--;
		
		if (stop_time >= 1)		stop_time--;
		
		if (Road_time >= 1)		Road_time--;
		
		if (Road_timee >= 1)    Road_timee--;
		
		if (Road_timeer >= 1)	Road_timeer--;
		
		if (Road_timeeeer >= 1) Road_timeeeer--;
		
		if (Road_timeeerr >= 1)	Road_timeeerr--;

		if (zhuang_time_r >= 1)	zhuang_time_r--;
		
		if (Grap_time >= 1)		Grap_time--;
		
		if (Grap_N_time >= 1)	Grap_N_time--;
		
		if (Hou_time >= 1)		Hou_time--;
		
		if (Hou_timee >= 1)		Hou_timee--;
		
		if (Hou_timeee >= 1)	Hou_timeee--;
		
		if (Close_XJ_time >= 1)	Close_XJ_time--;
		
		if (Close_XJ_timee >= 1)	Close_XJ_timee--;
		
		if (BJ_fall_time >= 1)	BJ_fall_time--;
		
		if (BJ_fall_timee >= 1)	BJ_fall_timee--;
		
		if (BJ_up_time >= 1)	BJ_up_time--;
		
		if (BJ_up_timee >= 1)	BJ_up_timee--;
		
		if (Wukuai_grap_time >= 1) Wukuai_grap_time--;
		
		if (Wukuai_release_time >= 1) Wukuai_release_time--;
		
		if (Mapan_zhuang_time >= 1) Mapan_zhuang_time--;
		
		if (P_time >= 1)	P_time--;
				
		if (Forward_time >= 1)	Forward_time--;		
				
		d = X_now_pos;
		
		
				
		
		//sprintf(str_1, "%d", Jel);
		sprintf(str_2, "%d", X_now_pos);
			sprintf(str_3, "%d", Kel);
				//sprintf(str_3, "%d", k);
		sprintf(str, "%d", Y_now_pos);
				//sprintf(str_3, "%.3f", Yaw);
//				OLED_ShowString(0, 0, str, 8);
//				OLED_ShowString(0, 2, str_1, 8);
				//OLED_ShowString(0, 2, str_3, 8);
				//OLED_ShowChar(0, 2, num + 0x30, 8);
				OLED_ShowString(0, 4, table, 8);
				OLED_ShowString(0, 6, str_2, 8);
					OLED_ShowString(20, 6, str, 8);
		
					OLED_ShowString(0, 2, str_3, 8);
				//	OLED_ShowString(40, 2, str_1, 8);
				
				
				

		TIM_ClearITPendingBit(TIM6, TIM_IT_Update);
	}
}

