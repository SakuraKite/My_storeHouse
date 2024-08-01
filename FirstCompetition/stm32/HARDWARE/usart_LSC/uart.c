#include "uart.h"	

unsigned char Re_buf[40],temp_buf[40],counter=0;
unsigned char sign;




static unsigned char Temp[40];


//串口3初始化
void uart_init(u32 bound)                    //初始化 配置USART2
{
	//GPIO端口设置
    GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	 
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
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;//抢占优先级3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;		//子优先级3
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
    USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);//开启串口接受中断
    USART_Cmd(USART1, ENABLE);                    //使能串口1          

	//如下语句解决第1个字节无法正确发送出去的问题
    USART_ClearFlag(USART1, USART_FLAG_TC);                //清串口3发送标志
	
}
//发送字符串 函数   应用指针 方法
void USART1_Send_Str(unsigned char *s)//发送字符串 函数   应用指针 方法
{
        unsigned char i=0;  //定义一个局部变量  用来 发送字符串 ++运算

        while(s[i]!=' ')  // 每个字符串结尾 都是以   结尾的
        {
                USART_SendData(USART1,s[i]);        //通过库函数  发送数据
                while( USART_GetFlagStatus(USART1,USART_FLAG_TC)!= SET);  
                //等待发送完成。   检测 USART_FLAG_TC 是否置1；    //见库函数 P359 介
                i++;                 //i++一次
        }

}

void USART1_IRQHandler(void)		   //串口3全局中断服务函数
{   
   if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)  //接收中断有效,若接收数据寄存器满
   {
      Temp[counter] = USART_ReceiveData(USART1);   //接收数据
		
	    if(counter == 0 && (Temp[0] != '+')) return;      //第 0 号数据不是帧头，跳过
      counter++; 
      if((Temp[counter-1]=='K'&&Temp[counter-2]=='O')||counter>=40) //接收到
      { 
         memcpy(Re_buf,Temp,counter);
         counter=0; //重新赋值，准备下一帧数据的接收
         sign=1;
      }    
   }
}

//绿白红黑蓝
unsigned char color_Update(void)//跟新数据
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
			if(R_BUF<45&&G_BUF<45&&B_BUF<45)//黑色
				return 4;
			else{
			if(R_BUF>200&&G_BUF>200&&B_BUF>200)//白色
				return 2;
			if(R_BUF>G_BUF&&R_BUF>B_BUF)//红
				return 3;
			if(G_BUF>R_BUF&&G_BUF>B_BUF)//绿
				return 1;
			if(B_BUF>R_BUF&&B_BUF>G_BUF)//蓝
				return 5;
			}
	}
	return 6;
	
}


















