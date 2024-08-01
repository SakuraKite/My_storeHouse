#ifndef __UART_H
#define __UART_H	

#include "stdio.h"	
#include "sys.h" 
#include "string.h"
# include <stdlib.h>

#include "my_typedef.h"
  
//虚拟串口仿真要创建一个.ini文件
/*内容如下
mode com1 115200,0,8,1
assign com1 <s1in>s1out
*/
  
#define USART_REC_LEN  			200  	//定义最大接收字节数 200
#define EN_USART1_RX 			1		//使能（1）/禁止（0）串口1接收

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//低端模式
#define BYTE0(dwTemp)       (*( (char *)(&dwTemp)    ))   /* !< uint32_t 数据拆分 byte0 */
#define BYTE1(dwTemp)       (*( (char *)(&dwTemp) + 1))   /* !< uint32_t 数据拆分 byte1 */
#define BYTE2(dwTemp)       (*( (char *)(&dwTemp) + 2))   /* !< uint32_t 数据拆分 byte2 */
#define BYTE3(dwTemp)       (*( (char *)(&dwTemp) + 3))   /* !< uint32_t 数据拆分 byte3 */




//串口选择
# define Test_USART1			1
# define Test_USART2			1
# define Test_USART3			0
# define Test_USART3_PartialRemap			0//串口3部分重映射
# define Test_UART4				0
# define Test_UART5				0
# define SHOUJI_UART5			0

extern u8  USART_RX_BUF[USART_REC_LEN]; //接收缓冲,最大USART_REC_LEN个字节.末字节为换行符 
extern u16 USART_RX_STA;         		//接收状态标记	
extern uint8_t g_TFminiPlus_flag;


//如果想串口中断接收，请不要注释以下宏定义
void uart_init(u32 bound);
void UART_Put_Num(unsigned long dat);
void UART_Put_Inf(char *inf,short dat);

void Usart1_Init(unsigned int baud);

void Wireless_Send(int16_t data, uint8_t Mode);//无线发送函数
void DiMianZan(void);

void Usart_SendString(USART_TypeDef *USARTx, unsigned char *str, unsigned short len);

#endif
