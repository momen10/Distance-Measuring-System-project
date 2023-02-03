/*
 * MINI_PROJECT4.c
 *
 *  Created on: Oct 13, 2022
 *      Author: Dell
 */
#include "lcd.h"
#include "ultrasonic.h"
#include "std_types.h"
#include <avr/io.h>
#include "gpio.h"

extern uint16 g_distance;
int main (void)
{
	GPIO_setupPinDirection(PORTB_ID, PIN1_ID, PIN_OUTPUT);
	GPIO_writePin(PORTB_ID, PIN1_ID, LOGIC_LOW);
	SREG |= (1<<7);
	LCD_init();
	Ultrasonic_init();

	LCD_displayString("distance = ");

	while(1)
	{
		Ultrasonic_readDistance();
		LCD_moveCursor(1, 0);
		LCD_intgerToString(g_distance);
		LCD_displayString("cm");
	}
}
