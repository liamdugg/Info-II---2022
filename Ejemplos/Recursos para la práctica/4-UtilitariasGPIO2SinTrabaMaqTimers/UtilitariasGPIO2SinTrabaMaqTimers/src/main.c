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

volatile uint8_t ledTimeoutFlag = 0;

void timer1Handler(void){
	ledTimeoutFlag = 1;
}

void timer2Handler(void){
	ledTimeoutFlag = 1;
	TimerStart(2,20,timer2Handler,DEC);
}

void timer3Handler(void){
	ledTimeoutFlag = 1;
	TimerStart(3,40,timer2Handler,DEC);
}


int main(void) {

	uint32_t cont = 0, flag = 0;
	volatile static uint8_t estadoLED = VERDE_ON;

    // TODO: insert code here
	inicializacion();
    // Force the counter to be placed into memory
	TimerStart(1,10,timer1Handler,DEC);

    // Enter an infinite loop, just incrementing a counter
    while(1) {

        // "Dummy" NOP to allow source level single
        // stepping of tight while() loop
        __asm volatile ("nop");

  	if(flag){

			switch (estadoLED){
			case VERDE_ON:
				if(!ledTimeoutFlag){
					SetPIN(LED_VERDE, 0);
					SetPIN(LED_AZUL, 1);
					SetPIN(LED_ROJO, 1);

				}else{
					ledTimeoutFlag = 0;
					estadoLED = AZUL_ON;
					TimerStart(2,20,timer2Handler,DEC);
				}
				break;
			case AZUL_ON:
				if(!ledTimeoutFlag){
					SetPIN(LED_VERDE, 1);
					SetPIN(LED_AZUL, 0);
					SetPIN(LED_ROJO, 1);
				}else{
					ledTimeoutFlag = 0;
					estadoLED = ROJO_ON;
					TimerStart(3,40,timer3Handler,DEC);

				}
				break;
			case ROJO_ON:
				if(!ledTimeoutFlag){
					SetPIN(LED_VERDE, 1);
					SetPIN(LED_AZUL, 1);
					SetPIN(LED_ROJO, 0);

				}else{
					ledTimeoutFlag = 0;
					estadoLED = VERDE_ON;
					TimerStart(1,10,timer1Handler,DEC);
				}
				break;
			default:
				break;
			}
    	}


    	if(GetPIN(TECLA_USR) == 0)
    	{
    		// TECLA PRESIONADA
    			flag = 1;
				cont++;
     	}
    	else{
    		flag = 0;
    	}

     	TimerEvent();

    }

    return 0 ;

}
