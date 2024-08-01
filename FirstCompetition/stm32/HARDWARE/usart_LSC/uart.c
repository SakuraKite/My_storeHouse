#include "uart.h"	

unsigned char Re_buf[40],temp_buf[40],counter=0;
unsigned char sign;




static unsigned char Temp[40];


//����3��ʼ��
void uart_init(u32 bound)                    //��ʼ�� ����USART2
{
	//GPIO�˿�����
    GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	 
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
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;//��ռ���ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;		//�����ȼ�3
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
    USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);//�������ڽ����ж�
    USART_Cmd(USART1, ENABLE);                    //ʹ�ܴ���1          

	//�����������1���ֽ��޷���ȷ���ͳ�ȥ������
    USART_ClearFlag(USART1, USART_FLAG_TC);                //�崮��3���ͱ�־
	
}
//�����ַ��� ����   Ӧ��ָ�� ����
void USART1_Send_Str(unsigned char *s)//�����ַ��� ����   Ӧ��ָ�� ����
{
        unsigned char i=0;  //����һ���ֲ�����  ���� �����ַ��� ++����

        while(s[i]!=' ')  // ÿ���ַ�����β ������   ��β��
        {
                USART_SendData(USART1,s[i]);        //ͨ���⺯��  ��������
                while( USART_GetFlagStatus(USART1,USART_FLAG_TC)!= SET);  
                //�ȴ�������ɡ�   ��� USART_FLAG_TC �Ƿ���1��    //���⺯�� P359 ��
                i++;                 //i++һ��
        }

}

void USART1_IRQHandler(void)		   //����3ȫ���жϷ�����
{   
   if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)  //�����ж���Ч,���������ݼĴ�����
   {
      Temp[counter] = USART_ReceiveData(USART1);   //��������
		
	    if(counter == 0 && (Temp[0] != '+')) return;      //�� 0 �����ݲ���֡ͷ������
      counter++; 
      if((Temp[counter-1]=='K'&&Temp[counter-2]=='O')||counter>=40) //���յ�
      { 
         memcpy(Re_buf,Temp,counter);
         counter=0; //���¸�ֵ��׼����һ֡���ݵĽ���
         sign=1;
      }    
   }
}

//�̰׺����
unsigned char color_Update(void)//��������
{   
int i;	int  R_BUF,G_BUF,B_BUF;
	int  num_wei;
	//long  buff_time=2000000;
	unsigned char  data[20]={'A','T','+','C','O','L','O','R',13,10,' '};
	USART1_Send_Str(data);
	//while(buff_time-->0)
	if(sign)
	{  
		 memcpy(Temp,Re_buf,40);
		 sign=0; 
			i=0;
			while(Temp[i++]!='R');
			i+=1;
			while(Temp[i++]!='R');
			i+=1;
			num_wei=0;
			while(Temp[i+num_wei]>='0'&&Temp[i+num_wei]<='9')num_wei++;
			if(num_wei==1)
			{
					R_BUF=Temp[i]-'0';
			}
			else if(num_wei==2)
			{
					R_BUF=10*(Temp[i]-'0')+Temp[i+1]-'0';
			}
			else if(num_wei==3)
			{
					R_BUF=100*(Temp[i]-'0')+10*(Temp[i+1]-'0')+Temp[i+2]-'0';
			}
			else
				return 6;
			/*---------------------------------------------*/
			while(Temp[i++]!='G');
			i+=1;
			num_wei=0;
			while(Temp[i+num_wei]>='0'&&Temp[i+num_wei]<='9')num_wei++;
			if(num_wei==1)
			{
					G_BUF=Temp[i]-'0';
			}
			else if(num_wei==2)
			{
					G_BUF=10*(Temp[i]-'0')+Temp[i+1]-'0';
			}
			else if(num_wei==3)
			{
					G_BUF=100*(Temp[i]-'0')+10*(Temp[i+1]-'0')+Temp[i+2]-'0';
			}
			else
				return 6;
			/*---------------------------------------------*/
			while(Temp[i++]!='B');
			i+=1;
			num_wei=0;
			while(Temp[i+num_wei]>='0'&&Temp[i+num_wei]<='9')num_wei++;
			if(num_wei==1)
			{
					B_BUF=Temp[i]-'0';
			}
			else if(num_wei==2)
			{
					B_BUF=10*(Temp[i]-'0')+Temp[i+1]-'0';
			}
			else if(num_wei==3)
			{
					B_BUF=100*(Temp[i]-'0')+10*(Temp[i+1]-'0')+Temp[i+2]-'0';
			}
			else
				return 6;
			if(R_BUF<45&&G_BUF<45&&B_BUF<45)//��ɫ
				return 4;
			else{
			if(R_BUF>200&&G_BUF>200&&B_BUF>200)//��ɫ
				return 2;
			if(R_BUF>G_BUF&&R_BUF>B_BUF)//��
				return 3;
			if(G_BUF>R_BUF&&G_BUF>B_BUF)//��
				return 1;
			if(B_BUF>R_BUF&&B_BUF>G_BUF)//��
				return 5;
			}
	}
	return 6;
	
}


















