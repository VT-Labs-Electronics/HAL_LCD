# HAL_LCD
HAL_LCD is an STM32 implementation of the [Arduino Liquid Crystal Library](https://github.com/arduino-libraries/LiquidCrystal). The Library is implemented using HAL HAL drivers to interface with HD44780 based LCDs.

The Library was tested on the [Nucleo-R334R8](https://www.st.com/en/evaluation-tools/nucleo-f334r8.html) Development board. Enjoy!

## Example of Usage
All of the functions in the Liquid Crystal Library are available on this library but are not implemented with the same function names. To use the library, you need to specify if you are using 4 bit or 8 bit mode plus the pins and ports you are using, for example

```
#include "hal_lcd.h"  //Include the library

/* USER CODE BEGIN PV */
LCD_Config_t myLcd;   //Create the LCD configuration variable
/* USER CODE END PV */

/* USER CODE BEGIN 2 */
myLcd.ColumnNumber = 16;
myLcd.RowNumber = 2;
myLcd.DisplayFunction = FUNCTION_4BIT;
myLcd.D4_Port = GPIOB;
myLcd.D4_Pin = GPIO_PIN_5; //PB5
myLcd.D5_Port = GPIOB;
myLcd.D5_Pin = GPIO_PIN_4; //PB4
myLcd.D6_Port = GPIOB;
myLcd.D6_Pin = GPIO_PIN_10; //PB10
myLcd.D7_Port = GPIOA;
myLcd.D7_Pin = GPIO_PIN_8; //PA8
myLcd.RS_Port = GPIOA;
myLcd.RS_Pin = GPIO_PIN_9; //PA9
myLcd.EN_Port = GPIOC;
myLcd.EN_Pin = GPIO_PIN_7; //PC7

HAL_LCD_Init(&myLcd);      //Initialize the LCD
HAL_LCD_Print("HELLO WORLD!");
HAL_LCD_SetCursor(0, 1); //second row
HAL_LCD_Print("FROM VT LABS");
/* USER CODE END 2 */
```

Note that you don't need to configure the Pins you asigned on Cube MX for example, the library will handle that for you.


