/*
 *file name: ultarsonic.c
 *description: source file for ULTRASONIC driver
 *Created on: Oct 16, 2022
 * Author: menna abdalla
 */
#include "gpio.h"
#include "icu.h"
#include "ultrasonic.h"
#include <avr/io.h>
#include <util/delay.h>
/*******************************************************************************
 *                            global variables
 ******************************************************************************/
uint8 g_edgeCount=0;
uint8 g_highTime=0;
uint16 g_distance=0;
/*******************************************************************************
 *                            functions definition
 ******************************************************************************/
/*
 * description: function to initialize the ULTRASONIC with initializing ICU driver
 * setup the ICU call back function
 * setup the direction for the trigger pin as output
 */
void ULTRASONIC_init(void)
{
	ICU_ConfigType config={F_CPU_CLOCK_8,RAISING};
	ICU_init(&config);
	SREG|=(1<<7);
	ICU_setCallBack(ULTRASONIC_edgeProcessing);
	GPIO_setupPinDirection(PORTB_ID,PIN5_ID,PIN_OUTPUT);
}

/*
 * description: function to send the trigger pulse to the ULTRASONIC
 */
void ULTRASONIC_trigger(void)
{
	GPIO_writePin(PORTB_ID,PIN5_ID,LOGIC_HIGH);
	_delay_ms(1); /* delay for 10us*/
	GPIO_writePin(PORTB_ID,PIN5_ID,LOGIC_LOW);
}
/*
 * description:send the trigger pulse and start the measurements
 */

uint16 ULTRASONIC_readDistance(void)
{
	ULTRASONIC_trigger();
	g_distance= (0.017 * g_highTime);
	return g_distance;
}
/*
 * description: this the call back function called by the ICU driver used to
 * calculate the high time
 */
void ULTRASONIC_edgeProcessing(void)
{
	g_edgeCount++;
	if (g_edgeCount==1)
	{
		ICU_clearTimer();
		ICU_setEdgeDetectionType(FALLING);
	}
	else if(g_edgeCount==2)
	{
		g_highTime=ICU_getInputCaptureValue();
		ICU_clearTimer();
		ICU_setEdgeDetectionType(RAISING);
		g_edgeCount=0;
	}

}
