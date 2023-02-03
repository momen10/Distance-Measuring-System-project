 /******************************************************************************
 *
 * Module: ULTRASONIC
 *
 * File Name: ultrasonic.h
 *
 * Description: header file for the ultrasonic driver
 *
 * Author: Mo'men Ahmed
 *
 *******************************************************************************/
#ifndef ULTRASONIC_H_
#define ULTRASONIC_H_

#include "gpio.h"
#include "icu.h"
#include "std_types.h"

#define SPEED_VELOCITY  34600  //(CM/SEC)
#define TRIGGER_PORT_ID PORTB_ID
#define TRIGGER_PIN_ID  PIN5_ID


void Ultrasonic_init(void);
void Ultrasonic_trigger(void);
uint16 Ultrasonic_readDistance (void);
void Ultrasonic_edgeProcessing(void);   //callback function

#endif /* ULTRASONIC_H_ */
