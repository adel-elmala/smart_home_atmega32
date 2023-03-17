/**
 * @file OLED_Interface.h
 * @author Mohamed Elhusseiny
 * @brief  OLED Interface File
 * @version 0.1
 * @date 2023-03-12
 *
 * @copyright Copyright (c) 2023
 *
 */
#ifndef OLED_INTERFACE_H
#define OLED_INTERFACE_H

#define SSD1306_LCDWIDTH 128
#define SSD1306_LCDHEIGHT 64

#define SSD1306_SETCONTRAST 0x81 //
#define SSD1306_DISPLAYALLON_RESUME 0xA4
#define SSD1306_DISPLAYALLON 0xA5
#define SSD1306_NORMALDISPLAY 0xA6
#define SSD1306_INVERTDISPLAY 0xA7
#define SSD1306_DISPLAYOFF 0xAE       /* Display off Power On/Off Sequence */
#define SSD1306_DISPLAYON 0xAF        /* Display on Power On/Off Sequence */
#define SSD1306_SETDISPLAYOFFSET 0xD3 /* Offset Enable  */
#define SSD1306_SETCOMPINS 0xDA
#define SSD1306_SETVCOMDETECT 0xDB
#define SSD1306_SETDISPLAYCLOCKDIV 0xD5
#define SSD1306_SETPRECHARGE 0xD9
#define SSD1306_SETMULTIPLEX 0xA8
#define SSD1306_SETLOWCOLUMN 0x00  //
#define SSD1306_SETHIGHCOLUMN 0x10 //
#define SSD1306_SETSTARTLINE 0x40  //
#define SSD1306_MEMORYMODE 0x20    //
#define SSD1306_COLUMNADDR 0x21    //
#define SSD1306_PAGEADDR 0x22      //
#define SSD1306_COMSCANINC 0xC0
#define SSD1306_COMSCANDEC 0xC8
#define SSD1306_SEGREMAP 0xA0 //
#define SSD1306_CHARGEPUMP 0x8D
#define SSD1306_EXTERNALVCC 0x1
#define SSD1306_SWITCHCAPVCC 0x2

void OLED_vInit(void);
void OLED_SendCmd(uint8 Cmd);
void OLED_SendChar(uint8 Data);

void OLED_DisplayOn(void);
void OLED_DisplayOff(void);

void OLED_Set_xy(uint8 Row, uint8 Col);
void OLED_sendStr_xy(uint8 *String, int Row, int Col);
void OLED_sendEmoji_xy(uint8 *String, uint16 Length, int Row, int Col);

void OLED_ClearDisplay(void);
void OLED_ResetDisplay(void);
void OLED_StoreFont(void);

#endif