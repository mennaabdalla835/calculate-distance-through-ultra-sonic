/*
 *      file name:icu.h
 *      description:header file for the ICU driver
 *      Created on: Oct 7, 2022
 *      Author: menna abdalla
 */

#ifndef ICU_H_
#define ICU_H_

#include "std_types.h"
/*******************************************************************************
 *                            DEFINITIONS
 ******************************************************************************/
typedef enum {
	NO_CLOCK,F_CPU_CLOCK,F_CPU_CLOCK_8,F_CPU_CLOCK_64,F_CPU_CLOCK_256,F_CPU_CLOCK_1024
}ICU_Clock;

typedef enum {
	FALLING,RAISING
}ICU_EdgeType;

typedef struct {
	ICU_Clock clock;
	ICU_EdgeType edge;
}ICU_ConfigType;

/******************************************************************************
 *                             FUNCTIONS PROTOTYPE
 ******************************************************************************/
/*
 * description: function to initialize the ICU driver
 * 1-set the required clock
 * 2-set the required edge
 * 3-enable ICR
 * 4-initialize registers in Timer1
 */
void ICU_init(const ICU_ConfigType * config_ptr);

/*
 * description: function to set the call back function adress
 *
 */
void ICU_setCallBack(void (*a_ptr)(void));

/*
 * description:function to set the required edge
 */
void ICU_setEdgeDetectionType (const ICU_EdgeType a_edgeType);
/*
 * description:function to return the value of timer1 that stored in ICR1
 */

uint16 ICU_getInputCaptureValue (void);

/*
 * description:function to clear timer1
 */
void ICU_clearTimer(void);

/*
 * description: function to disable timer1 to stop the ICU driver
 */
void ICU_DeInit(void);
#endif /* ICU_H_ */
