/******************************************************************************
 *      file name :lcd.c
 *      description: source file for the LCD driver
 *      Created on: Oct 7, 2022
 *      Author: menna abdalla
 *******************************************************************************/
#include "lcd.h"
#include "common_macros.h"
#include "gpio.h"
#include <util/delay.h>
/*******************************************************************************
 *                      FUNCTIONS DEFINITIONS
 *******************************************************************************/
/*
 * description:
 * initialize the LCD
 * 1-setup the LCD pins directions by using the GPIO driver
 * 2-setup the mode of the LCD 8bits or 4bits
 */
void LCD_init(void)
{
	/* configure the pin direction for the E and RS as output pins */
	GPIO_setupPinDirection(LCD_RS_PORT_ID,LCD_RS_PIN_ID,PIN_OUTPUT);
	GPIO_setupPinDirection(LCD_E_PORT_ID,LCD_E_PIN_ID,PIN_OUTPUT);

	_delay_ms(20);   /*LCD POWER on delay always >15 ms */

#if (LCD_DATA_BITS_MODE==4)
	/* configure the 4 pins in the  data port as output pins */
	GPIO_setupPinDirection(LCD_DATA_PORT_ID,LCD_DB4_PIN_ID,PIN_OUTPUT);
	GPIO_setupPinDirection(LCD_DATA_PORT_ID,LCD_DB5_PIN_ID,PIN_OUTPUT);
	GPIO_setupPinDirection(LCD_DATA_PORT_ID,LCD_DB6_PIN_ID,PIN_OUTPUT);
	GPIO_setupPinDirection(LCD_DATA_PORT_ID,LCD_DB7_PIN_ID,PIN_OUTPUT);

	/* send commands for 4 bit initialization of LCD */
	LCD_sendCommand(LCD_TWO_LINES_FOUR_BITS_MODE_INIT1);
	LCD_sendCommand(LCD_TWO_LINES_FOUR_BITS_MODE_INIT2);

	/* use two lines LCD + 4bits mode */
	LCD_sendCommand(LCD_TWO_LINES_FOUR_BITS_MODE);

#elif (LCD_DATA_BITS_MODE==8)
	/* configure the data port as a output */
	GPIO_setupPortDirection(LCD_DATA_PORT_ID,PORT_OUTPUT);

	/* send command for two lines and 8 bit mode*/
	LCD_sendCommand(LCD_TWO_LINES_EIGHT_BITS_MODE);
#endif
	LCD_sendCommand(LCD_CURSOR_OFF); /* set the cursor off */
	LCD_sendCommand(LCD_CLEAR_COMMAND); /* clear the LCD screen*/
}
/*
 * description:
 * send the required command to the LCD
 */
void LCD_sendCommand(uint8 command)
{
	/* set RS=0 */
	GPIO_writePin(LCD_RS_PORT_ID,LCD_RS_PIN_ID,LOGIC_LOW);
	_delay_ms(1); /* Tas=50ns */
	/* set E=1 */
	GPIO_writePin(LCD_E_PORT_ID,LCD_E_PIN_ID,LOGIC_HIGH);
	_delay_ms(1); /* Tpw-Tdsw=290-100=190ns */

#if (LCD_DATA_BITS_MODE==4)
	GPIO_writePin(LCD_DATA_PORT_ID,LCD_DB4_PIN_ID,GET_BIT(command,4));
	GPIO_writePin(LCD_DATA_PORT_ID,LCD_DB5_PIN_ID,GET_BIT(command,5));
	GPIO_writePin(LCD_DATA_PORT_ID,LCD_DB6_PIN_ID,GET_BIT(command,6));
	GPIO_writePin(LCD_DATA_PORT_ID,LCD_DB7_PIN_ID,GET_BIT(command,7));

	_delay_ms(1); /* Tdsw=100ns */
	GPIO_writePin(LCD_E_PORT_ID,LCD_E_PIN_ID,LOGIC_LOW); /* set E=0 after send the command */
	_delay_ms(1); /* Th=13ns */
	GPIO_writePin(LCD_E_PORT_ID,LCD_E_PIN_ID,LOGIC_HIGH); /* set E=1 to send the other 4 bits */
	_delay_ms(1);  /* Tpw-Tdsw=290-100=190ns */

	GPIO_writePin(LCD_DATA_PORT_ID,LCD_DB4_PIN_ID,GET_BIT(command,0));
	GPIO_writePin(LCD_DATA_PORT_ID,LCD_DB5_PIN_ID,GET_BIT(command,1));
	GPIO_writePin(LCD_DATA_PORT_ID,LCD_DB6_PIN_ID,GET_BIT(command,2));
	GPIO_writePin(LCD_DATA_PORT_ID,LCD_DB7_PIN_ID,GET_BIT(command,3));

	_delay_ms(1); /* Tdsw=100ns */
	GPIO_writePin(LCD_E_PORT_ID,LCD_E_PIN_ID,LOGIC_LOW); /* set E=0 after send the command */
	_delay_ms(1); /* Th=13ns */

#elif (LCD_DATA_BITS_MODE==8)
	 GPIO_writePort(LCD_DATA_PORT_ID,command);
	 _delay_ms(1); /* Tdsw= 100ns */
	 GPIO_writePin(LCD_E_PORT_ID,LCD_E_PIN_ID,LOGIC_LOW); /* set E=0*/
	 _delay_ms(1); /* Th=13ns */
#endif
}

/*
 * description
 * display characters on the LCD
 */
void LCD_displayCharacter(uint8 data)
{
	/* set RS=0 */
	GPIO_writePin(LCD_RS_PORT_ID,LCD_RS_PIN_ID,LOGIC_HIGH);
	_delay_ms(1); /* Tas=50ns */
	/* set E=1 */
	GPIO_writePin(LCD_E_PORT_ID,LCD_E_PIN_ID,LOGIC_HIGH);
	_delay_ms(1); /* Tpw-Tdsw=290-100=190ns */

#if (LCD_DATA_BITS_MODE==4)
	GPIO_writePin(LCD_DATA_PORT_ID,LCD_DB4_PIN_ID,GET_BIT(data,4));
	GPIO_writePin(LCD_DATA_PORT_ID,LCD_DB5_PIN_ID,GET_BIT(data,5));
	GPIO_writePin(LCD_DATA_PORT_ID,LCD_DB6_PIN_ID,GET_BIT(data,6));
	GPIO_writePin(LCD_DATA_PORT_ID,LCD_DB7_PIN_ID,GET_BIT(data,7));

	_delay_ms(1); /* Tdsw=100ns */
	GPIO_writePin(LCD_E_PORT_ID,LCD_E_PIN_ID,LOGIC_LOW); /* set E=0 after send the data */
	_delay_ms(1); /* Th=13ns */
	GPIO_writePin(LCD_E_PORT_ID,LCD_E_PIN_ID,LOGIC_HIGH); /* set E=1 to send the other 4 bits */
	_delay_ms(1);  /* Tpw-Tdsw=290-100=190ns */

	GPIO_writePin(LCD_DATA_PORT_ID,LCD_DB4_PIN_ID,GET_BIT(data,0));
	GPIO_writePin(LCD_DATA_PORT_ID,LCD_DB5_PIN_ID,GET_BIT(data,1));
	GPIO_writePin(LCD_DATA_PORT_ID,LCD_DB6_PIN_ID,GET_BIT(data,2));
	GPIO_writePin(LCD_DATA_PORT_ID,LCD_DB7_PIN_ID,GET_BIT(data,3));

	_delay_ms(1); /* Tdsw=100ns */
	GPIO_writePin(LCD_E_PORT_ID,LCD_E_PIN_ID,LOGIC_LOW); /* set E=0 after send the command */
	_delay_ms(1); /* Th=13ns */

#elif (LCD_DATA_BITS_MODE==8)
	 GPIO_writePort(LCD_DATA_PORT_ID,data);
	 _delay_ms(1); /* Tdsw= 100ns */
	 GPIO_writePin(LCD_E_PORT_ID,LCD_E_PIN_ID,LOGIC_LOW); /* set E=0*/
	 _delay_ms(1); /* Th=13ns */
#endif
}
/*
 * description
 * display the string n the LCD
 */

void LCD_displayString(const char *str)
{
	uint8 i=0;
	while (str[i] != '\0')
	{
		LCD_displayCharacter(str[i]);
		i++;
	}
}
/*
 * description
 * move the cursor to a specific row and column
 */
void LCD_moveCursor(uint8 row, uint8 col)
{
	uint8 lcd_memory_address;
	switch (row)
	{

	case 0:
		lcd_memory_address=col;
		break;
	case 1:
		lcd_memory_address=col+0x40;
		break;
	case 2:
		lcd_memory_address=col+0x10;
		break;
	case 3:
		lcd_memory_address=col+0x50;
		break;
	}
	/* move the cursor the specific address */
	LCD_sendCommand(lcd_memory_address | LCD_SET_CURSOR_LOCATION);
}
/*
 * description
 * display the required string in a specific row and column
 */
void LCD_displayStringRowColumn(uint8 row,uint8 col, const char*str)
{
	LCD_moveCursor(row,col); /* to go to the required position */
	LCD_displayString(str);  /* display string */
}
/*
 * description
 * display the decimal value on the LCD
 */
void LCD_intgerToString(int data)
{
	char buff[16]; /* string to hold the ASCII result */
	itoa(data,buff,10); /* C function to convert the data to its ASCII value with base 10 */
	LCD_displayString(buff); /* display string */
}
/*
 * description
 * clear the LCDscreen
 */
void LCD_clearScreen(void)
{
	LCD_sendCommand(LCD_CLEAR_COMMAND);
}
