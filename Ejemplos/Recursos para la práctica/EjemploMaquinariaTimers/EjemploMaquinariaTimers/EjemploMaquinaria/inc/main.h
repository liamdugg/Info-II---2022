/*
 * main.h
 *
 *  Created on: 28 jul. 2021
 *      Author: socco
 */

#ifndef MAIN_H_
#define MAIN_H_


#include "LPC845.h"
#include "inicializacion.h"
#include "gpio.h"
#include "stick.h"
#include "timer.h"


#define ON 	1
#define OFF 2
#define APAGATE 0
#define PRENDETE 1



void apagarLED(void);
void prenderLED(void);
void encenderTimer1();
void encenderTimer2();

#endif /* MAIN_H_ */
