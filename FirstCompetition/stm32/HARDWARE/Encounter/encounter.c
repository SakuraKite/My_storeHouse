
# include "encounter.h"

int X_Location_message[100] = {1, 10000};//�յ�λ��
int Y_Location_message[100] = {4, 10000};//�յ�λ��

//		# if Test_2
//			unsigned char Color_now_task[20] = {100};//��ǰ�����ɫ
//			unsigned char Color_Task_1[20] = { 100};
//			int X_mubiao_WZ[100] = { 10000};//����һ����㣨����C������꣩
//			int Y_mubiao_WZ[100] = { 10000};
		# if Test_2_two
			unsigned char Color_now_task[20] = {100};//��ǰ�����ɫ
			unsigned char Color_Task_1[20] = { 100};
			int X_mubiao_WZ[100] = {-2, 10000};//����һ����㣨����C������꣩
			int Y_mubiao_WZ[100] = {1, 10000};
		# else
			unsigned char Color_now_task[20] = {100};//��ǰ�����ɫ
			unsigned char Color_Task_1[20] = {3, 2, 1, 100}; //��������һʱ����Ϊ3 2 1 1 100
			int X_mubiao_WZ[100] = {1, -1, 10000};//����һ����㣨����C������꣩
			int Y_mubiao_WZ[100] = {6,  2, 10000};
		# endif

unsigned char Color_Task_2[20] = {4, 2, 1, 5, 3, 100}; //2 ** 3 ** 1  --- ��ǩ˳��Ĭ��Ϊ 2 4 3 5 1 �������һ�ν�����ɽ�����ӵڶ�λ��������һ�μ�Ϊ�ڶ���˳�򡣣����������ĩβ�Ӹ�100���ɣ�

int do_carry[100]   = { 10000};//�м䶯��
int do_advance[100] = { 10000};//Ԥ�ȶ���
int X_process[100]  = { 10000};//����λ��
//int Y_process[100] = {10000};//����λ��

char Copy_now_action[7] = {0};//���𿽱���һ������

int X_need_pos = 0;
int Y_need_pos = 0;
int X_now_pos  = -3;
int Y_now_pos  = 4;//��ʼ����ͷ����4

char X_init_flag = 0;
char Y_init_flag = 0;
char X_finish_flag = 1;
char Y_finish_flag = 1;

//MPU6050�Ƕ�
float Pitch = 0,Roll = 0,Yaw = 0;						//�Ƕ�

float zhuangwang_angle = 0;
float now_angle = 0;
float store_angle = 0;//����ת��ʱ�̵ĽǶ�
char Zhuang_Xiang_flag = 0;
char r_finish_flag = 1;//ת���Ƿ����
char ZT_finish = 0;
char task_ZT = 0;//����״̬ 0Ϊû������ 1Ϊæµ״̬
char H_flag = 0;

char jisuan_flag = 1;
//float need_angle = 0;
//int Encoder_Timer_Overflow_L;                                      //���������������ÿ729*4���һ�Σ�
//int Encoder_Timer_Overflow_R;                                      //���������������ÿ729*4���һ�Σ�
//u16 Previous_Count_L = 0;                                              //�ϴ�TIMx->CNT��ֵ
//u16 Previous_Count_R = 0;                                              //�ϴ�TIMx->CNT��ֵ



//int Lun_Left_Count = 0;
int Zhuang_Cout = 0;


int Jel = 0;
int Kel = 0;

short Read_Speed(int TIMx)
{
	short Count = 0;                                                      //һ��ʱ����ת����������	

	
	switch(TIMx)
	{
		case 3:	
				Count = (short)TIM3->CNT; /*CNTΪuint32, תΪint16*/
//				if ((ZT_Flag == zhuangwang) && (do_advance[0] == 180))
//				{
//					Lun_Left_Count += Count; Jel = Lun_Left_Count;
//				}
//				else	Lun_Left_Count = 0;//Ϊ�´μ�����׼��
//		Lun_Left_Count += Count;
						TIM3->CNT = 0;
							break;
		case 4:
				Count = -(short)TIM4->CNT; /*CNTΪuint32, תΪint16*/
				if (ZT_Flag == zhuangwang)
				{ Zhuang_Cout += Count; Kel = Zhuang_Cout;
//				if ((Zhuang_Cout > 2000) || (Zhuang_Cout < -1570))	Zhuang_Cout = 0;
				}
				else Zhuang_Cout = 0;//Ϊ�´�ת�������׼��
				TIM4->CNT = 0;	
							
					break;
					
		default:
				Count = 0;
							break;
	}
	
	//�޷�Count
	// Limit_Count(&Count);	
	
		return Count;
}

void Limit_Count(short *Count)
{
	if (*Count > (ENCODER_PPR_L-1)*4)	*Count = (ENCODER_PPR_L-1)*4;
	if (*Count < -(ENCODER_PPR_L-1)*4)	*Count = -(ENCODER_PPR_L-1)*4;
}

//��ڲ���q��Χ������4��-4
int Count1_7Xunhuan(int q)
{
	int y = 0;
	
	if (q < 0)	y = q + 8;
	else 		y = q;
	
	return y;
	
}
//function:��F�����ʶ�𵽵�����ת��ΪG���Ӧ����
void Trave_F_G(unsigned char  *target, const unsigned char *source, int dot, int length)
{//����1��Ŀ������ ����2��ԭ���� ����3���̶�Ϊ1������3λ�������е���㣩	����4������ת������ �̶�Ϊ5
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
unsigned char Hand_flag = 10;//����״̬ 1Ϊ�� 10Ϊ�� 2Ϊ������ڶ����ּټж���
unsigned char Task_ZT_flag = 100;// 1��������һ������2���������ϴ�ȡ��ı䴥��״̬ 5����������ȡ4�������� 10�������������� 100Ϊû��ʼ���� 0����ʼ��������һ
								// 50�������������ڶ����� 51�������ڽ��������¸�����ż����� 52����������ż�� 53����ż���ѽ����꣬�˵��հ�Բ��
# endif

unsigned char task_flagg = 0; // 10Ϊ���������������ڶ��� 1��������������һ���ֵĵ���

/*����������߼���������Ϊ2������
��һ�ΰ���5����飺
					��һ�ε����ϴ�ȡ����ʱ��������--ץ4�����--��������
		֮�󵽴�ж���ص�ǰ�Ŀհ�Բʱ 
����ִ��Ϊ  
ͣ��--�ſ��ֱ�--�Ƶ��ص�--����--�����count<4��ֱ�ӷ�����һ��������飬����������ת��ת���ٷ�--��ȡ��

------------------------------------------------------------------------------------------------------------------------------------
�ڶ��ΰ���5����飺����ʱ�������Ѿ�֪����������ķֲ�����֪�����Ҫ��Ҫ����
								
			������ڶ������߼�˼·�����������ϴ�ȡ��ʱ��˳��һ��Ϊ�ˣ���--����--��--����--����
					�ֱ��˶���ǡ�ÿ������--������--ץ5�����--����������ʱ�����ĸ߶ȱ�֮ǰ�ĸ߶ȸߣ�--��ס���
	�ڽ����˶�֮ǰ����ÿ���ڽ����¸������˶�֮ǰ���Ƚ����жϵ�ǰ���Ϊ�ڼ���ִ�еģ���������Ҫ����ż������Ҫ�����˶�ǰ�Ƚ�������λ��
		�����������һ���߶ȣ���������򽵵͸߶�
							��������հ�Բ��ʲô���������������ϵ�ʱ
					����һС�ξ���--���ּ�--������--С����ͷŸ����--��������ԭ�߶�--���ִ�--��������--ͣ--621--
					
						  ������
					���ϴ���������������հ�Բ��ʱ�¸����ض�Ϊ��������
				--	���͸߶�--�ж��Ƿ�������Ҫ��ת����Ҫ��ת������Ҫ��ת��--ֱ���ͷ����--���ּ�--�������������¸��������㡣*/

void Find_WZ(unsigned char color)
{
	int i = 0;
	
	if (Color_now_task[0] == 100)	{goto out;}
	
	switch (color)
	{
		case 1:	//��ɫ
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
					{//���������
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
	
		case 2://��ɫ
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
		
		case 3://��ɫ
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
		
		case 4://��ɫ
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
		
		case 5://��ɫ
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
				if (Task_ZT_flag == 10 || Task_ZT_flag == 5 ){//���������ʱ����״̬��־λ�ı��Ƴٵ� �������ص�ı�
					//�����ÿ�η����ʱҪ�������ηţ���һ�������ţ������ı�Hand_flag���ڶ���Ҳ���ǵ������ϵص��ٸı�Hand_flag
					if (Hand_flag == 100)	
					{//�Ʋ����¸�����
					   do_carry[0] = 0;Hand_flag = 10;
					}
					else if (Hand_flag == 10) 
					{
						if (Task_ZT_flag == 5) {do_carry[0] = 40;time_fuzhi(60); Hand_flag = 1;}//��һ�ε�������ȡ��
						else {do_carry[0] = 15; time_fuzhi(1);}
						
					}
					else				 {do_carry[0] = 15; time_fuzhi(1); 
											if (X_now_pos == 2 || X_now_pos == -2) Hand_flag = 10;}
				}
				else if (Task_ZT_flag == 40){//������ڶ�����
			
					if (Hand_flag == 100)
					{
						do_carry[0] = 0;Hand_flag = 10;
					}
					else if (Hand_flag == 10)
					{
						do_carry[0] = 56; time_fuzhi(67);
					}
					else if (Hand_flag == 8)
					{//����Ӧ����
						do_carry[0] = 71; time_fuzhi(91); Hand_flag = 9;
					}
					else if (Hand_flag == 9)
						{//����������ڶ���������Ѿ�������ϣ������¸��������
						do_carry[0] = 0; Hand_flag = 8;//�����¸�����
					}			
					
				}
				/*else if (Task_ZT_flag == 50 || Task_ZT_flag == 51 || Task_ZT_flag == 52 || Task_ZT_flag == 53){//������ڶ�����
					if (Hand_flag == 100)
					{
						do_carry[0] = 0;Hand_flag = 1;
					}
//					else if (Task_ZT_flag == 51)
//					{//ż���������
//						do_carry[0] = 57; time_fuzhi(70); Task_ZT_flag = 50;					
//					}
					else if (Task_ZT_flag == 53)
					{
						do_carry[0] = 42; time_fuzhi(62); Task_ZT_flag = 50; Hand_flag = 2;//���һ��(�ٶ�����¼Hand_flag = 2)
					}
					else if (Hand_flag == 10)
					{
						do_carry[0] = 40; time_fuzhi(60); Hand_flag = 1;//������ʼ�߶�
					}
					else
					{
						do_carry[0] = 15; time_fuzhi(1);
						if (X_now_pos == 2 || X_now_pos == -2) {Hand_flag = 10; if (Task_ZT_flag != 52 )Task_ZT_flag = 51;}
					}
					
				}*/
				else{//����һ
					if (Task_ZT_flag == 2) {do_carry[0] = 27; Task_ZT_flag = 5;}//�������ϴ�ȡ���ſ���
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
		//����һ��������������2��Ҫ��������ص㣨���˳���ǹ̶�����7��1��������д��X_mubiao_WZ��Y_mubiao_WZ�м���
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
	
	if (X_now_pos > 0 && Y_now_pos == 7)//��5�����ص㣬�ͽ��������
	{ memcpy(Color_now_task, Color_Task_2, sizeof(Color_Task_2)); task_flagg = 1;}
	else if (X_now_pos < 0 &&Y_now_pos == 1)
	{ Trave_F_G(Color_now_task, Color_Task_2, 1, 5); task_flagg = 10;}
	
	if (Color_now_task[0] == 100)
	{
		if (X_mubiao_WZ[0] == 10000){//������ڶ�������� �ص����
			X_mubiao_WZ[0] = -2;
			Y_mubiao_WZ[0] = 0;
			X_mubiao_WZ[1] = 10000;
			Y_mubiao_WZ[1] = 10000;
		}
	}
	
	Find_WZ(Color_now_task[0]);
}
void copy_tab(char *target, const char *source, int n)
{//����������Ϊ��ȡ����ִ�еĶ���������һ��Ŀ������ �ζ���ԭ���� ��������ȡ�������
	int i = 0;
	
	for (i=(n-1)*7; i<n*7; i++)		*target++ = source[i];
}

unsigned char force_XJ = 0;//�������һ����ǿ���л�Ѱ��ģʽ 10Ϊ�����Ѱ�� 100Ϊת����ʱ��Ѱ��ģ��

/*
**do_advance[]��װ��ֵΪ -135 -90 -45 0 45 90 135 180  
**
*/
void Jisuan_Target_Pos(void)
{
	# if Test_2_two
	static int count = 5;//�����¼Wu_Release����ִ�д���
	static int counter = 1;//�����¼Mapan_zhuang����ִ�д���
	# else
	static int count = 1;//�����¼Wu_Release����ִ�д���
	static int counter = 1;//�����¼Mapan_zhuang����ִ�д���
	# endif
	
	if((do_carry[0]!=10000) && (do_advance[0]!=10000) && (X_process[0]!=10000))//��ʼ�����
	{
		if (do_advance[0] != 0)
		{
			ZT_Flag = zhuangwang;

			if (do_advance[0] == 180)//ת180��
			{
				if (Y_now_pos >= 4)	Y_need_pos = Y_now_pos-4;
				else Y_need_pos = Y_now_pos + 4; 
				r_finish_flag = 0;//�����Ƿ�ִ��ת��
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
		{//������߼����룺����һ�ε���ȡ���ص�ʱ������ִ��Ϊ ��--5�����ץ--��--����ת��Ϊ�¸������׼����--����ץ ��
		//	������ж���ص�ʱ����ִ��Ϊ����--һ�������--��--����ת��Ϊ�¸������׼����--����ץ��
		
			if (X_now_pos == -2 && Y_now_pos == 0)	{do_carry[0] = 100; ZT_Flag = stop;}
			
			P_flag = 1;
			switch (do_carry[0])//ȱһ��������ɱ�־
			{
				case  5://ԭ��ͣ��
							ZT_Flag = stop;
							
							if (stop_time_r == 0)
							{do_carry[0] = 0;time_fuzhi(0);	time_fuzhi(3);}
							break;
				
				case 10://ͣ��ȡ�����ɫ	
							ZT_Flag = stop;
							if (stop_time_r == 0)	
							{ 		
								if (Task_ZT_flag == 5 || Task_ZT_flag == 10 || Task_ZT_flag == 40 )	Task_2();//Task_ZT_flag == 1��������һ�Ѿ����
								else									Task_1(); 
								
										#if Test_1//�����õ�   
											do_carry[0] = 0;
										#endif	
							}
							break;
							
				case 15://������հ�Բͣ�������
							ZT_Flag = stop;
							if (stop_time_r == 0)
							{		
								if (Hand_flag == 1)	{do_carry[0] = 18; time_fuzhi(20); }
								else if (task_flagg == 10)	{do_carry[0] = 56; time_fuzhi(67);}
								else	{do_carry[0] = 55; time_fuzhi(67);}
							}
							break;
							
				case 16://���˵��հ�Բʱͣ���������
							ZT_Flag = stop;
							if (stop_time_r == 0)
							{
								if (count >= 6)		{do_carry[0] = 0;}//������ڶ����ֽ��������
								else if (task_flagg == 20) {do_carry[0] = 0;}
								else{do_carry[0] = 54; time_fuzhi(70);}
							}
								
							break;
							
				case 17://������ڶ����ֶκ��˺�ͣ��
							ZT_Flag = stop;
							if (stop_time_r == 0)
							{do_carry[0] = 57; time_fuzhi(70);}
							break;
				case 18://�����������Ʋ
							ZT_Flag = left_grap;
							if (Grap_time == 0)
							{
								do_carry[0] = 26; time_fuzhi(21);
							}
							break;
				case 19://������ڶ�������Ʋ
							ZT_Flag = right_grap;
							if (Grap_time == 0)
							{
								do_carry[0] = 26; time_fuzhi(21);
							}
							break;
			
							
				case 20://����һץ	
							ZT_Flag = grap;
							Hand_flag = 1;
							if (Grap_time == 0)   
							{	//����һ����
								do_carry[0] = 0;time_fuzhi(2);time_fuzhi(51);
							}
							break;
							
				case 21://����һ��	
							ZT_Flag = grap_N;
							if (Grap_N_time == 0) 
							{
								do_carry[0] = 30; 
								time_fuzhi(30);	
								Store_XJ = 1;
							}
							break;
				case 24://�����ʱ ץ
							ZT_Flag = graps;
							if (Grap_time == 0)
							{//�����½�
								do_carry[0] = 39; time_fuzhi(59);
							}
							break;
				
				case 25://�����ץ
							ZT_Flag = grap;
							if (Grap_time == 0)
							{//�����¸�����
								if (X_Location_message[0] != 10000) do_carry[0] = 0;
								else		{do_carry[0] = 10; Hand_flag = 100; task_ZT = freedom;}
							}
							break;
				
				case 26://�������һ���� ��
							ZT_Flag = grap_N;
							Load(0, 0);
							if 	((X_now_pos == 2 || X_now_pos == -2) && Task_ZT_flag != 1)     goto link;//���������ڶ��ηŵ�ʱ��
							if (Grap_N_time == 0)
							{	if (Hand_flag == 10)
								{
link:					       		if(Task_ZT_flag != 5 )// Task_ZT_flag == 52 ����������ڶ�����ż����鵽�հ׵�
									{//�������ϴ�ȡ��
										
//										if (task_flagg == 10)	{do_carry[0] = 71; time_fuzhi(91);}
//										else 
										{
										do_carry[0] = 31; 
										time_fuzhi(30);		
										}	///////////------------------------------------------------------------------------�˴�������������������ľ�£��鶯��
										
										if (Task_ZT_flag == 52) Hand_flag = 10;
										else					Hand_flag = 1;
									}
									else
									{//�����ϴ�ȡ��
										do_carry[0] = 0;
									}
									
								}
								else//����ǰ��һ�ξ���
								{
									if (task_flagg == 10)	do_carry[0] = 0;
									else	{do_carry[0] = 31; time_fuzhi(33); Hand_flag = 10; }//�������һ���ֺ���
//									time_fuzhi(51);  Store_XJ = 100;
								}//�򿪴����Ѱ������
							}
							break;			

				case 27://���ϴ�ȡ�� �ţ��ֱ��Ŷ�ǡ��Ϊ5������ȣ�
							ZT_Flag = grap_Ns;
							if (Grap_N_time == 0)
							{
								do_carry[0] = 10;
							}
							break;
							
				case 28://������ڶ����� ��
							ZT_Flag = grap_N;
							if (Grap_N_time == 0)
							{
								do_carry[0] = 33; time_fuzhi(32);
							}
							break;
							
				case 30://����һ����
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
							
				case 31://����		�������һ�������
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
								
								//�������һ����
								//�������ֱ��ת����ж���
								do_carry[0] = 16;
								time_fuzhi(1);
								
								H_flag = 1;
							}
							break;
				
				case 32://�̺���		������ڶ��������
							ZT_Flag = houtui;
							if (Hou_timee == 0)
							{//ͣ-ץ
								do_carry[0] = 17; time_fuzhi(1);
							}
							break;
				case 33://������		������ڶ��������
							ZT_Flag = houtui;
							if (Hou_timeee == 0)
							{//ͣ������ת��ż�����   
								do_carry[0] = 16; time_fuzhi(1);
														
							}
							break;
							
				case 39://�ڶ����ֲ��������
							ZT_Flag = bj_WZ_2;
							if (BJ_fall_timee == 0)
							{
								do_carry[0] = 56; time_fuzhi(67);
							}
						
							break;
							
				case 40://�����½�
							ZT_Flag = bj_WZ_4;
							if (BJ_fall_time == 0)
							{//��case 50
								if (task_flagg == 10)	{do_carry[0] = 49;}
								else					 do_carry[0] = 50;
								time_fuzhi(66);
								//else if (Task_ZT_flag == 10){do_carry[0] = 51; time_fuzhi(67);}//���η������
							}
							break;
							
				case 41://�������һ���� ���������߶�
							ZT_Flag = bj_WZ_3;
							if (BJ_up_time == 0)
							{
								if (Task_ZT_flag == 5) 
								{//ץ���������
									Task_ZT_flag = 10;
									do_carry[0] = 25;
									time_fuzhi(20);
								}
								else if (Task_ZT_flag == 51)
								{//�����  ��ż�����
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
							
				case 42://������ڶ����� ���������߶�
							ZT_Flag = bj_WZ_1;
							if (BJ_up_timee == 0)
							{
								if(X_now_pos<0 && Y_now_pos == 1)	{do_carry[0] = 57; time_fuzhi(70); Task_ZT_flag = 40; Hand_flag = 100;}
//								else if (count%2 == 0)		{do_carry[0] = 28; time_fuzhi(21);}//���� ������
//								else if (Task_ZT_flag == 50)		{ do_carry[0] = 0;}
							}							
							break;
			
				case 49://5�����ץ
							ZT_Flag = bj_grap;
							copy_tab(Copy_now_action, Wu_Graps, 1);
							if (Wukuai_grap_time == 0)
							{//�ڶ����������߶�
								count = 1;//���еڶ�����������
								counter = 1;
								task_ZT = freedom;
								do_carry[0] = 42;
								time_fuzhi(62);
							}
							break;
							
				case 50://4�����ץ
							ZT_Flag = bj_grap;
							copy_tab(Copy_now_action, Wu_Grap, 1);
							if (Wukuai_grap_time == 0)
							{//����
								do_carry[0] = 41;
								time_fuzhi(61);
							}
							break;
				
				case 51://5��������η������
							ZT_Flag = bj_release;
							copy_tab(Copy_now_action, Wu_Release, count);
							if (Wukuai_release_time == 0)
							{//��ת��case 41
								do_carry[0] = 41;
								time_fuzhi(61);
								count++;//Ϊ�´ζ�����׼��
								if (count>=5)	count = 1;
							}
							break;
							
				case 52://����ת
							ZT_Flag = mapan_zhuang;
							copy_tab(Copy_now_action, Mapan_zhuang, counter);
							if (Mapan_zhuang_time == 0)
							{//��ɫʶ�� + ����ץȡ���
								do_carry[0] = 10;
								counter++;//ִ����ߴ�������һ������ִ����ϣ������������
								if (counter>=5)	counter = 1;
							}
							break;
							
											
				case 54://�������һ����  ����ת
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
							
		    	case 55://�������һ����  ���η������
//Glik:					
							ZT_Flag = bj_release;
							copy_tab(Copy_now_action, Wu_Release, count);
							if (Wukuai_release_time == 0)
							{//����ץȡ���
								count++;//Ϊ�´ζ�����׼��
								
								if (count >= 5)
								{ 
									if (task_flagg  == 10)
									{
										do_carry[0] = 0;
									}				
									else
									{
										do_carry[0] = 60; time_fuzhi(70);
									} //�������һ�������
								}
								else			{do_carry[0] = 31; time_fuzhi(33);}//����
								
								if (count >= 5)	{count = 1;}
							}
							break;
							
				case 56://�ڶ����� �����
//Slik:
							ZT_Flag = bj_release;
							copy_tab(Copy_now_action, Wu_Releases, count);
							if (Wukuai_release_time == 0)
							{
								count++;//Ϊ�´ζ�����׼��
								
								Hand_flag = 8;
								do_carry[0] = 0;	
								Store_XJ = 100;
								time_fuzhi(2);
							}
							break;
							
				case 57://������ڶ����� ����ת
							ZT_Flag = mapan_zhuang;
							
							time_fuzhi(67);
							if (Mapan_zhuang_time == 0)
							{
								counter++;
								
								do_carry[0] = 10;//�����¸�����
								
								Hand_flag = 100;
								
								break;
							}
							{copy_tab(Copy_now_action, Mapan_zhuangs, counter);}
							break;
							
			    case 60://���̸�λ
							ZT_Flag = mapan_zhuang;
							copy_tab(Copy_now_action, Mapan_Init, 1);
							if (Mapan_zhuang_time == 0)	{//���ڶ������ϴ�ȡ��
								do_carry[0] = 31;//����
								time_fuzhi(33);
								Hand_flag = 10;
								task_flagg = 20;
								Task_ZT_flag = 2;//Ϊ�������ϴ�ȡ�㴥�ֶ���׼��
							}
							break;
							
				case 70://�������һ������ǰ��һС��
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
							
				case 71://������ڶ�������ǰ��һС��
							ZT_Flag = qianjin;
							if (Forward_time == 0)
							{
								do_carry[0] = 72;
								time_fuzhi(1);
							}
							break;
				
				case 72://�����ͣ
							ZT_Flag = stop;
							if (stop_time_r == 0)
							{
								if (task_flagg == 10)	{do_carry[0] = 73; time_fuzhi(20);}
								else if (task_flagg == 1)	{do_carry[0] = 31; time_fuzhi(33); force_XJ = 0;}
								else 	do_carry[0] = 0;
							}
							break;
				case 73://���������£���ſ����             -------------------------------------------------�˴�������������Ϊһ�� ע���ڶ�����ư�����¶���
							ZT_Flag = collect_grap;
							if (Grap_time == 0)
							{
								do_carry[0] = 74; time_fuzhi(32);
							}
							break;
				case 74://������ڶ����ֺ���
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
				case 75://������ڰ����ſ���
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
			if (Y_Location_message[0]-Y_now_pos==0)//Y_now_pos  Ϊ��ǰ��ͷ����
			{
//					if ((X_now_pos >= 0 && X_Location_message[0] > 0) || (X_now_pos < 0 && X_Location_message[0] < 0))
//					{
						X_process[0] = X_Location_message[0];
						do_advance[0]= 0;//ת0��
						do_carry[0] = 10;
						
						X_process[1] = 10000;
						do_advance[1] = 10000;
						do_carry[1] = 10000;
//					}
//					else
//					{
//						X_process[0] = 0;
//						do_advance[0]= 0;//ת0��
//						do_carry[0] = 5;
//							
//						X_process[1] = X_Location_message[0];
//						do_advance[1]= 0;//ת0��
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
				if (Y_now_pos != 7 && Y_now_pos != 1)	force_XJ = 100;//ת��������
				
			
					X_process[0] = 0;
					do_advance[0]= 180;//ת180��
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
			else//�߼����֣���Ϊ��ΧΪ����һ��ֱ���ϣ�����һ�����ȵ�ͷ��ԭ�㣬Ȼ����ת����Ӧ�ĽǶȣ������ֱ�С�
			{
				if((X_now_pos>0 && Y_now_pos >=4)||(X_now_pos<0 && Y_now_pos <4))
				{
					do_advance[0]= 180; //180��
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
					do_advance[0]= 0; //0��
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
		else//����˵�ǰ���������ִ����һ���������
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
				{P_flag = 4; H_flag = 0; time_fuzhi(51);}//���ݹر�Ѱ��
	
	do_advance[0] = 0;
	
	if ((X_now_pos == 2 && Y_now_pos == 3) || (X_now_pos == -2 && Y_now_pos == 5))	return;		
	else 	{ time_fuzhi(88);}
}

//��ڲ���Ϊ��ǰ���Ƕ�
//���ܣ�ת��ת��
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




