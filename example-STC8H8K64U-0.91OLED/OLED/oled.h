
#ifndef __OLED_H__
#define __OLED_H__

// #include "main.h"
#include	"config.h"

#define OLED_ADDR 0x78

#define OLED_WIDTH 128
#define OLED_HEIGHT 32

void OLED_Write_cmd(u8 cmd);
void OLED_Write_data(u8 data_w);
void OLED_ShowPic(u8 x0, u8 y0, u8 x1, u8 y1, u8 BMP[]);
void OLED_ShowHanzi(u8 x, u8 y, u8 no);
void OLED_ShowHzbig(u8 x, u8 y, u8 n);
void OLED_ShowFloat(u8 x, u8 y, float num, u8 accuracy, u8 fontsize);
void OLED_ShowNum(u8 x, u8 y, u32 num, u8 length, u8 fontsize);
void OLED_ShowStr(u8 x, u8 y, char *ch, u8 fontsize);
void OLED_ShowChar(u8 x, u8 y, u8 ch, u8 fontsize);
void OLED_Allfill(void);
void OLED_Set_Position(u8 x, u8 y);
void OLED_Clear(void);
void OLED_Display_On(void);
void OLED_Display_Off(void);
void OLED_Init(void);

#endif  /*__OLED_H__*/
