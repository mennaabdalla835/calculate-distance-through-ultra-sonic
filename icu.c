/*
 *      file name: icu.c
 *      description:source file for ICU driver
 *      Created on: Oct 7, 2022
 *      Author: menna abdalla
 */
#include "icu.h"
#include "common_macros.h"
#include  <avr/io.h>
#include  <avr/interrupt.h>
/*******************************************************************************
 *                             GLOBAL VARIABLES
 */
/* global variable to hold the adress of the call back function */
 static volatile void (*g_callBackPtr) (void)= NULL_PTR;
/*******************************************************************************
 *                              ISR FUNCTION
 ******************************************************************************/
ISR(TIMER1_CAPT_vect)
{
	if (g_callBackPtr != NULL_PTR)
	{
		(*g_callBackPtr)(); /* call the call back function after the edge is detected */
	}
}
/*******************************************************************************
  *                             FUNCTIONS DEFINITIONS
  ******************************************************************************/
void ICU_init(const ICU_ConfigType * config_ptr)
{
	/* set timer1 with normal mode */
	TCCR1A= (1<<FOC1A) |(1<<FOC1B);

	/* set the clock of timer1 */
	TCCR1B= (TCCR1B & 0xF8) | (config_ptr->clock);

	/* set the required edge */
	TCCR1B= (TCCR1B & 0xBF)  | ((config_ptr->edge)<<6);

	/* Initial value for timer1 */
	TCNT1=0;

	/* Initial value for ICR1 */
	ICR1=0;

	/* enable the input capture interrupt to detect the interrupts */
	TIMSK=(1<<TICIE1);

	/* configure PD6 as input */
	DDRD&=~(1<<6);
}
/*
 * description: function to set the call back function adress
 *
 */
void ICU_setCallBack(void (*a_ptr)(void))
{
	g_callBackPtr=a_ptr; /* put the address of the function at the global variable */
}
/*
 * description:function to set the required edge
 */
void ICU_setEdgeDetectionType (const ICU_EdgeType a_edgeType)
{
	TCCR1B=(TCCR1B & 0xBF) | (a_edgeType <<6);
}
/*
 * description:function to return the value of timer1 that stored in ICR1
 */

uint16 ICU_getInputCaptureValue (void)
{
	return ICR1;
}
/*
 * description:function to clear timer1
 */
void ICU_clearTimer(void)
{
	TCNT1=0;
}
/*
 * description: function to disable timer1 to stop the ICU driver
 */
void ICU_DeInit(void)
{
	TCCR1A=0;
	TCCR1B=0;
	TCNT1=0;
	ICR1=0;
	TIMSK&=~(1<<TICIE1);
}
