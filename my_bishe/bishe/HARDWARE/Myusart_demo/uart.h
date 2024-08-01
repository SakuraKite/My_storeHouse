#ifndef __UART_H
#define __UART_H	

#include "stdio.h"	
#include "sys.h" 
#include "string.h"
# include <stdlib.h>

#include "my_typedef.h"
  
//���⴮�ڷ���Ҫ����һ��.ini�ļ�
/*��������
mode com1 115200,0,8,1
assign com1 <s1in>s1out
*/
  
#define USART_REC_LEN  			200  	//�����������ֽ��� 200
#define EN_USART1_RX 			1		//ʹ�ܣ�1��/��ֹ��0������1����

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//�Ͷ�ģʽ
#define BYTE0(dwTemp)       (*( (char *)(&dwTemp)    ))   /* !< uint32_t ���ݲ�� byte0 */
#define BYTE1(dwTemp)       (*( (char *)(&dwTemp) + 1))   /* !< uint32_t ���ݲ�� byte1 */
#define BYTE2(dwTemp)       (*( (char *)(&dwTemp) + 2))   /* !< uint32_t ���ݲ�� byte2 */
#define BYTE3(dwTemp)       (*( (char *)(&dwTemp) + 3))   /* !< uint32_t ���ݲ�� byte3 */




//����ѡ��
# define Test_USART1			1
# define Test_USART2			1
# define Test_USART3			0
# define Test_USART3_PartialRemap			0//����3������ӳ��
# define Test_UART4				0
# define Test_UART5				0
# define SHOUJI_UART5			0

extern u8  USART_RX_BUF[USART_REC_LEN]; //���ջ���,���USART_REC_LEN���ֽ�.ĩ�ֽ�Ϊ���з� 
extern u16 USART_RX_STA;         		//����״̬���	
extern uint8_t g_TFminiPlus_flag;


//����봮���жϽ��գ��벻Ҫע�����º궨��
void uart_init(u32 bound);
void UART_Put_Num(unsigned long dat);
void UART_Put_Inf(char *inf,short dat);

void Usart1_Init(unsigned int baud);

void Wireless_Send(int16_t data, uint8_t Mode);//���߷��ͺ���
void DiMianZan(void);

void Usart_SendString(USART_TypeDef *USARTx, unsigned char *str, unsigned short len);

#endif
