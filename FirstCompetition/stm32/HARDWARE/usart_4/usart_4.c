
#include "stm32f10x_usart.h"
#include "stm32f10x.h"
#include "usart_4.h"


char LSC_Release[7] = {0x55, 0x55, 0x05, 0x06, 0x01, 0x01, 0x00};
char LSC_Releases[7] = {0x55, 0x55, 0x05, 0x06, 0x02, 0x01, 0x00};

char LSC_Grap[7] = {0x55, 0x55, 0x05, 0x06, 0x00, 0x01, 0x00};
char LSC_L_Grap[7] = {0x55, 0x55, 0x05, 0x06, 0x03, 0x01, 0x00};//摞物块抓

char LSC_Zuo[7] = {0x55, 0x55, 0x05, 0x06, 0x04, 0x01, 0x00};//左撇
char LSC_Right[7] = {0x55, 0x55, 0x05, 0x06, 0x05, 0x01, 0x00};//右撇
char LSC_Collect[7] = {0x55, 0x55, 0x05, 0x06, 0x06, 0x01, 0x00};//聚拢物块

char Wu_Release[35] = {0x55, 0x55, 0x05, 0x06, 0x1e, 0x01, 0x00,//放A
					   0x55, 0x55, 0x05, 0x06, 0x1f, 0x01, 0x00,//放E
					   0x55, 0x55, 0x05, 0x06, 0x20, 0x01, 0x00,//放D
					   0x55, 0x55, 0x05, 0x06, 0x21, 0x01, 0x00,//放C
					   100};
char Wu_Releases[42] = {0x55, 0x55, 0x05, 0x06, 0x28, 0x01, 0x00,//放A
						0x55, 0x55, 0x05, 0x06, 0x1e, 0x01, 0x00,//放B
					    0x55, 0x55, 0x05, 0x06, 0x1f, 0x01, 0x00,//放C
					    0x55, 0x55, 0x05, 0x06, 0x20, 0x01, 0x00,//放D
					    0x55, 0x55, 0x05, 0x06, 0x21, 0x01, 0x00,//放E
						100};
					 
char Wu_Grap[7] = {0x55, 0x55, 0x05, 0x06, 0x28, 0x01, 0x00};//抓4个物块

char Wu_Graps[7] = {0x55, 0x55, 0x05, 0x06, 0x29, 0x01, 0x00};//抓5个物块

char Mapan_zhuang[35] = {0x55, 0x55, 0x05, 0x06, 0x15, 0x01, 0x00,//转A
					     0x55, 0x55, 0x05, 0x06, 0x16, 0x01, 0x00,//转E
					     0x55, 0x55, 0x05, 0x06, 0x17, 0x01, 0x00,//转D
					     0x55, 0x55, 0x05, 0x06, 0x18, 0x01, 0x00,//转C
					     100};
char Mapan_zhuangs[42] = {0x55, 0x55, 0x05, 0x06, 0x32, 0x01, 0x00,//摞A
						  0x55, 0x55, 0x05, 0x06, 0x33, 0x01, 0x00,//转B 
						  0x55, 0x55, 0x05, 0x06, 0x34, 0x01, 0x00,//摞C
						  0x55, 0x55, 0x05, 0x06, 0x35, 0x01, 0x00,//转D 
						  0x55, 0x55, 0x05, 0x06, 0x36, 0x01, 0x00,//摞E
						  100};//第二部分

char Mapan_Init[7] = {0x55, 0x55, 0x05, 0x06, 0x14, 0x01, 0x00};

u8 UART4_RX_BUF[250];

u16 UART4_RX_CNT=0;

void UART4_Init(u32 bound)
{
    USART_InitTypeDef USART_InitStructure;
    GPIO_InitTypeDef GPIO_InitStructure;
	
	//NVIC_InitTypeDef NVIC_InitStructure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART4, ENABLE);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_Init(GPIOC, &GPIO_InitStructure);

//    GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_11;
//    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
//    GPIO_Init(GPIOC, &GPIO_InitStructure);


    USART_InitStructure.USART_BaudRate = bound;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No ;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Tx;

    USART_Init(UART4, &USART_InitStructure);
	
//	NVIC_InitStructure.NVIC_IRQChannel = UART4_IRQn;
//	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3;//抢占优先级3
//	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;	  //子优先级3
//	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;		  //IRQ通道使能
//	NVIC_Init(&NVIC_InitStructure); //根据指定的参数初始化VIC寄存器
//	
    USART_Cmd(UART4, ENABLE);
//    USART_ITConfig(UART4, USART_IT_RXNE, ENABLE);//开启串口接受中断
    USART_ClearFlag(UART4,USART_FLAG_TC);
	

}



//USART1发送len个字节.
//buf:发送区首地址
//len:发送的字节数(为了和本代码的接收匹配,这里建议不要超过64个字节)
void UART4_Send_Data(u8 *buf,u16 len)
{
    while (len--) {
		while ((UART4->SR & 0x40) == 0);
		USART_SendData(UART4,*buf++);
	}
}





///***************************
////检测是否发送完成数据
//***************************/
void UART_IT_Puts(char *str, char len)
{
//	while (len--)
//	{
//		//USART_ClearFlag(UART4,USART_FLAG_TC); 
//		while ( (UART4->SR & 0x80) == 0 );//等待数据全部处于待发送状态
//		//USART_ClearFlag(UART4, USART_FLAG_RXNE);
//		UART4->DR = *str++;//*str++是使用完 *str ,然后str++
//		while ( (UART4->SR & 0x40) == 0 );//等待发送完成
//	}
	
	while (len--) {
		while ((UART4->SR & 0x40) == 0);
		USART_SendData(UART4,*str++);
	}
	
}



