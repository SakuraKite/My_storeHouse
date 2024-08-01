# ifndef _NVIC_H_
# define _NVIC_H_

# include <misc.h>
# include <usart.h>

# include "oled.h"
# include "encounter.h"
# include "pid.h"
# include "motor.h"
# include "timercontrol.h"
# include "mpu6050.h" 
# include "inv_mpu.h"
# include "inv_mpu_dmp_motion_driver.h" 
# include "usart_4.h"
# include "driver.h"


# define qianjin 	1
# define stop       2
# define zhuangwang 3
# define grap       4
# define grap_N		5
# define houtui		6
# define bj_WZ_1	7
# define bj_WZ_2	8
# define bj_WZ_3	9
# define bj_WZ_4	10
# define bj_grap	11
# define bj_release 12
# define mapan_zhuang  13 
# define grap_Ns    14
# define bj_graps   15
# define graps		16
# define left_grap  17
# define right_grap	18
# define collect_grap 19

//测试模块 该测试模块主要为了方便单独测试转弯度数
# define Test 0

//功能函数
void NVIC_ALL_Init(void);

void qian_Pid(void);
void Zi_Zhuang_Pid(void);
void Stop_Pid(void);
void houtui_Pid(void);
void Zhuang_Su(void);


extern char qianjin_flag;
extern char stop_flag;
extern char zhuangwang_flag;
extern char xiu_flag;

extern int qianjin_time;
extern int PWM_L, PWM_R;
extern int Road_time;
extern int Road_timee;
extern int Road_timeer;
extern int Road_timeeeer;
extern int Road_timeeerr;
extern int stop_time;
extern int stop_time_r;
extern int zhuang_time_r;
extern int Grap_time;
extern int Grap_N_time;
extern int Hou_time;
extern int Hou_timee;
extern int Close_XJ_time;
extern int Close_XJ_timee;
extern int BJ_fall_time;
extern int BJ_up_time;
extern int BJ_up_timee;
extern int Wukuai_grap_time;
extern int Wukuai_release_time;
extern int Mapan_zhuang_time;
extern int BJ_fall_timee;
extern int Hou_timeee;
extern int P_time;
extern int Forward_time;

//extern int tiao_time;

//extern int Road_Count;

extern unsigned char table[7];


extern unsigned char ARR;
//本函数内的标志位
extern char ZT_Flag;
extern char houtui_flag;
//extern char Road_flag;


extern float zhuangwang_angle;


//外部调用
extern int X_now_pos;
extern int X_need_pos;
extern char ZT_finish;

extern int X_Location_message[100];//终点位置
extern int Y_Location_message[100];//终点位置
extern int do_carry[100];//中间动作
extern int do_advance[100];//预先动作
extern int X_process[100];//过程位置
extern int Y_process[100];//过程位置

extern char Copy_now_action[7];

extern float Yaw;
extern float Roll;
extern float Pitch;

extern int Zhuang_Cout;

//观察现象用的变量
extern int Kel;
extern int Jel;
extern unsigned char kk;

# endif
