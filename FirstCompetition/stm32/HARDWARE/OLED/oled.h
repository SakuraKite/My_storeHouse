# ifndef _OLED_H_
# define _OLED_H_

# include <stm32f10x_gpio.h>
# include "oled_font.h"

/***************可根据需求设置选项*********************/
# define DISPLAY_MODE 0	// 显示模式，1位黑字白底，2位白字黑体
# define OLED_CMD  0	//写命令
# define OLED_DATA 1	//写数据
/******************引脚定义*******************************/
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

/* OLED初始化函数 */
void OLED_Init(void);

/* 功能函数 */
void OLED_Refresh(void);									//更新显存到OLED
void OLED_ShowChar(u8 x, u8 y, u8 chr, u8 size);			//显示一个字符，（x坐标，y坐标，显示字符，字体）ps：字体为16 or 8
void OLED_ShowNum(u8 x, u8 y, long num, u8 len, u8 size);;	//显示数字，（x坐标，y坐标，数字，数字长度，数字大小）ps：字体为16 or 8
void OLED_DrawBMP(u8 x0, u8 y0, u8 x1, u8 y1, u8 BMP[]);	//显示图片，（起始x，y坐标，终止x，y坐标，图片地址）
void OLED_Draw12864BMP(u8 BMP[]);							//显示128*64的图片（图片地址）
void OLED_Clear(void);
void OLED_ShowString(u8 x, u8 y, u8 *chr, u8 size);			//显示字符串，（x坐标，y坐标，文字串，字符串字体）
							
void OLED_ShowChinese(u8 x,u8 y,u8 num,u8 size1);			// 汉字的字体固定为16*16，不可改变

/* 其他函数，不需要调用 */
void OLED_Set_Pos(u8 x, u8 y);
void OLED_WR_Byte(u8 dat, u8 m);							//(数据or命令，选择模式：数据1 or 命令0)


# endif
