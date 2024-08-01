# include "oled.h"
# include "oled_font.h"

u8 OLED_GRAM[144][8];

//��ʼ�ź�
void IIC_Start(void)
{
	GPIO_SetBits(SCL_GPIO, SCL_GPIO_Pin);
	GPIO_SetBits(SDA_GPIO, SDA_GPIO_Pin);
	GPIO_ResetBits(SDA_GPIO, SDA_GPIO_Pin);
	GPIO_ResetBits(SCL_GPIO, SCL_GPIO_Pin);
}

//�����ź�
void IIC_Stop(void)
{
	GPIO_ResetBits(SCL_GPIO,SCL_GPIO_Pin); 
    GPIO_ResetBits(SDA_GPIO,SDA_GPIO_Pin);
     GPIO_SetBits(SCL_GPIO,SCL_GPIO_Pin);
    GPIO_SetBits(SDA_GPIO,SDA_GPIO_Pin);
}

//�ȴ��ź���Ӧ
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


//дһ���ֽں���
//dat Ҫд������ݻ�����
//mode ����/�����־λ 0���� 1����
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
	//����OLED��ʾ 
	OLED_WR_Byte(0x8d, OLED_CMD);//��ɱ�ʹ��
	OLED_WR_Byte(0x14, OLED_CMD);//������ɱ�
	OLED_WR_Byte(0xaf, OLED_CMD);//������Ļ
}


void OLED_DisPlay_Off(void)
{
	//�ر�OLED��ʾ 
	OLED_WR_Byte(0x8D,OLED_CMD);//��ɱ�ʹ��
	OLED_WR_Byte(0x10,OLED_CMD);//�رյ�ɱ�
	OLED_WR_Byte(0xAF,OLED_CMD);//�ر���Ļ
}


void OLED_Refresh(void)
{
	//�����Դ浽OLED	
	u8 i,n;
	for(i=0;i<8;i++)
	{
	   OLED_WR_Byte(0xb0+i,OLED_CMD); //��������ʼ��ַ
	   OLED_WR_Byte(0x00,OLED_CMD);   //���õ�����ʼ��ַ
	   OLED_WR_Byte(0x10,OLED_CMD);   //���ø�����ʼ��ַ
	   for(n=0;n<128;n++)
		 OLED_WR_Byte(OLED_GRAM[n][i],OLED_DATA);
	}
}


void OLED_Clear(void)
{
	     //����
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
	 //��ָ���ط���ʾһ���ַ������������ַ�
     //x��0~127
     //y��0~63
     //size��ѡ������16*16��8*6
	
	u8 c = 0, i = 0;
	
	c = chr - ' ';
	if (x > 128 - size)//����
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
	//m^n����
	u32 result = 1;
	
	while (n--)	result *= m;
	
		return result;
}

void OLED_ShowNum(u8 x, u8 y, long num, u8 len, u8 size)
{
	//function:��ʾ��������
	//num:+-65535;����
	//x,y:�������
	//len:����λ��,���Ų���һλ
	//size�������С
	
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
						flag = 0;//���ű�־λ��0
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
	 //��ʾһ�����ִ����ַ��Ŵ�
     //д���º�����Ҫ���еǼ�
	 // ���ֵ�����̶�Ϊ16*16�����ɸı䣬��Ҫ���뺺�֣��������Ϊ16������Ϊ8Ϊ���ַ���
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

//���� 
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


//���һ����
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
						{temp=hz16[chr1][i];}//����16*16����
//				else if(size1==24)
//						{temp=Hzk2[chr1][i];}//����24*24����
//				else if(size1==32)       
//						{temp=Hzk3[chr1][i];}//����32*32����
//				else if(size1==64)
//						{temp=Hzk4[chr1][i];}//����64*64����
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
	//��ʾ��ʾBMPͼƬ128��64��ʼ������(x,y),x�ķ�Χ0��127��yΪҳ�ķ�Χ0��7
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
	//��ʾ��ʾBMPͼƬ128��64
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
	//��ʼ����Ҫ�õ���IO,��ͷ�ļ��޸ļ���
    //ִ�г�ʼ��OLED����
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
    
     
     OLED_WR_Byte(0xAE,OLED_CMD);//�ر���ʾ
     OLED_WR_Byte(0x02,OLED_CMD);//[1:0],00���е�ַģʽ;01��
                                                             //�е�ַģʽ;10,ҳ��ַģʽ;Ĭ�� 10;
     OLED_WR_Byte(0x10,OLED_CMD);//���ø��е�ַ
     OLED_WR_Byte(0x40,OLED_CMD);//������ʾ��ʼ�� [5:0],����
     OLED_WR_Byte(0x81,OLED_CMD);//�Աȶ�����
     OLED_WR_Byte(0xCF,OLED_CMD);//�趨SEG�����������
     OLED_WR_Byte(0xA1,OLED_CMD);//���ض�������,bit0:0,0->0;1,0->127;     0xa0���ҷ��� 0xa1����
     OLED_WR_Byte(0xC8,OLED_CMD);//���� COM ɨ�跽��;bit3:0,��ͨģʽ;1,
                                                             //�ض���ģʽ COM[N-1]->COM0;N:����·��   0xc0���·��� 0xc8����
     OLED_WR_Byte(0xA8,OLED_CMD);//��������·��
     OLED_WR_Byte(0x3f,OLED_CMD);//Ĭ�� 0X3F(1/64)
     OLED_WR_Byte(0x81,OLED_CMD);//�Աȶ�����
    OLED_WR_Byte(0xfF,OLED_CMD);//1~255;Ĭ��0X7F (��������,Խ��Խ��)
     OLED_WR_Byte(0xD3,OLED_CMD);////������ʾƫ��(0x00~0x3F)
     OLED_WR_Byte(0x00,OLED_CMD);//-not offset
     OLED_WR_Byte(0xd5,OLED_CMD);//����ʱ�ӷ�Ƶ����,��Ƶ��
     OLED_WR_Byte(0x80,OLED_CMD);//[3:0],��Ƶ����;[7:4],��Ƶ��
     OLED_WR_Byte(0xD9,OLED_CMD);//����Ԥ�������
     OLED_WR_Byte(0xF1,OLED_CMD);//��Ԥ�����Ϊ15��ʱ�Ӻͷŵ���Ϊ1��ʱ��
     OLED_WR_Byte(0xDA,OLED_CMD);//���� COM Ӳ����������
     OLED_WR_Byte(0x12,OLED_CMD);//[5:4]����
     OLED_WR_Byte(0xDB,OLED_CMD);//���� VCOMH ��ѹ����
     OLED_WR_Byte(0x40,OLED_CMD);//Set VCOM Deselect Level
    OLED_WR_Byte(0x20,OLED_CMD);//�����ڴ��ַģʽ (0x00/0x01/0x02)
    OLED_WR_Byte(0x02,OLED_CMD);//[1:0],00���е�ַģʽ;01��
                                                             //�е�ַģʽ;10,ҳ��ַģʽ;Ĭ�� 10;
     OLED_WR_Byte(0x8D,OLED_CMD);//��ɱ�����/����
     OLED_WR_Byte(0x14,OLED_CMD);//--set(0x10) disable
     OLED_WR_Byte(0xA4,OLED_CMD);// Disable Entire Display On (0xa4/0xa5)
     #if DISPLAY_MODE == 1
     OLED_WR_Byte(0xA7,OLED_CMD);//������ʾ��ʽ;bit0:1,������ʾ;0,������ʾ 
     #else
     OLED_WR_Byte(0xA6,OLED_CMD);//������ʾ��ʽ;bit0:1,������ʾ;0,������ʾ    
     #endif
     OLED_WR_Byte(0xAF,OLED_CMD);//--turn on oled panel
 
     OLED_WR_Byte(0xAF,OLED_CMD); /*display ON*/     
     OLED_Clear();
     OLED_Set_Pos(0,0);    
     
	
}


