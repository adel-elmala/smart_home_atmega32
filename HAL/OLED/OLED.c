/**
 * @file OLED_Prog.c
 * @author Mohamed Elhusseiny
 * @brief  OLED Implementation file
 * @version 0.1
 * @date 2023-03-12
 *
 * @copyright Copyright (c) 2023
 *
 */
#include "../../LIB/Datatypes.h"
// #include "../../LIB/Calcbit.h"
#include "../../MCAL/I2C/I2C_Interface.h"
#include "../../MCAL/EEPROM_Internal/EEPROM_Interface.h"
#include "./OLED_Interface.h"
#include "../LCD/LCD_Interface.h"
#include "../../font.h"

void OLED_SendCmd(uint8 Cmd)
{
    // 0b10000000 -> 0x80
    I2C_Write(0x80, Cmd); /*  0x80 for command  Why ? After Sending Slave Address frame
                              there is a frame have : Co,D/C,0,0,0,0,0,0 [Byte]
                                  1- Co Bit :
                                      if it 0 the following info will contain data byte only ,
                                      if 1 the follwoing info will contain Comand.
                                  2- D/C Bit :
                                      if it 0 the data byte will be as comand
                                      if it 1 the following data byte as data & store it in GDDRAM.
                          */
}

void OLED_SendChar(uint8 Data)
{
    // 0b01000000 -> 0x40
    I2C_Write(0x40, Data);
}

void OLED_vInit(void)
{
    I2C_vInit();
    OLED_SendCmd(SSD1306_DISPLAYOFF);         // 0xAE
    OLED_SendCmd(SSD1306_SETDISPLAYCLOCKDIV); // 0xD5
    OLED_SendCmd(0x80);                       // the suggested ratio 0x80
    OLED_SendCmd(SSD1306_SETMULTIPLEX);       // 0xA8
    OLED_SendCmd(0x3F);
    OLED_SendCmd(SSD1306_SETDISPLAYOFFSET); // 0xD3
    OLED_SendCmd(0x0);                      // no offset
    OLED_SendCmd(SSD1306_SETSTARTLINE);     // | 0x0);           // line #0
    OLED_SendCmd(SSD1306_CHARGEPUMP);       // 0x8D
    OLED_SendCmd(0x14);                     // using internal VCC
    OLED_SendCmd(SSD1306_MEMORYMODE);       // 0x20
    OLED_SendCmd(0x00);                     // 0x00 horizontal addressing
    OLED_SendCmd(SSD1306_SEGREMAP | 0x1);   // rotate screen 180
    OLED_SendCmd(SSD1306_COMSCANDEC);       // rotate screen 180
    OLED_SendCmd(SSD1306_SETCOMPINS);       // 0xDA
    OLED_SendCmd(0x12);
    OLED_SendCmd(SSD1306_SETCONTRAST); // 0x81
    OLED_SendCmd(0xCF);
    OLED_SendCmd(SSD1306_SETPRECHARGE); // 0xd9
    OLED_SendCmd(0xF1);
    OLED_SendCmd(SSD1306_SETVCOMDETECT); // 0xDB
    OLED_SendCmd(0x40);
    OLED_SendCmd(SSD1306_DISPLAYALLON_RESUME); // 0xA4
    OLED_SendCmd(SSD1306_NORMALDISPLAY);       // 0xA6
    OLED_SendCmd(SSD1306_DISPLAYON);           // switch on OLED
}

// Not used?
void OLED_DisplayOn(void)
{
    OLED_SendCmd(SSD1306_DISPLAYON);
}

void OLED_DisplayOff(void)
{
    OLED_SendCmd(SSD1306_DISPLAYOFF);
}

void OLED_Set_xy(uint8 Row, uint8 Col)
{
    OLED_SendCmd(0xb0 + Row);                     // set page address
    OLED_SendCmd(0x00 + (8 * Col & 0x0f));        // set low col address  //lower nibble
    OLED_SendCmd(0x10 + ((8 * Col >> 4) & 0x0f)); // set high col address //higher nibble
}

void OLED_sendStr_xy(uint8 *String, int Row, int Col)
{
    uint8 Data = 0;
    OLED_Set_xy(Row, Col);
    uint16 BaseAddress;
    while (*String != '\0')
    {
        BaseAddress = (*String - 0x20) * 8;
        for (uint8 i = 0; i < 8; i++)
        {
            EEPROM_enuRead(BaseAddress + i, &Data);
            OLED_SendChar(Data);
        }
        String++;
    }
}

// emoji
// for(int i=0;i<sizeof(image_data_test);i++)     // show 128* 64 Logo
// SendChar(pgm_read_byte(image_data_test+i));

void OLED_sendEmoji_xy(uint8 *String, uint16 Length, int Row, int Col)
{
    OLED_Set_xy(Row, Col);
    for (uint16 i = 0; i < Length; i++)
    {
        OLED_SendChar(String[i]);
    }
}

void OLED_ClearDisplay(void)
{
    uint8 i, k;
    for (k = 0; k < 8; k++)
    {
        OLED_Set_xy(k, 0);
        {
            for (i = 0; i < 128; i++) // clear all COL
            {
                OLED_SendChar(0); // clear all COL
            }
        }
    }
}

void OLED_ResetDisplay(void)
{
    OLED_DisplayOff();
    OLED_ClearDisplay();
    OLED_DisplayOn();
}

void OLED_StoreFont(void)
{
    uint16 EEPromAddressCountner = 0;
    for (uint8 i = 0; i < sizeof(myFont1) / 8; i++)
    {
        for (uint8 j = 0; j < 8; j++)
        {
            // LCD_4_bitSendChar(myFont1[i][j]);
            lcd_sendData(myFont1[i][j]);
            EEPROM_enuWrite(EEPromAddressCountner, myFont1[i][j]);
            EEPromAddressCountner++;
        }
    }
}