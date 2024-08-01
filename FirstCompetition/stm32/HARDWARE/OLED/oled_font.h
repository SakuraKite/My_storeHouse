# ifndef _OLED_FONT_H_
# define _OLED_FONT_H_

# define hz16_num 3 //ºº×Ö¸öÊý

struct typFNT_GB162
{
	char Msk[32];
	unsigned char Index[2];
	unsigned char num;
};

extern const unsigned char hz16[12][16];
extern const unsigned char F6x8[][6];
extern const unsigned char F8X16[];


# endif
