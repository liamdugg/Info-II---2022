/**
*	\file       AP_FuncionesMDE.c
*	\brief      Funciones de Eventos y Acciones asociadas a las Maquinas de estados
*	\details    Descripcion detallada del archivo
*	\author     Fede
*	\date       18-09-2021 17:26:28
*/

/************************************************************************************************************
 *** INCLUDES
 ************************************************************************************************************/
#include "AP_FuncionesMDE.h"
#include "timer.h"
#include "stick.h"
#include "AP_MDE.h"
#include "timer_handler.h"

/************************************************************************************************************
 *** DEFINES PRIVADOS AL MODULO
 ************************************************************************************************************/


/************************************************************************************************************
 *** VARIABLES GLOBALES PUBLICAS
 ************************************************************************************************************/

/************************************************************************************************************
 *** FUNCIONES GLOBALES AL MODULO
 ************************************************************************************************************/

void m_detener_timers(void){
	TimerClose();
}

void m_init_timer_boton_2s(void){
	TimerStart(2,2,timer_boton_Handler,SEG);
}

void m_init_timer_amarillo_5s(void){
	//TimerStart(1,5,timer_amar_Handler,SEG);
	TimerStart(1,1,timer_amar_Handler,SEG);
}

void m_init_timer_rojo_30s(void){
	//TimerStart(3,30,timer_rojo_Handler,SEG);
	TimerStart(3,3,timer_rojo_Handler,SEG);
}

void m_init_timer_verde_20s(void){
	//TimerStart(4,20,timer_verde_Handler,SEG);
	TimerStart(4,2,timer_verde_Handler,SEG);
}

void m_limpiar_flags(void){
	flag_amarillo = 0 ;
	flag_boton = 0 ;
	flag_verde = 0 ;
	flag_rojo = 0 ;
	flag_boton_repetido = 0 ;
}

void m_prender_amarillo(void){
	SetPIN(LED_VERDE, 1);
	SetPIN(LED_AZUL, 0);
	SetPIN(LED_ROJO, 1);
}

void m_prender_rojo(void){
	SetPIN(LED_VERDE, 1);
	SetPIN(LED_AZUL, 1);
	SetPIN(LED_ROJO, 0);
}

void m_prender_verde(void){
	SetPIN(LED_VERDE, 0);
	SetPIN(LED_AZUL, 1);
	SetPIN(LED_ROJO, 1);
}
