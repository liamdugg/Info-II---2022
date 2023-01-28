/*
===============================================================================
 Name        : pruebaLPC845TotalmentePelado.c
 Author      : $(author)
 Version     :
 Copyright   : $(copyright)
 Description : main definition
===============================================================================
*/

#include <cr_section_macros.h>
#include "main.h"
// TODO: insert other include files here

// TODO: insert other definitions and declarations here

volatile uint8_t flag_led = 0;

void timer1Handler(void){
	flag_led=PRENDETE;
}

void timer2Handler(void){
	flag_led=APAGATE;
}


int main(void) {

	volatile static uint8_t estadoLED = OFF;

	inicializacion();
	encenderTimer1();

    while(1) {

     	TimerEvent();
		switch (estadoLED){

			case OFF:
				if(flag_led==PRENDETE)
				{
					prenderLED();
					encenderTimer2();
					estadoLED = ON;
				}
				break;

			case ON:
				if(flag_led==APAGATE)
				{
					apagarLED();
					encenderTimer1();
					estadoLED = OFF;
				}
				break;


			default:
				break;
		}

    }

    return 0;

}


void apagarLED(void){
	SetPIN(LED_VERDE, 1);
	SetPIN(LED_AZUL, 1);
	SetPIN(LED_ROJO, 1);
}

void prenderLED(void){
	SetPIN(LED_VERDE, 1);
	SetPIN(LED_AZUL, 0);
	SetPIN(LED_ROJO, 1);
}

void encenderTimer1(){
	int segundos = 1;
	int num_timer = 1;
	TimerStart(num_timer,segundos,timer1Handler,SEG);
}


void encenderTimer2(){
	int segundos = 3;
	int num_timer = 2;
	TimerStart(num_timer,segundos,timer2Handler,SEG);
}
