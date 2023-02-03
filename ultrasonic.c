 /******************************************************************************
 *
 * Module: ULTRASONIC
 *
 * File Name: ultrasonic.c
 *
 * Description: Source file for the ultrasonic driver
 *
 * Author: Mo'men Ahmed
 *
 *******************************************************************************/
#include "ultrasonic.h"
#include <util/delay.h>
#include "std_types.h"

Icu_ConfigType icu_for_ultrasonic = {F_CPU_8 ,RISING};

volatile static uint8 g_num_edges =0; //volatile because func edge processing is called
 //by the isr of the icu, so we will cancel compiler optimizations
volatile uint16 g_distance ;
volatile static uint16 g_time_high ;

//this function aims to initiate the ultrasonic sensor and set the callback function
void Ultrasonic_init(void)
{
  Icu_init(&icu_for_ultrasonic);
  Icu_setCallBack(Ultrasonic_edgeProcessing); //icu has the function to be
                                              //done when interrupt comes
  GPIO_setupPinDirection(TRIGGER_PORT_ID, TRIGGER_PIN_ID, PIN_OUTPUT);
  //microcontroller will trigger the sensor to generate ultrasound wave
}

//this function aims to trigger the ultrasonic sensor to generate an ultrasound wave
void Ultrasonic_trigger(void)
{
	GPIO_writePin(TRIGGER_PORT_ID, TRIGGER_PIN_ID, LOGIC_HIGH);
	_delay_us(10);
	GPIO_writePin(TRIGGER_PORT_ID, TRIGGER_PIN_ID, LOGIC_LOW);
	_delay_us(10);
}


//this function is responsible for getting the distance from the sensor to the
//object , it triggers the sensor to generate the ultrasound wave, when the wave
//hits the object and return back to the sensor, I calculate the distance.
uint16 Ultrasonic_readDistance (void)
{
  Ultrasonic_trigger();
  g_distance = (uint16) ((float) 173 / 10000 *g_time_high);
  return g_distance;
}


/*this is the callback function, when the icu catches a rising edge from the
 * echo pin, it jumps to this function, it aims to calculate the time at which
 * the echo pin is high, at first rising edge, I will clear the timer value to start
 * high time from zero and I will switch icu edge to falling, when icu catches
 * a falling edge I save the value of the timer in a variable called time_high
 which I'll use in calculating the distance */
void Ultrasonic_edgeProcessing(void)   //callback function
{
  g_num_edges++;
  if(g_num_edges ==1)
  {
	Icu_clearTimerValue();    //to start calculating high time
	Icu_setEdgeDetectionType(FALLING);
  }
  else if(g_num_edges==2)
  {
    g_num_edges=0;
    g_time_high = Icu_getInputCaptureValue();
	Icu_setEdgeDetectionType(RISING);
  }
}
