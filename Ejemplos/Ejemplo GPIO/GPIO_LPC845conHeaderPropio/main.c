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

void delay(void){
	uint32_t i;

	for(i = 0 ; i < 50000 ; i++);
	for(i = 0 ; i < 50000 ; i++);
	for(i = 0 ; i < 50000 ; i++);
	for(i = 0 ; i < 50000 ; i++);
	for(i = 0 ; i < 50000 ; i++);

}


int main(void) {

	uint32_t cont = 0, flag = 0;

    // TODO: insert code here
	inicializacion();
    // Force the counter to be placed into memory

    // Enter an infinite loop, just incrementing a counter
    while(1) {

        // "Dummy" NOP to allow source level single
        // stepping of tight while() loop
        __asm volatile ("nop");

    	if(flag){
			SetPIN(LED_VERDE, 0);
			SetPIN(LED_AZUL, 1);
			SetPIN(LED_ROJO, 1);

			delay();

			SetPIN(LED_VERDE, 1);
			SetPIN(LED_AZUL, 0);
			SetPIN(LED_ROJO, 1);

			delay();

			SetPIN(LED_VERDE, 1);
			SetPIN(LED_AZUL, 1);
			SetPIN(LED_ROJO, 0);

			delay();
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
    }
    return 0 ;
}
