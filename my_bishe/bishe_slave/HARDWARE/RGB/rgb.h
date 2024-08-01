#ifndef __RGB_H
#define __RGB_H

void WS_0(void);
void WS_1(void);

void WS2812_Init(void);
void WS_SetRGB(uint8_t W_i,uint8_t W_r,uint8_t W_g,uint8_t W_b);
void Send_RGBData(void);
void Reset_RGBData(void);
void LED_OFF(void);

void LED_Mode1(uint16_t time);
void LED_Mode2(uint16_t time);
void LED_Mode3(uint16_t time);
void LED_Mode4(uint16_t time);


void LED_Switch(uint8_t Colour,uint8_t Switch);

#endif
