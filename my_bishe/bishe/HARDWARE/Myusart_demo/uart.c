#include "sys.h"
#include "uart.h"	  
////////////////////////////////////////////////////////////////////////////////// 	 
//如果使用ucos,则包括下面的头文件即可.
#if SYSTEM_SUPPORT_OS
#include "includes.h"					//ucos 使用	  
#endif
//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//ALIENTEK STM32开发板
//串口1初始化		   
//正点原子@ALIENTEK
//技术论坛:www.openedv.com
//修改日期:2012/8/18
//版本：V1.5
//版权所有，盗版必究。
//Copyright(C) 广州市星翼电子科技有限公司 2009-2019
//All rights reserved
//********************************************************************************
//V1.3修改说明 
//支持适应不同频率下的串口波特率设置.
//加入了对printf的支持
//增加了串口接收命令功能.
//修正了printf第一个字符丢失的bug
//V1.4修改说明
//1,修改串口初始化IO的bug
//2,修改了USART_RX_STA,使得串口最大接收字节数为2的14次方
//3,增加了USART_REC_LEN,用于定义串口最大允许接收的字节数(不大于2的14次方)
//4,修改了EN_USART1_RX的使能方式
//V1.5修改说明
//1,增加了对UCOSII的支持
////////////////////////////////////////////////////////////////////////////////// 	  
 

//////////////////////////////////////////////////////////////////
//加入以下代码,支持printf函数,而不需要选择use MicroLIB	  
#if 1
#pragma import(__use_no_semihosting)             
//标准库需要的支持函数                 
struct __FILE 
{ 
	int handle; 

}; 

FILE __stdout;       
//定义_sys_exit()以避免使用半主机模式    
void _sys_exit(int x) 
{ 
	x = x; 
} 

void _ttywrch(int ch)
{
	ch = ch;
}

//重定义fputc函数 
int fputc(int ch, FILE *f)
{   
	# if Test_USART1
	while((USART1->SR&0X40)==0){};//循环发送,直到发送完毕   
    USART1->DR = (u8) ch;     
	# endif
	
	#if Test_USART2
	while((USART2->SR&0X40)==0){};//循环发送,直到发送完毕   
    USART2->DR = (u8) ch;      
	# endif 
	
	# if Test_USART3
	while((USART3->SR&0X40)==0);//循环发送,直到发送完毕   
    USART3->DR = (u8) ch; 
	# endif
	
	# if Test_UART4
	while ((UART4->SR&0x40) == 0);
	UART4->DR = (u8) ch;
	# endif 
	
	# if Test_UART5 | SHOUJI_UART5
	while ((UART5->SR&0x40) == 0);
	UART5->DR = (u8) ch;
	# endif 
	
	return ch;
}
#endif 

 
 
#if EN_USART1_RX   //如果使能了接收
//串口1中断服务程序
//注意,读取USARTx->SR能避免莫名其妙的错误   	
u8 USART_RX_BUF[USART_REC_LEN];     //接收缓冲,最大USART_REC_LEN个字节.
//接收状态
//bit15，	接收完成标志
//bit14，	接收到0x0d
//bit13~0，	接收到的有效字节数目

u16 USART_RX_STA=0;       //接收状态标记	  

void Usart1_Init(unsigned int baud)
{

	GPIO_InitTypeDef gpioInitStruct;
	USART_InitTypeDef usartInitStruct;
	NVIC_InitTypeDef nvicInitStruct;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
	
	//PA9	TXD
	gpioInitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
	gpioInitStruct.GPIO_Pin = GPIO_Pin_9;
	gpioInitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &gpioInitStruct);
	
	//PA10	RXD
	gpioInitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	gpioInitStruct.GPIO_Pin = GPIO_Pin_10;
	gpioInitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &gpioInitStruct);
	
	usartInitStruct.USART_BaudRate = baud;
	usartInitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;		//无硬件流控
	usartInitStruct.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;						//接收和发送
	usartInitStruct.USART_Parity = USART_Parity_No;									//无校验
	usartInitStruct.USART_StopBits = USART_StopBits_1;								//1位停止位
	usartInitStruct.USART_WordLength = USART_WordLength_8b;							//8位数据位
	USART_Init(USART1, &usartInitStruct);
	
	USART_Cmd(USART1, ENABLE);														//使能串口
	
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);									//使能接收中断
	
	nvicInitStruct.NVIC_IRQChannel = USART1_IRQn;
	nvicInitStruct.NVIC_IRQChannelCmd = ENABLE;
	nvicInitStruct.NVIC_IRQChannelPreemptionPriority = 0;
	nvicInitStruct.NVIC_IRQChannelSubPriority = 2;
	NVIC_Init(&nvicInitStruct);

}
  
void uart_init(u32 bound){
	
	  USART_InitTypeDef USART_InitStructure;  
      NVIC_InitTypeDef NVIC_InitStructure;   
     GPIO_InitTypeDef GPIO_InitStructure;    //声明一个结构体变量，用来初始化GPIO  
      
	# if Test_USART1
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1|RCC_APB2Periph_GPIOA, ENABLE);	//使能USART1，GPIOA时钟
  
		//USART1_TX   GPIOA.9
	  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9; //PA.9
	  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//复用推挽输出
	  GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化GPIOA.9
	   
	  //USART1_RX	  GPIOA.10初始化
	  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;//PA10
	  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//浮空输入
	  GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化GPIOA.10  

	  //Usart1 NVIC 配置
	  NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0 ;//抢占优先级3
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;		//子优先级3
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
		NVIC_Init(&NVIC_InitStructure);	//根据指定的参数初始化VIC寄存器
	  
	   //USART 初始化设置

		USART_InitStructure.USART_BaudRate = bound;//串口波特率
		USART_InitStructure.USART_WordLength = USART_WordLength_8b;//字长为8位数据格式
		USART_InitStructure.USART_StopBits = USART_StopBits_1;//一个停止位
		USART_InitStructure.USART_Parity = USART_Parity_No;//无奇偶校验位
		USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件数据流控制
		USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//收发模式

	  USART_Init(USART1, &USART_InitStructure); //初始化串口1
//	  USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);//开启串口接受中断
//	  USART_Cmd(USART1, ENABLE);                    //使能串口1 
	  
	 # endif
	
	
	# if Test_USART2
		//使能串口的RCC时钟  
      RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA , ENABLE); //使能UART3所在GPIOB的时钟  
      RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);  
	
	  USART_DeInit(USART2);//复位串口3
  
      //串口使用的GPIO口配置  
      // Configure USART3 Rx (PB.11) as input floating    
      GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;  
      GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;  
      GPIO_Init(GPIOA, &GPIO_InitStructure);  
  
      // Configure USART3 Tx (PB.10) as alternate function push-pull  
      GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;  
      GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;  
      GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  
      GPIO_Init(GPIOA, &GPIO_InitStructure);  
  
	  // Enable the USART3 Interrupt   
      NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;   
      NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=1;//抢占优先级3
      NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;        //子优先级3
      NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;  
      NVIC_Init(&NVIC_InitStructure);  
  
     USART_InitStructure.USART_BaudRate = bound;//串口波特率
	 USART_InitStructure.USART_WordLength = USART_WordLength_8b;//字长为8位数据格式
	 USART_InitStructure.USART_StopBits = USART_StopBits_1;//一个停止位
	 USART_InitStructure.USART_Parity = USART_Parity_No;//无奇偶校验位
	 USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件数据流控制
   	 USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//收发模式
  
  
      // Configure USART3   
      USART_Init(USART2, &USART_InitStructure);//配置串口3 
      // Enable USART3 Receive interrupts 使能串口接收中断  
      USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);  
      // Enable the USART3   
      USART_Cmd(USART2, ENABLE);//使能串口3  
 # endif
   
   # if Test_USART3

	  RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3,ENABLE);
	  # if	Test_USART3_PartialRemap
	   RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC | RCC_APB2Periph_AFIO,ENABLE);//开启GPIOB和USART3时钟
	   GPIO_PinRemapConfig(GPIO_PartialRemap_USART3, ENABLE);
	  # else
	   RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);//开启GPIOB和USART3时钟
	  # endif
	
	  USART_DeInit(USART3);//复位串口3
  
      //串口使用的GPIO口配置  
      // Configure USART3 Rx (PB.11) as input floating    
      GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;  
      GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;  
      # if Test_USART3_PartialRemap
	   GPIO_Init(GPIOC, &GPIO_InitStructure);
	  # else
	   GPIO_Init(GPIOB, &GPIO_InitStructure);  
	  # endif
  
      // Configure USART3 Tx (PB.10) as alternate function push-pull  
      GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;  
      GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;  
      GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  
      # if Test_USART3_PartialRemap
	   GPIO_Init(GPIOC, &GPIO_InitStructure);
	  # else
	   GPIO_Init(GPIOB, &GPIO_InitStructure);  
	  # endif
  
	  // Enable the USART3 Interrupt   
      NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;   
      NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3 ;//抢占优先级3
      NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;        //子优先级3
      NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;  
      NVIC_Init(&NVIC_InitStructure);  
  
     USART_InitStructure.USART_BaudRate = bound;//串口波特率
	 USART_InitStructure.USART_WordLength = USART_WordLength_8b;//字长为8位数据格式
	 USART_InitStructure.USART_StopBits = USART_StopBits_1;//一个停止位
	 USART_InitStructure.USART_Parity = USART_Parity_No;//无奇偶校验位
	 USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件数据流控制
   	 USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//收发模式
  
  
      USART_Init(USART3, &USART_InitStructure); //初始化串口3
	  USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);//开启串口接受中断
	  USART_Cmd(USART3, ENABLE);                    //使能串口3 
	  
   # endif
	
	
  # if Test_UART4
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART4, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
	
		 USART_DeInit(UART4);//复位串口4
	//TX
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC, &GPIO_InitStructure);
	
	//RX
	 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;  
	 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;  
	 GPIO_Init(GPIOC, &GPIO_InitStructure); 
	 
	 NVIC_InitStructure.NVIC_IRQChannel = UART4_IRQn;   
	 NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3 ;//抢占优先级3
	 NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;        //子优先级3
     NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;  
     NVIC_Init(&NVIC_InitStructure);  
	
	 USART_InitStructure.USART_BaudRate = bound;//串口波特率
	 USART_InitStructure.USART_WordLength = USART_WordLength_8b;//字长为8位数据格式
	 USART_InitStructure.USART_StopBits = USART_StopBits_1;//一个停止位
	 USART_InitStructure.USART_Parity = USART_Parity_No;//无奇偶校验位
	 USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件数据流控制
   	 USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//收发模式
	 
	  USART_Init(UART4, &USART_InitStructure); //初始化串口3
	  USART_ITConfig(UART4, USART_IT_RXNE, ENABLE);//开启串口接受中断
	  USART_Cmd(UART4, ENABLE);                    //使能串口3 
	
   # endif
   
   # if Test_UART5 | SHOUJI_UART5
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC|RCC_APB2Periph_GPIOD, ENABLE );
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART5, ENABLE );
	
		 USART_DeInit(UART5);//复位串口4
	//TX
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_12;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC, &GPIO_InitStructure);
	
	//RX
	 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;  
	 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;  
	 GPIO_Init(GPIOD, &GPIO_InitStructure); 
	 
	 NVIC_InitStructure.NVIC_IRQChannel = UART5_IRQn;   
	 NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0 ;//抢占优先级3
	 NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;        //子优先级3
     NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;  
     NVIC_Init(&NVIC_InitStructure);  
	
	 USART_InitStructure.USART_BaudRate = bound;//串口波特率
	 USART_InitStructure.USART_WordLength = USART_WordLength_8b;//字长为8位数据格式
	 USART_InitStructure.USART_StopBits = USART_StopBits_1;//一个停止位
	 USART_InitStructure.USART_Parity = USART_Parity_No;//无奇偶校验位
	 USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件数据流控制
   	 USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//收发模式
	 
	  USART_Init(UART5, &USART_InitStructure); //初始化串口3
	  USART_ITConfig(UART5, USART_IT_RXNE, ENABLE);//开启串口接受中断
	  USART_Cmd(UART5, ENABLE);                    //使能串口3 
	# endif

}

void Wireless_Receive(uint8_t data);

//USART5
struct NY
{
	unsigned Jieshou_FLAG:1;//接收标志位
	unsigned Fasong_FLAG :1;//发送标志位
}NANYA;

unsigned char JS_flag = 0;//接收状态标志位
unsigned char Mode_store = 0;//功能选择位

enum Gen_Xin
{
	MODE_P = 0xA1, MODE_I, Mode_D,
	BOXING1 = 0x01, BOXING2, BOXING3
}Gen_XinPID, Gen_XinBOXING;


extern uint8_t g_TFminiPlus_flag;

//u8 Res;

 # if Test_USART1
	void USART1_IRQHandler(void)                	//串口1中断服务程序
	{
 u8 Res;

	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)  //接收中断(接收到的数据必须是0x0d 0x0a结尾)
	{
		
		Res =USART_ReceiveData(USART1);	//读取接收到的数据

		if (g_TFminiPlus_flag != 1)//未接收成功一帧数据
		Wireless_Receive(Res);
//		USART_ClearFlag(USART1, USART_FLAG_TC);
//		if((USART_RX_STA&0x8000)==0)//接收未完成
//			{
//			if(USART_RX_STA&0x4000)//接收到了0x0d
//				{
//				if(Res!=0x0a)USART_RX_STA=0;//接收错误,重新开始
//				else USART_RX_STA|=0x8000;	//接收完成了 
//				}
//			else //还没收到0X0D
//				{	
//				if(Res==0x0d)USART_RX_STA|=0x4000;
//				else
//					{
//					USART_RX_BUF[USART_RX_STA&0X3FFF]=Res ;
//					USART_RX_STA++;
//					if(USART_RX_STA>(USART_REC_LEN-1))USART_RX_STA=0;//接收数据错误,重新开始接收	  
//					}		 
//				}
//			}   		 

     } 

} 

 # endif




 # if Test_USART2
//	void USART2_IRQHandler(void)                	//串口1中断服务程序
//		{
//		 u8 Res;
//		if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)  //接收中断(接收到的数据必须是0x0d 0x0a结尾)
//			{
//			Res =USART_ReceiveData(USART2);	//读取接收到的数据
//			
//			if((USART_RX_STA&0x8000)==0)//接收未完成
//				{
//				if(USART_RX_STA&0x4000)//接收到了0x0d
//					{
//					if(Res!=0x0a)USART_RX_STA=0;//接收错误,重新开始
//					else USART_RX_STA|=0x8000;	//接收完成了 
//					}
//				else //还没收到0X0D
//					{	
//					if(Res==0x0d)USART_RX_STA|=0x4000;
//					else
//						{
//						USART_RX_BUF[USART_RX_STA&0X3FFF]=Res ;
//						USART_RX_STA++;
//						if(USART_RX_STA>(USART_REC_LEN-1))USART_RX_STA=0;//接收数据错误,重新开始接收	  
//						}		 
//					}
//				} 
//			//	USART_ClearITPendingBit(USART3, USART_IT_RXNE);
//		 } 

//}
# endif

	# if Test_USART3
	void USART3_IRQHandler(void)                	//串口1中断服务程序
		{
		 u8 Res;
		if(USART_GetITStatus(USART3, USART_IT_RXNE) != RESET)  //接收中断(接收到的数据必须是0x0d 0x0a结尾)
			{
			Res =USART_ReceiveData(USART3);	//读取接收到的数据
			
			if((USART_RX_STA&0x8000)==0)//接收未完成
				{
				if(USART_RX_STA&0x4000)//接收到了0x0d
					{
					if(Res!=0x0a)USART_RX_STA=0;//接收错误,重新开始
					else USART_RX_STA|=0x8000;	//接收完成了 
					}
				else //还没收到0X0D
					{	
					if(Res==0x0d)USART_RX_STA|=0x4000;
					else
						{
						USART_RX_BUF[USART_RX_STA&0X3FFF]=Res ;
						USART_RX_STA++;
						if(USART_RX_STA>(USART_REC_LEN-1))USART_RX_STA=0;//接收数据错误,重新开始接收	  
						}		 
					}
				} 
				// USART_ClearITPendingBit(USART3,USART_WakeUp_IdleLine);//退出本次接收中断
			//	USART_ClearITPendingBit(USART3, USART_IT_RXNE);
		 } 

	}

	# endif

	# if Test_UART4
		void UART4_IRQHandler(void)
		{
		 u8 Res;
			if (USART_GetITStatus(UART4, USART_IT_RXNE) != RESET)
			{
				Res = USART_ReceiveData(UART4);
				
				if ((USART_RX_STA&0x8000) == 0)//接收未完成
				{
					if (USART_RX_STA&0x4000)//接收到来0x0d
					{
						if (Res != 0x0a) USART_RX_STA = 0;//重新接收
						else
						{
							USART_RX_STA |= 0x8000;//接收完成
						}
					}
					else
					{
						if (Res==0x0d) USART_RX_STA |= 0x4000;
						else
						{
							USART_RX_BUF[USART_RX_STA&0x3fff] = Res;
							USART_RX_STA++;
							if (USART_RX_STA > (USART_REC_LEN-1)) USART_RX_STA = 0;
						}
					}
				}
			}
		
		}
	# endif
	
	# if Test_UART5
		void UART5_IRQHandler(void)
			{
				 u8 Res;
				if (USART_GetITStatus(UART5, USART_IT_RXNE) != RESET)
				{
					Res = USART_ReceiveData(UART5);
					
					if ((USART_RX_STA&0x8000) == 0)//接收未完成
					{
						if (USART_RX_STA&0x4000)//接收到来0x0d
						{
							if (Res != 0x0a) USART_RX_STA = 0;//重新接收
							else
							{
								USART_RX_STA |= 0x8000;//接收完成
							}
						}
						else
						{
							if (Res==0x0d) USART_RX_STA |= 0x4000;
							else
							{
								USART_RX_BUF[USART_RX_STA&0x3fff] = Res;
								USART_RX_STA++;
								if (USART_RX_STA > (USART_REC_LEN-1)) USART_RX_STA = 0;
							}
						}
					}
				}
			
			}
	# endif
	
	# if SHOUJI_UART5
	void UART5_IRQHandler(void)
	{
/*
**discription:								功能选择位A B C D...(注意是大写的字母)
**数据格式：0x2a 0x2a 功能选择位 数据位 0x23 0x24(十六进制) --- **功能选择位 数据位 #$(字符模式发送) 
**地面站蓝牙接收数据时只接收数据位数据
**mode:1	手机端发送数据以字符形式发送，字符长度只要不超过USART_REC_LEN+4就可以
**mode:2	手机端发送数据以十六进制发送。数据长度固定
*/
		
		u8 Res = 0;

		if(USART_GetITStatus(UART5, USART_IT_RXNE) != RESET)  //接收中断(接收到的数据必须是0x0d 0x0a结尾)
		{
				Res =USART_ReceiveData(UART5);	//读取接收到的数据
				
				if (Res == 0x2a && JS_flag == 0)
				{
					JS_flag = 1;
				}
				else if (JS_flag == 1)
				{
					if (Res == 0x2a)
					{
						JS_flag = 10;//等待接收数据位数据
					}
					else
					{
						JS_flag = 0;
					}
				}
				else if (JS_flag == 10)
				{//模式选择
					Mode_store = Res;
					JS_flag = 100;
				}
				else if (JS_flag == 100)
				{//数据位数据接收
					if ((USART_RX_STA & 0x8000) == 0)//接收未完成
					{
						if (USART_RX_STA & 0x4000)
						{
							if (Res != 0x24) USART_RX_STA = 0;
							else	{USART_RX_STA |= 0x8000; NANYA.Jieshou_FLAG = 1; JS_flag = 0;
							USART_RX_BUF[USART_RX_STA] = 0;//补加结束符
							}//接收完成
						}
						else
						{
							if (Res == 0x23)	USART_RX_STA |= 0x4000;
							else
							{
								USART_RX_BUF[USART_RX_STA] = Res;
								USART_RX_STA++;
								if (USART_RX_STA > (USART_REC_LEN-1)) USART_RX_STA = 0;
							}
						}
					}
				}
			} 
	}
	# endif


# define UserDataLen 6*2 //数据长度
//enum 
//{
//	INT = 10,
//	FLOAT,
//}Data_Mode;

void Wireless_Send(int16_t data, uint8_t Mode)
/*
data为整型数据（）
mode传入Data_Mode.      直接传象征性的字母即可代表模式，具体的是不是要/100其实这里作者已经知道了。即在DiMianZan()里可以处理。          (***数据类型,if是float类型，默认数据是扩大2倍的)--舍弃了

*-0xAA 帧头
*-0xAA (辅助帧头),也可改为目标地址，不过目标地址的话需要更改接收函数
*-0xf1 ID号
*-**** 有效字节wei
*-Mode 数据类型flag----支持int float两种类型(float 类型默认扩大了2倍,即表示两位小数)
*-BYTE0小段模式（具体表示数据范围,可以自行更改大小）
*-BYTE1
*-BYTE2
*-BYTE3
*-_sumcheck 和校验
*-_addcheck 附加校验
*/
{
	uint8_t waveform[5 + UserDataLen] = {0};//数据帧缓存
	uint8_t _cnt = 0;
	
	memset(waveform, 0, sizeof(waveform));
	
	waveform[_cnt++] = 0xAA;        			// 帧头
    waveform[_cnt++] = 0xAA;        			// 目标地址
    waveform[_cnt++] = 0xF1;        			// 功能码ID
	waveform[_cnt++] = 0;					// 有效字节数
	waveform[_cnt++] = Mode;				// 数据类型选择
	
	int16_t _UserData_1 = (int16_t)(data);
	//数据区使用小端模式, 低字节在前。
    waveform[_cnt++] = BYTE0(_UserData_1);   	// 数据内容
    waveform[_cnt++] = BYTE1(_UserData_1);
	
	waveform[3] = _cnt - 5; 					// 写入有效数据字节数
	
	uint8_t _sumcheck = 0;  			 			// 和校验SC
    uint8_t _addcheck = 0;   					// 附加校验AC
	for(uint8_t i = 0; i < waveform[3] + 5; i++) {
      _sumcheck += waveform[i];      			// 从帧头开始, 一直到 data 区结束, 对每一字节进行累加操作, 只取低8位
      _addcheck += _sumcheck;         			// 计算和校验时, 每进行一字节的加法运算, 同时进行一次 sumcheck 的累加操作, 只取低8位
    }
	waveform[_cnt++] = _sumcheck;
    waveform[_cnt++] = _addcheck;
	
	//此处可以更改发送串口通道------------具体视情况而定
	//UART5_Send_Data(waveform, sizeof(waveform));
	int len = sizeof(waveform);
	u8 *buf = waveform;
	while (len--) {
		while ((USART1->SR & 0x40) == 0);
		USART_SendData(USART1,*buf++);
	}
}


# define TFMINI_DATA_Len UserDataLen+4//数据帧长度
# define TFMINT_DATA_HEAD    (0xAA)//帧头
# define NUM_FRONT_STOREDATA  3//协议帧数据前面的字节数
# define NUM_BACK_STOREDATA 2//协议帧数据后面的字节数

uint16_t g_TFmin_Dist = 0;    // 数据信息 

uint8_t TFminiPlus_buf[TFMINI_DATA_Len] = {0};  // 暂存数据帧
uint8_t g_TFminiPlus_num = 0;                     // 暂存本字节数据编码
uint8_t g_TFminiPlus_flag = 0;                    // 接收数据标志位 1-成功;2-帧头错误;3-SC校验错误


extern SMART_HOME Smart_home;

void Wireless_Receive(uint8_t data)
//串口接收函数
{
	uint8_t i = 0;
    uint8_t checksum = 0;
	
	 if (g_TFminiPlus_num == 0 && data == TFMINT_DATA_HEAD) {                      // 校验并记录帧头
        TFminiPlus_buf[0] = TFMINT_DATA_HEAD;
        g_TFminiPlus_num = 1;
    } else if (g_TFminiPlus_num == 1 && data == TFMINT_DATA_HEAD) {               // 校验并记录帧头
        TFminiPlus_buf[1] = TFMINT_DATA_HEAD;
        g_TFminiPlus_num = 2;
    } else if (g_TFminiPlus_num == 2){											//模式选择
		TFminiPlus_buf[2] = data;//有效字节数
//		Mode_store = data;
		g_TFminiPlus_num = 3;
	}else if (g_TFminiPlus_num >= 3 && g_TFminiPlus_num <= (TFminiPlus_buf[2] + 4 - 1)) {
        TFminiPlus_buf[g_TFminiPlus_num] = data;
        g_TFminiPlus_num++;
		if (g_TFminiPlus_num == (TFMINI_DATA_Len)) {
			for (i = 0; i < (TFMINI_DATA_Len - 1); i++) {
				checksum += TFminiPlus_buf[i];                                      // 从帧头开始到数据区结束, 做checksum校验
			}
			
			if (checksum == TFminiPlus_buf[TFMINI_DATA_Len - 1]) {                                                 // 校验Checksum
				//数据为小端模式, 低字节在前保存在数据帧的低地址中
				g_TFminiPlus_flag = 1;
				g_TFmin_Dist = 0;//重新计算新的数据
				
				for (int k = NUM_FRONT_STOREDATA; k < NUM_FRONT_STOREDATA + UserDataLen; k=k+2){
					for (int j = 0; j < 2; j++)
					{
						g_TFmin_Dist |= TFminiPlus_buf[k+j] << (8*j);
					}
					switch (k)
					{
						case NUM_FRONT_STOREDATA:      Smart_home._data.temperature_one = (float)(g_TFmin_Dist) * 1.0 / 10.0; break;
						case NUM_FRONT_STOREDATA + 2:  Smart_home._data.window_ZT_zero = g_TFmin_Dist; break;
						case NUM_FRONT_STOREDATA + 4:  Smart_home._data.humidity_zero = g_TFmin_Dist; break;
						case NUM_FRONT_STOREDATA + 6:  Smart_home._data.chuanglian_ZT_zero = g_TFmin_Dist; break;
						case NUM_FRONT_STOREDATA + 8:  Smart_home._data.fan_ZT_zero = g_TFmin_Dist; break;
						case NUM_FRONT_STOREDATA + 10:  Smart_home._data.led_ZT_zero = g_TFmin_Dist; break;
						default:
							break;
					}
					g_TFmin_Dist = 0;
				}
			}else {
				memset(TFminiPlus_buf, 0, sizeof(TFminiPlus_buf));
				g_TFminiPlus_flag = 3;
				g_TFminiPlus_num = 0;//为下次数据接收做准备
			}
		
			g_TFminiPlus_num = 0;//为下次数据接收做准备
			
		}
			
    }else{//错误数据
		g_TFminiPlus_flag = 2;
		memset(TFminiPlus_buf, 0, sizeof(TFminiPlus_buf));
		g_TFminiPlus_num = 0;//为下次数据接收做准备
	}
	
}



	
/*************蓝牙地面站****************/
void DiMianZan(void)
{
	float test_data = 0;
	
# if SHOUJI_UART5
	if (NANYA.Jieshou_FLAG)
	{
		switch (Mode_store)
		{
//			case 'P': P = (float)atof(USART_RX_BUF);
//				break;
//			case 'I': I = (float)atof(USART_RX_BUF);
//				break;
//			case 'D': D = (float)atof(USART_RX_BUF);
//				break;
//			case 'A': PRINTF_BOXING();
//			OLED_Float(0, 6, P, 2);	
//				break;
			case 'B':
				break;
			case 'C':
				break;
			default:
				break;
		}
		NANYA.Jieshou_FLAG = 0;
		USART_RX_STA = 0;
	}
# else
	if (g_TFminiPlus_flag == 1)
	{
		switch (Mode_store)
		{
			case 'P': test_data = g_TFmin_Dist*1.0/100.0;
				break;
//			case 'I': I = g_TFmin_Dist*1.0/100.0;
//				break;
//			case 'D': D = g_TFmin_Dist*1.0/100.0;
//				break;
//			case 'B': 整型数据直接复制数据即可 = g_TFmin_Dist;
//				break;
			default:
				break;
				
		}
		g_TFminiPlus_flag = 0;
	}
	
	
# endif
	
}
	
	
#endif	
	
void u32tostr(unsigned long dat,char *str) 
{
    char temp[20];
    unsigned char i=0,j=0;
    i=0;
    while(dat)
    {
        temp[i]=dat%10+0x30;
        i++;
        dat/=10;
    }
    j=i;
    for(i=0;i<j;i++)
    {
          str[i]=temp[j-i-1];
    }
    if(!i) {str[i++]='0';}
    str[i]=0;
}
/**********************************************************
** 函数名: strtou32
** 功能描述: 将一个字符串转为32位的变量，比如"1234"转为1234
** 输入参数: str:指向待转换的字符串     
** 输出参数: 无
** 返回：转换后的数值  
***********************************************************/
unsigned long strtou32(char *str) 
{
    unsigned long temp=0;
    unsigned long fact=1;
    unsigned char len=strlen(str);
    unsigned char i;
    for(i=len;i>0;i--)
    {
        temp+=((str[i-1]-0x30)*fact);
        fact*=10;
    }
    return temp;
}

/**********************************************************
** 函数名:USART5_Putc
** 功能描述: 串口1发送一字符
** 输入参数: c
** 输出参数: 无
***********************************************************/
void UART5_Putc(unsigned char c)
{
    UART5->DR = (u8)c; //要发送的字符赋给串口数据寄存器  
    while((UART5->SR&0X40)==0); //等待发送完成  
}
/**********************************************************
** 函数名:USART1_Puts
** 功能描述: 串口1发送一字符串
** 输入参数: 指针str
** 输出参数: 无
***********************************************************/
void UART5_Puts(char * str)
{
    while(*str)
    {
        UART5->DR= *str++;
        while((UART5->SR&0X40)==0);//等待发送完成  
    }
}
/**********************************************************
** 函数名:UART_Send_Enter
** 功能描述: 串口1发送一换行符
** 输入参数: 无
** 输出参数: 无
***********************************************************/
void UART_Send_Enter(void)
{
    UART5_Putc(0x0d);
    UART5_Putc(0x0a);
}

/*
************************************************************
*	函数名称：	Usart_SendString
*
*	函数功能：	串口数据发送
*
*	入口参数：	USARTx：串口组
*				str：要发送的数据
*				len：数据长度
*
*	返回参数：	无
*
*	说明：		
************************************************************
*/
void Usart_SendString(USART_TypeDef *USARTx, unsigned char *str, unsigned short len)
{

	unsigned short count = 0;
	
	for(; count < len; count++)
	{
		USART_SendData(USARTx, *str++);									//发送数据
		while(USART_GetFlagStatus(USARTx, USART_FLAG_TC) == RESET);		//等待发送完成
	}

}

/**********************************************************
** 函数名:UART_Send_Str
** 功能描述: 串口1发送一字符串，带回车换行功能
** 输入参数: 指针s
** 输出参数: 无
***********************************************************/
void UART_Send_Str(char *s)
{
 
     for(;*s;s++)
     {
         if(*s=='\n') 
              UART_Send_Enter();
         else
              UART5_Putc(*s);
     }
}
/**********************************************************
** 函数名: UART_Put_Num
** 功能描述: STM32F的USART发送数值
** 输入参数: dat:要发送的数值
** 输出参数: 无
** 说明：函数中会将数值转为相应的字符串，发送出去。比如 4567 转为 "4567" 
***********************************************************/
void UART_Put_Num(unsigned long dat)
{
    char temp[20];
    u32tostr(dat,temp);
    UART_Send_Str(temp);
}
/**********************************************************
** 函数名: UART_Put_Inf
** 功能描述: STM32F的USART发送调试信息
** 输入参数: inf:指向提示信息字符串的指针
             dat:一个数值，前面的提示信息就是在说明这个数值的意义
** 输出参数: 无 
***********************************************************/
void UART_Put_Inf(char *inf,short dat)
{
    UART_Send_Str(inf);
    UART_Put_Num(dat);
    UART_Send_Str("\n");  
}
