# ifndef _OLED_H_
# define _OLED_H_

# include <stm32f10x_gpio.h>
# include "oled_font.h"

/***************�ɸ�����������ѡ��*********************/
# define DISPLAY_MODE 0	// ��ʾģʽ��1λ���ְ׵ף�2λ���ֺ���
# define OLED_CMD  0	//д����
# define OLED_DATA 1	//д����
/******************���Ŷ���*******************************/
// IIC_SCL
# define SCL_GPIOClock    RCC_APB2Periph_GPIOB
# define SCL_GPIO	   GPIOB
# define SCL_GPIO_Pin  GPIO_Pin_0
// IIC_SDA
# define SDA_GPIOClock    RCC_APB2Periph_GPIOB
# define SDA_GPIO	   GPIOB
# define SDA_GPIO_Pin  GPIO_Pin_1
// OLED_Clock
# define OLED_GPIOClock RCC_APB2Periph_GPIOB

/*********************************************************/

/* OLED��ʼ������ */
void OLED_Init(void);

/* ���ܺ��� */
void OLED_Refresh(void);									//�����Դ浽OLED
void OLED_ShowChar(u8 x, u8 y, u8 chr, u8 size);			//��ʾһ���ַ�����x���꣬y���꣬��ʾ�ַ������壩ps������Ϊ16 or 8
void OLED_ShowNum(u8 x, u8 y, long num, u8 len, u8 size);;	//��ʾ���֣���x���꣬y���꣬���֣����ֳ��ȣ����ִ�С��ps������Ϊ16 or 8
void OLED_DrawBMP(u8 x0, u8 y0, u8 x1, u8 y1, u8 BMP[]);	//��ʾͼƬ������ʼx��y���꣬��ֹx��y���꣬ͼƬ��ַ��
void OLED_Draw12864BMP(u8 BMP[]);							//��ʾ128*64��ͼƬ��ͼƬ��ַ��
void OLED_Clear(void);
void OLED_ShowString(u8 x, u8 y, u8 *chr, u8 size);			//��ʾ�ַ�������x���꣬y���꣬���ִ����ַ������壩
							
void OLED_ShowChinese(u8 x,u8 y,u8 num,u8 size1);			// ���ֵ�����̶�Ϊ16*16�����ɸı�

/* ��������������Ҫ���� */
void OLED_Set_Pos(u8 x, u8 y);
void OLED_WR_Byte(u8 dat, u8 m);							//(����or���ѡ��ģʽ������1 or ����0)


# endif
