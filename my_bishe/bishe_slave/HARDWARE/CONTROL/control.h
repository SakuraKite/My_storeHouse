#ifndef _CONTROL_H_
#define _CONTROL_H_

#include <sys.h>
#include "uart.h"
#include "my_typedef.h"
//typedef enum{
//OFF = 0, OPEN 
//}ZT;

//typedef enum{
//	RUNNING = 4, SUSPENDING
//}PROGRESS_ZT;

//typedef struct DATA_MK
//{
//	float temp;
//}DATA_MK;

//typedef struct DEMO
//{
//	int _key;
//	int _mutex;
//	DATA_MK _data;
//}SMART_HOME;



extern struct DEMO Smart_home;
extern char g_oledflg;

#endif

