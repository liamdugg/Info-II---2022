/*
 * timer_handlers.c
 *
 *  Created on: 18 sep. 2021
 *      Author: Federico
 */


#include "AP_MDE.h"
#include "timer_handler.h"

void timer_amar_Handler(void){
	flag_verde = 1; //Vencido el amarillo cambia a verde
}

void timer_boton_Handler(void){
	flag_boton_repetido = 1; //Es el encargado de avisar que 2 segundos después el botón siguió apretado
}
void timer_rojo_Handler(void){
	flag_amarillo = 1;
}
void timer_verde_Handler(void){
	flag_rojo = 1;
}

