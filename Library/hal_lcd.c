
#include "main.h"
#include "hal_lcd.h"
#include <string.h>
/***********************************************************************
 * Local Variables
************************************************************************/
LCD_Config_t *_config;
LCD_Data_t _lcd;
LCD_DotSize_t dotSize = DOTS_5x8;

/***********************************************************************
 * Local Functions
************************************************************************/
void HAL_LCD_Send(uint8_t, uint8_t);
void HAL_LCD_Write4bits(uint8_t);
void HAL_LCD_Write8bits(uint8_t);
void HAL_LCD_PulseEnable();
void HAL_LCD_InitPins(void);

/**
 * Configures and Initializes the pins defined in the LCD
 * Definition structure LCD_Config_t* _config
*/
void HAL_LCD_InitPins(void)
{
    GPIO_InitTypeDef InitStruct = {0};
    if (_config->DisplayFunction == FUNCTION_8BIT)
    {
        /*Configure GPIO pin Output Level */
        HAL_GPIO_WritePin(_config->D0_Port, _config->D0_Pin, GPIO_PIN_RESET);
        /*Configure GPIO pin : D0_Pin */
        InitStruct.Pin = _config->D0_Pin;
        InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
        InitStruct.Pull = GPIO_NOPULL;
        InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
        HAL_GPIO_Init(_config->D0_Port, &InitStruct);

        HAL_GPIO_WritePin(_config->D1_Port, _config->D1_Pin, GPIO_PIN_RESET);
        /*Configure GPIO pin : D1_Pin */
        InitStruct.Pin = _config->D1_Pin;
        HAL_GPIO_Init(_config->D1_Port, &InitStruct);

        HAL_GPIO_WritePin(_config->D2_Port, _config->D2_Pin, GPIO_PIN_RESET);
        /*Configure GPIO pin : D2_Pin */
        InitStruct.Pin = _config->D2_Pin;
        HAL_GPIO_Init(_config->D2_Port, &InitStruct);

        HAL_GPIO_WritePin(_config->D3_Port, _config->D3_Pin, GPIO_PIN_RESET);
        /*Configure GPIO pin : D3_Pin */
        InitStruct.Pin = _config->D3_Pin;
        HAL_GPIO_Init(_config->D3_Port, &InitStruct);
    }
    /*Configure GPIO pin Output Level */
    HAL_GPIO_WritePin(_config->D4_Port, _config->D4_Pin, GPIO_PIN_RESET);
    /*Configure GPIO pin : D4_Pin */
    InitStruct.Pin = _config->D4_Pin;
    InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    InitStruct.Pull = GPIO_NOPULL;
    InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(_config->D4_Port, &InitStruct);

    HAL_GPIO_WritePin(_config->D5_Port, _config->D5_Pin, GPIO_PIN_RESET);
    /*Configure GPIO pin : D5_Pin */
    InitStruct.Pin = _config->D5_Pin;
    HAL_GPIO_Init(_config->D5_Port, &InitStruct);

    HAL_GPIO_WritePin(_config->D6_Port, _config->D6_Pin, GPIO_PIN_RESET);
    /*Configure GPIO pin : D6_Pin */
    InitStruct.Pin = _config->D6_Pin;
    HAL_GPIO_Init(_config->D6_Port, &InitStruct);

    HAL_GPIO_WritePin(_config->D7_Port, _config->D7_Pin, GPIO_PIN_RESET);
    /*Configure GPIO pin : D7_Pin */
    InitStruct.Pin = _config->D7_Pin;
    HAL_GPIO_Init(_config->D7_Port, &InitStruct);

    HAL_GPIO_WritePin(_config->RS_Port, _config->RS_Pin, GPIO_PIN_RESET);
    /*Configure GPIO pin : RS_Pin */
    InitStruct.Pin = _config->RS_Pin;
    HAL_GPIO_Init(_config->RS_Port, &InitStruct);

    HAL_GPIO_WritePin(_config->EN_Port, _config->EN_Pin, GPIO_PIN_RESET);
    /*Configure GPIO pin : EN_Pin */
    InitStruct.Pin = _config->EN_Pin;
    HAL_GPIO_Init(_config->EN_Port, &InitStruct);
}
/**
 * Write either command or data, with automatic 4/8-bit selection
 * @param value The value to write
 * @param mode Command(0) or Data(1) 
*/
void HAL_LCD_Send(uint8_t value, uint8_t mode)
{
    HAL_GPIO_WritePin(_config->RS_Port, _config->RS_Pin, mode);

    if (_config->DisplayFunction == FUNCTION_8BIT)
    {
        HAL_LCD_Write8bits(value);
    }
    else
    {
        HAL_LCD_Write4bits(value >> 4);
        HAL_LCD_Write4bits(value);
    }
}
/**
 * Writes a value to the LCD in 4 bit mode
 * @param value The value to write
*/
void HAL_LCD_Write4bits(uint8_t value)
{
    HAL_GPIO_WritePin(_config->D4_Port, _config->D4_Pin, value & 0x01);
    HAL_GPIO_WritePin(_config->D5_Port, _config->D5_Pin, (value >> 1) & 0x01);
    HAL_GPIO_WritePin(_config->D6_Port, _config->D6_Pin, (value >> 2) & 0x01);
    HAL_GPIO_WritePin(_config->D7_Port, _config->D7_Pin, (value >> 3) & 0x01);

    HAL_LCD_PulseEnable();
}
/**
 * Writes a value to the LCD in 8 bit mode
 * @param value The value to write
*/
void HAL_LCD_Write8bits(uint8_t value)
{
    HAL_GPIO_WritePin(_config->D0_Port, _config->D0_Pin, value & 0x01);
    HAL_GPIO_WritePin(_config->D1_Port, _config->D1_Pin, (value >> 1) & 0x01);
    HAL_GPIO_WritePin(_config->D2_Port, _config->D2_Pin, (value >> 2) & 0x01);
    HAL_GPIO_WritePin(_config->D3_Port, _config->D3_Pin, (value >> 3) & 0x01);
    HAL_GPIO_WritePin(_config->D4_Port, _config->D4_Pin, (value >> 4) & 0x01);
    HAL_GPIO_WritePin(_config->D5_Port, _config->D5_Pin, (value >> 5) & 0x01);
    HAL_GPIO_WritePin(_config->D6_Port, _config->D6_Pin, (value >> 6) & 0x01);
    HAL_GPIO_WritePin(_config->D7_Port, _config->D7_Pin, (value >> 7) & 0x01);

    HAL_LCD_PulseEnable();
}
/**
 * Generates an Enable Pulse to validate the data
*/
void HAL_LCD_PulseEnable()
{
    HAL_GPIO_WritePin(_config->EN_Port, _config->EN_Pin, GPIO_PIN_RESET);
    HAL_Delay(1); //originally 1us
    HAL_GPIO_WritePin(_config->EN_Port, _config->EN_Pin, GPIO_PIN_SET);
    HAL_Delay(1); //originally 1us
    HAL_GPIO_WritePin(_config->EN_Port, _config->EN_Pin, GPIO_PIN_RESET);
    HAL_Delay(1); //originally 100us
}
/***********************************************************************
 * Public Functions
************************************************************************/
/**
 * Initializes the LCD Using the configuration information provided.
 * Function also initializes the GPIO specified in case its not initialized
 * @param config The LCD_Config_t settings to use
*/
void HAL_LCD_Init(LCD_Config_t *config)
{
    _config = config;
    if (config->RowNumber > 1)
    {
        _lcd.DisplayFunction |= LCD_2LINE;
    }

    HAL_LCD_SetRowOffsets(0x00, 0x40, 0x00 + config->ColumnNumber, 0x40 + config->ColumnNumber);

    // for some 1 line displays you can select a 10 pixel high font
    if ((dotSize != LCD_5x8DOTS) && (config->RowNumber == 1))
    {
        _lcd.DisplayFunction |= LCD_5x10DOTS;
    }

    HAL_LCD_InitPins();
    HAL_Delay(40); //wait 40ms for LCD to start up
    // Now we pull both RS and R/W low to begin commands
    HAL_GPIO_WritePin(config->RS_Port, config->RS_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(config->EN_Port, config->EN_Pin, GPIO_PIN_RESET);

    if (config->DisplayFunction == FUNCTION_4BIT)
    {
        // we start in 8bit mode, try to set 4 bit mode
        HAL_LCD_Write4bits(0x03);
        HAL_Delay(5);

        // second try
        HAL_LCD_Write4bits(0x03);
        HAL_Delay(5);

        // third go!
        HAL_LCD_Write4bits(0x03);
        HAL_Delay(150);

        // finally, set to 4-bit interface
        HAL_LCD_Write4bits(0x02);
    }
    else
    {
        // Send function set HAL_LCD_Command sequence
        HAL_LCD_Command(LCD_FUNCTIONSET | _lcd.DisplayFunction);
        HAL_Delay(5); // wait more than 4.1ms

        // second try
        HAL_LCD_Command(LCD_FUNCTIONSET | _lcd.DisplayFunction);
        HAL_Delay(1);

        // third go
        HAL_LCD_Command(LCD_FUNCTIONSET | _lcd.DisplayFunction);
    }

    // finally, set # lines, font size, etc.
    HAL_LCD_Command(LCD_FUNCTIONSET | _lcd.DisplayFunction);

    // turn the display on with no cursor or blinking default
    _lcd.DisplayControl = LCD_DISPLAYON | LCD_CURSOROFF | LCD_BLINKOFF;
    HAL_LCD_On();

    // clear it off
    HAL_LCD_Clear();

    // Initialize to default text direction (for romance languages)
    _lcd.DisplayMode = LCD_ENTRYLEFT | LCD_ENTRYSHIFTDECREMENT;
    // set the entry mode
    HAL_LCD_Command(LCD_ENTRYMODESET | _lcd.DisplayMode);
}
/**
 * Writes a command to the LCD
 * @param value the command to write
*/
void HAL_LCD_Command(uint8_t value)
{
    HAL_LCD_Send(value, GPIO_PIN_RESET);
}
/**
 * Writes a data value to the LCD
 * @param value the data to write
*/
void HAL_LCD_Write(uint8_t value)
{
    HAL_LCD_Send(value, GPIO_PIN_SET);
}
/**
 * Configures the Dot size for the LCD.
 * LCD_Init needs to called after this functions to take effect.
 * @param size The LCD_DotSize_t to configure
*/
void HAL_LCD_SetDotSize(LCD_DotSize_t size)
{
    dotSize = size;
}
/**
 * Clears the display
*/
void HAL_LCD_Clear()
{
    HAL_LCD_Command(LCD_CLEARDISPLAY); // clear display, set cursor position to zero
    HAL_Delay(2);                      // this HAL_LCD_Command takes a long time!
}
/**
 * Clears the display and sets the cursor home
*/
void HAL_LCD_Home()
{
    HAL_LCD_Command(LCD_RETURNHOME); // set cursor position to zero
    HAL_Delay(2);                    // this HAL_LCD_Command takes a long time!
}
/**
 * Turns off the LCD
*/
void HAL_LCD_Off()
{
    _lcd.DisplayControl &= ~LCD_DISPLAYON;
    HAL_LCD_Command(LCD_DISPLAYCONTROL | _lcd.DisplayControl);
}
/**
 * Turns on the LCD
*/
void HAL_LCD_On()
{
    _lcd.DisplayControl |= LCD_DISPLAYON;
    HAL_LCD_Command(LCD_DISPLAYCONTROL | _lcd.DisplayControl);
}
/**
 * Disables blinking
*/
void HAL_LCD_BlinkOff()
{
    _lcd.DisplayControl &= ~LCD_BLINKON;
    HAL_LCD_Command(LCD_DISPLAYCONTROL | _lcd.DisplayControl);
}
/**
 * Enables blinking
*/
void HAL_LCD_BlinkOn()
{
    _lcd.DisplayControl |= LCD_BLINKON;
    HAL_LCD_Command(LCD_DISPLAYCONTROL | _lcd.DisplayControl);
}
/**
 * Disables the cursor
*/
void HAL_LCD_CursorOff()
{
    _lcd.DisplayControl &= ~LCD_CURSORON;
    HAL_LCD_Command(LCD_DISPLAYCONTROL | _lcd.DisplayControl);
}
/**
 * Enables the cursor
*/
void HAL_LCD_CursorOn()
{
    _lcd.DisplayControl |= LCD_CURSORON;
    HAL_LCD_Command(LCD_DISPLAYCONTROL | _lcd.DisplayControl);
}
/**
 * Scrolls the display without changing the RAM
*/
void HAL_LCD_ScrollDisplayLeft()
{
    HAL_LCD_Command(LCD_CURSORSHIFT | LCD_DISPLAYMOVE | LCD_MOVELEFT);
}
/**
 * Scrolls the display without changing the RAM
*/
void HAL_LCD_ScrollDisplayRight()
{
    HAL_LCD_Command(LCD_CURSORSHIFT | LCD_DISPLAYMOVE | LCD_MOVERIGHT);
}
/**
 * Scrolls the display without changing the RAM
*/
void HAL_LCD_LeftToRight()
{
    _lcd.DisplayMode |= LCD_ENTRYLEFT;
    HAL_LCD_Command(LCD_ENTRYMODESET | _lcd.DisplayMode);
}
/**
 * Scrolls the display without changing the RAM
*/
void HAL_LCD_RightToLeft()
{
    _lcd.DisplayMode &= ~LCD_ENTRYLEFT;
    HAL_LCD_Command(LCD_ENTRYMODESET | _lcd.DisplayMode);
}
/**
 * This will 'right justify' text from the cursor
*/
void HAL_LCD_AutoscrollOn()
{
    _lcd.DisplayMode |= LCD_ENTRYSHIFTINCREMENT;
    HAL_LCD_Command(LCD_ENTRYMODESET | _lcd.DisplayMode);
}
/**
 * This will 'left justify' text from the cursor
*/
void HAL_LCD_AutoscrollOff()
{
    _lcd.DisplayMode &= ~LCD_ENTRYSHIFTINCREMENT;
    HAL_LCD_Command(LCD_ENTRYMODESET | _lcd.DisplayMode);
}
/**
 * Sets the RAM offsets for the Rows
 * @param row1 RAM address offset for row1
 * @param row2 RAM address offset for row2
 * @param row3 RAM address offset for row3
 * @param row4 RAM address offset for row4
*/
void HAL_LCD_SetRowOffsets(int row1, int row2, int row3, int row4)
{
    _lcd.RowOffsets[0] = row1;
    _lcd.RowOffsets[1] = row2;
    _lcd.RowOffsets[2] = row3;
    _lcd.RowOffsets[3] = row4;
}
/**
 * Sets the cursor position
 * @param col the LCD Column Number
 * @param row the LCD Row Number
*/
void HAL_LCD_SetCursor(uint8_t col, uint8_t row)
{
    const size_t max_lines = sizeof(_lcd.RowOffsets) / sizeof(*_lcd.RowOffsets);
    if (row >= max_lines)
    {
        row = max_lines - 1; // we count rows starting w/0
    }
    if (row >= _config->RowNumber)
    {
        row = _config->RowNumber - 1; // we count rows starting w/0
    }

    HAL_LCD_Command(LCD_SETDDRAMADDR | (col + _lcd.RowOffsets[row]));
}
/**
 * Prints text to the LCD from a array variable in RAM
 * @param txt the text to print
*/
void HAL_LCD_Print(char *txt)
{
    for (uint8_t i = 0; i < strlen(txt); i++)
    {
        HAL_LCD_Write(txt[i]);
    }
}
