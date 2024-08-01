# ifndef _TYPEDEF_H_
# define _TYPEDEF_H_

typedef struct 
{
	/*PID算法接口变量，用于给用户获取或修改PID算法的特性*/
	float Kp_L;
	float Ki_L;
	float Kd_L;
	float U_max_L;//误差积分上限
	float U_min_L;//误差积分下限
	
	float Need_Speed_L;//期望速度
	float Actual_Speed_L;//实际速度
	
	float errNow_L;//当前误差
	float ctrOut_L;//控制量输出
	
	/*PID算法内部变量，其值不能修改*/
	float err_last_L;//上一个偏差
	float erri_L;
	
}Z_PID_AbsoluteType_L;


typedef struct 
{
	/*PID算法接口变量，用于给用户获取或修改PID算法的特性*/
	float Kp_R;
	float Ki_R;
	float Kd_R;
	float U_max_R;//误差积分上限
	float U_min_R;//误差积分下限
	
	float Need_Speed_R;//期望速度
	float Actual_Speed_R;//实际速度
	
	float errNow_R;//当前误差
	float ctrOut_R;//控制量输出
	
	/*PID算法内部变量，其值不能修改*/
	float err_last_R;//上一个偏差
	float erri_R;
	
}Z_PID_AbsoluteType_R;


//左右调PID
typedef struct
{
	/*PID算法接口变量，用于给用户获取或修改PID算法的特性*/
	float Kp_Rs;
	float Ki_Rs;
	float Kd_Rs;
	float U_max_Rs;//误差积分上限
	float U_min_Rs;//误差积分下限
	
	float Need_Speed_Rs;//期望速度
	float Actual_Speed_Rs;//实际速度
	
	float errNow_Rs;//当前误差
	float ctrOut_Rs;//控制量输出
	
	/*PID算法内部变量，其值不能修改*/
	float err_last_Rs;//上一个偏差
	float erri_Rs;
	
}T_PID_AbsoluteType_R;


typedef struct 
{
	/*PID算法接口变量，用于给用户获取或修改PID算法的特性*/
	float Kp_Ls;
	float Ki_Ls;
	float Kd_Ls;
	float U_max_Ls;//误差积分上限
	float U_min_Ls;//误差积分下限
	
	float Need_Speed_Ls;//期望速度
	float Actual_Speed_Ls;//实际速度
	
	float errNow_Ls;//当前误差
	float ctrOut_Ls;//控制量输出
	
	/*PID算法内部变量，其值不能修改*/
	float err_last_Ls;//上一个偏差
	float erri_Ls;
	
}T_PID_AbsoluteType_L;

typedef struct 
{
	/*PID算法接口变量，用于给用户获取或修改PID算法的特性*/
	float Kp_Ld;
	float Ki_Ld;
	float Kd_Ld;
	float U_max_Ld;//误差积分上限
	float U_min_Ld;//误差积分下限
	
	float Need_Speed_Ld;//期望速度
	float Actual_Speed_Ld;//实际速度
	
	float errNow_Ld;//当前误差
	float ctrOut_Ld;//控制量输出
	
	/*PID算法内部变量，其值不能修改*/
	float err_last_Ld;//上一个偏差
	float erri_Ld;
	
}W_PID_AbsoluteType_L;

typedef struct
{
	/*PID算法接口变量，用于给用户获取或修改PID算法的特性*/
	float Kp_Rd;
	float Ki_Rd;
	float Kd_Rd;
	float U_max_Rd;//误差积分上限
	float U_min_Rd;//误差积分下限
	
	float Need_Speed_Rd;//期望速度
	float Actual_Speed_Rd;//实际速度
	
	float errNow_Rd;//当前误差
	float ctrOut_Rd;//控制量输出
	
	/*PID算法内部变量，其值不能修改*/
	float err_last_Rd;//上一个偏差
	float erri_Rd;
	
}W_PID_AbsoluteType_R;

typedef struct 
{
	/*PID算法接口变量，用于给用户获取或修改PID算法的特性*/
	float Kp_Lds;
	float Ki_Lds;
	float Kd_Lds;
	float U_max_Lds;//误差积分上限
	float U_min_Lds;//误差积分下限
	
	float Need_Speed_Lds;//期望速度
	float Actual_Speed_Lds;//实际速度
	
	float errNow_Lds;//当前误差
	float ctrOut_Lds;//控制量输出
	
	/*PID算法内部变量，其值不能修改*/
	float err_last_Lds;//上一个偏差
	float erri_Lds;
	
}Stop_PID_AbsoluteType_L;

typedef struct
{
	/*PID算法接口变量，用于给用户获取或修改PID算法的特性*/
	float Kp_Rds;
	float Ki_Rds;
	float Kd_Rds;
	float U_max_Rds;//误差积分上限
	float U_min_Rds;//误差积分下限
	
	float Need_Speed_Rds;//期望速度
	float Actual_Speed_Rds;//实际速度
	
	float errNow_Rds;//当前误差
	float ctrOut_Rds;//控制量输出
	
	/*PID算法内部变量，其值不能修改*/
	float err_last_Rds;//上一个偏差
	float erri_Rds;
	
}Stop_PID_AbsoluteType_R;

typedef struct 
{
	/*PID算法接口变量，用于给用户获取或修改PID算法的特性*/
	float Kp_Lk;
	float Ki_Lk;
	float Kd_Lk;
	float U_max_Lk;//误差积分上限
	float U_min_Lk;//误差积分下限
	
	float Need_Speed_Lk;//期望速度
	float Actual_Speed_Lk;//实际速度
	
	float errNow_Lk;//当前误差
	float ctrOut_Lk;//控制量输出
	
	/*PID算法内部变量，其值不能修改*/
	float err_last_Lk;//上一个偏差
	float erri_Lk;
	
}D_PID_AbsoluteType_L;

typedef struct 
{
	/*PID算法接口变量，用于给用户获取或修改PID算法的特性*/
	float Kp_Rk;
	float Ki_Rk;
	float Kd_Rk;
	float U_max_Rk;//误差积分上限
	float U_min_Rk;//误差积分下限
	
	float Need_Speed_Rk;//期望速度
	float Actual_Speed_Rk;//实际速度
	
	float errNow_Rk;//当前误差
	float ctrOut_Rk;//控制量输出
	
	/*PID算法内部变量，其值不能修改*/
	float err_last_Rk;//上一个偏差
	float erri_Rk;
	
}D_PID_AbsoluteType_R;

typedef struct 
{
	/*PID算法接口变量，用于给用户获取或修改PID算法的特性*/
	float Kp_Lsk;
	float Ki_Lsk;
	float Kd_Lsk;
	float U_max_Lsk;//误差积分上限
	float U_min_Lsk;//误差积分下限
	
	float Need_Speed_Lsk;//期望速度
	float Actual_Speed_Lsk;//实际速度
	
	float errNow_Lsk;//当前误差
	float ctrOut_Lsk;//控制量输出
	
	/*PID算法内部变量，其值不能修改*/
	float err_last_Lsk;//上一个偏差
	float erri_Lsk;
	
}DT_PID_AbsoluteType_L;

typedef struct
{
	/*PID算法接口变量，用于给用户获取或修改PID算法的特性*/
	float Kp_Rsk;
	float Ki_Rsk;
	float Kd_Rsk;
	float U_max_Rsk;//误差积分上限
	float U_min_Rsk;//误差积分下限
	
	float Need_Speed_Rsk;//期望速度
	float Actual_Speed_Rsk;//实际速度
	
	float errNow_Rsk;//当前误差
	float ctrOut_Rsk;//控制量输出
	
	/*PID算法内部变量，其值不能修改*/
	float err_last_Rsk;//上一个偏差
	float erri_Rsk;
	
}DT_PID_AbsoluteType_R;

# endif 
