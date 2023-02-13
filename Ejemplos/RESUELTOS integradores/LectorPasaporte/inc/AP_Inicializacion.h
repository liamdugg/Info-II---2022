/**
*	\file       AP_Inicializacion.h
*	\brief      prototipo de la Funcion general de inicializaciones
*	\details    Descripcion detallada del archivo
*	\author     Nahuel
*	\date       12-02-2023 19:01:08
*/

#ifndef INC_AP_INICIALIZACION_H_
#define INC_AP_INICIALIZACION_H_

/************************************************************************************************************
 *** INCLUDES GLOBALES
 ************************************************************************************************************/
#include "Regs_LPC845.h"
#include "Fun_GPIO.h"
#include "swm.h"
#include "uart.h"
#include "adc.h"

/************************************************************************************************************
 *** DEFINES GLOBALES
 ************************************************************************************************************/

#define LED     1,5
#define DIV     600000

#define PWM_BASE    0x40000000
#define PWM         (*((volatile uint32_t *)(PWM_BASE)))

#define 	MAX_NUMP		8
/************************************************************************************************************
 *** PROTOTIPO DE FUNCIONES GLOBALES
 ************************************************************************************************************/
void Inicializar( void ) ;

#endif /* INC_AP_INICIALIZACION_H_ */
