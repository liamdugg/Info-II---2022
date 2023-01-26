/*
 * inializacion.c
 *
 *  Created on: 28 jul. 2021
 *      Author: socco
 */

#include "main.h"

/**
	\fn  	void inicializacionGPIO(void)
	\brief 	Inicializacion de los pines de GPIO
 	\author Ing. Gabriel Soccodato
 	\date 	28 de Julio de 2021
 	\param 	void
 	\return void
*/
void inicializacionGPIO(void){
	/** Habilita clock a P0 y P1 */
	SYSCON->SYSAHBCLKCTRL0 |= SYSCON_SYSAHBCLKCTRL0_GPIO0_MASK | SYSCON_SYSAHBCLKCTRL0_GPIO1_MASK;

	SetDIR(LED_VERDE, SALIDA);
	SetPINMODE_OUT(PIN_LED_VERDE, PUSH_PULL);
	SetPIN(LED_VERDE, 1);

	SetDIR(LED_AZUL, SALIDA);
	SetPINMODE_OUT(PIN_LED_AZUL, PUSH_PULL);
	SetPIN(LED_AZUL, 1);

	SetDIR(LED_ROJO, SALIDA);
	SetPINMODE_OUT(PIN_LED_ROJO, PUSH_PULL);
	SetPIN(LED_ROJO, 1);

	SetDIR(TECLA_USR, ENTRADA);
	SetPINMODE_IN(PIN_TECLA_USR, PULL_UP);

}


void inicializacion_hw(void){
	inicializacionGPIO();
	SysTickInic(12000);
}
