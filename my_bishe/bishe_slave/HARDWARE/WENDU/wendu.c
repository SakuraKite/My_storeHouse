#include "wendu.h"
#include "delay.h"

//初始化IIC
void IIC_Init_s(void)
{					     
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(	RCC_APB2Periph_GPIOB, ENABLE );	//使能GPIOB时钟
	   
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3|GPIO_Pin_4;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP ;   //推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	GPIO_SetBits(GPIOB,GPIO_Pin_3|GPIO_Pin_4); 	//PB6,PB7 输出高
}
//产生IIC起始信号
void IIC_Start_s(void)
{
	SDA_OUT();     //sda线输出
	IIC_SDA=1;	  	  
	IIC_SCL=1;
	delay_us(4);
 	IIC_SDA=0;//START:when CLK is high,DATA change form high to low 
	delay_us(4);
	IIC_SCL=0;//钳住I2C总线，准备发送或接收数据 
}	  
//产生IIC停止信号
void IIC_Stop_s(void)
{
	SDA_OUT();//sda线输出
	IIC_SCL=0;
	IIC_SDA=0;//STOP:when CLK is high DATA change form low to high
 	delay_us(4);
	IIC_SCL=1; 
	IIC_SDA=1;//发送I2C总线结束信号
	delay_us(4);							   	
}
//等待应答信号到来
//返回值：1，接收应答失败
//        0，接收应答成功
u8 IIC_Wait_Ack_s(void)
{
	u8 ucErrTime=0;
	SDA_IN();      //SDA设置为输入  
	IIC_SDA=1;delay_us(1);	   
	IIC_SCL=1;delay_us(1);	 
	while(READ_SDA)
	{
		ucErrTime++;
		if(ucErrTime>250)
		{
			IIC_Stop_s();
			return 1;
		}
	}
	IIC_SCL=0;//时钟输出0 	   
	return 0;  
} 
//产生ACK应答
void IIC_Ack_s(void)
{
	IIC_SCL=0;
	SDA_OUT();
	IIC_SDA=0;
	delay_us(2);
	IIC_SCL=1;
	delay_us(2);
	IIC_SCL=0;
}
//不产生ACK应答		    
void IIC_NAck_s(void)
{
	IIC_SCL=0;
	SDA_OUT();
	IIC_SDA=1;
	delay_us(2);
	IIC_SCL=1;
	delay_us(2);
	IIC_SCL=0;
}					 				     
//IIC发送一个字节
//返回从机有无应答
//1，有应答
//0，无应答			  
void IIC_Send_Byte_s(u8 txd)
{                        
    u8 t;   
	SDA_OUT(); 	    
    IIC_SCL=0;//拉低时钟开始数据传输
    for(t=0;t<8;t++)
    {              
        //IIC_SDA=(txd&0x80)>>7;
		if((txd&0x80)>>7)
			IIC_SDA=1;
		else
			IIC_SDA=0;
		txd<<=1; 	  
		delay_us(2);   //对TEA5767这三个延时都是必须的
		IIC_SCL=1;
		delay_us(2); 
		IIC_SCL=0;	
		delay_us(2);
    }	 
} 	    
//读1个字节，ack=1时，发送ACK，ack=0，发送nACK   
u8 IIC_Read_Byte_s(unsigned char ack)
{
	unsigned char i,receive=0;
	SDA_IN();//SDA设置为输入
    for(i=0;i<8;i++ )
	{
        IIC_SCL=0; 
        delay_us(2);
		IIC_SCL=1;
        receive<<=1;
        if(READ_SDA)receive++;   
		delay_us(1); 
    }					 
    if (!ack)
        IIC_NAck_s();//发送nACK
    else
        IIC_Ack_s(); //发送ACK   
    return receive;
}


/**
brief AHT10初始化函数
param NONE
return NONE
*/
void AHT10Init()
{
	//IIC_Init();
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO|RCC_APB2Periph_GPIOB, ENABLE);
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable , ENABLE);
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_3|GPIO_Pin_4;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; //设置为推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
 	GPIO_Init(GPIOB, &GPIO_InitStructure);//初始化GPIOBA	
	GPIO_SetBits(GPIOB,GPIO_Pin_3|GPIO_Pin_4);				 //PA4 输出高
	
	IIC_Start_s();
	IIC_Send_Byte_s(AHT10_ADDRESS);
	IIC_Send_Byte_s(0xe1);	
	IIC_Send_Byte_s(0x08);
	IIC_Send_Byte_s(0x00);
	IIC_Stop_s();	
	delay_ms(40);//延时20ms让传感器稳定
}

/**
brief 检查AHT10是否存在
param NONE
return 0存在  1不存在
*/
u8 AHT10Check(void)
{
	u8 ack=0;
	IIC_Start_s();
	IIC_Send_Byte_s(AHT10_ADDRESS);
	ack=IIC_Wait_Ack_s();
	IIC_Stop_s();	
	return ack;
}

/**
brief AHT10软复位
param NONE
return NONE
*/
void AHT10Reset(void)
{
	IIC_Start_s();
	IIC_Send_Byte_s(AHT10_WRITE);
	IIC_Wait_Ack_s();
	IIC_Send_Byte_s(0xba);
	IIC_Wait_Ack_s();
	IIC_Stop_s();	
}

/**
brief 检查AHT10读温湿度数据
param *temperature：需要读出的温度数据，float指针类型,精度范围+-0.3C
param *humidity：需要读出的湿度数据，u8指针类型,精度范围+-2RH
return 0 读数据正常 1读数据失败
*/
u8 AHT10ReadData(float *temperature,u8 *humidity)
{
	u8 ack;
	u32 SRH=0,ST=0;
	u8 databuff[6];
	IIC_Start_s();
	IIC_Send_Byte_s(AHT10_WRITE);
	IIC_Wait_Ack_s();
	IIC_Send_Byte_s(0xac);
	IIC_Wait_Ack_s();
	IIC_Send_Byte_s(0x33);
	IIC_Wait_Ack_s();
	IIC_Send_Byte_s(0x00);
	IIC_Wait_Ack_s();
	IIC_Stop_s();	  
	delay_ms(80);//延时一会等待数据读出
	IIC_Start_s();
	IIC_Send_Byte_s(AHT10_READ);
	IIC_Wait_Ack_s();
	ack=IIC_Read_Byte_s(1);
	if((ack&0x40)==0)
	{
		databuff[0]=IIC_Read_Byte_s(1);
		databuff[1]=IIC_Read_Byte_s(1);
		databuff[2]=IIC_Read_Byte_s(1);
		databuff[3]=IIC_Read_Byte_s(1);
		databuff[4]=IIC_Read_Byte_s(0);
		IIC_Stop_s();
		SRH=(databuff[0]<<12)+(databuff[1]<<4)+(databuff[2]>>4);
		ST=((databuff[2]&0X0f)<<16)+(databuff[3]<<8)+(databuff[4]);
		*humidity=(int)(SRH*100.0/1024/1024+0.5);
		*temperature=((int)(ST*2000.0/1024/1024+0.5))/10.0-50;
		return 0;
	}
	IIC_Stop_s();	
	return 1;
}
