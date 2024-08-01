# ifndef _PID_H_
# define _PID_H_

# include <stdio.h>
# include "typedef.h"
# include "oled.h"

# define PID_MAX 500
# define PID_MIN -500


//pid初始化
void PID_Init(void);
//绝对式pid
float T_PID_AbsoluteMode_L(float speed);
float T_PID_AbsoluteMode_R(float speed);
float Z_PID_AbsoluteMode_L(float speed);
float Z_PID_AbsoluteMode_R(float speed);
float W_PID_AbsoluteMode_L(float speed);
float W_PID_AbsoluteMode_R(float speed);
float Stop_PID_L(float speed);
float Stop_PID_R(float speed);
float D_PID_AbsoluteMode_L(float speed);
float D_PID_AbsoluteMode_R(float speed);
float DT_PID_AbsoluteMode_L(float speed);
float DT_PID_AbsoluteMode_R(float speed);


void PID_I_clear(void);

extern int PWM_L, PWM_R;
extern Z_PID_AbsoluteType_R PIDs;
extern Z_PID_AbsoluteType_L PID;
extern T_PID_AbsoluteType_L pid;
extern T_PID_AbsoluteType_R pids;
extern W_PID_AbsoluteType_L W_pid;
extern W_PID_AbsoluteType_R Ws_pid;


# endif
