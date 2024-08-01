# ifndef _ENCOUNTER_H_
# define _ENCOUNTER_H_

# include <sys.h>
# include "NVIC.h"

# define Test_1   0 // 1为测试模块
# define Test_2   0// 任务二第一部分测试模块
# define Test_2_two 0//任务二第二部分测试模块

//# define Right 1
//# define Left  2
//# define Zhi   3
//# define HouTui   4

//# define Xuan_0_Du	 50
//# define Xuan_45_Du  1
//# define Xuan_90_Du  2
//# define Xuan_135_Du 3
//# define Xuan_180_Du 100

typedef enum 
{
	freedom = 0, busy
}Task_ZT;

void Encounter_TIM3_Init(u16 arr, u16 psc);
short Read_Speed(int TIMx);
void Limit_Count(short *Count);

//-----------位置---------------------
void Pos_init(void);
void Jisuan_Target_Pos(void);
void Pos_Move(void);

void Zhuangdu(float angle);

extern char ZT_Flag;
extern char houtui_flag;
extern char Road_flag;

extern char qianjin_flag;
extern char stop_flag;
extern char zhuangwang_flag;
extern char xiu_flag;

extern int P_flag;
extern unsigned char ARR;
extern short Store_XJ;

extern u8 Guang_Data;
extern int X_now_pos;

extern unsigned char sign;

extern unsigned char color_Update(void);

//外部调用数组
extern char Wu_Release[35];
extern char Wu_Releases[42];
extern char Mapan_zhuang[35];
extern char Mapan_zhuangs[42];

# endif 
