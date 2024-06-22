/*
 *   File name: lcd.h
 *
 *   Author: menna abdalla
 *
 *  Created on: Oct 7, 2022
 *
 *    Description: header file for LCD driver
 */

#ifndef LCD_H_
#define LCD_H_
#include "std_types.h"
/*******************************************************************************
 *                        DEFINITIONS
 ******************************************************************************/

/* lcd data bits mode configurations it should be 8 or 4 */
#define LCD_DATA_BITS_MODE 8
#if((LCD_DATA_BITS_MODE !=4) && (LCD_DATA_BITS_MODE != 8))
#error
#endif
/*LCD HW definitIons */
#define LCD_RS_PORT_ID    PORTB_ID
#define LCD_RS_PIN_ID     PIN0_ID

#define LCD_E_PORT_ID     PORTB_ID
#define LCD_E_PIN_ID      PIN2_ID

#define LCD_DATA_PORT_ID  PORTA_ID
/* LCD pins in 4 bits mode */
#if ( LCD_DATA_BITS_MODE==4)
#define LCD_DB4_PIN_ID     PIN3_ID
#define LCD_DB5_PIN_ID     PIN4_ID
#define LCD_DB6_PIN_ID     PIN5_ID
#define LCD_DB7_PIN_ID     PIN6_ID
#endif

/* LCD commands*/
#define LCD_CLEAR_COMMAND                    0x01
#define LCD_GO_TO_HOME                       0x02
#define LCD_TWO_LINES_EIGHT_BITS_MODE        0x38
#define LCD_TWO_LINES_FOUR_BITS_MODE         0x28
#define LCD_TWO_LINES_FOUR_BITS_MODE_INIT1   0x33
#define LCD_TWO_LINES_FOUR_BITS_MODE_INIT2   0x32
#define LCD_CURSOR_OFF                       0x0C
#define LCD_CURSOR_ON                        0x0E
#define LCD_SET_CURSOR_LOCATION              0x80

/*******************************************************************************
 *                    FUNCTIONS PROTO TYPES
 ******************************************************************************/
/*
 * description:
 * initialize the LCD
 * 1-setup the LCD pins directions by using the GPIO driver
 * 2-setup the mode of the LCD 8bits or 4bits
 */
void LCD_init(void);

/*
 * description:
 * send the required command to the LCD
 */

void LCD_sendCommand(uint8 command);

/*
 * description
 * display characters on the LCD
 */

void LCD_displayCharacter(uint8 data);

/*
 * description
 * display the string n the LCD
 */

void LCD_displayString(const char *str);

/*
 * description
 * move the cursor to a specific row and column
 */

void LCD_moveCursor(uint8 row,uint8 col);

/*
 * description
 * display the required string in a specific row and column
 */

void LCD_displayStringRowColumn(uint8 row,uint8 col,const char*str);

/*
 * description
 * display the decimal value on the LCD
 */
void LCD_intgerToString(int data);

/*
 * description
 * clear the LCDscreen
 */

void LCD_clearScreen(void);

#endif /* LCD_H_ */
