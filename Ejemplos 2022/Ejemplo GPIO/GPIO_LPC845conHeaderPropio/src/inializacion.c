/*
 * inializacion.c
 *
 *  Created on: 28 jul. 2021
 *      Author: socco
 */

#include "main.h"

void inicializacionGPIO(void){
	/** Habilita clock a P0 y P1 */
	SYSCON->SYSAHBCLKCTRL0 |= SYSCON_SYSAHBCLKCTRL0_GPIO0_MASK | SYSCON_SYSAHBCLKCTRL0_GPIO1_MASK;
	SetDIR(LED_VERDE, SALIDA);
	SetPINMODE_OUT(PIN_LED_VERDE, PUSH_PULL);
	SetDIR(LED_AZUL, SALIDA);
	SetPINMODE_OUT(PIN_LED_AZUL, PUSH_PULL);
	SetDIR(LED_ROJO, SALIDA);
	SetPINMODE_OUT(PIN_LED_ROJO, PUSH_PULL);
	SetDIR(TECLA_USR, ENTRADA);
	SetPINMODE_IN(PIN_TECLA_USR, PUSH_PULL);
}


/**
	\fn  	void inicializacion(void)
	\brief 	Inicializacion del sistema
 	\author Ing. Gabriel Soccodato
 	\date 	28 de Julio de 2021
 	\param 	void
 	\return void
*/
void inicializacion(void){
	inicializacionGPIO();
}
