
# include "encounter.h"

int X_Location_message[100] = {1, 10000};//终点位置
int Y_Location_message[100] = {4, 10000};//终点位置

//		# if Test_2
//			unsigned char Color_now_task[20] = {100};//当前物块颜色
//			unsigned char Color_Task_1[20] = { 100};
//			int X_mubiao_WZ[100] = { 10000};//任务一坐标点（不算C点的坐标）
//			int Y_mubiao_WZ[100] = { 10000};
		# if Test_2_two
			unsigned char Color_now_task[20] = {100};//当前物块颜色
			unsigned char Color_Task_1[20] = { 100};
			int X_mubiao_WZ[100] = {-2, 10000};//任务一坐标点（不算C点的坐标）
			int Y_mubiao_WZ[100] = {1, 10000};
		# else
			unsigned char Color_now_task[20] = {100};//当前物块颜色
			unsigned char Color_Task_1[20] = {3, 2, 1, 100}; //测试任务一时数组为3 2 1 1 100
			int X_mubiao_WZ[100] = {1, -1, 10000};//任务一坐标点（不算C点的坐标）
			int Y_mubiao_WZ[100] = {6,  2, 10000};
		# endif

unsigned char Color_Task_2[20] = {4, 2, 1, 5, 3, 100}; //2 ** 3 ** 1  --- 抽签顺序默认为 2 4 3 5 1 任务二第一次结束后可将数组从第二位逆序排列一次即为第二次顺序。（最后在数组末尾加个100即可）

int do_carry[100]   = { 10000};//中间动作
int do_advance[100] = { 10000};//预先动作
int X_process[100]  = { 10000};//过程位置
//int Y_process[100] = {10000};//过程位置

char Copy_now_action[7] = {0};//负责拷贝出一个动作

int X_need_pos = 0;
int Y_need_pos = 0;
int X_now_pos  = -3;
int Y_now_pos  = 4;//初始化车头朝向4

char X_init_flag = 0;
char Y_init_flag = 0;
char X_finish_flag = 1;
char Y_finish_flag = 1;

//MPU6050角度
float Pitch = 0,Roll = 0,Yaw = 0;						//角度

float zhuangwang_angle = 0;
float now_angle = 0;
float store_angle = 0;//储存转弯时刻的角度
char Zhuang_Xiang_flag = 0;
char r_finish_flag = 1;//转弯是否完成
char ZT_finish = 0;
char task_ZT = 0;//任务状态 0为没有任务 1为忙碌状态
char H_flag = 0;

char jisuan_flag = 1;
//float need_angle = 0;
//int Encoder_Timer_Overflow_L;                                      //编码器溢出次数（每729*4溢出一次）
//int Encoder_Timer_Overflow_R;                                      //编码器溢出次数（每729*4溢出一次）
//u16 Previous_Count_L = 0;                                              //上次TIMx->CNT的值
//u16 Previous_Count_R = 0;                                              //上次TIMx->CNT的值



//int Lun_Left_Count = 0;
int Zhuang_Cout = 0;


int Jel = 0;
int Kel = 0;

short Read_Speed(int TIMx)
{
	short Count = 0;                                                      //一段时间内转过的脉冲数	

	
	switch(TIMx)
	{
		case 3:	
				Count = (short)TIM3->CNT; /*CNT为uint32, 转为int16*/
//				if ((ZT_Flag == zhuangwang) && (do_advance[0] == 180))
//				{
//					Lun_Left_Count += Count; Jel = Lun_Left_Count;
//				}
//				else	Lun_Left_Count = 0;//为下次计算做准备
//		Lun_Left_Count += Count;
						TIM3->CNT = 0;
							break;
		case 4:
				Count = -(short)TIM4->CNT; /*CNT为uint32, 转为int16*/
				if (ZT_Flag == zhuangwang)
				{ Zhuang_Cout += Count; Kel = Zhuang_Cout;
//				if ((Zhuang_Cout > 2000) || (Zhuang_Cout < -1570))	Zhuang_Cout = 0;
				}
				else Zhuang_Cout = 0;//为下次转弯计数做准备
				TIM4->CNT = 0;	
							
					break;
					
		default:
				Count = 0;
							break;
	}
	
	//限幅Count
	// Limit_Count(&Count);	
	
		return Count;
}

void Limit_Count(short *Count)
{
	if (*Count > (ENCODER_PPR_L-1)*4)	*Count = (ENCODER_PPR_L-1)*4;
	if (*Count < -(ENCODER_PPR_L-1)*4)	*Count = -(ENCODER_PPR_L-1)*4;
}

//入口参数q范围不等于4和-4
int Count1_7Xunhuan(int q)
{
	int y = 0;
	
	if (q < 0)	y = q + 8;
	else 		y = q;
	
	return y;
	
}
//function:将F点物块识别到的坐标转化为G点对应坐标
void Trave_F_G(unsigned char  *target, const unsigned char *source, int dot, int length)
{//参数1：目标数组 参数2：原数组 参数3：固定为1（参数3位逆序排列的起点）	参数4：数组转化长度 固定为5
	int i = 0;
	int j = 0;

	for (i=dot; i>=0; i--)
	{
		*target++ = source[i];
	}
	for (i=length-1,j=1; i!= dot; i--,j++)
	{
		*target++ = source[i];
	}

	*target++ = 100;
}



//# if Test_2
//unsigned char Task_ZT_flag = 1;
//unsigned char Hand_flag = 1;
# if Test_2_two
unsigned char Task_ZT_flag = 10;
unsigned char Hand_flag = 10;
# else 
unsigned char Hand_flag = 10;//夹手状态 1为夹 10为开 2为任务二第二部分假夹动作
unsigned char Task_ZT_flag = 100;// 1代表任务一结束，2代表到达物料代取点改变触手状态 5代表步进降夹取4个物块过程 10代表进行着任务二 100为没开始任务 0代表开始进行任务一
								// 50代表进行任务二第二部分 51代表正在进行奇数下个是运偶数物块 52代表正在运偶数 53代表偶数已近运完，退到空白圆点
# endif

unsigned char task_flagg = 0; // 10为代表进行这任务二第二问 1代表进行任务二第一部分的倒车

/*任务二处理逻辑：整体拆分为2个部分
第一次搬运5个物块：
					第一次到物料代取中心时，步进降--抓4个物块--步进升，
		之后到达卸货地点前的空白圆时 
动作执行为  
停车--张开手臂--推到地点--倒车--（如果count<4）直接放下下一个代运物块，否则码盘先转，转完再放--夹取。

------------------------------------------------------------------------------------------------------------------------------------
第二次搬运5个物块：（此时隐含车已经知道任务二物块的分布，即知道物块要不要摞）
								
			任务二第二部分逻辑思路：当到达物料代取点时，顺序一定为此（摞--不摞--摞--不摞--摞）
					手臂运动到恰好卡着物块--步进降--抓5个物块--步进升（此时步进的高度比之前的高度高）--夹住物块
	在进行运动之前（即每次在进行下个坐标运动之前）先进行判断当前物块为第几次执行的，奇数则需要摞，偶数不需要摞。运动前先将步进就位，
		如果摞则升到一定高度，如果不摞则降低高度
							摞：到达空白圆点什么都不做，到达物料点时
					后退一小段距离--触手夹--步进降--小舵机释放该物块--步进升回原高度--触手打开--正常后退--停--621--
					
						  不摞：
					在上次物块结束，车到达空白圆点时下个物块必定为不摞，则
				--	降低高度--判断是否码盘需要旋转（需要则转，不需要则不转）--直接释放物块--触手夹--结束动作进行下个坐标运算。*/

void Find_WZ(unsigned char color)
{
	int i = 0;
	
	if (Color_now_task[0] == 100)	{goto out;}
	
	switch (color)
	{
		case 1:	//绿色
				if (task_ZT == freedom)
				{	
					task_ZT = busy;
					if (task_flagg == 1)
					{
						X_Location_message[0] = 1;
						Y_Location_message[0] = 6;
						X_Location_message[1] = 10000;
						Y_Location_message[1] = 10000;
					}	
					else if (Task_ZT_flag == 10 || Task_ZT_flag == 5|| Task_ZT_flag == 40)
					{//进行任务二
						X_Location_message[0] = 1;
						Y_Location_message[0] = 6;
						X_Location_message[1] = 2;
						Y_Location_message[1] = 6;
						X_Location_message[2] = 10000;
						Y_Location_message[2] = 10000;
					}
					else{
						X_Location_message[0] = 2;
						Y_Location_message[0] = 6;
						X_Location_message[1] = 10000;
						Y_Location_message[1] = 10000;
					}
					for (i=0; i<20; i++)		Color_now_task[i] = Color_now_task[i+1];
				}	
				goto out;
					//break;
	
		case 2://白色
				if (task_ZT == freedom)
				{
					task_ZT = busy;
					if (task_flagg == 1)
					{
						X_Location_message[0] = 1;
						Y_Location_message[0] = 5;
						X_Location_message[1] = 10000;
						Y_Location_message[1] = 10000;
					}	
					else if (Task_ZT_flag == 10 || Task_ZT_flag == 5 || Task_ZT_flag == 40)
					{
						X_Location_message[0] = 1;
						Y_Location_message[0] = 5;
						X_Location_message[1] = 2;
						Y_Location_message[1] = 5;
						X_Location_message[2] = 10000;
						Y_Location_message[2] = 10000;
					}
					else{
						X_Location_message[0] = 2;
						Y_Location_message[0] = 5;
						X_Location_message[1] = 10000;
						Y_Location_message[1] = 10000;
					}
					for (i=0; i<20; i++)		Color_now_task[i] = Color_now_task[i+1];
				}
				goto out;
				//	break;
		
		case 3://红色
				if (task_ZT == freedom)
				{
					task_ZT = busy;
					if (task_flagg == 1)
					{
						X_Location_message[0] = 1;
						Y_Location_message[0] = 4;
						X_Location_message[1] = 10000;
						Y_Location_message[1] = 10000;
					}	
					else if (Task_ZT_flag == 10 || Task_ZT_flag == 5|| Task_ZT_flag == 40)
					{
						X_Location_message[0] = 1;
						Y_Location_message[0] = 4;
						X_Location_message[1] = 2;
						Y_Location_message[1] = 4;
						X_Location_message[2] = 10000;
						Y_Location_message[2] = 10000;
					}
					else{
						X_Location_message[0] = 2;
						Y_Location_message[0] = 4;
						X_Location_message[1] = 10000;
						Y_Location_message[1] = 10000;
					}
					for (i=0; i<20; i++)		Color_now_task[i] = Color_now_task[i+1];
				}	
				goto out;
					//break;
		
		case 4://黑色
				if (task_ZT == freedom)
				{
					task_ZT = busy;
					if (task_flagg == 1)
					{
						X_Location_message[0] = -1;
						Y_Location_message[0] = 3;
						X_Location_message[1] = 10000;
						Y_Location_message[1] = 10000;
					}	
					else if (Task_ZT_flag == 10 || Task_ZT_flag == 5|| Task_ZT_flag == 40)
					{
						X_Location_message[0] = -1;
						Y_Location_message[0] = 3;
						X_Location_message[1] = -2;
						Y_Location_message[1] = 3;
						X_Location_message[2] = 10000;
						Y_Location_message[2] = 10000;
					}
					else{
						X_Location_message[0] = -2;
						Y_Location_message[0] = 3;
						X_Location_message[1] = 10000;
						Y_Location_message[1] = 10000;
					}
					for (i=0; i<20; i++)		Color_now_task[i] = Color_now_task[i+1];
				}
				goto out;
					//break;
		
		case 5://蓝色
				if (task_ZT == freedom)
				{
					task_ZT = busy;
					if (task_flagg == 1)
					{
						X_Location_message[0] = -1;
						Y_Location_message[0] = 2;
						X_Location_message[1] = 10000;
						Y_Location_message[1] = 10000;
					}	
					else if (Task_ZT_flag == 10 || Task_ZT_flag == 5|| Task_ZT_flag == 40)
					{
						X_Location_message[0] = -1;
						Y_Location_message[0] = 2;
						X_Location_message[1] = -2;
						Y_Location_message[1] = 2;
						X_Location_message[2] = 10000;
						Y_Location_message[2] = 10000;
					}
					else{
						X_Location_message[0] = -2;
						Y_Location_message[0] = 2;
						X_Location_message[1] = 10000;
						Y_Location_message[1] = 10000;
					}
					for (i=0; i<20; i++)		Color_now_task[i] = Color_now_task[i+1];
				}
out:    	  				
				if (Task_ZT_flag == 10 || Task_ZT_flag == 5 ){//进行任务二时触手状态标志位改变推迟到 到达物块地点改变
					//任务二每次放物块时要经历两次放，第一次正常放，但不改变Hand_flag，第二次也就是到达物料地点再改变Hand_flag
					if (Hand_flag == 100)	
					{//移步到下个坐标
					   do_carry[0] = 0;Hand_flag = 10;
					}
					else if (Hand_flag == 10) 
					{
						if (Task_ZT_flag == 5) {do_carry[0] = 40;time_fuzhi(60); Hand_flag = 1;}//第一次到达物块代取点
						else {do_carry[0] = 15; time_fuzhi(1);}
						
					}
					else				 {do_carry[0] = 15; time_fuzhi(1); 
											if (X_now_pos == 2 || X_now_pos == -2) Hand_flag = 10;}
				}
				else if (Task_ZT_flag == 40){//任务二第二部分
			
					if (Hand_flag == 100)
					{
						do_carry[0] = 0;Hand_flag = 10;
					}
					else if (Hand_flag == 10)
					{
						do_carry[0] = 56; time_fuzhi(67);
					}
					else if (Hand_flag == 8)
					{//到对应物料
						do_carry[0] = 71; time_fuzhi(91); Hand_flag = 9;
					}
					else if (Hand_flag == 9)
						{//代表任务二第二部分物块已经运送完毕，进行下个物块任务
						do_carry[0] = 0; Hand_flag = 8;//进行下个坐标
					}			
					
				}
				/*else if (Task_ZT_flag == 50 || Task_ZT_flag == 51 || Task_ZT_flag == 52 || Task_ZT_flag == 53){//任务二第二部分
					if (Hand_flag == 100)
					{
						do_carry[0] = 0;Hand_flag = 1;
					}
//					else if (Task_ZT_flag == 51)
//					{//偶数物块运完
//						do_carry[0] = 57; time_fuzhi(70); Task_ZT_flag = 50;					
//					}
					else if (Task_ZT_flag == 53)
					{
						do_carry[0] = 42; time_fuzhi(62); Task_ZT_flag = 50; Hand_flag = 2;//虚晃一招(假动作记录Hand_flag = 2)
					}
					else if (Hand_flag == 10)
					{
						do_carry[0] = 40; time_fuzhi(60); Hand_flag = 1;//步进起始高度
					}
					else
					{
						do_carry[0] = 15; time_fuzhi(1);
						if (X_now_pos == 2 || X_now_pos == -2) {Hand_flag = 10; if (Task_ZT_flag != 52 )Task_ZT_flag = 51;}
					}
					
				}*/
				else{//任务一
					if (Task_ZT_flag == 2) {do_carry[0] = 27; Task_ZT_flag = 5;}//到达物料代取点张开手
					else if (Hand_flag == 10) {time_fuzhi(20);do_carry[0] = 20; Hand_flag = 1;}
					else	{time_fuzhi(21);do_carry[0] = 21; Hand_flag = 10;}		
				}
				
					break;
		
		case 6:
		default:do_carry[0] = 0;
					break;		
	}
	
}


unsigned char kk = 0;

void Task_1(void)
{
	unsigned char color = color_Update();
	kk = color;
	
	if (Task_ZT_flag == 100)	{Task_ZT_flag = 0; memcpy(Color_now_task, Color_Task_1, sizeof(Color_Task_1));}

	#if Test_1
	#else
		if (Color_now_task[0] == 100 && Task_ZT_flag != 2)
		{
		 Task_ZT_flag = 1;
		//任务一结束，传入任务2需要到达的物块地点（这个顺序是固定的先7后1）将坐标写入X_mubiao_WZ和Y_mubiao_WZ中即可
			X_mubiao_WZ[0] = 2;
			Y_mubiao_WZ[0] = 7;
			X_mubiao_WZ[1] = -2;
			Y_mubiao_WZ[1] = 1;
			X_mubiao_WZ[2] = 10000;
			Y_mubiao_WZ[2] = 10000;
		}
 
		Find_WZ(Color_now_task[0]);
	#endif
	
}

//15 18 26 31 15 18 26 31 
void Task_2(void)
{
	unsigned char colors = color_Update();
	
	if (X_now_pos > 0 && Y_now_pos == 7)//到5个物块地点，就进行任务二
	{ memcpy(Color_now_task, Color_Task_2, sizeof(Color_Task_2)); task_flagg = 1;}
	else if (X_now_pos < 0 &&Y_now_pos == 1)
	{ Trave_F_G(Color_now_task, Color_Task_2, 1, 5); task_flagg = 10;}
	
	if (Color_now_task[0] == 100)
	{
		if (X_mubiao_WZ[0] == 10000){//任务二第二部分完成 回到起点
			X_mubiao_WZ[0] = -2;
			Y_mubiao_WZ[0] = 0;
			X_mubiao_WZ[1] = 10000;
			Y_mubiao_WZ[1] = 10000;
		}
	}
	
	Find_WZ(Color_now_task[0]);
}
void copy_tab(char *target, const char *source, int n)
{//本函数功能为抽取即将执行的动作。参数一：目标数组 参二：原数组 参三：抽取动作序号
	int i = 0;
	
	for (i=(n-1)*7; i<n*7; i++)		*target++ = source[i];
}

unsigned char force_XJ = 0;//任务二第一部分强制切换寻迹模式 10为存物块寻迹 100为转完弯时修寻迹模块

/*
**do_advance[]中装载值为 -135 -90 -45 0 45 90 135 180  
**
*/
void Jisuan_Target_Pos(void)
{
	# if Test_2_two
	static int count = 5;//负责记录Wu_Release动作执行次数
	static int counter = 1;//负责记录Mapan_zhuang动作执行次数
	# else
	static int count = 1;//负责记录Wu_Release动作执行次数
	static int counter = 1;//负责记录Mapan_zhuang动作执行次数
	# endif
	
	if((do_carry[0]!=10000) && (do_advance[0]!=10000) && (X_process[0]!=10000))//初始化完成
	{
		if (do_advance[0] != 0)
		{
			ZT_Flag = zhuangwang;

			if (do_advance[0] == 180)//转180°
			{
				if (Y_now_pos >= 4)	Y_need_pos = Y_now_pos-4;
				else Y_need_pos = Y_now_pos + 4; 
				r_finish_flag = 0;//代表是否执行转弯
			}
			else
			{
				if (r_finish_flag == 1) 
				{
					Y_need_pos = Y_Location_message[0];
					r_finish_flag = 0;
					for (int i=0; i<=99; i++)
					{
						X_Location_message[i] = X_Location_message[i+1];
						Y_Location_message[i] = Y_Location_message[i+1];
					}
				}
			}	
		}
		else if((X_now_pos != X_process[0]))
		{	
			if (stop_time == 0)
			{
				ZT_Flag = qianjin;
				if (Road_timee == 0)	Encounter_Road();
				time_fuzhi(1);
			}
		}
		else if (do_carry[0] != 0)
		{//任务二逻辑代码：当第一次到达取物块地点时，动作执行为 降--5个舵机抓--升--舵盘转（为下个物块做准备）--触手抓 。
		//	当到达卸货地点时动作执行为：降--一个舵机放--升--舵盘转（为下个物块做准备）--触手抓。
		
			if (X_now_pos == -2 && Y_now_pos == 0)	{do_carry[0] = 100; ZT_Flag = stop;}
			
			P_flag = 1;
			switch (do_carry[0])//缺一个动作完成标志
			{
				case  5://原点停车
							ZT_Flag = stop;
							
							if (stop_time_r == 0)
							{do_carry[0] = 0;time_fuzhi(0);	time_fuzhi(3);}
							break;
				
				case 10://停获取物块颜色	
							ZT_Flag = stop;
							if (stop_time_r == 0)	
							{ 		
								if (Task_ZT_flag == 5 || Task_ZT_flag == 10 || Task_ZT_flag == 40 )	Task_2();//Task_ZT_flag == 1代表任务一已经完成
								else									Task_1(); 
								
										#if Test_1//测试用的   
											do_carry[0] = 0;
										#endif	
							}
							break;
							
				case 15://任务二空白圆停车放物块
							ZT_Flag = stop;
							if (stop_time_r == 0)
							{		
								if (Hand_flag == 1)	{do_carry[0] = 18; time_fuzhi(20); }
								else if (task_flagg == 10)	{do_carry[0] = 56; time_fuzhi(67);}
								else	{do_carry[0] = 55; time_fuzhi(67);}
							}
							break;
							
				case 16://后退到空白圆时停车放下物块
							ZT_Flag = stop;
							if (stop_time_r == 0)
							{
								if (count >= 6)		{do_carry[0] = 0;}//任务二第二部分结束回起点
								else if (task_flagg == 20) {do_carry[0] = 0;}
								else{do_carry[0] = 54; time_fuzhi(70);}
							}
								
							break;
							
				case 17://任务二第二部分段后退后停车
							ZT_Flag = stop;
							if (stop_time_r == 0)
							{do_carry[0] = 57; time_fuzhi(70);}
							break;
				case 18://任务二触手左撇
							ZT_Flag = left_grap;
							if (Grap_time == 0)
							{
								do_carry[0] = 26; time_fuzhi(21);
							}
							break;
				case 19://任务二第二部分右撇
							ZT_Flag = right_grap;
							if (Grap_time == 0)
							{
								do_carry[0] = 26; time_fuzhi(21);
							}
							break;
			
							
				case 20://任务一抓	
							ZT_Flag = grap;
							Hand_flag = 1;
							if (Grap_time == 0)   
							{	//任务一结束
								do_carry[0] = 0;time_fuzhi(2);time_fuzhi(51);
							}
							break;
							
				case 21://任务一放	
							ZT_Flag = grap_N;
							if (Grap_N_time == 0) 
							{
								do_carry[0] = 30; 
								time_fuzhi(30);	
								Store_XJ = 1;
							}
							break;
				case 24://摞物块时 抓
							ZT_Flag = graps;
							if (Grap_time == 0)
							{//步进下降
								do_carry[0] = 39; time_fuzhi(59);
							}
							break;
				
				case 25://任务二抓
							ZT_Flag = grap;
							if (Grap_time == 0)
							{//进行下个坐标
								if (X_Location_message[0] != 10000) do_carry[0] = 0;
								else		{do_carry[0] = 10; Hand_flag = 100; task_ZT = freedom;}
							}
							break;
				
				case 26://任务二第一部分 放
							ZT_Flag = grap_N;
							Load(0, 0);
							if 	((X_now_pos == 2 || X_now_pos == -2) && Task_ZT_flag != 1)     goto link;//作用跳过第二次放的时间
							if (Grap_N_time == 0)
							{	if (Hand_flag == 10)
								{
link:					       		if(Task_ZT_flag != 5 )// Task_ZT_flag == 52 代表任务二第二步运偶数物块到空白点
									{//不是物料代取点
										
//										if (task_flagg == 10)	{do_carry[0] = 71; time_fuzhi(91);}
//										else 
										{
										do_carry[0] = 31; 
										time_fuzhi(30);		
										}	///////////------------------------------------------------------------------------此处可视情况添加任务二最后的聚拢物块动作
										
										if (Task_ZT_flag == 52) Hand_flag = 10;
										else					Hand_flag = 1;
									}
									else
									{//是物料代取点
										do_carry[0] = 0;
									}
									
								}
								else//进行前进一段距离
								{
									if (task_flagg == 10)	do_carry[0] = 0;
									else	{do_carry[0] = 31; time_fuzhi(33); Hand_flag = 10; }//任务二第一部分后退
//									time_fuzhi(51);  Store_XJ = 100;
								}//打开存物块寻迹函数
							}
							break;			

				case 27://物料代取点 放（手臂张度恰好为5个物块宽度）
							ZT_Flag = grap_Ns;
							if (Grap_N_time == 0)
							{
								do_carry[0] = 10;
							}
							break;
							
				case 28://任务二第二部分 放
							ZT_Flag = grap_N;
							if (Grap_N_time == 0)
							{
								do_carry[0] = 33; time_fuzhi(32);
							}
							break;
							
				case 30://任务一后退
							ZT_Flag = houtui;
							if (Hou_time == 0)  
							{
								task_ZT = freedom;
								if (Task_ZT_flag == 1)		Task_ZT_flag = 2;
								
								do_carry[0] = 0; 
								time_fuzhi(4);
								H_flag = 1;
							}
							break;
							
				case 31://后退		任务二第一次运物块
							ZT_Flag = houtui;
							EXTI_InitTypeDef EXTI_InitStructure;
							EXTI_InitStructure.EXTI_LineCmd = DISABLE;
							EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
							EXTI_InitStructure.EXTI_Line=EXTI_Line1;
							EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
							EXTI_Init(&EXTI_InitStructure);	  
							
							if (Hou_time == 0)
							{
								Store_XJ = 1;
								task_ZT = freedom;
								
								//任务二第一部分
								//后退完成直接转码盘卸物块
								do_carry[0] = 16;
								time_fuzhi(1);
								
								H_flag = 1;
							}
							break;
				
				case 32://短后退		任务二第二次运物块
							ZT_Flag = houtui;
							if (Hou_timee == 0)
							{//停-抓
								do_carry[0] = 17; time_fuzhi(1);
							}
							break;
				case 33://接着退		任务二第二次运物块
							ZT_Flag = houtui;
							if (Hou_timeee == 0)
							{//停车码盘转到偶数物块   
								do_carry[0] = 16; time_fuzhi(1);
														
							}
							break;
							
				case 39://第二部分步进摞物块
							ZT_Flag = bj_WZ_2;
							if (BJ_fall_timee == 0)
							{
								do_carry[0] = 56; time_fuzhi(67);
							}
						
							break;
							
				case 40://步进下降
							ZT_Flag = bj_WZ_4;
							if (BJ_fall_time == 0)
							{//到case 50
								if (task_flagg == 10)	{do_carry[0] = 49;}
								else					 do_carry[0] = 50;
								time_fuzhi(66);
								//else if (Task_ZT_flag == 10){do_carry[0] = 51; time_fuzhi(67);}//依次放下物块
							}
							break;
							
				case 41://任务二第一部分 步进上升高度
							ZT_Flag = bj_WZ_3;
							if (BJ_up_time == 0)
							{
								if (Task_ZT_flag == 5) 
								{//抓完结束动作
									Task_ZT_flag = 10;
									do_carry[0] = 25;
									time_fuzhi(20);
								}
								else if (Task_ZT_flag == 51)
								{//任务二  放偶数物块
									do_carry[0] = 56;
									time_fuzhi(67);
									Task_ZT_flag = 52;
									counter++;
								}
								else
								{
									do_carry[0] = 54;
									time_fuzhi(70);
								}
							}
							break;
							
				case 42://任务二第二部分 步进上升高度
							ZT_Flag = bj_WZ_1;
							if (BJ_up_timee == 0)
							{
								if(X_now_pos<0 && Y_now_pos == 1)	{do_carry[0] = 57; time_fuzhi(70); Task_ZT_flag = 40; Hand_flag = 100;}
//								else if (count%2 == 0)		{do_carry[0] = 28; time_fuzhi(21);}//打开手 长倒车
//								else if (Task_ZT_flag == 50)		{ do_carry[0] = 0;}
							}							
							break;
			
				case 49://5个舵机抓
							ZT_Flag = bj_grap;
							copy_tab(Copy_now_action, Wu_Graps, 1);
							if (Wukuai_grap_time == 0)
							{//第二部分上升高度
								count = 1;//进行第二部分则重置
								counter = 1;
								task_ZT = freedom;
								do_carry[0] = 42;
								time_fuzhi(62);
							}
							break;
							
				case 50://4个舵机抓
							ZT_Flag = bj_grap;
							copy_tab(Copy_now_action, Wu_Grap, 1);
							if (Wukuai_grap_time == 0)
							{//上升
								do_carry[0] = 41;
								time_fuzhi(61);
							}
							break;
				
				case 51://5个舵机依次放下物块
							ZT_Flag = bj_release;
							copy_tab(Copy_now_action, Wu_Release, count);
							if (Wukuai_release_time == 0)
							{//跳转到case 41
								do_carry[0] = 41;
								time_fuzhi(61);
								count++;//为下次动作做准备
								if (count>=5)	count = 1;
							}
							break;
							
				case 52://舵盘转
							ZT_Flag = mapan_zhuang;
							copy_tab(Copy_now_action, Mapan_zhuang, counter);
							if (Mapan_zhuang_time == 0)
							{//颜色识别 + 触手抓取物块
								do_carry[0] = 10;
								counter++;//执行最高次数（即一次任务执行完毕），则进行重置
								if (counter>=5)	counter = 1;
							}
							break;
							
											
				case 54://任务二第一部分  舵盘转
							ZT_Flag = mapan_zhuang;
							
							time_fuzhi(67);
							if (Mapan_zhuang_time == 0)
							{
								if (X_Location_message[0] != 10000) do_carry[0] = 0;
								else		{do_carry[0] = 10; Hand_flag = 100; task_ZT = freedom;}
								counter++;								
							}
							copy_tab(Copy_now_action, Mapan_zhuang, counter);
							break;
							
		    	case 55://任务二第一部分  依次放下物块
//Glik:					
							ZT_Flag = bj_release;
							copy_tab(Copy_now_action, Wu_Release, count);
							if (Wukuai_release_time == 0)
							{//触手抓取物块
								count++;//为下次动作做准备
								
								if (count >= 5)
								{ 
									if (task_flagg  == 10)
									{
										do_carry[0] = 0;
									}				
									else
									{
										do_carry[0] = 60; time_fuzhi(70);
									} //任务二第一部分完成
								}
								else			{do_carry[0] = 31; time_fuzhi(33);}//后退
								
								if (count >= 5)	{count = 1;}
							}
							break;
							
				case 56://第二部分 放物块
//Slik:
							ZT_Flag = bj_release;
							copy_tab(Copy_now_action, Wu_Releases, count);
							if (Wukuai_release_time == 0)
							{
								count++;//为下次动作做准备
								
								Hand_flag = 8;
								do_carry[0] = 0;	
								Store_XJ = 100;
								time_fuzhi(2);
							}
							break;
							
				case 57://任务二第二部分 码盘转
							ZT_Flag = mapan_zhuang;
							
							time_fuzhi(67);
							if (Mapan_zhuang_time == 0)
							{
								counter++;
								
								do_carry[0] = 10;//进行下个坐标
								
								Hand_flag = 100;
								
								break;
							}
							{copy_tab(Copy_now_action, Mapan_zhuangs, counter);}
							break;
							
			    case 60://码盘复位
							ZT_Flag = mapan_zhuang;
							copy_tab(Copy_now_action, Mapan_Init, 1);
							if (Mapan_zhuang_time == 0)	{//到第二个物料代取点
								do_carry[0] = 31;//后退
								time_fuzhi(33);
								Hand_flag = 10;
								task_flagg = 20;
								Task_ZT_flag = 2;//为到达物料代取点触手动作准备
							}
							break;
							
				case 70://任务二第一部分往前推一小段
							ZT_Flag = qianjin;
							if (Forward_time == 0)
							{
								do_carry[0] = 72; 
								time_fuzhi(1);
								task_flagg = 1;
																							
								if (Task_ZT_flag == 52) Hand_flag = 10;
								else					Hand_flag = 1;
							}
							break;
							
				case 71://任务二第二部分往前推一小段
							ZT_Flag = qianjin;
							if (Forward_time == 0)
							{
								do_carry[0] = 72;
								time_fuzhi(1);
							}
							break;
				
				case 72://任务二停
							ZT_Flag = stop;
							if (stop_time_r == 0)
							{
								if (task_flagg == 10)	{do_carry[0] = 73; time_fuzhi(20);}
								else if (task_flagg == 1)	{do_carry[0] = 31; time_fuzhi(33); force_XJ = 0;}
								else 	do_carry[0] = 0;
							}
							break;
				case 73://任务二最后聚拢并放开物块             -------------------------------------------------此处将两个动作和为一个 注意在舵机控制板里该下动作
							ZT_Flag = collect_grap;
							if (Grap_time == 0)
							{
								do_carry[0] = 74; time_fuzhi(32);
							}
							break;
				case 74://任务二第二部分后退
							ZT_Flag = houtui;
							if (Hou_timeee == 0)
							{
								Hand_flag = 10;
								Store_XJ = 1;
								task_ZT = freedom;

								do_carry[0] = 17;
								time_fuzhi(1);
				
								H_flag = 1;
							}
							break;
				case 75://任务二在靶心张开手
							ZT_Flag = grap_N;
							if (Grap_N_time == 0)
							{
								do_carry[0] = 74; time_fuzhi(32);
							}
							break;
						
				default:	break;
			}
		}
		else
		{
				ZT_Flag = stop;
					
				for (int i=0; i<=99; i++)
				{
					do_carry[i]   = do_carry[i+1];
					do_advance[i] = do_advance[i+1];
					X_process[i]  = X_process[i+1];
				}
			
		}
				
	}
		
	else
	{
		if(X_Location_message[0]!=10000 && Y_Location_message[0]!=10000)
		{
			if (Y_Location_message[0]-Y_now_pos==0)//Y_now_pos  为当前车头朝向
			{
//					if ((X_now_pos >= 0 && X_Location_message[0] > 0) || (X_now_pos < 0 && X_Location_message[0] < 0))
//					{
						X_process[0] = X_Location_message[0];
						do_advance[0]= 0;//转0°
						do_carry[0] = 10;
						
						X_process[1] = 10000;
						do_advance[1] = 10000;
						do_carry[1] = 10000;
//					}
//					else
//					{
//						X_process[0] = 0;
//						do_advance[0]= 0;//转0°
//						do_carry[0] = 5;
//							
//						X_process[1] = X_Location_message[0];
//						do_advance[1]= 0;//转0°
//						do_carry[1] = 10;
//						
//						X_process[2] = 10000;
//						do_advance[2] = 10000;
//						do_carry[2] = 10000;
//					}
					for (int i=0; i<=99; i++)
					{
						X_Location_message[i] = X_Location_message[i+1];
						Y_Location_message[i] = Y_Location_message[i+1];
					}
				
			}
			else if(Y_Location_message[0]-Y_now_pos==-4 || Y_Location_message[0]-Y_now_pos==4)
			{
				if (Y_now_pos != 7 && Y_now_pos != 1)	force_XJ = 100;//转完弯修正
				
			
					X_process[0] = 0;
					do_advance[0]= 180;//转180°
					do_carry[0]  = 0;
					
					X_process[1] = X_Location_message[0];
					do_advance[1] = 0;
					do_carry[1] = 10;
					for(int i=0; i<=99; i++)
					{
						X_Location_message[i] = X_Location_message[i+1];
						Y_Location_message[i] = Y_Location_message[i+1];
					}
					X_process[2] = 10000;
					do_advance[2]= 10000;
					do_carry[2]  = 10000;
			
			}
			else//逻辑部分，因为大范围为不在一条直线上，所以一定会先调头回原点，然后再转到相应的角度，最后再直行。
			{
				if((X_now_pos>0 && Y_now_pos >=4)||(X_now_pos<0 && Y_now_pos <4))
				{
					do_advance[0]= 180; //180°
					X_process[0] = 0;
					do_carry[0]  = 5;

					X_process[1] = X_Location_message[0];
					do_carry[1]  = 10;
					Y_need_pos = Y_Location_message[0];
					
					if (Y_now_pos != 4 && Y_now_pos != 0)
						switch( Count1_7Xunhuan(Y_Location_message[0]-Y_now_pos) )
						{
							case 1:	 do_advance[1] = -135;	break;
							case 2:	 do_advance[1] = -90;	break;
							case 3:	 do_advance[1] = -45;	break;
									
							case 5: do_advance[1] = 45;		break;
							case 6: do_advance[1] = 90;		break;
							case 7: do_advance[1] = 135;	break;
							default:	break;
						}
					else
					{
						if (Y_now_pos == 4)
							switch (Y_Location_message[0]-Y_now_pos)
							{
								case 1:	do_advance[1] = -135;		break;
								case 2:	do_advance[1] = -90;		break;
								case 3:	do_advance[1] = -45;	break;
								
								case -1:do_advance[1] = 135;	break;
								case -2:do_advance[1] = 90;	break;
								case -3:do_advance[1] = 45;	break;
								default:	break;
							}
						else 
							switch (Y_Location_message[0]-Y_now_pos)
							{
								case 1:	do_advance[1] = -135;		break;
								case 2:	do_advance[1] = -90;		break;
								case 3:	do_advance[1] = -45;	    break;
								
								case 5:do_advance[1] = 45;		break;
								case 6:do_advance[1] = 90;		break;
								case 7:do_advance[1] = 135;	break;
								default:	break;
							}
					}
						X_process[2] = 10000;
					//	Y_process[2] = 10000;
						do_advance[2]= 10000;						
						do_carry[2]  = 10000;
				}
				else if((X_now_pos<0 && Y_now_pos >=4)||(X_now_pos>0 && Y_now_pos <4)) 
				{
					do_advance[0]= 0; //0°
					X_process[0] = 0;
					do_carry[0]  = 5;
					
					X_process[1] = X_Location_message[0];
					do_carry[1]  = 10;
					Y_need_pos = Y_Location_message[0];
					
					if (Y_now_pos != 4 && Y_now_pos != 0)
						switch( Count1_7Xunhuan(Y_Location_message[0]-Y_now_pos) )
						{
							case 1:	 do_advance[1] = -135;	break;
							case 2:	 do_advance[1] = -90;	break;
							case 3:	 do_advance[1] = -45;	break;
									
							case 5: do_advance[1] = 45;		break;
							case 6: do_advance[1] = 90;		break;
							case 7: do_advance[1] = 135;	break;
							default:	break;
						}
					else
					{
						if (Y_now_pos == 4)
							switch (Y_Location_message[0]-Y_now_pos)
							{
								case 1:	do_advance[1] = 45;		break;
								case 2:	do_advance[1] = 90;		break;
								case 3:	do_advance[1] = 135;	break;
								
								case -1:do_advance[1] = -45;	break;
								case -2:do_advance[1] = -90;	break;
								case -3:do_advance[1] = -135;	break;//////////////////////////
								default:	break;
							}
						else 
							switch (Y_Location_message[0]-Y_now_pos)
							{
								case 1:	do_advance[1] = 45;		break;
								case 2:	do_advance[1] = 90;		break;
								case 3:	do_advance[1] = 135;	    break;
								
								case -1:do_advance[1] = -45;		break;
								case -2:do_advance[1] = -90;		break;
								case -3:do_advance[1] = -135;	break;
								default:	break;
							}
					}
						X_process[2] = 10000;
					//	Y_process[2] = 10000;
						do_advance[2]= 10000;						
						do_carry[2]  = 10000;
				}
				
			}		
		}
		else//完成了当前的物块任务，执行下一个物块任务
		{
			if (X_mubiao_WZ[0] != 10000 && Y_mubiao_WZ[0] != 10000)
			{
				X_Location_message[0] = X_mubiao_WZ[0];
				Y_Location_message[0] = Y_mubiao_WZ[0];
				
				X_Location_message[1] = 10000;
				Y_Location_message[1] = 10000;
				
				for (int i=0; i<=99; i++)
				{
					X_mubiao_WZ[i] = X_mubiao_WZ[i+1];
					Y_mubiao_WZ[i] = Y_mubiao_WZ[i+1];
				}
			}
		}
		
	}
}


void arrive_WZ(void)
{
	if (do_advance[0] == 180)	
	{
		if (X_now_pos == 2 && Y_now_pos == 7)	time_fuzhi(5);
	    else		time_fuzhi(2);//time_fuzhi(4);
	}
	else						time_fuzhi(3);
		
	time_fuzhi(0);
	r_finish_flag = 1;
	
	ZT_Flag = stop;
	
	if (Y_now_pos >= 2 && Y_now_pos <= 6)
	{
		if (X_now_pos == 2)			X_now_pos = 1;
		else if (X_now_pos == -2)	X_now_pos = -1;
	}
	Y_now_pos = Y_need_pos;
	PID_I_clear();
	if (H_flag == 1 || 
	   (do_advance[0] == 180 && (X_now_pos == 1 || X_now_pos == -1)))	
				{P_flag = 4; H_flag = 0; time_fuzhi(51);}//短暂关闭寻迹
	
	do_advance[0] = 0;
	
	if ((X_now_pos == 2 && Y_now_pos == 3) || (X_now_pos == -2 && Y_now_pos == 5))	return;		
	else 	{ time_fuzhi(88);}
}

//入口参数为当前车角度
//功能：转向、转速
void Zhuangdu(float angle)
{	
	switch(do_advance[0])
	{
		case 45:
				if ((Zhuang_Cout >= 305) && (get_G_3 == BLACK || get_G_4 == BLACK || (get_G_2 == BLACK && get_G_5 == WHITE) || (get_G_2 == WHITE && get_G_5 == BLACK) || get_G_6 == BLACK))		arrive_WZ();	break;
		
		case 90:	
			if ((Zhuang_Cout >= 640)  && (get_G_3 == BLACK || get_G_4 == BLACK || (get_G_2 == BLACK && get_G_5 == WHITE) || (get_G_2 == WHITE && get_G_5 == BLACK) || get_G_6 == BLACK))		arrive_WZ();	break;
		
		case 135:
				if ((Zhuang_Cout >= 995)  && (get_G_3 == BLACK || get_G_4 == BLACK || (get_G_2 == BLACK && get_G_5 == WHITE) || (get_G_2 == WHITE && get_G_5 == BLACK) || get_G_6 == BLACK))		arrive_WZ();	break;
				
		case -135:
				if ((Zhuang_Cout <= -995) && (get_G_3 == BLACK || get_G_4 == BLACK || (get_G_2 == BLACK && get_G_5 == WHITE) || (get_G_2 == WHITE && get_G_5 == BLACK) || get_G_1 == BLACK))		arrive_WZ();	break; // -1100
				
		case -90:
				if ( (Zhuang_Cout <= -640) && (get_G_3 == BLACK || get_G_4 == BLACK || (get_G_2 == BLACK && get_G_5 == WHITE) || (get_G_2 == WHITE && get_G_5 == BLACK) || get_G_1 == BLACK))	 	arrive_WZ();	break; // -680
				//-1510
		case -45:	
				if ((Zhuang_Cout <= -305) && (get_G_3 == BLACK || get_G_4 == BLACK || (get_G_2 == BLACK && get_G_5 == WHITE) || (get_G_2 == WHITE && get_G_5 == BLACK) || get_G_1 == BLACK))   	arrive_WZ();	break; // -287
				
		case 180:
				if (Zhuang_Cout >= 1320 && (get_G_3 == BLACK || get_G_4 == BLACK || (get_G_2 == BLACK && get_G_5 == WHITE) || (get_G_2 == WHITE && get_G_5 == BLACK)|| get_G_6 == BLACK))	        arrive_WZ();	break;//1600
		
		default:
				break;
		
	}
	
}




