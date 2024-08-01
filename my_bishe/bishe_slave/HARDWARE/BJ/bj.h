#ifndef _BJ_H_
#define _BJ_H_

#include "delay.h"
#include "sys.h"


#define PUL1 PBout(7)
#define DIR1 PBout(9)

#define GUANGMING_ZT GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_10)


void stepper_init(void);
void conter_stepper1(int tim,float angle,float xifen,int dir);

#endif


