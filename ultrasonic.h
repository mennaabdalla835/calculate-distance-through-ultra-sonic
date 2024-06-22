/*
 *file name: ultrasonic.h
 *description: header file for ULTRASONIC driver
 *Created on: Oct 16, 2022
 * Author: menna abdalla
 */

#ifndef ULTRASONIC_H_
#define ULTRASONIC_H_

#include "std_types.h"
/*******************************************************************************
 *                         functions prototype
 ******************************************************************************/
/*
 * description: function to initialize the ULTRASONIC with initializing ICU driver
 * setup the ICU call back function
 * setup the direction for the trigger pin as output
 */
void ULTRASONIC_init(void);

/*
 * description: function to send the trigger pulse to the ULTRASONIC
 */
void ULTRASONIC_trigger(void);

/*
 * description:send the trigger pulse and start the measurements
 */

uint16 ULTRASONIC_readDistance(void);

/*
 * description: this the call back function called by the ICU driver used to
 * calculate the high time
 */
void ULTRASONIC_edgeProcessing(void);
#endif /* ULTRASONIC_H_ */
