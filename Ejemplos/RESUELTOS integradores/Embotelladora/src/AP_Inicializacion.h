/**
*	\file       AP_Inicializacion.h
*	\brief      prototipo de la Funcion general de inicializaciones
*	\details    Descripcion detallada del archivo
*	\author     Liam
*	\date       10-02-2023 16:37:13
*/

#ifndef INC_AP_INICIALIZACION_H_
#define INC_AP_INICIALIZACION_H_

/************************************************************************************************************
 *** INCLUDES GLOBALES
 ************************************************************************************************************/
#include "uart.h"
#include "Timer.h"
#include "Regs_LPC845.h"
#include "Fun_GPIO.h"
#include "swm.h"
/************************************************************************************************************
 *** DEFINES GLOBALES
 ************************************************************************************************************/
#define BTN_ON	0,0
#define BTN_OFF 0,1
#define LED		0,2
#define CINTA	0,3
#define PISTON	0,4
#define SENSOR	0,5
/************************************************************************************************************
 *** PROTOTIPO DE FUNCIONES GLOBALES
 ************************************************************************************************************/
void Inicializar( void ) ;

#endif /* INC_AP_INICIALIZACION_H_ */
