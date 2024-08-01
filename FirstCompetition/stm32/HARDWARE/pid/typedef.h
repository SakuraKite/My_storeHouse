# ifndef _TYPEDEF_H_
# define _TYPEDEF_H_

typedef struct 
{
	/*PID�㷨�ӿڱ��������ڸ��û���ȡ���޸�PID�㷨������*/
	float Kp_L;
	float Ki_L;
	float Kd_L;
	float U_max_L;//����������
	float U_min_L;//����������
	
	float Need_Speed_L;//�����ٶ�
	float Actual_Speed_L;//ʵ���ٶ�
	
	float errNow_L;//��ǰ���
	float ctrOut_L;//���������
	
	/*PID�㷨�ڲ���������ֵ�����޸�*/
	float err_last_L;//��һ��ƫ��
	float erri_L;
	
}Z_PID_AbsoluteType_L;


typedef struct 
{
	/*PID�㷨�ӿڱ��������ڸ��û���ȡ���޸�PID�㷨������*/
	float Kp_R;
	float Ki_R;
	float Kd_R;
	float U_max_R;//����������
	float U_min_R;//����������
	
	float Need_Speed_R;//�����ٶ�
	float Actual_Speed_R;//ʵ���ٶ�
	
	float errNow_R;//��ǰ���
	float ctrOut_R;//���������
	
	/*PID�㷨�ڲ���������ֵ�����޸�*/
	float err_last_R;//��һ��ƫ��
	float erri_R;
	
}Z_PID_AbsoluteType_R;


//���ҵ�PID
typedef struct
{
	/*PID�㷨�ӿڱ��������ڸ��û���ȡ���޸�PID�㷨������*/
	float Kp_Rs;
	float Ki_Rs;
	float Kd_Rs;
	float U_max_Rs;//����������
	float U_min_Rs;//����������
	
	float Need_Speed_Rs;//�����ٶ�
	float Actual_Speed_Rs;//ʵ���ٶ�
	
	float errNow_Rs;//��ǰ���
	float ctrOut_Rs;//���������
	
	/*PID�㷨�ڲ���������ֵ�����޸�*/
	float err_last_Rs;//��һ��ƫ��
	float erri_Rs;
	
}T_PID_AbsoluteType_R;


typedef struct 
{
	/*PID�㷨�ӿڱ��������ڸ��û���ȡ���޸�PID�㷨������*/
	float Kp_Ls;
	float Ki_Ls;
	float Kd_Ls;
	float U_max_Ls;//����������
	float U_min_Ls;//����������
	
	float Need_Speed_Ls;//�����ٶ�
	float Actual_Speed_Ls;//ʵ���ٶ�
	
	float errNow_Ls;//��ǰ���
	float ctrOut_Ls;//���������
	
	/*PID�㷨�ڲ���������ֵ�����޸�*/
	float err_last_Ls;//��һ��ƫ��
	float erri_Ls;
	
}T_PID_AbsoluteType_L;

typedef struct 
{
	/*PID�㷨�ӿڱ��������ڸ��û���ȡ���޸�PID�㷨������*/
	float Kp_Ld;
	float Ki_Ld;
	float Kd_Ld;
	float U_max_Ld;//����������
	float U_min_Ld;//����������
	
	float Need_Speed_Ld;//�����ٶ�
	float Actual_Speed_Ld;//ʵ���ٶ�
	
	float errNow_Ld;//��ǰ���
	float ctrOut_Ld;//���������
	
	/*PID�㷨�ڲ���������ֵ�����޸�*/
	float err_last_Ld;//��һ��ƫ��
	float erri_Ld;
	
}W_PID_AbsoluteType_L;

typedef struct
{
	/*PID�㷨�ӿڱ��������ڸ��û���ȡ���޸�PID�㷨������*/
	float Kp_Rd;
	float Ki_Rd;
	float Kd_Rd;
	float U_max_Rd;//����������
	float U_min_Rd;//����������
	
	float Need_Speed_Rd;//�����ٶ�
	float Actual_Speed_Rd;//ʵ���ٶ�
	
	float errNow_Rd;//��ǰ���
	float ctrOut_Rd;//���������
	
	/*PID�㷨�ڲ���������ֵ�����޸�*/
	float err_last_Rd;//��һ��ƫ��
	float erri_Rd;
	
}W_PID_AbsoluteType_R;

typedef struct 
{
	/*PID�㷨�ӿڱ��������ڸ��û���ȡ���޸�PID�㷨������*/
	float Kp_Lds;
	float Ki_Lds;
	float Kd_Lds;
	float U_max_Lds;//����������
	float U_min_Lds;//����������
	
	float Need_Speed_Lds;//�����ٶ�
	float Actual_Speed_Lds;//ʵ���ٶ�
	
	float errNow_Lds;//��ǰ���
	float ctrOut_Lds;//���������
	
	/*PID�㷨�ڲ���������ֵ�����޸�*/
	float err_last_Lds;//��һ��ƫ��
	float erri_Lds;
	
}Stop_PID_AbsoluteType_L;

typedef struct
{
	/*PID�㷨�ӿڱ��������ڸ��û���ȡ���޸�PID�㷨������*/
	float Kp_Rds;
	float Ki_Rds;
	float Kd_Rds;
	float U_max_Rds;//����������
	float U_min_Rds;//����������
	
	float Need_Speed_Rds;//�����ٶ�
	float Actual_Speed_Rds;//ʵ���ٶ�
	
	float errNow_Rds;//��ǰ���
	float ctrOut_Rds;//���������
	
	/*PID�㷨�ڲ���������ֵ�����޸�*/
	float err_last_Rds;//��һ��ƫ��
	float erri_Rds;
	
}Stop_PID_AbsoluteType_R;

typedef struct 
{
	/*PID�㷨�ӿڱ��������ڸ��û���ȡ���޸�PID�㷨������*/
	float Kp_Lk;
	float Ki_Lk;
	float Kd_Lk;
	float U_max_Lk;//����������
	float U_min_Lk;//����������
	
	float Need_Speed_Lk;//�����ٶ�
	float Actual_Speed_Lk;//ʵ���ٶ�
	
	float errNow_Lk;//��ǰ���
	float ctrOut_Lk;//���������
	
	/*PID�㷨�ڲ���������ֵ�����޸�*/
	float err_last_Lk;//��һ��ƫ��
	float erri_Lk;
	
}D_PID_AbsoluteType_L;

typedef struct 
{
	/*PID�㷨�ӿڱ��������ڸ��û���ȡ���޸�PID�㷨������*/
	float Kp_Rk;
	float Ki_Rk;
	float Kd_Rk;
	float U_max_Rk;//����������
	float U_min_Rk;//����������
	
	float Need_Speed_Rk;//�����ٶ�
	float Actual_Speed_Rk;//ʵ���ٶ�
	
	float errNow_Rk;//��ǰ���
	float ctrOut_Rk;//���������
	
	/*PID�㷨�ڲ���������ֵ�����޸�*/
	float err_last_Rk;//��һ��ƫ��
	float erri_Rk;
	
}D_PID_AbsoluteType_R;

typedef struct 
{
	/*PID�㷨�ӿڱ��������ڸ��û���ȡ���޸�PID�㷨������*/
	float Kp_Lsk;
	float Ki_Lsk;
	float Kd_Lsk;
	float U_max_Lsk;//����������
	float U_min_Lsk;//����������
	
	float Need_Speed_Lsk;//�����ٶ�
	float Actual_Speed_Lsk;//ʵ���ٶ�
	
	float errNow_Lsk;//��ǰ���
	float ctrOut_Lsk;//���������
	
	/*PID�㷨�ڲ���������ֵ�����޸�*/
	float err_last_Lsk;//��һ��ƫ��
	float erri_Lsk;
	
}DT_PID_AbsoluteType_L;

typedef struct
{
	/*PID�㷨�ӿڱ��������ڸ��û���ȡ���޸�PID�㷨������*/
	float Kp_Rsk;
	float Ki_Rsk;
	float Kd_Rsk;
	float U_max_Rsk;//����������
	float U_min_Rsk;//����������
	
	float Need_Speed_Rsk;//�����ٶ�
	float Actual_Speed_Rsk;//ʵ���ٶ�
	
	float errNow_Rsk;//��ǰ���
	float ctrOut_Rsk;//���������
	
	/*PID�㷨�ڲ���������ֵ�����޸�*/
	float err_last_Rsk;//��һ��ƫ��
	float erri_Rsk;
	
}DT_PID_AbsoluteType_R;

# endif 
