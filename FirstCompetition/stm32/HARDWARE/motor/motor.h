# ifndef _MOTOR_H_
# define _MOTOR_H_

# include <sys.h>
# include <oled.h>

//pwm输出范围
# define PWM_MAX 1000
# define PWM_MIN -1000

/*********光电引脚*****************/
# define H_1	PCin(2) 
# define H_2 	PAin(0)
# define H_3 	PCin(4)
# define H_4	PCin(5)
# define H_5 	PCin(0)
# define H_6 	PCin(3) 
# define H_7	PCin(1)//触手
//# define H_7		PCin(13)



typedef enum {BLACKs = 0, WHITEs}Guang;


//功能函数
void Limit(float *motoA, float *motoB);
void Load(float moto1, float moto2);
void ALL_RCC_GPIO_Init(void);


# endif 
