/*
 * leds.h
 *
 *  Created on: Aug 15, 2022
 *      Author: asantini
 */

#ifndef LEDS_H_
#define LEDS_H_


#define LED_GREEN 0
#define	LED_RED 1
#define LED_BLUE 2
#define	LEDS_ALL 3


void Initialize(void);

void SET_LED(int);
void CLEAR_LED(int);


#endif /* LEDS_H_ */
