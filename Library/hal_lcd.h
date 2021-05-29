
#ifndef HAL_LCD_H
#define HAL_LCD_H

#include "main.h"
#include <stdint.h>
#include <stdbool.h>
// commands
#define LCD_CLEARDISPLAY 0x01
#define LCD_RETURNHOME 0x02
#define LCD_ENTRYMODESET 0x04
#define LCD_DISPLAYCONTROL 0x08
#define LCD_CURSORSHIFT 0x10
#define LCD_FUNCTIONSET 0x20
#define LCD_SETCGRAMADDR 0x40
#define LCD_SETDDRAMADDR 0x80

// flags for display entry mode
#define LCD_ENTRYRIGHT 0x00
#define LCD_ENTRYLEFT 0x02
#define LCD_ENTRYSHIFTINCREMENT 0x01
#define LCD_ENTRYSHIFTDECREMENT 0x00

// flags for display on/off control
#define LCD_DISPLAYON 0x04
#define LCD_DISPLAYOFF 0x00
#define LCD_CURSORON 0x02
#define LCD_CURSOROFF 0x00
#define LCD_BLINKON 0x01
#define LCD_BLINKOFF 0x00

// flags for display/cursor shift
#define LCD_DISPLAYMOVE 0x08
#define LCD_CURSORMOVE 0x00
#define LCD_MOVERIGHT 0x04
#define LCD_MOVELEFT 0x00

// flags for function set
#define LCD_8BITMODE 0x10
#define LCD_4BITMODE 0x00
#define LCD_2LINE 0x08
#define LCD_1LINE 0x00
#define LCD_5x10DOTS 0x04
#define LCD_5x8DOTS 0x00

typedef enum
{
    FUNCTION_4BIT,
    FUNCTION_8BIT
} LCD_DisplayFunction_t;

typedef enum
{
    DOTS_5x8 = 0,
    DOT_5x10 = 0x04
} LCD_DotSize_t;

typedef struct
{
    GPIO_TypeDef *D0_Port;
    GPIO_TypeDef *D1_Port;
    GPIO_TypeDef *D2_Port;
    GPIO_TypeDef *D3_Port;
    GPIO_TypeDef *D4_Port;
    GPIO_TypeDef *D5_Port;
    GPIO_TypeDef *D6_Port;
    GPIO_TypeDef *D7_Port;
    GPIO_TypeDef *RS_Port;
    GPIO_TypeDef *EN_Port;
    uint16_t D0_Pin;
    uint16_t D1_Pin;
    uint16_t D2_Pin;
    uint16_t D3_Pin;
    uint16_t D4_Pin;
    uint16_t D5_Pin;
    uint16_t D6_Pin;
    uint16_t D7_Pin;
    uint16_t RS_Pin;
    uint16_t EN_Pin;
    uint8_t RowNumber;
    uint8_t ColumnNumber;
    LCD_DisplayFunction_t DisplayFunction;
} LCD_Config_t;

typedef struct
{
    uint8_t DisplayFunction;
    uint8_t DisplayControl;
    uint8_t DisplayMode;
    uint8_t RowOffsets[4];
} LCD_Data_t;

void HAL_LCD_Init(LCD_Config_t *config);
void HAL_LCD_SetDotSize(LCD_DotSize_t size);
void HAL_LCD_Clear();
void HAL_LCD_Home();
void HAL_LCD_Off();
void HAL_LCD_On();
void HAL_LCD_BlinkOff();
void HAL_LCD_BlinkOn();
void HAL_LCD_CursorOff();
void HAL_LCD_CursorOn();
void HAL_LCD_ScrollDisplayLeft();
void HAL_LCD_ScrollDisplayRight();
void HAL_LCD_LeftToRight();
void HAL_LCD_RightToLeft();
void HAL_LCD_AutoscrollOn();
void HAL_LCD_AutoscrollOff();
void HAL_LCD_SetRowOffsets(int row1, int row2, int row3, int row4);
void HAL_LCD_SetCursor(uint8_t, uint8_t);
void HAL_LCD_Write(uint8_t);
void HAL_LCD_Command(uint8_t);
void HAL_LCD_Print(char *txt);

#endif
