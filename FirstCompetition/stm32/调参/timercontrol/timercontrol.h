# ifndef _TIMERCONTROL_H_
# define _TIMERCONTROL_H_

# include <sys.h>
# include "motor.h"
# include "encounter.h"

# define BLACK 1
# define WHITE 0

typedef enum
{
	Small = 1, Middle, Big
}Zhuang_time;

//S M L 代表大中小时间
//# define Zhuangquan_time_S	200
//# define Zhuangquan_time_M	150
//# define Zhuangquan_time_L	90

# define Stop_times			15 //10
# define Stop_timer  		15	//10 该处时间不能超过 Road_timess
# define Zhuangwang_time    100
# define Grap_times			100//100
# define Grap_N_times		100//100
# define Hou_times			80
# define Hou_timess			20
# define oled_time_s		100
# define Close_times		0
# define Close_timess		0
# define BJ_fall_times      400
# define BJ_fall_timess		250
# define BJ_up_times        600
# define BJ_up_timess       600
# define Wukuai_grap_times  50
# define Wukuai_release_times 70
# define Mapan_zhuang_times 50
# define Road_timessss      50//80
# define Road_timeesss      100
# define Hou_timesss		Hou_times-Hou_timess//Hou_times-Hou_timess
//# define Tiao_timer			110
//# define qianjin_time_s 	100
//# define time_Right_s		50
//# define time_Left_s		40

//正常前进速度
# define qianjin_PWM_Left  45//60
# define qianjin_PWM_Right 45//60
//调整车状态
//# define Need_PWM_Left_S	   300
//# define Need_PWM_Right_S	   25
# define Need_PWM_Left_M	   16
# define Need_PWM_Right_M	   0
# define Need_PWM_Left_L	   45//80
# define Need_PWM_Right_L	   40//75

//# define Need_PWM_Left_YS	   30
//# define Need_PWM_Right_YS	   300
# define Need_PWM_Left_YM	   0
# define Need_PWM_Right_YM	   16
# define Need_PWM_Left_YL	   40//75
# define Need_PWM_Right_YL	   45//80

//# define Hou_PWM_L			   -60
//# define Hou_PWM_R			   -60

//# define Hou_PWM_Left_M		   -75
//# define Hou_PWM_Right_M	   -68
//# define Hou_PWM_Left_L		   -70
//# define Hou_PWM_Right_L	   -62
//	
//# define Hou_PWM_Left_YM	   -68
//# define Hou_PWM_Right_YM	   -75
//# define Hou_PWM_Left_YL	   -62
//# define Hou_PWM_Right_YL	   -70


//左转
# define Zhuang_PWM_Left_Z		-24	//-110
# define Zhuang_PWM_Right_Z		24	//80
//右转
# define Zhuang_PWM_Left_Y 		24	  //65
# define Zhuang_PWM_Right_Y		-24   //-110
//180
# define Zhuang_PWM_Left_180		-28 //-90
# define Zhuang_PWM_Right_180		 28 //50



# define Road_times 		   75//4
# define Road_timess		   100//180
# define Road_timesss		   2//倒车后计数间隔


//存储光电信息
# define get_G_1 (0x01&Guang_Data)>>0
# define get_G_2 (0x02&Guang_Data)>>1
# define get_G_3 (0x04&Guang_Data)>>2
# define get_G_4 (0x08&Guang_Data)>>3
# define get_G_5 (0x10&Guang_Data)>>4
# define get_G_6 (0x20&Guang_Data)>>5
# define get_G_7 (0x40&Guang_Data)>>6
	
//功能函数
void TIM2_PWM_Init(u32 arr, u32 psc);//pwm
void TIM5_Zt_Init(u32 arr, u32 psc);//状态检测
void TIM6_Init(u32 arr, u32 psc);//定时器


//捕获编码器数值
void TIM3_INT_Init(void);
void TIM4_INT_Init(void);
void time_fuzhi(int flag);
void Xun_ji(void);
void Encounter_Road(void);
void Zi_Zhuang(void);
void Store_Guang_Zt(void);
//void Find_flag(int flag);

extern void Zhuangdu(float angle);

extern int PWM_L, PWM_R;
extern char ZT_Flag;
extern char xiu_flag;
extern char Road_flag;
extern char Zhuang_Xiang_flag;
extern float Yaw;
extern float zhuangwang_angle;

extern int tiao_time;
extern int P_flag;
extern int Close_XJ_time;
extern int Close_XJ_timee;

extern int X_process[100];
extern int X_Location_message[100];
//extern int Road_Count;
extern int X_now_pos;
extern int Y_now_pos;
extern int Y_need_pos;

# endif
