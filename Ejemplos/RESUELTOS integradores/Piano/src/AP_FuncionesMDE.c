/**
*	\file       AP_FuncionesMDE.c
*	\brief      Funciones de Eventos y Acciones asociadas a las Maquinas de estados
*	\details    Descripcion detallada del archivo
*	\author     Liam
*	\date       26-01-2023 23:36:06
*/

/************************************************************************************************************
 *** INCLUDES
 ************************************************************************************************************/
#include "AP_FuncionesMDE.h"
#include "AP_Inicializacion.h"
#include "Teclado.h"

#define	E_START			0
#define E_CANT_TECLAS	1
#define E_TECLAS		2
#define E_TIEMPO		3
#define E_FIN			4

uint32_t notaActual = 0;

uint8_t buffNotas[MAX_NOTAS];
uint8_t cantTeclas = 0;

extern int prender;
extern int tiempo;
extern int tramaOK;
extern uint8_t bufKey;

void PININT3_IRQHandler(void){
	prender = 1;
}

void f_enviarTramaOn(void){
	Transmitir("$START#",strlen("$START#"));
}

void f_guardarTeclas(void){

}

uint8_t teclaOK(void){

	uint8_t tecla = NO_KEY;
	tecla = getKey();

	if(tecla == buffNotas[notaActual])
		return 1;

	else if(tecla == TECLA_INC){
		if(tiempo < 10)
			tiempo++;
		return 2;
	}

	else if(tecla == TECLA_DEC){
		if(tiempo > 1)
			tiempo--;
		return 3;
	}

	return 0;
}

void f_pasarNota(void){

	if(notaActual == 0){
		f_prenderLED();
		f_setTimer();
		notaActual++;
	}

	else{
		f_apagarLED();
		notaActual++;
		f_prenderLED();
		f_setTimer();
	}
}

void f_prenderLED(void){
	setPIN(1,buffNotas[notaActual],ON);
}

void f_apagarLED(void){
	setPIN(1,buffNotas[notaActual],OFF);
}

void f_setTimer(void){
	TimerStart(TIM_TECLA, tiempo, NULL, SEG);
}

void f_startTimer3S(void){
	TimerStart(TIM_3S, 3, NULL, SEG);
}

void f_startTimer500ms(void){
	TimerStart(TIM_500ms, 50, NULL, DEC);
}

void checkTrama(void){

	uint8_t dato;
	static int  teclasContadas = 0;
	static int estado;

	switch(estado){

		case E_START:
			if(popRx() == '$')
				estado = E_CANT_TECLAS;
			break;

		case E_CANT_TECLAS:

			dato = (uint8_t)popRx();

			if(dato>0 || dato<=20){
				cantTeclas = dato;
				estado = E_TECLAS;
			}

			else estado = E_START;
			break;

		case E_TECLAS:

			if(teclasContadas < cantTeclas){

				dato = (uint8_t)popRx();

				if(dato>0 || dato<=12){
					buffNotas[teclasContadas] = dato;
					teclasContadas++;
				}

				else estado = E_START;
			}

			else estado = E_TIEMPO;
			break;

		case E_TIEMPO:

			dato = (uint8_t)popRx();

			if(dato>0 || dato<=10){
				tiempo = dato;
				estado = E_FIN;
			}

			else estado = E_START;
			break;

		case E_FIN:

			if(popRx() == '#'){
				tramaOK = 1;
				estado = E_START;
			}

			else estado = E_START;
			break;

		default:
			estado = E_START;
			break;
		}

}
