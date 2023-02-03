/**
*	\file       AP_FuncionesMDE.c
*	\brief      Funciones de Eventos y Acciones asociadas a las Maquinas de estados
*	\details    Descripcion detallada del archivo
*	\author     Liam
*	\date       01-02-2023 21:14:08
*/

/************************************************************************************************************
 *** INCLUDES
 ************************************************************************************************************/
#include "AP_FuncionesMDE.h"

extern int tiempoAlarma;
extern int tiempoCamara;
extern int tiempoBalanza;
extern int flagIR;
extern int apagarAlarma;

int stopTimAlarma;
int stopTimCamara;
int stopTimBalanza;
uint8_t idEquipo;
uint8_t pesoMax;
/*-------------------------------------------- EVENTOS ----------------------------------------------------*/

void f_activarAlarma(uint8_t alarma){

	if(alarma == ALARMA_S)
		SetPIN(PIN_ALARMA_S, ON);

	else if(alarma == ALARMA_A)
		SetPIN(PIN_ALARMA_A, ON);
}

void f_apagarAlarma(uint8_t alarma){

	if(alarma == ALARMA_S)
		SetPIN(PIN_ALARMA_S, OFF);

	else if(alarma == ALARMA_A)
		SetPIN(PIN_ALARMA_A, OFF);
}

void f_enviarTrama(uint8_t tipoTrama){

	// LAS DOS TRAMAS SE MANDAN POR LA MISMA UART
	// PORQUE NO QUERIAMOS CONFIGURAR 2
	// LO QUE HABRIA QUE HACER ES TENER DOS BUFFER TX DISTINTOS
	// PONERLE UN PARAMETRO A PUSH_TX QUE CARGUE AL BUFFER QUE CORRESPONDA
	// Y DESPUES LOS HANDLER DE CADA UART LEEN EL BUFFER QUE DEBAN.

	if(tipoTrama == TRAMA_BAL){
		Transmitir("$@#", 3);
	}

	else if(tipoTrama == TRAMA_CAM){
		Transmitir("$", 1);
		Transmitir(&idEquipo, 1);
		Transmitir("#", 1);
	}
}

void f_prenderCamara(void){
	f_enviarTrama(TRAMA_CAM);
}

void f_startTimer(uint8_t timer, uint32_t tiempo ){

	if(timer == TIM_BAL){
		tiempoBalanza = tiempo;
		stopTimBalanza = 0;
	}

	else if(timer == TIM_CAM){
		tiempoCamara = tiempo;
		stopTimCamara = 0;
	}

	else if(timer == TIM_ALARMA){
		tiempoAlarma = tiempo;
		stopTimAlarma = 0;
	}
}

void f_stopTimer(uint8_t timer){

	if(timer == TIM_BAL)
		stopTimBalanza = 1;

	else if(timer == TIM_CAM)
		stopTimCamara = 1;

	else if(timer == TIM_ALARMA)
		stopTimAlarma = 1;

}

void SysTick_Handler(void){

	if(!stopTimAlarma && tiempoAlarma > 0)
		tiempoAlarma--;

	if(!stopTimBalanza && tiempoBalanza > 0)
		tiempoBalanza--;

	if(!stopTimCamara && tiempoCamara > 0)
		tiempoCamara--;

}

void PININT0_IRQHandler(void){
	apagarAlarma = 1;
}

void PININT1_IRQHandler(void){
	flagIR = 1;
}

/*------------------------------------------TEMPORIZADORES -------------------------------------------------*/

