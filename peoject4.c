/*
 *file name: peoject4.c
 *description: project4 that calculate the distance through ULTRASONIC sensor
 *description: and display it on the LCD
 *Created on: Oct 16, 2022
 *Author: menna abdalla
 */
#include "lcd.h"
#include "ultrasonic.h"
#include "common_macros.h"

int main ()
{
	uint8 distance;
	LCD_init();
	ULTRASONIC_init();
	LCD_displayString("Distance=  ");
	while (1)
	{
		distance=ULTRASONIC_readDistance();
		LCD_moveCursor(0,11);
		if (distance>100)
		{
			LCD_intgerToString(distance);
		}
		else
		{
			LCD_intgerToString(distance);
			LCD_displayCharacter(' ');
		}
	}

}


