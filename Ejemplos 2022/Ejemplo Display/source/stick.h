/*
 * stick.h
 *
 *  Created on: 6 ago. 2021
 *      Author: socco
 */

#ifndef STICK_H_
#define STICK_H_

#include "LPC845.h"
#include "dr_gpio.h"
#include "stick.h"

#define PIN_LED_VERDE	IOCON_INDEX_PIO1_0
#define PIN_LED_AZUL	IOCON_INDEX_PIO1_1
#define PIN_LED_ROJO	IOCON_INDEX_PIO1_2
#define PIN_TECLA_USR	IOCON_INDEX_PIO0_4
#define PIN_TECLA_ISP	IOCON_INDEX_PIO0_12

#define LED_VERDE	1,0
#define LED_AZUL	1,1
#define LED_ROJO	1,2
#define	TECLA_USR	0,4
#define	TECLA_ISP	0,12

#define LED_VERDE_TOGGLE	NotPIN(LED_VERDE)
#define LED_VERDE_ON	SetPIN(LED_VERDE,0)
#define LED_VERDE_OFF	SetPIN(LED_VERDE,1)


#endif /* STICK_H_ */
