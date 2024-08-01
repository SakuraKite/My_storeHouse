#include "sys.h"
#include "uart.h"	  
////////////////////////////////////////////////////////////////////////////////// 	 
//���ʹ��ucos,����������ͷ�ļ�����.
#if SYSTEM_SUPPORT_OS
#include "includes.h"					//ucos ʹ��	  
#endif
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEK STM32������
//����1��ʼ��		   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//�޸�����:2012/8/18
//�汾��V1.5
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2009-2019
//All rights reserved
//********************************************************************************
//V1.3�޸�˵�� 
//֧����Ӧ��ͬƵ���µĴ��ڲ���������.
//�����˶�printf��֧��
//�����˴��ڽ��������.
//������printf��һ���ַ���ʧ��bug
//V1.4�޸�˵��
//1,�޸Ĵ��ڳ�ʼ��IO��bug
//2,�޸���USART_RX_STA,ʹ�ô����������ֽ���Ϊ2��14�η�
//3,������USART_REC_LEN,���ڶ��崮�����������յ��ֽ���(������2��14�η�)
//4,�޸���EN_USART1_RX��ʹ�ܷ�ʽ
//V1.5�޸�˵��
//1,�����˶�UCOSII��֧��
////////////////////////////////////////////////////////////////////////////////// 	  
 

//////////////////////////////////////////////////////////////////
//�������´���,֧��printf����,������Ҫѡ��use MicroLIB	  
#if 1
#pragma import(__use_no_semihosting)             
//��׼����Ҫ��֧�ֺ���                 
struct __FILE 
{ 
	int handle; 

}; 

FILE __stdout;       
//����_sys_exit()�Ա���ʹ�ð�����ģʽ    
void _sys_exit(int x) 
{ 
	x = x; 
} 

void _ttywrch(int ch)
{
	ch = ch;
}

//�ض���fputc���� 
int fputc(int ch, FILE *f)
{   
	# if Test_USART1
	while((USART1->SR&0X40)==0){};//ѭ������,ֱ���������   
    USART1->DR = (u8) ch;     
	# endif
	
	#if Test_USART2
	while((USART2->SR&0X40)==0){};//ѭ������,ֱ���������   
    USART2->DR = (u8) ch;      
	# endif 
	
	# if Test_USART3
	while((USART3->SR&0X40)==0);//ѭ������,ֱ���������   
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

 
 
#if EN_USART1_RX   //���ʹ���˽���
//����1�жϷ������
//ע��,��ȡUSARTx->SR�ܱ���Ī������Ĵ���   	
u8 USART_RX_BUF[USART_REC_LEN];     //���ջ���,���USART_REC_LEN���ֽ�.
//����״̬
//bit15��	������ɱ�־
//bit14��	���յ�0x0d
//bit13~0��	���յ�����Ч�ֽ���Ŀ

u16 USART_RX_STA=0;       //����״̬���	  

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
	usartInitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;		//��Ӳ������
	usartInitStruct.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;						//���պͷ���
	usartInitStruct.USART_Parity = USART_Parity_No;									//��У��
	usartInitStruct.USART_StopBits = USART_StopBits_1;								//1λֹͣλ
	usartInitStruct.USART_WordLength = USART_WordLength_8b;							//8λ����λ
	USART_Init(USART1, &usartInitStruct);
	
	USART_Cmd(USART1, ENABLE);														//ʹ�ܴ���
	
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);									//ʹ�ܽ����ж�
	
	nvicInitStruct.NVIC_IRQChannel = USART1_IRQn;
	nvicInitStruct.NVIC_IRQChannelCmd = ENABLE;
	nvicInitStruct.NVIC_IRQChannelPreemptionPriority = 0;
	nvicInitStruct.NVIC_IRQChannelSubPriority = 2;
	NVIC_Init(&nvicInitStruct);

}
  
void uart_init(u32 bound){
	
	  USART_InitTypeDef USART_InitStructure;  
      NVIC_InitTypeDef NVIC_InitStructure;   
     GPIO_InitTypeDef GPIO_InitStructure;    //����һ���ṹ�������������ʼ��GPIO  
      
	# if Test_USART1
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1|RCC_APB2Periph_GPIOA, ENABLE);	//ʹ��USART1��GPIOAʱ��
  
		//USART1_TX   GPIOA.9
	  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9; //PA.9
	  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//�����������
	  GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��GPIOA.9
	   
	  //USART1_RX	  GPIOA.10��ʼ��
	  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;//PA10
	  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//��������
	  GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��GPIOA.10  

	  //Usart1 NVIC ����
	  NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0 ;//��ռ���ȼ�3
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;		//�����ȼ�3
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
		NVIC_Init(&NVIC_InitStructure);	//����ָ���Ĳ�����ʼ��VIC�Ĵ���
	  
	   //USART ��ʼ������

		USART_InitStructure.USART_BaudRate = bound;//���ڲ�����
		USART_InitStructure.USART_WordLength = USART_WordLength_8b;//�ֳ�Ϊ8λ���ݸ�ʽ
		USART_InitStructure.USART_StopBits = USART_StopBits_1;//һ��ֹͣλ
		USART_InitStructure.USART_Parity = USART_Parity_No;//����żУ��λ
		USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ������������
		USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//�շ�ģʽ

	  USART_Init(USART1, &USART_InitStructure); //��ʼ������1
//	  USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);//�������ڽ����ж�
//	  USART_Cmd(USART1, ENABLE);                    //ʹ�ܴ���1 
	  
	 # endif
	
	
	# if Test_USART2
		//ʹ�ܴ��ڵ�RCCʱ��  
      RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA , ENABLE); //ʹ��UART3����GPIOB��ʱ��  
      RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);  
	
	  USART_DeInit(USART2);//��λ����3
  
      //����ʹ�õ�GPIO������  
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
      NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=1;//��ռ���ȼ�3
      NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;        //�����ȼ�3
      NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;  
      NVIC_Init(&NVIC_InitStructure);  
  
     USART_InitStructure.USART_BaudRate = bound;//���ڲ�����
	 USART_InitStructure.USART_WordLength = USART_WordLength_8b;//�ֳ�Ϊ8λ���ݸ�ʽ
	 USART_InitStructure.USART_StopBits = USART_StopBits_1;//һ��ֹͣλ
	 USART_InitStructure.USART_Parity = USART_Parity_No;//����żУ��λ
	 USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ������������
   	 USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//�շ�ģʽ
  
  
      // Configure USART3   
      USART_Init(USART2, &USART_InitStructure);//���ô���3 
      // Enable USART3 Receive interrupts ʹ�ܴ��ڽ����ж�  
      USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);  
      // Enable the USART3   
      USART_Cmd(USART2, ENABLE);//ʹ�ܴ���3  
 # endif
   
   # if Test_USART3

	  RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3,ENABLE);
	  # if	Test_USART3_PartialRemap
	   RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC | RCC_APB2Periph_AFIO,ENABLE);//����GPIOB��USART3ʱ��
	   GPIO_PinRemapConfig(GPIO_PartialRemap_USART3, ENABLE);
	  # else
	   RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);//����GPIOB��USART3ʱ��
	  # endif
	
	  USART_DeInit(USART3);//��λ����3
  
      //����ʹ�õ�GPIO������  
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
      NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3 ;//��ռ���ȼ�3
      NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;        //�����ȼ�3
      NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;  
      NVIC_Init(&NVIC_InitStructure);  
  
     USART_InitStructure.USART_BaudRate = bound;//���ڲ�����
	 USART_InitStructure.USART_WordLength = USART_WordLength_8b;//�ֳ�Ϊ8λ���ݸ�ʽ
	 USART_InitStructure.USART_StopBits = USART_StopBits_1;//һ��ֹͣλ
	 USART_InitStructure.USART_Parity = USART_Parity_No;//����żУ��λ
	 USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ������������
   	 USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//�շ�ģʽ
  
  
      USART_Init(USART3, &USART_InitStructure); //��ʼ������3
	  USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);//�������ڽ����ж�
	  USART_Cmd(USART3, ENABLE);                    //ʹ�ܴ���3 
	  
   # endif
	
	
  # if Test_UART4
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART4, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
	
		 USART_DeInit(UART4);//��λ����4
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
	 NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3 ;//��ռ���ȼ�3
	 NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;        //�����ȼ�3
     NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;  
     NVIC_Init(&NVIC_InitStructure);  
	
	 USART_InitStructure.USART_BaudRate = bound;//���ڲ�����
	 USART_InitStructure.USART_WordLength = USART_WordLength_8b;//�ֳ�Ϊ8λ���ݸ�ʽ
	 USART_InitStructure.USART_StopBits = USART_StopBits_1;//һ��ֹͣλ
	 USART_InitStructure.USART_Parity = USART_Parity_No;//����żУ��λ
	 USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ������������
   	 USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//�շ�ģʽ
	 
	  USART_Init(UART4, &USART_InitStructure); //��ʼ������3
	  USART_ITConfig(UART4, USART_IT_RXNE, ENABLE);//�������ڽ����ж�
	  USART_Cmd(UART4, ENABLE);                    //ʹ�ܴ���3 
	
   # endif
   
   # if Test_UART5 | SHOUJI_UART5
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC|RCC_APB2Periph_GPIOD, ENABLE );
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART5, ENABLE );
	
		 USART_DeInit(UART5);//��λ����4
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
	 NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0 ;//��ռ���ȼ�3
	 NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;        //�����ȼ�3
     NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;  
     NVIC_Init(&NVIC_InitStructure);  
	
	 USART_InitStructure.USART_BaudRate = bound;//���ڲ�����
	 USART_InitStructure.USART_WordLength = USART_WordLength_8b;//�ֳ�Ϊ8λ���ݸ�ʽ
	 USART_InitStructure.USART_StopBits = USART_StopBits_1;//һ��ֹͣλ
	 USART_InitStructure.USART_Parity = USART_Parity_No;//����żУ��λ
	 USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ������������
   	 USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//�շ�ģʽ
	 
	  USART_Init(UART5, &USART_InitStructure); //��ʼ������3
	  USART_ITConfig(UART5, USART_IT_RXNE, ENABLE);//�������ڽ����ж�
	  USART_Cmd(UART5, ENABLE);                    //ʹ�ܴ���3 
	# endif

}

void Wireless_Receive(uint8_t data);

//USART5
struct NY
{
	unsigned Jieshou_FLAG:1;//���ձ�־λ
	unsigned Fasong_FLAG :1;//���ͱ�־λ
}NANYA;

unsigned char JS_flag = 0;//����״̬��־λ
unsigned char Mode_store = 0;//����ѡ��λ

enum Gen_Xin
{
	MODE_P = 0xA1, MODE_I, Mode_D,
	BOXING1 = 0x01, BOXING2, BOXING3
}Gen_XinPID, Gen_XinBOXING;


extern uint8_t g_TFminiPlus_flag;

//u8 Res;

 # if Test_USART1
	void USART1_IRQHandler(void)                	//����1�жϷ������
	{
 u8 Res;

	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)  //�����ж�(���յ������ݱ�����0x0d 0x0a��β)
	{
		
		Res =USART_ReceiveData(USART1);	//��ȡ���յ�������

		if (g_TFminiPlus_flag != 1)//δ���ճɹ�һ֡����
		Wireless_Receive(Res);
//		USART_ClearFlag(USART1, USART_FLAG_TC);
//		if((USART_RX_STA&0x8000)==0)//����δ���
//			{
//			if(USART_RX_STA&0x4000)//���յ���0x0d
//				{
//				if(Res!=0x0a)USART_RX_STA=0;//���մ���,���¿�ʼ
//				else USART_RX_STA|=0x8000;	//��������� 
//				}
//			else //��û�յ�0X0D
//				{	
//				if(Res==0x0d)USART_RX_STA|=0x4000;
//				else
//					{
//					USART_RX_BUF[USART_RX_STA&0X3FFF]=Res ;
//					USART_RX_STA++;
//					if(USART_RX_STA>(USART_REC_LEN-1))USART_RX_STA=0;//�������ݴ���,���¿�ʼ����	  
//					}		 
//				}
//			}   		 

     } 

} 

 # endif




 # if Test_USART2
//	void USART2_IRQHandler(void)                	//����1�жϷ������
//		{
//		 u8 Res;
//		if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)  //�����ж�(���յ������ݱ�����0x0d 0x0a��β)
//			{
//			Res =USART_ReceiveData(USART2);	//��ȡ���յ�������
//			
//			if((USART_RX_STA&0x8000)==0)//����δ���
//				{
//				if(USART_RX_STA&0x4000)//���յ���0x0d
//					{
//					if(Res!=0x0a)USART_RX_STA=0;//���մ���,���¿�ʼ
//					else USART_RX_STA|=0x8000;	//��������� 
//					}
//				else //��û�յ�0X0D
//					{	
//					if(Res==0x0d)USART_RX_STA|=0x4000;
//					else
//						{
//						USART_RX_BUF[USART_RX_STA&0X3FFF]=Res ;
//						USART_RX_STA++;
//						if(USART_RX_STA>(USART_REC_LEN-1))USART_RX_STA=0;//�������ݴ���,���¿�ʼ����	  
//						}		 
//					}
//				} 
//			//	USART_ClearITPendingBit(USART3, USART_IT_RXNE);
//		 } 

//}
# endif

	# if Test_USART3
	void USART3_IRQHandler(void)                	//����1�жϷ������
		{
		 u8 Res;
		if(USART_GetITStatus(USART3, USART_IT_RXNE) != RESET)  //�����ж�(���յ������ݱ�����0x0d 0x0a��β)
			{
			Res =USART_ReceiveData(USART3);	//��ȡ���յ�������
			
			if((USART_RX_STA&0x8000)==0)//����δ���
				{
				if(USART_RX_STA&0x4000)//���յ���0x0d
					{
					if(Res!=0x0a)USART_RX_STA=0;//���մ���,���¿�ʼ
					else USART_RX_STA|=0x8000;	//��������� 
					}
				else //��û�յ�0X0D
					{	
					if(Res==0x0d)USART_RX_STA|=0x4000;
					else
						{
						USART_RX_BUF[USART_RX_STA&0X3FFF]=Res ;
						USART_RX_STA++;
						if(USART_RX_STA>(USART_REC_LEN-1))USART_RX_STA=0;//�������ݴ���,���¿�ʼ����	  
						}		 
					}
				} 
				// USART_ClearITPendingBit(USART3,USART_WakeUp_IdleLine);//�˳����ν����ж�
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
				
				if ((USART_RX_STA&0x8000) == 0)//����δ���
				{
					if (USART_RX_STA&0x4000)//���յ���0x0d
					{
						if (Res != 0x0a) USART_RX_STA = 0;//���½���
						else
						{
							USART_RX_STA |= 0x8000;//�������
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
					
					if ((USART_RX_STA&0x8000) == 0)//����δ���
					{
						if (USART_RX_STA&0x4000)//���յ���0x0d
						{
							if (Res != 0x0a) USART_RX_STA = 0;//���½���
							else
							{
								USART_RX_STA |= 0x8000;//�������
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
**discription:								����ѡ��λA B C D...(ע���Ǵ�д����ĸ)
**���ݸ�ʽ��0x2a 0x2a ����ѡ��λ ����λ 0x23 0x24(ʮ������) --- **����ѡ��λ ����λ #$(�ַ�ģʽ����) 
**����վ������������ʱֻ��������λ����
**mode:1	�ֻ��˷����������ַ���ʽ���ͣ��ַ�����ֻҪ������USART_REC_LEN+4�Ϳ���
**mode:2	�ֻ��˷���������ʮ�����Ʒ��͡����ݳ��ȹ̶�
*/
		
		u8 Res = 0;

		if(USART_GetITStatus(UART5, USART_IT_RXNE) != RESET)  //�����ж�(���յ������ݱ�����0x0d 0x0a��β)
		{
				Res =USART_ReceiveData(UART5);	//��ȡ���յ�������
				
				if (Res == 0x2a && JS_flag == 0)
				{
					JS_flag = 1;
				}
				else if (JS_flag == 1)
				{
					if (Res == 0x2a)
					{
						JS_flag = 10;//�ȴ���������λ����
					}
					else
					{
						JS_flag = 0;
					}
				}
				else if (JS_flag == 10)
				{//ģʽѡ��
					Mode_store = Res;
					JS_flag = 100;
				}
				else if (JS_flag == 100)
				{//����λ���ݽ���
					if ((USART_RX_STA & 0x8000) == 0)//����δ���
					{
						if (USART_RX_STA & 0x4000)
						{
							if (Res != 0x24) USART_RX_STA = 0;
							else	{USART_RX_STA |= 0x8000; NANYA.Jieshou_FLAG = 1; JS_flag = 0;
							USART_RX_BUF[USART_RX_STA] = 0;//���ӽ�����
							}//�������
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


# define UserDataLen 6*2 //���ݳ���
//enum 
//{
//	INT = 10,
//	FLOAT,
//}Data_Mode;

void Wireless_Send(int16_t data, uint8_t Mode)
/*
dataΪ�������ݣ���
mode����Data_Mode.      ֱ�Ӵ������Ե���ĸ���ɴ���ģʽ��������ǲ���Ҫ/100��ʵ���������Ѿ�֪���ˡ�����DiMianZan()����Դ���          (***��������,if��float���ͣ�Ĭ������������2����)--������

*-0xAA ֡ͷ
*-0xAA (����֡ͷ),Ҳ�ɸ�ΪĿ���ַ������Ŀ���ַ�Ļ���Ҫ���Ľ��պ���
*-0xf1 ID��
*-**** ��Ч�ֽ�wei
*-Mode ��������flag----֧��int float��������(float ����Ĭ��������2��,����ʾ��λС��)
*-BYTE0С��ģʽ�������ʾ���ݷ�Χ,�������и��Ĵ�С��
*-BYTE1
*-BYTE2
*-BYTE3
*-_sumcheck ��У��
*-_addcheck ����У��
*/
{
	uint8_t waveform[5 + UserDataLen] = {0};//����֡����
	uint8_t _cnt = 0;
	
	memset(waveform, 0, sizeof(waveform));
	
	waveform[_cnt++] = 0xAA;        			// ֡ͷ
    waveform[_cnt++] = 0xAA;        			// Ŀ���ַ
    waveform[_cnt++] = 0xF1;        			// ������ID
	waveform[_cnt++] = 0;					// ��Ч�ֽ���
	waveform[_cnt++] = Mode;				// ��������ѡ��
	
	int16_t _UserData_1 = (int16_t)(data);
	//������ʹ��С��ģʽ, ���ֽ���ǰ��
    waveform[_cnt++] = BYTE0(_UserData_1);   	// ��������
    waveform[_cnt++] = BYTE1(_UserData_1);
	
	waveform[3] = _cnt - 5; 					// д����Ч�����ֽ���
	
	uint8_t _sumcheck = 0;  			 			// ��У��SC
    uint8_t _addcheck = 0;   					// ����У��AC
	for(uint8_t i = 0; i < waveform[3] + 5; i++) {
      _sumcheck += waveform[i];      			// ��֡ͷ��ʼ, һֱ�� data ������, ��ÿһ�ֽڽ����ۼӲ���, ֻȡ��8λ
      _addcheck += _sumcheck;         			// �����У��ʱ, ÿ����һ�ֽڵļӷ�����, ͬʱ����һ�� sumcheck ���ۼӲ���, ֻȡ��8λ
    }
	waveform[_cnt++] = _sumcheck;
    waveform[_cnt++] = _addcheck;
	
	//�˴����Ը��ķ��ʹ���ͨ��------------�������������
	//UART5_Send_Data(waveform, sizeof(waveform));
	int len = sizeof(waveform);
	u8 *buf = waveform;
	while (len--) {
		while ((USART1->SR & 0x40) == 0);
		USART_SendData(USART1,*buf++);
	}
}


# define TFMINI_DATA_Len UserDataLen+4//����֡����
# define TFMINT_DATA_HEAD    (0xAA)//֡ͷ
# define NUM_FRONT_STOREDATA  3//Э��֡����ǰ����ֽ���
# define NUM_BACK_STOREDATA 2//Э��֡���ݺ�����ֽ���

uint16_t g_TFmin_Dist = 0;    // ������Ϣ 

uint8_t TFminiPlus_buf[TFMINI_DATA_Len] = {0};  // �ݴ�����֡
uint8_t g_TFminiPlus_num = 0;                     // �ݴ汾�ֽ����ݱ���
uint8_t g_TFminiPlus_flag = 0;                    // �������ݱ�־λ 1-�ɹ�;2-֡ͷ����;3-SCУ�����


extern SMART_HOME Smart_home;

void Wireless_Receive(uint8_t data)
//���ڽ��պ���
{
	uint8_t i = 0;
    uint8_t checksum = 0;
	
	 if (g_TFminiPlus_num == 0 && data == TFMINT_DATA_HEAD) {                      // У�鲢��¼֡ͷ
        TFminiPlus_buf[0] = TFMINT_DATA_HEAD;
        g_TFminiPlus_num = 1;
    } else if (g_TFminiPlus_num == 1 && data == TFMINT_DATA_HEAD) {               // У�鲢��¼֡ͷ
        TFminiPlus_buf[1] = TFMINT_DATA_HEAD;
        g_TFminiPlus_num = 2;
    } else if (g_TFminiPlus_num == 2){											//ģʽѡ��
		TFminiPlus_buf[2] = data;//��Ч�ֽ���
//		Mode_store = data;
		g_TFminiPlus_num = 3;
	}else if (g_TFminiPlus_num >= 3 && g_TFminiPlus_num <= (TFminiPlus_buf[2] + 4 - 1)) {
        TFminiPlus_buf[g_TFminiPlus_num] = data;
        g_TFminiPlus_num++;
		if (g_TFminiPlus_num == (TFMINI_DATA_Len)) {
			for (i = 0; i < (TFMINI_DATA_Len - 1); i++) {
				checksum += TFminiPlus_buf[i];                                      // ��֡ͷ��ʼ������������, ��checksumУ��
			}
			
			if (checksum == TFminiPlus_buf[TFMINI_DATA_Len - 1]) {                                                 // У��Checksum
				//����ΪС��ģʽ, ���ֽ���ǰ����������֡�ĵ͵�ַ��
				g_TFminiPlus_flag = 1;
				g_TFmin_Dist = 0;//���¼����µ�����
				
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
				g_TFminiPlus_num = 0;//Ϊ�´����ݽ�����׼��
			}
		
			g_TFminiPlus_num = 0;//Ϊ�´����ݽ�����׼��
			
		}
			
    }else{//��������
		g_TFminiPlus_flag = 2;
		memset(TFminiPlus_buf, 0, sizeof(TFminiPlus_buf));
		g_TFminiPlus_num = 0;//Ϊ�´����ݽ�����׼��
	}
	
}



	
/*************��������վ****************/
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
//			case 'B': ��������ֱ�Ӹ������ݼ��� = g_TFmin_Dist;
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
** ������: strtou32
** ��������: ��һ���ַ���תΪ32λ�ı���������"1234"תΪ1234
** �������: str:ָ���ת�����ַ���     
** �������: ��
** ���أ�ת�������ֵ  
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
** ������:USART5_Putc
** ��������: ����1����һ�ַ�
** �������: c
** �������: ��
***********************************************************/
void UART5_Putc(unsigned char c)
{
    UART5->DR = (u8)c; //Ҫ���͵��ַ������������ݼĴ���  
    while((UART5->SR&0X40)==0); //�ȴ��������  
}
/**********************************************************
** ������:USART1_Puts
** ��������: ����1����һ�ַ���
** �������: ָ��str
** �������: ��
***********************************************************/
void UART5_Puts(char * str)
{
    while(*str)
    {
        UART5->DR= *str++;
        while((UART5->SR&0X40)==0);//�ȴ��������  
    }
}
/**********************************************************
** ������:UART_Send_Enter
** ��������: ����1����һ���з�
** �������: ��
** �������: ��
***********************************************************/
void UART_Send_Enter(void)
{
    UART5_Putc(0x0d);
    UART5_Putc(0x0a);
}

/*
************************************************************
*	�������ƣ�	Usart_SendString
*
*	�������ܣ�	�������ݷ���
*
*	��ڲ�����	USARTx��������
*				str��Ҫ���͵�����
*				len�����ݳ���
*
*	���ز�����	��
*
*	˵����		
************************************************************
*/
void Usart_SendString(USART_TypeDef *USARTx, unsigned char *str, unsigned short len)
{

	unsigned short count = 0;
	
	for(; count < len; count++)
	{
		USART_SendData(USARTx, *str++);									//��������
		while(USART_GetFlagStatus(USARTx, USART_FLAG_TC) == RESET);		//�ȴ��������
	}

}

/**********************************************************
** ������:UART_Send_Str
** ��������: ����1����һ�ַ��������س����й���
** �������: ָ��s
** �������: ��
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
** ������: UART_Put_Num
** ��������: STM32F��USART������ֵ
** �������: dat:Ҫ���͵���ֵ
** �������: ��
** ˵���������лὫ��ֵתΪ��Ӧ���ַ��������ͳ�ȥ������ 4567 תΪ "4567" 
***********************************************************/
void UART_Put_Num(unsigned long dat)
{
    char temp[20];
    u32tostr(dat,temp);
    UART_Send_Str(temp);
}
/**********************************************************
** ������: UART_Put_Inf
** ��������: STM32F��USART���͵�����Ϣ
** �������: inf:ָ����ʾ��Ϣ�ַ�����ָ��
             dat:һ����ֵ��ǰ�����ʾ��Ϣ������˵�������ֵ������
** �������: �� 
***********************************************************/
void UART_Put_Inf(char *inf,short dat)
{
    UART_Send_Str(inf);
    UART_Put_Num(dat);
    UART_Send_Str("\n");  
}
