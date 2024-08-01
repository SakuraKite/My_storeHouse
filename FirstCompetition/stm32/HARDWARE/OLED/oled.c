# include "oled.h"
# include "oled_font.h"

u8 OLED_GRAM[144][8];

//起始信号
void IIC_Start(void)
{
	GPIO_SetBits(SCL_GPIO, SCL_GPIO_Pin);
	GPIO_SetBits(SDA_GPIO, SDA_GPIO_Pin);
	GPIO_ResetBits(SDA_GPIO, SDA_GPIO_Pin);
	GPIO_ResetBits(SCL_GPIO, SCL_GPIO_Pin);
}

//结束信号
void IIC_Stop(void)
{
	GPIO_ResetBits(SCL_GPIO,SCL_GPIO_Pin); 
    GPIO_ResetBits(SDA_GPIO,SDA_GPIO_Pin);
     GPIO_SetBits(SCL_GPIO,SCL_GPIO_Pin);
    GPIO_SetBits(SDA_GPIO,SDA_GPIO_Pin);
}

//等待信号相应
void IIC_WaitAck(void)
{
	GPIO_SetBits(SCL_GPIO, SCL_GPIO_Pin);
	GPIO_ResetBits(SCL_GPIO, SCL_GPIO_Pin);
}

/******************************
//IIC Write Byte
******************************/
void IIC_Write_Byte(u8 IIC_Byte)
{
//	u8 i;
//	
//	for (i=0; i<8; i++)
//	{
//		GPIO_ResetBits(SCL_GPIO, SCL_GPIO_Pin);
//		
//		if (IIC_Byte & 0x80)
//			GPIO_SetBits(SDA_GPIO,	SDA_GPIO_Pin);
//		else
//			GPIO_ResetBits(SDA_GPIO, SDA_GPIO_Pin);
//			
//		IIC_WaitAck();
//		IIC_Byte<<=1;
//	}
	u8 i;
     for(i=0;i<8;i++)        
     {
         GPIO_ResetBits(SCL_GPIO,SCL_GPIO_Pin);
         if(IIC_Byte & 0x80)
             GPIO_SetBits(SDA_GPIO,SDA_GPIO_Pin);
         else
             GPIO_ResetBits(SDA_GPIO,SDA_GPIO_Pin);
         GPIO_SetBits(SCL_GPIO,SCL_GPIO_Pin);
         IIC_Byte<<=1;
     }
     GPIO_ResetBits(SCL_GPIO,SCL_GPIO_Pin);
     GPIO_SetBits(SDA_GPIO,SDA_GPIO_Pin);
     GPIO_SetBits(SCL_GPIO,SCL_GPIO_Pin);
     GPIO_ResetBits(SCL_GPIO,SCL_GPIO_Pin);
}

void OLED_Set_Pos(u8 x, u8 y)
{
	OLED_WR_Byte(0xb0+y, OLED_CMD);
	OLED_WR_Byte(((x&0xf0)>>4)|0x10, OLED_CMD);
	OLED_WR_Byte((x&0x0f), OLED_CMD);
	
}


//写一个字节函数
//dat 要写入的数据或命令
//mode 数据/命令标志位 0命令 1数据
void OLED_WR_Byte(u8 dat, u8 mode)
{
	IIC_Start();
	IIC_Write_Byte(0x78);
	//IIC_WaitAck();
	if (mode)
		IIC_Write_Byte(0x40);
	else
		IIC_Write_Byte(0x00);
	//IIC_WaitAck();
	IIC_Write_Byte(dat);
	IIC_WaitAck();
	IIC_Stop();
}


void OLED_Display_On(void)
{
	//开启OLED显示 
	OLED_WR_Byte(0x8d, OLED_CMD);//电荷泵使能
	OLED_WR_Byte(0x14, OLED_CMD);//开启电荷泵
	OLED_WR_Byte(0xaf, OLED_CMD);//点亮屏幕
}


void OLED_DisPlay_Off(void)
{
	//关闭OLED显示 
	OLED_WR_Byte(0x8D,OLED_CMD);//电荷泵使能
	OLED_WR_Byte(0x10,OLED_CMD);//关闭电荷泵
	OLED_WR_Byte(0xAF,OLED_CMD);//关闭屏幕
}


void OLED_Refresh(void)
{
	//更新显存到OLED	
	u8 i,n;
	for(i=0;i<8;i++)
	{
	   OLED_WR_Byte(0xb0+i,OLED_CMD); //设置行起始地址
	   OLED_WR_Byte(0x00,OLED_CMD);   //设置低列起始地址
	   OLED_WR_Byte(0x10,OLED_CMD);   //设置高列起始地址
	   for(n=0;n<128;n++)
		 OLED_WR_Byte(OLED_GRAM[n][i],OLED_DATA);
	}
}


void OLED_Clear(void)
{
	     //清屏
     u8 i,n;
     for(i=0;i<8;i++)
     {
         OLED_WR_Byte(0xb0+i,OLED_CMD);
         OLED_WR_Byte(0x00,OLED_CMD);
         OLED_WR_Byte(0x10,OLED_CMD);    
         for(n=0;n<128;n++)OLED_WR_Byte(0,OLED_DATA);
    }
}

void OLED_ShowChar(u8 x, u8 y, u8 chr, u8 size)
{
	 //在指定地方显示一个字符，包括部分字符
     //x：0~127
     //y：0~63
     //size：选择字体16*16或8*6
	
	u8 c = 0, i = 0;
	
	c = chr - ' ';
	if (x > 128 - size)//换行
	{
		x = 0;
		y = y + 2;
	}
	if (size == 16)
	{
		OLED_Set_Pos(x, y);
		for (i=0; i<8; ++i)
		{
			OLED_WR_Byte(F8X16[c*16+i], OLED_DATA);
		}
		OLED_Set_Pos(x, y+1);
		for(i=0; i<8; i++)
        {
             OLED_WR_Byte(F8X16[c*16+i+8],OLED_DATA);
        }
		
	}
	else
	{
		OLED_Set_Pos(x, y);
		
		 for(i=0; i<6; i++)
         {
             OLED_WR_Byte(F6x8[c][i],OLED_DATA);
         } 
	}
	
	
}

u32 OLED_Pow(u8 m, u8 n)
{
	//m^n函数
	u32 result = 1;
	
	while (n--)	result *= m;
	
		return result;
}

void OLED_ShowNum(u8 x, u8 y, long num, u8 len, u8 size)
{
	//function:显示整数数字
	//num:+-65535;整数
	//x,y:起点坐标
	//len:数字位数,负号不算一位
	//size：字体大小
	
	u32 t, temp1;
	u32  temp2;
	
	int flag = 0;
	
	if (num < 0)
	{
		flag = 1;
		num = -num;
	}
	temp2 = num;
	
	for (t=0; t<len; ++t)
	{
		temp1 = temp2 / OLED_Pow(10, len-t-1);
		temp2 -= temp1 * OLED_Pow(10, len-t-1);
		
		if (temp1 != 0)
		{
			if(flag)//-
			{
				OLED_ShowChar(x, y, '-', size);
						flag = 0;//负号标志位清0
				x = x+8;
			}
			
			OLED_ShowChar(x, y, temp1+'0', size);
		}
		else
		{
			 OLED_ShowChar(x,y,'0',size);
		}
		
		x += 8;
	}
}

void OLED_ShowString(u8 x,u8 y,u8 *chr,u8 size)
{
	 //显示一个汉字串和字符号串
     //写入新汉字需要进行登记
	 // 汉字的字体固定为16*16，不可改变，若要输入汉字，字体必须为16，字体为8为纯字符串
     u8 x0=x;
    // u16 k;
     while(*chr!='\0')
     {
         if((*chr)<128)
         {
             if(*chr==13)
             {
                 x=x0;
                 y+=size/8;
            }
             else
             {
                 OLED_ShowChar(x,y,*chr,size);
                 x+=8;
                 if(x>120)
                 {
                     x=0;
                    y+=size/8;
                 }            
             } 
             chr++;
         }
     }
}

//画点 
//x:0~127
//y:0~63
void OLED_DrawPoint(u8 x,u8 y)
{
	u8 i,m,n;
	i=y/8;
	m=y%8;
	n=1<<m;
	OLED_GRAM[x][i]|=n;
}


//清除一个点
//x:0~127
//y:0~63
void OLED_ClearPoint(u8 x,u8 y)
{
	u8 i,m,n;
	i=y/8;
	m=y%8;
	n=1<<m;
	OLED_GRAM[x][i]=~OLED_GRAM[x][i];
	OLED_GRAM[x][i]|=n;
	OLED_GRAM[x][i]=~OLED_GRAM[x][i];
}

void OLED_ShowChinese(u8 x,u8 y,u8 num,u8 size1)
{
	u8 i,m,n=0,temp,chr1;
	u8 x0=x,y0=y;
	u8 size3=size1/8;
	while(size3--)
	{
		chr1=num*size1/8+n;
		n++;
			for(i=0;i<size1;i++)
			{
				if(size1==16)
						{temp=hz16[chr1][i];}//调用16*16字体
//				else if(size1==24)
//						{temp=Hzk2[chr1][i];}//调用24*24字体
//				else if(size1==32)       
//						{temp=Hzk3[chr1][i];}//调用32*32字体
//				else if(size1==64)
//						{temp=Hzk4[chr1][i];}//调用64*64字体
//				else return;
							
						for(m=0;m<8;m++)
							{
								if(temp&0x01)OLED_DrawPoint(x,y);
								else OLED_ClearPoint(x,y);
								temp>>=1;
								y++;
							}
							x++;
							if((x-x0)==size1)
							{x=x0;y0=y0+8;}
							y=y0;
			 }
	}
}


void OLED_DrawDMP(u8 x0, u8 y0, u8 x1, u8 y1, u8 BMP[])
{
	//显示显示BMP图片128×64起始点坐标(x,y),x的范围0～127，y为页的范围0～7
	u16 j = 0;
	u8 x, y;
	
	for (y=y0; y<y1; y++)
	{
		OLED_Set_Pos(x0, y);
		
		for (x=x0; x<x1; x++)
		{
			OLED_WR_Byte(BMP[j++], OLED_DATA);
		}
	}
	
	
}

void OLED_Draw12864BMP(u8 BMP[])
{
	//显示显示BMP图片128×64
	u16 j = 0;
	u8 x, y;
	
	for (y=0; y<8; y++)
	{
		OLED_Set_Pos(0, y);
		for (x=0; x<128; x++)
		{
			# if DISPLAY_MODE
			OLED_WR_Byte(~BMP[j++], OLED_DATA);
			# else
			OLED_WR_Byte(BMP[j++], OLED_DATA);
			# endif
		}
	}
}

void OLED_Init(void)
{
	//初始化需要用到的IO,从头文件修改即可
    //执行初始化OLED代码
//	   GPIO_InitTypeDef GPIO_InitStructure;
//     //SCL  D0
//     RCC_APB2PeriphClockCmd(OLED_GPIOClock | RCC_APB2Periph_AFIO, ENABLE);
//	
//	 GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);
//	
//     GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
//     GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//	
//		GPIO_InitStructure.GPIO_Pin = SCL_GPIO_Pin;
//     GPIO_Init(SCL_GPIO,&GPIO_InitStructure);    
//		GPIO_SetBits(SCL_GPIO,SCL_GPIO_Pin);
//     //SDA  D1
//	 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
//     GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//	
//		GPIO_InitStructure.GPIO_Pin = SDA_GPIO_Pin;
//    GPIO_Init(SDA_GPIO,&GPIO_InitStructure);    
//		GPIO_SetBits(SDA_GPIO,SDA_GPIO_Pin);
    
     
     OLED_WR_Byte(0xAE,OLED_CMD);//关闭显示
     OLED_WR_Byte(0x02,OLED_CMD);//[1:0],00，列地址模式;01，
                                                             //行地址模式;10,页地址模式;默认 10;
     OLED_WR_Byte(0x10,OLED_CMD);//设置高列地址
     OLED_WR_Byte(0x40,OLED_CMD);//设置显示开始行 [5:0],行数
     OLED_WR_Byte(0x81,OLED_CMD);//对比度设置
     OLED_WR_Byte(0xCF,OLED_CMD);//设定SEG输出电流亮度
     OLED_WR_Byte(0xA1,OLED_CMD);//段重定义设置,bit0:0,0->0;1,0->127;     0xa0左右反置 0xa1正常
     OLED_WR_Byte(0xC8,OLED_CMD);//设置 COM 扫描方向;bit3:0,普通模式;1,
                                                             //重定义模式 COM[N-1]->COM0;N:驱动路数   0xc0上下反置 0xc8正常
     OLED_WR_Byte(0xA8,OLED_CMD);//设置驱动路数
     OLED_WR_Byte(0x3f,OLED_CMD);//默认 0X3F(1/64)
     OLED_WR_Byte(0x81,OLED_CMD);//对比度设置
    OLED_WR_Byte(0xfF,OLED_CMD);//1~255;默认0X7F (亮度设置,越大越亮)
     OLED_WR_Byte(0xD3,OLED_CMD);////设置显示偏移(0x00~0x3F)
     OLED_WR_Byte(0x00,OLED_CMD);//-not offset
     OLED_WR_Byte(0xd5,OLED_CMD);//设置时钟分频因子,震荡频率
     OLED_WR_Byte(0x80,OLED_CMD);//[3:0],分频因子;[7:4],震荡频率
     OLED_WR_Byte(0xD9,OLED_CMD);//设置预充电周期
     OLED_WR_Byte(0xF1,OLED_CMD);//将预充电作为15个时钟和放电作为1个时钟
     OLED_WR_Byte(0xDA,OLED_CMD);//设置 COM 硬件引脚配置
     OLED_WR_Byte(0x12,OLED_CMD);//[5:4]配置
     OLED_WR_Byte(0xDB,OLED_CMD);//设置 VCOMH 电压倍率
     OLED_WR_Byte(0x40,OLED_CMD);//Set VCOM Deselect Level
    OLED_WR_Byte(0x20,OLED_CMD);//设置内存地址模式 (0x00/0x01/0x02)
    OLED_WR_Byte(0x02,OLED_CMD);//[1:0],00，列地址模式;01，
                                                             //行地址模式;10,页地址模式;默认 10;
     OLED_WR_Byte(0x8D,OLED_CMD);//电荷泵启用/禁用
     OLED_WR_Byte(0x14,OLED_CMD);//--set(0x10) disable
     OLED_WR_Byte(0xA4,OLED_CMD);// Disable Entire Display On (0xa4/0xa5)
     #if DISPLAY_MODE == 1
     OLED_WR_Byte(0xA7,OLED_CMD);//设置显示方式;bit0:1,反相显示;0,正常显示 
     #else
     OLED_WR_Byte(0xA6,OLED_CMD);//设置显示方式;bit0:1,反相显示;0,正常显示    
     #endif
     OLED_WR_Byte(0xAF,OLED_CMD);//--turn on oled panel
 
     OLED_WR_Byte(0xAF,OLED_CMD); /*display ON*/     
     OLED_Clear();
     OLED_Set_Pos(0,0);    
     
	
}


