#include "oled_font.h"
/*
 此文件用来存放汉字的点阵和字符点阵
 必须在.h文件声明
 */
 
/*     字模选项
    阴码
    列行试
     点阵32
    索引  随便
     取模逆向
     输出数制 十六进制数
     C51格式
     段前缀      无
    段后缀      无
 18     注释前缀    "
 19     注释后缀    ",
 20     数据前缀    0x
 21     数据后缀    ,
 22     行前缀      无
 23     行后缀      ,
 24     行尾缀      ,
 25 */
 
 //常用ASCII表
 //偏移量32
 //ASCII字符集
 //偏移量32
 //大小:12*6
 
/***************************6*8的点阵**************************/
const unsigned char F6x8[][6] = 
{
0x00,0x00,0x00,0x00,0x00,0x00,//  0,
0x00,0x00,0x5E,0x00,0x00,0x00,//! 1,
0x00,0x04,0x02,0x04,0x02,0x00,//" 2,
0x28,0x78,0x3C,0x78,0x2C,0x28,//# 3,
0x6C,0x54,0xFE,0x54,0x64,0x00,//$ 4,
0x08,0x54,0x28,0x38,0x54,0x20,//% 5,
0x60,0x5C,0x74,0x2C,0x58,0x40,//& 6,
0x04,0x02,0x00,0x00,0x00,0x00,//' 7,
0x00,0x00,0x00,0x38,0x44,0x82,//( 8,
0x00,0x82,0x44,0x38,0x00,0x00,//) 9,
0x18,0x18,0x3C,0x18,0x18,0x00,//* 10,
0x08,0x08,0x3E,0x08,0x08,0x00,//+ 11,
0x80,0x40,0x00,0x00,0x00,0x00,//, 12,
0x08,0x08,0x08,0x08,0x08,0x00,//- 13,
0x00,0x40,0x00,0x00,0x00,0x00,//. 14,
0x80,0x60,0x10,0x0C,0x02,0x00,/// 15,
0x38,0x44,0x44,0x44,0x38,0x00,//0 16,
0x00,0x48,0x7C,0x40,0x00,0x00,//1 17,
0x48,0x64,0x64,0x54,0x4C,0x00,//2 18,
0x28,0x44,0x4C,0x4C,0x34,0x00,//3 19,
0x10,0x28,0x24,0x7C,0x20,0x00,//4 20,
0x3C,0x54,0x54,0x54,0x34,0x00,//5 21,
0x38,0x54,0x54,0x54,0x30,0x00,//6 22,
0x0C,0x04,0x74,0x0C,0x04,0x00,//7 23,
0x2C,0x54,0x54,0x54,0x6C,0x00,//8 24,
0x18,0x54,0x54,0x54,0x38,0x00,//9 25,
0x00,0x00,0x48,0x00,0x00,0x00,//: 26,
0x00,0x00,0xC8,0x00,0x00,0x00,//; 27,
0x00,0x10,0x10,0x28,0x44,0x00,//< 28,
0x28,0x28,0x28,0x28,0x28,0x00,//= 29,
0x00,0x44,0x48,0x28,0x10,0x10,//> 30,
0x04,0x02,0x52,0x0A,0x04,0x00,//? 31,
0x38,0x44,0x74,0x6C,0x38,0x00,//@ 32,
0x40,0x70,0x2C,0x38,0x60,0x40,//A 33,
0x44,0x7C,0x4C,0x4C,0x34,0x00,//B 34,
0x38,0x44,0x44,0x44,0x24,0x00,//C 35,
0x44,0x7C,0x44,0x44,0x38,0x00,//D 36,
0x44,0x7C,0x4C,0x5C,0x44,0x00,//E 37,
0x44,0x7C,0x4C,0x1C,0x04,0x00,//F 38,
0x38,0x44,0x44,0x64,0x24,0x20,//G 39,
0x44,0x7C,0x10,0x10,0x7C,0x44,//H 40,
0x44,0x44,0x7C,0x44,0x44,0x00,//I 41,
0x80,0x84,0x84,0xFC,0x04,0x04,//J 42,
0x44,0x7C,0x5C,0x78,0x64,0x44,//K 43,
0x44,0x7C,0x44,0x40,0x40,0x40,//L 44,
0x7C,0x1C,0x70,0x0C,0x7C,0x00,//M 45,
0x44,0x7C,0x58,0x24,0x7C,0x04,//N 46,
0x38,0x44,0x44,0x44,0x38,0x00,//O 47,
0x44,0x7C,0x54,0x14,0x1C,0x00,//P 48,
0x38,0x64,0x64,0xC4,0xB8,0x00,//Q 49,
0x44,0x7C,0x4C,0x1C,0x6C,0x40,//R 50,
0x6C,0x54,0x54,0x54,0x64,0x00,//S 51,
0x04,0x44,0x7C,0x44,0x04,0x00,//T 52,
0x04,0x7C,0x40,0x40,0x7C,0x04,//U 53,
0x04,0x1C,0x60,0x34,0x0C,0x04,//V 54,
0x0C,0x70,0x0C,0x70,0x0C,0x00,//W 55,
0x44,0x6C,0x54,0x6C,0x44,0x00,//X 56,
0x04,0x4C,0x74,0x4C,0x04,0x00,//Y 57,
0x44,0x64,0x74,0x4C,0x44,0x00,//Z 58,
0x00,0x00,0xFE,0x82,0x82,0x00,//[ 59,
0x00,0x06,0x18,0x20,0x40,0x00,//\ 60,
0x00,0x82,0x82,0xFE,0x00,0x00,//] 61,
0x00,0x04,0x02,0x04,0x00,0x00,//^ 62,
0x80,0x80,0x80,0x80,0x80,0x80,//_ 63,
0x00,0x00,0x02,0x00,0x00,0x00,//` 64,
0x00,0x68,0x58,0x58,0x78,0x40,//a 65,
0x04,0x7C,0x48,0x48,0x30,0x00,//b 66,
0x00,0x30,0x48,0x48,0x48,0x00,//c 67,
0x00,0x30,0x48,0x4C,0x7C,0x40,//d 68,
0x00,0x30,0x58,0x58,0x50,0x00,//e 69,
0x00,0x48,0x7C,0x4C,0x4C,0x04,//f 70,
0x00,0xF8,0xD8,0xD8,0xD8,0xC8,//g 71,
0x44,0x7C,0x48,0x08,0x78,0x40,//h 72,
0x00,0x48,0x7C,0x40,0x00,0x00,//i 73,
0x80,0x80,0x88,0x7C,0x00,0x00,//j 74,
0x44,0x7C,0x60,0x38,0x48,0x48,//k 75,
0x44,0x44,0x7E,0x40,0x40,0x00,//l 76,
0x78,0x08,0x78,0x08,0x78,0x00,//m 77,
0x48,0x78,0x48,0x08,0x78,0x40,//n 78,
0x00,0x30,0x48,0x48,0x30,0x00,//o 79,
0x88,0xF8,0xC8,0x48,0x38,0x00,//p 80,
0x00,0x30,0x48,0xC8,0xF8,0x80,//q 81,
0x48,0x78,0x50,0x08,0x08,0x00,//r 82,
0x00,0x58,0x68,0x68,0x68,0x00,//s 83,
0x00,0x08,0x7C,0x48,0x40,0x00,//t 84,
0x08,0x78,0x40,0x48,0x78,0x40,//u 85,
0x08,0x18,0x68,0x20,0x18,0x08,//v 86,
0x18,0x60,0x18,0x70,0x18,0x00,//w 87,
0x48,0x78,0x30,0x78,0x48,0x00,//x 88,
0x88,0x98,0x68,0x30,0x18,0x08,//y 89,
0x00,0x48,0x68,0x58,0x48,0x00,//z 90,
0x00,0x00,0x10,0xFE,0x82,0x00,//{ 91,
0x00,0x00,0x00,0xFF,0x00,0x00,//| 92,
0x00,0x82,0xFE,0x10,0x00,0x00,//} 93,
0x02,0x01,0x01,0x02,0x02,0x01,//~ 94,

};
/**************8*16的点阵*********************/
const unsigned char F8X16[] = 
{
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,//  0,
0x00,0x00,0x00,0xF8,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x33,0x00,0x00,0x00,0x00,//! 1,
0x00,0x10,0x0C,0x02,0x10,0x0C,0x02,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,//" 2,
0x00,0x40,0xC0,0x78,0x40,0xC0,0x78,0x00,0x00,0x04,0x3F,0x04,0x04,0x3F,0x04,0x00,//# 3,
0x00,0x70,0x88,0x88,0xFC,0x08,0x30,0x00,0x00,0x18,0x20,0x20,0xFF,0x21,0x1E,0x00,//$ 4,
0xF0,0x08,0xF0,0x80,0x60,0x18,0x00,0x00,0x00,0x31,0x0C,0x03,0x1E,0x21,0x1E,0x00,//% 5,
0x00,0xF0,0x08,0x88,0x70,0x00,0x00,0x00,0x1E,0x21,0x23,0x2C,0x19,0x27,0x21,0x10,//& 6,
0x00,0x12,0x0E,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,//' 7,
0x00,0x00,0x00,0xE0,0x18,0x04,0x02,0x00,0x00,0x00,0x00,0x07,0x18,0x20,0x40,0x00,//( 8,
0x00,0x02,0x04,0x18,0xE0,0x00,0x00,0x00,0x00,0x40,0x20,0x18,0x07,0x00,0x00,0x00,//) 9,
0x40,0x40,0x80,0xF0,0x80,0x40,0x40,0x00,0x02,0x02,0x01,0x0F,0x01,0x02,0x02,0x00,//* 10,
0x00,0x00,0x00,0x00,0xE0,0x00,0x00,0x00,0x00,0x01,0x01,0x01,0x0F,0x01,0x01,0x01,//+ 11,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x90,0x70,0x00,0x00,0x00,0x00,0x00,//, 12,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x01,0x01,0x01,0x01,0x01,0x00,//- 13,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x30,0x30,0x00,0x00,0x00,0x00,0x00,//. 14,
0x00,0x00,0x00,0x00,0xC0,0x38,0x04,0x00,0x00,0x60,0x18,0x07,0x00,0x00,0x00,0x00,/// 15,
0x00,0xE0,0x10,0x08,0x08,0x10,0xE0,0x00,0x00,0x0F,0x10,0x20,0x20,0x10,0x0F,0x00,//0 16,
0x00,0x00,0x10,0x10,0xF8,0x00,0x00,0x00,0x00,0x00,0x20,0x20,0x3F,0x20,0x20,0x00,//1 17,
0x00,0x70,0x08,0x08,0x08,0x08,0xF0,0x00,0x00,0x30,0x28,0x24,0x22,0x21,0x30,0x00,//2 18,
0x00,0x30,0x08,0x08,0x08,0x88,0x70,0x00,0x00,0x18,0x20,0x21,0x21,0x22,0x1C,0x00,//3 19,
0x00,0x00,0x80,0x40,0x30,0xF8,0x00,0x00,0x00,0x06,0x05,0x24,0x24,0x3F,0x24,0x24,//4 20,
0x00,0xF8,0x88,0x88,0x88,0x08,0x08,0x00,0x00,0x19,0x20,0x20,0x20,0x11,0x0E,0x00,//5 21,
0x00,0xE0,0x10,0x88,0x88,0x90,0x00,0x00,0x00,0x0F,0x11,0x20,0x20,0x20,0x1F,0x00,//6 22,
0x00,0x18,0x08,0x08,0x88,0x68,0x18,0x00,0x00,0x00,0x00,0x3E,0x01,0x00,0x00,0x00,//7 23,
0x00,0x70,0x88,0x08,0x08,0x88,0x70,0x00,0x00,0x1C,0x22,0x21,0x21,0x22,0x1C,0x00,//8 24,
0x00,0xF0,0x08,0x08,0x08,0x10,0xE0,0x00,0x00,0x01,0x12,0x22,0x22,0x11,0x0F,0x00,//9 25,
0x00,0x00,0x00,0xC0,0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x30,0x30,0x00,0x00,0x00,//: 26,
0x00,0x00,0x00,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xE0,0x00,0x00,0x00,0x00,//; 27,
0x00,0x00,0x80,0x40,0x20,0x10,0x08,0x00,0x00,0x01,0x02,0x04,0x08,0x10,0x20,0x00,//< 28,
0x00,0x40,0x40,0x40,0x40,0x40,0x40,0x00,0x00,0x02,0x02,0x02,0x02,0x02,0x02,0x00,//= 29,
0x00,0x08,0x10,0x20,0x40,0x80,0x00,0x00,0x00,0x20,0x10,0x08,0x04,0x02,0x01,0x00,//> 30,
0x00,0x70,0x48,0x08,0x08,0x88,0x70,0x00,0x00,0x00,0x00,0x30,0x37,0x00,0x00,0x00,//? 31,
0xC0,0x30,0xC8,0x28,0xE8,0x10,0xE0,0x00,0x07,0x18,0x27,0x28,0x2F,0x28,0x17,0x00,//@ 32,
0x00,0x00,0xC0,0x38,0xE0,0x00,0x00,0x00,0x20,0x3C,0x23,0x02,0x02,0x27,0x38,0x20,//A 33,
0x08,0xF8,0x88,0x88,0x88,0x70,0x00,0x00,0x20,0x3F,0x20,0x20,0x20,0x11,0x0E,0x00,//B 34,
0xC0,0x30,0x08,0x08,0x08,0x08,0x38,0x00,0x07,0x18,0x20,0x20,0x20,0x10,0x08,0x00,//C 35,
0x08,0xF8,0x08,0x08,0x08,0x10,0xE0,0x00,0x20,0x3F,0x20,0x20,0x20,0x10,0x0F,0x00,//D 36,
0x08,0xF8,0x88,0x88,0xE8,0x08,0x10,0x00,0x20,0x3F,0x20,0x20,0x23,0x20,0x18,0x00,//E 37,
0x08,0xF8,0x88,0x88,0xE8,0x08,0x10,0x00,0x20,0x3F,0x20,0x00,0x03,0x00,0x00,0x00,//F 38,
0xC0,0x30,0x08,0x08,0x08,0x38,0x00,0x00,0x07,0x18,0x20,0x20,0x22,0x1E,0x02,0x00,//G 39,
0x08,0xF8,0x08,0x00,0x00,0x08,0xF8,0x08,0x20,0x3F,0x21,0x01,0x01,0x21,0x3F,0x20,//H 40,
0x00,0x08,0x08,0xF8,0x08,0x08,0x00,0x00,0x00,0x20,0x20,0x3F,0x20,0x20,0x00,0x00,//I 41,
0x00,0x00,0x08,0x08,0xF8,0x08,0x08,0x00,0xC0,0x80,0x80,0x80,0x7F,0x00,0x00,0x00,//J 42,
0x08,0xF8,0x88,0xC0,0x28,0x18,0x08,0x00,0x20,0x3F,0x20,0x01,0x26,0x38,0x20,0x00,//K 43,
0x08,0xF8,0x08,0x00,0x00,0x00,0x00,0x00,0x20,0x3F,0x20,0x20,0x20,0x20,0x30,0x00,//L 44,
0x08,0xF8,0xF8,0x00,0xF8,0xF8,0x08,0x00,0x20,0x3F,0x01,0x3E,0x01,0x3F,0x20,0x00,//M 45,
0x08,0xF8,0x30,0xC0,0x00,0x08,0xF8,0x08,0x20,0x3F,0x20,0x00,0x07,0x18,0x3F,0x00,//N 46,
0xE0,0x10,0x08,0x08,0x08,0x10,0xE0,0x00,0x0F,0x10,0x20,0x20,0x20,0x10,0x0F,0x00,//O 47,
0x08,0xF8,0x08,0x08,0x08,0x08,0xF0,0x00,0x20,0x3F,0x21,0x01,0x01,0x01,0x00,0x00,//P 48,
0xE0,0x10,0x08,0x08,0x08,0x10,0xE0,0x00,0x0F,0x10,0x28,0x28,0x30,0x50,0x4F,0x00,//Q 49,
0x08,0xF8,0x88,0x88,0x88,0x88,0x70,0x00,0x20,0x3F,0x20,0x00,0x03,0x0C,0x30,0x20,//R 50,
0x00,0x70,0x88,0x08,0x08,0x08,0x38,0x00,0x00,0x38,0x20,0x21,0x21,0x22,0x1C,0x00,//S 51,
0x18,0x08,0x08,0xF8,0x08,0x08,0x18,0x00,0x00,0x00,0x20,0x3F,0x20,0x00,0x00,0x00,//T 52,
0x08,0xF8,0x08,0x00,0x00,0x08,0xF8,0x08,0x00,0x1F,0x20,0x20,0x20,0x20,0x1F,0x00,//U 53,
0x08,0x78,0x88,0x00,0x00,0xC8,0x38,0x08,0x00,0x00,0x07,0x38,0x0E,0x01,0x00,0x00,//V 54,
0x08,0xF8,0x00,0xF8,0x00,0xF8,0x08,0x00,0x00,0x03,0x3E,0x01,0x3E,0x03,0x00,0x00,//W 55,
0x08,0x18,0x68,0x80,0x80,0x68,0x18,0x08,0x20,0x30,0x2C,0x03,0x03,0x2C,0x30,0x20,//X 56,
0x08,0x38,0xC8,0x00,0xC8,0x38,0x08,0x00,0x00,0x00,0x20,0x3F,0x20,0x00,0x00,0x00,//Y 57,
0x10,0x08,0x08,0x08,0xC8,0x38,0x08,0x00,0x20,0x38,0x26,0x21,0x20,0x20,0x18,0x00,//Z 58,
0x00,0x00,0x00,0xFE,0x02,0x02,0x02,0x00,0x00,0x00,0x00,0x7F,0x40,0x40,0x40,0x00,//[ 59,
0x00,0x04,0x38,0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x06,0x38,0xC0,0x00,//\ 60,
0x00,0x02,0x02,0x02,0xFE,0x00,0x00,0x00,0x00,0x40,0x40,0x40,0x7F,0x00,0x00,0x00,//] 61,
0x00,0x00,0x04,0x02,0x02,0x04,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,//^ 62,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,//_ 63,
0x00,0x02,0x02,0x04,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,//` 64,
0x00,0x00,0x80,0x80,0x80,0x00,0x00,0x00,0x00,0x19,0x24,0x24,0x12,0x3F,0x20,0x00,//a 65,
0x10,0xF0,0x00,0x80,0x80,0x00,0x00,0x00,0x00,0x3F,0x11,0x20,0x20,0x11,0x0E,0x00,//b 66,
0x00,0x00,0x00,0x80,0x80,0x80,0x00,0x00,0x00,0x0E,0x11,0x20,0x20,0x20,0x11,0x00,//c 67,
0x00,0x00,0x80,0x80,0x80,0x90,0xF0,0x00,0x00,0x1F,0x20,0x20,0x20,0x10,0x3F,0x20,//d 68,
0x00,0x00,0x80,0x80,0x80,0x80,0x00,0x00,0x00,0x1F,0x24,0x24,0x24,0x24,0x17,0x00,//e 69,
0x00,0x80,0x80,0xE0,0x90,0x90,0x20,0x00,0x00,0x20,0x20,0x3F,0x20,0x20,0x00,0x00,//f 70,
0x00,0x00,0x80,0x80,0x80,0x80,0x80,0x00,0x00,0x6B,0x94,0x94,0x94,0x93,0x60,0x00,//g 71,
0x10,0xF0,0x00,0x80,0x80,0x80,0x00,0x00,0x20,0x3F,0x21,0x00,0x00,0x20,0x3F,0x20,//h 72,
0x00,0x80,0x98,0x98,0x00,0x00,0x00,0x00,0x00,0x20,0x20,0x3F,0x20,0x20,0x00,0x00,//i 73,
0x00,0x00,0x00,0x80,0x98,0x98,0x00,0x00,0x00,0xC0,0x80,0x80,0x80,0x7F,0x00,0x00,//j 74,
0x10,0xF0,0x00,0x00,0x80,0x80,0x80,0x00,0x20,0x3F,0x24,0x06,0x29,0x30,0x20,0x00,//k 75,
0x00,0x10,0x10,0xF8,0x00,0x00,0x00,0x00,0x00,0x20,0x20,0x3F,0x20,0x20,0x00,0x00,//l 76,
0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x00,0x20,0x3F,0x20,0x00,0x3F,0x20,0x00,0x3F,//m 77,
0x80,0x80,0x00,0x80,0x80,0x80,0x00,0x00,0x20,0x3F,0x21,0x00,0x00,0x20,0x3F,0x20,//n 78,
0x00,0x00,0x80,0x80,0x80,0x80,0x00,0x00,0x00,0x1F,0x20,0x20,0x20,0x20,0x1F,0x00,//o 79,
0x80,0x80,0x00,0x80,0x80,0x00,0x00,0x00,0x80,0xFF,0x91,0x20,0x20,0x11,0x0E,0x00,//p 80,
0x00,0x00,0x00,0x80,0x80,0x00,0x80,0x00,0x00,0x0E,0x11,0x20,0x20,0x91,0xFF,0x80,//q 81,
0x80,0x80,0x80,0x00,0x80,0x80,0x80,0x00,0x20,0x20,0x3F,0x21,0x20,0x00,0x01,0x00,//r 82,
0x00,0x00,0x80,0x80,0x80,0x80,0x80,0x00,0x00,0x33,0x24,0x24,0x24,0x24,0x19,0x00,//s 83,
0x00,0x80,0x80,0xE0,0x80,0x80,0x00,0x00,0x00,0x00,0x00,0x1F,0x20,0x20,0x10,0x00,//t 84,
0x80,0x80,0x00,0x00,0x00,0x80,0x80,0x00,0x00,0x1F,0x20,0x20,0x20,0x10,0x3F,0x20,//u 85,
0x80,0x80,0x80,0x00,0x80,0x80,0x80,0x00,0x00,0x03,0x0C,0x30,0x0C,0x03,0x00,0x00,//v 86,
0x80,0x80,0x00,0x80,0x80,0x00,0x80,0x80,0x01,0x0E,0x30,0x0C,0x07,0x38,0x06,0x01,//w 87,
0x00,0x80,0x80,0x80,0x00,0x80,0x80,0x00,0x00,0x20,0x31,0x0E,0x2E,0x31,0x20,0x00,//x 88,
0x80,0x80,0x80,0x00,0x00,0x80,0x80,0x80,0x00,0x81,0x86,0x78,0x18,0x06,0x01,0x00,//y 89,
0x00,0x80,0x80,0x80,0x80,0x80,0x80,0x00,0x00,0x21,0x30,0x2C,0x22,0x21,0x30,0x00,//z 90,
0x00,0x00,0x00,0x00,0x00,0xFC,0x02,0x02,0x00,0x00,0x00,0x00,0x01,0x3E,0x40,0x40,//{ 91,
0x00,0x00,0x00,0x00,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0x00,0x00,0x00,//| 92,
0x02,0x02,0xFC,0x00,0x00,0x00,0x00,0x00,0x40,0x40,0x3E,0x01,0x00,0x00,0x00,0x00,//} 93,
0x00,0x02,0x01,0x02,0x02,0x04,0x02,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,//~ 94,
};

const unsigned char hz16[12][16] = 
{
{0x40,0x40,0x42,0xCC,0x00,0x08,0x28,0x48,0x89,0x0E,0xC8,0x38,0x08,0x08,0x00,0x00},
{0x00,0x40,0x20,0x1F,0x20,0x50,0x48,0x44,0x42,0x41,0x42,0x44,0x58,0x40,0x40,0x00},//这 0,
/* (16 X 16 , 宋体 )*/
{0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x00},
{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},//一 1,
/* (16 X 16 , 宋体 )*/
{0x40,0x40,0x40,0xFF,0x20,0x20,0x20,0x04,0x04,0xFC,0x04,0x04,0x04,0xFC,0x00,0x00},
{0x00,0x00,0x00,0x1F,0x08,0x84,0x42,0x20,0x18,0x07,0x40,0x80,0x40,0x3F,0x00,0x00},//切 2,
/* (16 X 16 , 宋体 )*/
{0x00,0x00,0x00,0x7E,0x42,0x42,0x42,0xC2,0x42,0x42,0x42,0x7E,0x00,0x00,0x00,0x00},
{0x80,0x40,0x30,0x0E,0x10,0x20,0x40,0x7F,0x44,0x44,0x44,0x44,0x44,0x40,0x40,0x00},//足 3,
/* (16 X 16 , 宋体 )*/
{0x10,0xCC,0x4B,0x48,0xC8,0x08,0xF8,0x00,0x90,0x8C,0x57,0xA4,0x14,0x0C,0x00,0x00},
{0x00,0x0F,0x04,0x44,0x8F,0x40,0x3F,0x00,0x88,0x84,0x46,0x29,0x11,0x0D,0x03,0x00},//够 4,
/* (16 X 16 , 宋体 )*/
{0x00,0x02,0x02,0x02,0x02,0x02,0x02,0xE2,0x22,0x12,0x0A,0x06,0x02,0x00,0x00,0x00},
{0x00,0x00,0x00,0x00,0x00,0x40,0x80,0x7F,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},//了 5,
/* (16 X 16 , 宋体 )*/
};

