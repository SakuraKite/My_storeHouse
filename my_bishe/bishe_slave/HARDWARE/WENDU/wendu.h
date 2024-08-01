#ifndef _WENDU_H__
#define _WENDU_H__

#include  "sys.h"

#define AHT10_ADDRESS 0x70
#define AHT10_WRITE 0x70
#define AHT10_READ 0x71


#define SDA_IN()  {GPIOB->CRL&=0XFFF0FFFF;GPIOB->CRL|=(u32)8<<16;}
#define SDA_OUT() {GPIOB->CRL&=0XFFF0FFFF;GPIOB->CRL|=(u32)3<<16;}

//IO操作函数	 
#define IIC_SCL    PBout(3) //SCL
#define IIC_SDA    PBout(4) //SDA	 
#define READ_SDA   PBin(4)  //输入SDA 


void IIC_Write_One_Byte(u8 daddr,u8 addr,u8 data);
u8 IIC_Read_One_Byte(u8 daddr,u8 addr);	  

/*****************函数声明******************/
extern void AHT10Init(void);
extern u8 AHT10Check(void);
extern void AHT10Reset(void);
extern u8 AHT10ReadData(float *temperature,u8 *humidity);

#endif
