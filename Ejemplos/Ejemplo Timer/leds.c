/*
 * leds.c
 *
 *  Created on: Aug 15, 2022
 *      Author: asantini
 */


#include "leds.h"
#include "registers.h"

void Initialize(void){


	SYSCON_SYSAHBCLKCTRL0_ADDR->GPIO1=1;

	GPIO_DIR1_ADDR->PIO1_0=1;
	GPIO_SET1_ADDR->PIO1_0=1;

	GPIO_DIR1_ADDR->PIO1_1=1;
	GPIO_SET1_ADDR->PIO1_1=1;

	GPIO_DIR1_ADDR->PIO1_2=1;
	GPIO_SET1_ADDR->PIO1_2=1;
}

void SET_LED(int L_COLOUR){
	switch(L_COLOUR){
		case LED_GREEN:
				CLEAR_LED(LED_BLUE);
				CLEAR_LED(LED_RED);
				GPIO_CLR1_ADDR->PIO1_0=1;
			break;
		case LED_BLUE:
				CLEAR_LED(LED_GREEN);
				CLEAR_LED(LED_RED);
				GPIO_CLR1_ADDR->PIO1_1=1;
			break;
		case LED_RED:
				CLEAR_LED(LED_BLUE);
				CLEAR_LED(LED_GREEN);
				GPIO_CLR1_ADDR->PIO1_2=1;
			break;
		default:

			break;
	}
}

void CLEAR_LED(int L_COLOUR){
	switch(L_COLOUR){
			case LED_GREEN:
					GPIO_SET1_ADDR->PIO1_0=1;
				break;
			case LED_BLUE:
					GPIO_SET1_ADDR->PIO1_1=1;
				break;
			case LED_RED:
					GPIO_SET1_ADDR->PIO1_2=1;
				break;
			default:

				break;
		}

}

