# ifndef _UART_H_
# define _UART_H_

# include <stm32f10x_rcc.h>
# include <stm32f10x_gpio.h>

# include <string.h>

# define ZHENLENGTH 1

/* ���Ŷ��� */
# define UART_GPIO GPIOC
# define UART_CKL  RCC_APB1Periph_UART4
//# define UART_Tx   GPIO_Pin_9
# define UART_Tx   GPIO_Pin_10
# define UART_Rx   GPIO_Pin_11

/**********************
//����������
***********************/
# define MAX 15

/************************
//ѡ������λ
************************/
# define DateBit_8 1	// DateBit_8 == 0 Ϊ2��֡ͷ������1֡ͷ��� 
								//@@��֡ͷ��ѡ�����������λΪ8λ����9λ��������λ����Ҫ����Ӳ����HC-06��ֻ��֧��8λ����λ
								

/****���ڳ�ʼ������*****/
void UART_Init(u32 bound);	//(������)
/*******�������ư巢�����ݺ���************/
void UART_IT_Puts(char *str, char len);
/**********����������*********************/
int StringToInteger(unsigned char *p);

void UART4_Init(u32 bound);
void UART4_Send_Data(u8 *buf,u16 len);
//void UART4_Configuration(void);
void UART4_Send_Byte(u8 Data);
void UART4_Send_String(u8 *Data) ;


extern char LSC_Collect[7];
extern char LSC_Zuo[7];
extern char LSC_Right[7];
extern char LSC_Release[7];
extern char LSC_Releases[7];
extern char LSC_Grap[7];
extern char LSC_L_Grap[7];
extern char Wu_Grap[7];
extern char Wu_Graps[7];
extern char Wu_Release[35];
extern char Wu_Releases[42];
extern char Mapan_zhuang[35];
extern char Mapan_Init[7];


# endif
