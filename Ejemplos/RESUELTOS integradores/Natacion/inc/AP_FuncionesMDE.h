/**
*	\file       AP_FuncionesMDE.h
*	\brief      Prototipos, defines, etc. de los Eventos y Acciones asociadas a la M de E
*	\details    Descripcion detallada del archivo
*	\author     Nahuel
*	\date       29-01-2023 21:05:56
*/

#ifndef INC_AP_FUNCIONESMDEE_H_
#define INC_AP_FUNCIONESMDEE_H_

/************************************************************************************************************
 *** INCLUDES GLOBALES
 ************************************************************************************************************/
#include "AP_Inicializacion.h"



/************************************************************************************************************
 *** DEFINES GLOBALES
 ************************************************************************************************************/
#define		TRUE		1
#define		FALSE		0
#define		ON		1
#define		OFF		0

/************************************************************************************************************
 *** VARIABLES GLOBALES PUBLICAS
 ************************************************************************************************************/

/************************************************************************************************************
 *** PROTOTIPO DE FUNCIONES GLOBALES
 ************************************************************************************************************/

/*-------------------------------------------- EVENTOS ----------------------------------------------------*/


/*-------------------------------------------- ACCIONES ----------------------------------------------------*/
uint8_t Inicio(void);
uint8_t llegada(void);
void f_Deneter_Timer ( uint8_t nadador );
void f_Display_Corredor ( void );
void f_Envio_trama ( int nadador );
void f_Iniciar_Display_Carrera ( void );
void f_Iniciar_Timer_2s ( void );
void f_Iniciar_Timers ( void );

uint32_t parseo_tiempo(int nadador);

/*------------------------------------------TEMPORIZADORES -------------------------------------------------*/


#endif /* INC_AP_FUNCIONESMDEE_H_ */
