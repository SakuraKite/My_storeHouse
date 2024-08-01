# include "pid.h"

//---------------------------------------------------------
Z_PID_AbsoluteType_L PID;

void Z_PID_Init_L(void)
{	PID.Kp_L = 25;   // 35
	
	PID.Ki_L = 0.05;  	 // 
	PID.Kd_L = 0;

	PID.Actual_Speed_L = 0;//实际速度
	PID.Need_Speed_L   = 0;//期望速度
	
	PID.U_max_L = 1800;
	PID.U_min_L = -1800;
	
	PID.ctrOut_L   = 0;//输出量
	PID.errNow_L   = 0;//当前误差
	PID.err_last_L = 0;//上一次误差
	PID.erri_L     = 0;
	
};

Z_PID_AbsoluteType_R PIDs;

void Z_PID_Init_R(void)
{	PIDs.Kp_R = 20;   //25

	PIDs.Ki_R = 0.06;  //0 
	PIDs.Kd_R = 0;
	
	PIDs.Actual_Speed_R = 0;//实际速度
	PIDs.Need_Speed_R   = 0;//期望速度
	
	PIDs.U_max_R = 1800;
	PIDs.U_min_R = -1800;
	
	PIDs.ctrOut_R   = 0;//输出量
	PIDs.errNow_R   = 0;//当前误差
	PIDs.err_last_R = 0;//上一次误差
	PIDs.erri_R     = 0;
	
};
//---------------------------------------------------

T_PID_AbsoluteType_L pid;					//左右调PID还得改

void T_PID_Init_L(void)
{	pid.Kp_Ls = 25; //40

	pid.Ki_Ls = 0.1;//0.5
	pid.Kd_Ls = 0;

	pid.Actual_Speed_Ls = 0;//实际速度
	pid.Need_Speed_Ls  = 0;//期望速度
	
	pid.U_max_Ls = 1800;
	pid.U_min_Ls = -1800;
	
	pid.ctrOut_Ls   = 0;//输出量
	pid.errNow_Ls   = 0;//当前误差
	pid.err_last_Ls = 0;//上一次误差
	pid.erri_Ls     = 0;
	
};

T_PID_AbsoluteType_R pids;

void T_PID_Init_R(void)
{	
	pids.Kp_Rs = 25;//30
	pids.Ki_Rs = 0.1;//0.4
	pids.Kd_Rs = 0;
	
	pids.Actual_Speed_Rs = 0;//实际速度
	pids.Need_Speed_Rs   = 0;//期望速度
	
	pids.U_max_Rs = 1800;
	pids.U_min_Rs = -1800;
	
	pids.ctrOut_Rs   = 0;//输出量
	pids.errNow_Rs   = 0;//当前误差
	pids.err_last_Rs = 0;//上一次误差
	pids.erri_Rs     = 0;
};

//-------------------------------------------------

W_PID_AbsoluteType_L W_pid;

void W_PID_Init_L(void)
{	W_pid.Kp_Ld = 35;  //15
	
	W_pid.Ki_Ld = 1.2;  //1
	W_pid.Kd_Ld = 0;

	W_pid.Actual_Speed_Ld = 0;//实际速度
	W_pid.Need_Speed_Ld  = 0;//期望速度 -24.62 == 0
	
	W_pid.U_max_Ld = 1800;
	W_pid.U_min_Ld = -1800;
	
	W_pid.ctrOut_Ld   = 0;//输出量
	W_pid.errNow_Ld   = 0;//当前误差
	W_pid.err_last_Ld = 0;//上一次误差
	W_pid.erri_Ld     = 0;
	
};

W_PID_AbsoluteType_R Ws_pid;

void W_PID_Init_R(void)
{	Ws_pid.Kp_Rd = 35;   //15
	
	Ws_pid.Ki_Rd = 1.2;  //1
	Ws_pid.Kd_Rd = 0;
	
	Ws_pid.Actual_Speed_Rd = 0;//实际速度
	Ws_pid.Need_Speed_Rd   = 0;//期望速度
	
	Ws_pid.U_max_Rd = 1800;
	Ws_pid.U_min_Rd = -1800;
	
	Ws_pid.ctrOut_Rd   = 0;//输出量
	Ws_pid.errNow_Rd   = 0;//当前误差
	Ws_pid.err_last_Rd = 0;//上一次误差
	Ws_pid.erri_Rd     = 0;
};

Stop_PID_AbsoluteType_L Stop_pid;

void Stop_PID_Init_L(void)
{
	Stop_pid.Kp_Lds = 10;
	//Stop_pid.Ki_Lds = 0.1;
	Stop_pid.Ki_Lds = 0;
	Stop_pid.Kd_Lds = 0;
	
	Stop_pid.Actual_Speed_Lds = 0;
	Stop_pid.Need_Speed_Lds = 0;
	
	Stop_pid.U_max_Lds = 1800;
	Stop_pid.U_min_Lds = -1800;
	
	Stop_pid.ctrOut_Lds = 0;
	Stop_pid.errNow_Lds = 0;
	Stop_pid.err_last_Lds = 0;
	Stop_pid.erri_Lds = 0;
}


Stop_PID_AbsoluteType_R Stops_pid;

void Stop_PID_Init_R(void)
{
	Stops_pid.Kp_Rds = 10;
//	Stops_pid.Ki_Rds = 0.1;
	Stops_pid.Ki_Rds = 0;
	Stops_pid.Kd_Rds = 0;
	
	Stops_pid.Actual_Speed_Rds = 0;
	Stops_pid.Need_Speed_Rds = 0;
	
	Stops_pid.U_max_Rds = 1800;
	Stops_pid.U_min_Rds = -1800;
	
	Stops_pid.ctrOut_Rds = 0;
	Stops_pid.errNow_Rds = 0;
	Stops_pid.err_last_Rds = 0;
	Stops_pid.erri_Rds = 0;
}

D_PID_AbsoluteType_L Dao_Pid_L;

void Dao_PID_Init_L(void)
{
	Dao_Pid_L.Kp_Lk = 25;
	Dao_Pid_L.Ki_Lk = 0.08;//0.005
	Dao_Pid_L.Kd_Lk = 0;
	
	Dao_Pid_L.Actual_Speed_Lk = 0;
	Dao_Pid_L.Need_Speed_Lk = 0;//期望速度;
	
	Dao_Pid_L.U_max_Lk = 1800;
	Dao_Pid_L.U_min_Lk = -1800;
	
	Dao_Pid_L.ctrOut_Lk = 0;
	Dao_Pid_L.errNow_Lk = 0;
	Dao_Pid_L.err_last_Lk = 0;
	Dao_Pid_L.erri_Lk = 0;
}

D_PID_AbsoluteType_R Dao_Pid_R;

void Dao_PID_Init_R(void)
{
	Dao_Pid_R.Kp_Rk = 27;//27
	Dao_Pid_R.Ki_Rk = 0.1;//0.01
	Dao_Pid_R.Kd_Rk = 0;
	
	Dao_Pid_R.Actual_Speed_Rk = 0;
	Dao_Pid_R.Need_Speed_Rk = 0;//期望速度;
	
	Dao_Pid_R.U_max_Rk = 1800;
	Dao_Pid_R.U_min_Rk = -1800;
	
	Dao_Pid_R.ctrOut_Rk = 0;
	Dao_Pid_R.errNow_Rk = 0;
	Dao_Pid_R.err_last_Rk = 0;
	Dao_Pid_R.erri_Rk = 0;
}

DT_PID_AbsoluteType_L Dao_Tiao_L;

void Dao_T_PID_Init_L(void)
{
	Dao_Tiao_L.Kp_Lsk = 30;
	Dao_Tiao_L.Ki_Lsk = 0;
	Dao_Tiao_L.Kd_Lsk = 0;
	
	Dao_Tiao_L.Actual_Speed_Lsk = 0;
	Dao_Tiao_L.Need_Speed_Lsk = 0;//期望速度;;
	
	Dao_Tiao_L.U_max_Lsk = 1800;
	Dao_Tiao_L.U_min_Lsk = -1800;
	
	Dao_Tiao_L.ctrOut_Lsk = 0;
	Dao_Tiao_L.errNow_Lsk = 0;
	Dao_Tiao_L.err_last_Lsk = 0;
	Dao_Tiao_L.erri_Lsk = 0;
}	

DT_PID_AbsoluteType_R Dao_Tiao_R;

void Dao_T_PID_Init_R(void)
{
	Dao_Tiao_R.Kp_Rsk = 30;
	Dao_Tiao_R.Ki_Rsk = 0;
	Dao_Tiao_R.Kd_Rsk = 0;
	
	Dao_Tiao_R.Actual_Speed_Rsk = 0;
	Dao_Tiao_R.Need_Speed_Rsk = 0;//期望速度;;;
	
	Dao_Tiao_R.U_max_Rsk = 1800;
	Dao_Tiao_R.U_min_Rsk = -1800;
	
	Dao_Tiao_R.ctrOut_Rsk = 0;
	Dao_Tiao_R.errNow_Rsk = 0;
	Dao_Tiao_R.err_last_Rsk = 0;
	Dao_Tiao_R.erri_Rsk = 0;
}

//----------------------------------------------------------------


void PID_Init(void)
{
	T_PID_Init_L();
	T_PID_Init_R();
	Z_PID_Init_L();
    Z_PID_Init_R();
	W_PID_Init_L();
	W_PID_Init_R();
	Stop_PID_Init_L();
	Stop_PID_Init_R();
	Dao_PID_Init_L();
	Dao_PID_Init_R();
	Dao_T_PID_Init_L();
	Dao_T_PID_Init_R();
}

//----------------------------------------------------------------
/*限幅errI的大小*/
//(左轮)
void Limit_I_L(float *p)
{
	if (*p > PID.U_max_L) *p = PID.U_max_L;
	if (*p < PID.U_min_L) *p = PID.U_min_L;
}
//（右轮）
void Limit_I_R(float *q)
{	
	if (*q > PIDs.U_max_R) *q = PIDs.U_max_R;
	if (*q < PIDs.U_min_R) *q = PIDs.U_min_R;
}

//限幅pid计算的结果
float xianfu(float *p)
{
	return (*p>PID_MAX)?PID_MAX:( (*p<PID_MIN)?PID_MIN:*p );
}

//----------------------------------------------------------------

float T_PID_AbsoluteMode_L(float speed)
{
	
	pid.Need_Speed_Ls = PWM_L;//期望速度
	pid.Actual_Speed_Ls = speed;
	pid.errNow_Ls = pid.Need_Speed_Ls - pid.Actual_Speed_Ls;
	pid.erri_Ls += pid.errNow_Ls;
	Limit_I_L(&pid.erri_Ls);
	pid.ctrOut_Ls = pid.Kp_Ls*pid.errNow_Ls + pid.Ki_Ls*pid.erri_Ls;
	
	pid.ctrOut_Ls = xianfu(&pid.ctrOut_Ls);

	return pid.ctrOut_Ls;
	
}


float T_PID_AbsoluteMode_R(float speed)
{
	pids.Need_Speed_Rs = PWM_R;//期望速度
	pids.Actual_Speed_Rs = speed;
	pids.errNow_Rs = pids.Need_Speed_Rs - pids.Actual_Speed_Rs;
	pids.erri_Rs += pids.errNow_Rs;
	Limit_I_R(&pids.erri_Rs);
	pids.ctrOut_Rs = pids.Kp_Rs*pids.errNow_Rs + pids.Ki_Rs*pids.erri_Rs;
	
//	pids.err_last_Rs = pids.errNow_Rs;
//	pids.Actual_Speed_Rs = pids.ctrOut_Rs * 1.0;
	
	pids.ctrOut_Rs = xianfu(&pids.ctrOut_Rs);

	return pids.ctrOut_Rs;
	
}

float Z_PID_AbsoluteMode_L(float speed)
{
	
	PID.Need_Speed_L = PWM_L;//期望速度
	PID.Actual_Speed_L = speed;
	PID.errNow_L = PID.Need_Speed_L - PID.Actual_Speed_L;
	PID.erri_L += PID.errNow_L;
	Limit_I_L(&PID.erri_L);
	PID.ctrOut_L = PID.Kp_L*PID.errNow_L + PID.Ki_L*PID.erri_L;
	
//	PID.err_last_L = PID.errNow_L;
	//PID.Actual_Speed_L = PID.ctrOut_L * 1.0;
	
	PID.ctrOut_L = xianfu(&PID.ctrOut_L);

	return PID.ctrOut_L;
	
	
}


float Z_PID_AbsoluteMode_R(float speed)
{
	PIDs.Need_Speed_R = PWM_R;//期望速度
	PIDs.Actual_Speed_R = speed;

	PIDs.errNow_R = PIDs.Need_Speed_R - PIDs.Actual_Speed_R;
	PIDs.erri_R += PIDs.errNow_R;
	Limit_I_R(&PIDs.erri_R);
	PIDs.ctrOut_R = PIDs.Kp_R*PIDs.errNow_R + PIDs.Ki_R*PIDs.erri_R;
	
	//PIDs.err_last_R = PIDs.errNow_R;//D时用到的变量
	//PIDs.Actual_Speed_R = PIDs.ctrOut_R * 1.0;
	
	PIDs.ctrOut_R = xianfu(&PIDs.ctrOut_R);

	return PIDs.ctrOut_R;
	
	
}

/****转弯PID****/
float W_PID_AbsoluteMode_L(float speed)
{
	W_pid.Need_Speed_Ld  = PWM_L;//期望速度
	W_pid.Actual_Speed_Ld = speed;
	if (W_pid.Need_Speed_Ld > 0)
	{
		W_pid.errNow_Ld = W_pid.Need_Speed_Ld - W_pid.Actual_Speed_Ld;
	}
	else
	{
		W_pid.errNow_Ld = -W_pid.Actual_Speed_Ld + W_pid.Need_Speed_Ld;
	}
	
	W_pid.erri_Ld += W_pid.errNow_Ld;
	Limit_I_L(&W_pid.erri_Ld);
	W_pid.ctrOut_Ld = W_pid.Kp_Ld*W_pid.errNow_Ld + W_pid.Ki_Ld*W_pid.erri_Ld;
	
	W_pid.err_last_Ld = W_pid.errNow_Ld;
	W_pid.Actual_Speed_Ld = W_pid.ctrOut_Ld * 1.0;
	
	W_pid.Actual_Speed_Ld = xianfu(&W_pid.Actual_Speed_Ld);

	return W_pid.Actual_Speed_Ld;
	
	
}


float W_PID_AbsoluteMode_R(float speed)
{
	Ws_pid.Need_Speed_Rd   = PWM_R;//期望速度
	Ws_pid.Actual_Speed_Rd = speed;
	if (Ws_pid.Need_Speed_Rd > 0)
	{
		Ws_pid.errNow_Rd = Ws_pid.Need_Speed_Rd - Ws_pid.Actual_Speed_Rd;
	}
	else
	{
		Ws_pid.errNow_Rd = -Ws_pid.Actual_Speed_Rd + Ws_pid.Need_Speed_Rd;
	}
	
	Ws_pid.erri_Rd += Ws_pid.errNow_Rd;
	Limit_I_R(&Ws_pid.erri_Rd);
	Ws_pid.ctrOut_Rd = Ws_pid.Kp_Rd*Ws_pid.errNow_Rd + Ws_pid.Ki_Rd*Ws_pid.erri_Rd;
	
	Ws_pid.err_last_Rd = Ws_pid.errNow_Rd;
	Ws_pid.Actual_Speed_Rd = Ws_pid.ctrOut_Rd * 1.0;
	
	Ws_pid.Actual_Speed_Rd = xianfu(&Ws_pid.Actual_Speed_Rd);

	return Ws_pid.Actual_Speed_Rd;
	
	
}


float Stop_PID_L(float speed)
{
	Stop_pid.Need_Speed_Lds = 0;//期望速度
	Stop_pid.Actual_Speed_Lds = speed;
	Stop_pid.errNow_Lds = Stop_pid.Need_Speed_Lds - Stop_pid.Actual_Speed_Lds;
	Stop_pid.erri_Lds += Stop_pid.errNow_Lds;
	Limit_I_R(&Stop_pid.erri_Lds);
	Stop_pid.ctrOut_Lds = Stop_pid.Kp_Lds*Stop_pid.errNow_Lds + Stop_pid.Ki_Lds*Stop_pid.erri_Lds;
	
	Stop_pid.ctrOut_Lds = xianfu(&Stop_pid.ctrOut_Lds);
	
	return Stop_pid.ctrOut_Lds;
}


float Stop_PID_R(float speed)
{
	Stops_pid.Need_Speed_Rds = 0;//期望速度
	Stops_pid.Actual_Speed_Rds = speed;
	Stops_pid.errNow_Rds = Stops_pid.Need_Speed_Rds - Stops_pid.Actual_Speed_Rds;
	Stops_pid.erri_Rds += Stops_pid.errNow_Rds;
	Limit_I_R(&Stops_pid.erri_Rds);
	Stops_pid.ctrOut_Rds = Stops_pid.Kp_Rds*Stops_pid.errNow_Rds + Stops_pid.Ki_Rds*Stops_pid.erri_Rds;
	
	Stops_pid.ctrOut_Rds = xianfu(&Stops_pid.ctrOut_Rds);
	
	return Stops_pid.ctrOut_Rds;
	
}

float D_PID_AbsoluteMode_L(float speed)
{
	Dao_Pid_L.Need_Speed_Lk = -30;//期望速度 -20
	Dao_Pid_L.Actual_Speed_Lk = speed;
	Dao_Pid_L.errNow_Lk = Dao_Pid_L.Need_Speed_Lk - Dao_Pid_L.Actual_Speed_Lk;
	Dao_Pid_L.erri_Lk += Dao_Pid_L.errNow_Lk;
	Limit_I_L(&Dao_Pid_L.erri_Lk);
	Dao_Pid_L.ctrOut_Lk = Dao_Pid_L.Kp_Lk*Dao_Pid_L.errNow_Lk + Dao_Pid_L.Ki_Lk*Dao_Pid_L.erri_Lk;
	
	Dao_Pid_L.ctrOut_Lk = xianfu(&Dao_Pid_L.ctrOut_Lk);

	return Dao_Pid_L.ctrOut_Lk;
}

float D_PID_AbsoluteMode_R(float speed)
{
	Dao_Pid_R.Need_Speed_Rk = -30;//期望速度 -20
	Dao_Pid_R.Actual_Speed_Rk = speed;
	Dao_Pid_R.errNow_Rk = Dao_Pid_R.Need_Speed_Rk - Dao_Pid_R.Actual_Speed_Rk;
	Dao_Pid_R.erri_Rk += Dao_Pid_R.errNow_Rk;
	Limit_I_R(&Dao_Pid_R.erri_Rk);
	Dao_Pid_R.ctrOut_Rk = Dao_Pid_R.Kp_Rk*Dao_Pid_R.errNow_Rk + Dao_Pid_R.Ki_Rk*Dao_Pid_R.erri_Rk;
	
	Dao_Pid_R.ctrOut_Rk = xianfu(&Dao_Pid_R.ctrOut_Rk);

	return Dao_Pid_R.ctrOut_Rk;
}

float DT_PID_AbsoluteMode_L(float speed)
{
	Dao_Tiao_L.Need_Speed_Lsk = PWM_L;//期望速度
	Dao_Tiao_L.Actual_Speed_Lsk = speed;
	Dao_Tiao_L.errNow_Lsk = Dao_Tiao_L.Need_Speed_Lsk - Dao_Tiao_L.Actual_Speed_Lsk;
	Dao_Tiao_L.erri_Lsk += Dao_Tiao_L.errNow_Lsk;
	Limit_I_L(&Dao_Tiao_L.erri_Lsk);
	Dao_Tiao_L.ctrOut_Lsk = Dao_Tiao_L.Kp_Lsk*Dao_Tiao_L.errNow_Lsk + Dao_Tiao_L.Ki_Lsk*Dao_Tiao_L.erri_Lsk;
	
	Dao_Tiao_L.err_last_Lsk = Dao_Tiao_L.errNow_Lsk;
	Dao_Tiao_L.Actual_Speed_Lsk = Dao_Tiao_L.ctrOut_Lsk;
	
	Dao_Tiao_L.Actual_Speed_Lsk = xianfu(&Dao_Tiao_L.Actual_Speed_Lsk);
	
	return Dao_Tiao_L.Actual_Speed_Lsk;
	
}

float DT_PID_AbsoluteMode_R(float speed)
{
	Dao_Tiao_R.Need_Speed_Rsk = PWM_R;//期望速度
	Dao_Tiao_R.Actual_Speed_Rsk = speed;
	Dao_Tiao_R.errNow_Rsk = Dao_Tiao_R.Need_Speed_Rsk - Dao_Tiao_R.Actual_Speed_Rsk;
	Dao_Tiao_R.erri_Rsk += Dao_Tiao_R.errNow_Rsk;
	Limit_I_R(&Dao_Tiao_R.erri_Rsk);
	Dao_Tiao_R.ctrOut_Rsk = Dao_Tiao_R.Kp_Rsk*Dao_Tiao_R.errNow_Rsk + Dao_Tiao_R.Ki_Rsk*Dao_Tiao_R.erri_Rsk;
	
	Dao_Tiao_R.err_last_Rsk = Dao_Tiao_R.errNow_Rsk;
	Dao_Tiao_R.Actual_Speed_Rsk = Dao_Tiao_R.ctrOut_Rsk;
	
	Dao_Tiao_R.Actual_Speed_Rsk = xianfu(&Dao_Tiao_R.Actual_Speed_Rsk);
	
	return Dao_Tiao_R.Actual_Speed_Rsk;
}
//-------------------------------------------------------

void PID_I_clear(void)
{
//	TIM3->CNT = 0;
//	TIM4->CNT = 0;
	PID.erri_L = 0;
	PIDs.erri_R = 0;
	
	pid.erri_Ls = 0;
	pids.erri_Rs = 0;
	
	W_pid.erri_Ld = 0;
	Ws_pid.erri_Rd = 0;
	
	Dao_Pid_L.erri_Lk = 0;
	Dao_Pid_R.erri_Rk = 0;
	
	Stop_pid.erri_Lds = 0;
	Stops_pid.erri_Rds = 0;
	
	Dao_Tiao_L.errNow_Lsk = 0;
	Dao_Tiao_R.erri_Rsk = 0;
}


