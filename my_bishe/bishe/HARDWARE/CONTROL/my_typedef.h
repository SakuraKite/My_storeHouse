#ifndef _MY_TYPEDEF_H_
#define _MY_TYPEDEF_H_


typedef enum{
OFF = 0, OPEN, STOP
}ZT;

typedef enum{
	RUNNING = 4, SUSPENDING
}PROGRESS_ZT;



typedef struct DATA_MK
{
	float temperature_one;//Ĭ��һλС��
	unsigned char humidity_zero;
	char window_ZT_zero;// 0 or 1
	char chuanglian_ZT_zero;//0 or 1
	char fan_ZT_zero;
	char led_ZT_zero;
	
}DATA_MK;

typedef struct MK_FATHER
{
	int _key;
	int _mutex;
}MK_FATHER;

typedef struct DEMO
{
//	int _key;//��������
//	int _mutex;
	MK_FATHER window;
	DATA_MK _data;
	MK_FATHER chuanglian;
	MK_FATHER fan;
	MK_FATHER led;
//	int _chuanglian_key;
//	int _fan_key;//���ȿ���
//	int _led_key;
}SMART_HOME;


#endif 
