/**
*	\file       AP_Inicializacion.c
*	\brief      Funciones de inicializacion de todo el proyecto
*	\details    Descripcion detallada del archivo
*	\author     Liam
*	\date       26-01-2023 23:36:06
*/

/************************************************************************************************************
 *** INCLUDES
 ************************************************************************************************************/
#include "AP_Inicializacion.h"
#include "AP_MDE.h"

static void Inicializar_Maquinas( void ){

	teclaOK = 0;
	finMusica = 0;
	parpadear = 0;
	prender = 0;
}

void initUART(void){

	SYSCON->SYSAHBCLKCTRL0 |= (1<<14);	// UART0
	SYSCON->SYSAHBCLKCTRL0 |= (1<<7);	// SWM

	// Seleccionamos fuente de clock para la USART0
	SYSCON->FCLKSEL[0] &= ~(0x111);

	//lo repite 3 veces para asegurar que se reinicie (creo)
	SYSCON->PRESETCTRL0 &= ~(1<<14);
	SYSCON->PRESETCTRL0 &= ~(1<<14);
	SYSCON->PRESETCTRL0 &= ~(1<<14);
	SYSCON->PRESETCTRL0 |= (1<<14);
	SYSCON->PRESETCTRL0 |= (1<<14);
	SYSCON->PRESETCTRL0 |= (1<<14);

	PINASSIGN0 &= ~(0xFFFF);
	PINASSIGN0 |= 20;			// PIN 0,20 para Tx
	PINASSIGN0 |= (21 << 8);	// PIN 0,21 para Rx

	SYSCON->SYSAHBCLKCTRL0 &= ~(1<<7);

	USART0->CFG |= (1<<0);

	USART0->CFG &= ~(3 << 2);
	USART0->CFG |= (1<<2);

	USART0->CFG &= ~(3 << 4);

	USART0->CFG &= ~(1<<6);

	// Configuramos baudrate 9600
	// BRGVAL = (FCLK/((OSRVAL + 1) x baud rate)) – 1
	// BRGVAL = (12MHz / ((15 + 1) * 9600)) - 1
	// BRGVAL = 77,125
	// BRGVAL = 77
	USART0->BRG = 77;

	USART0->INTENSET |= (1 << 0) | (1 << 2);
	ISER0 |= (1 << 3);
}

void initGPIO(void){

	SYSCON->SYSAHBCLKCTRL0 |= (1<<6);

	// Inicializamos teclado matricial

	SetDIR(FILA_0, SALIDA);
	SetDIR(FILA_1, SALIDA);
	SetDIR(FILA_2, SALIDA);
	SetDIR(FILA_3, SALIDA);

	SetPINMODE_OUT(IOCON_INDEX_PIO0_0, PUSH_PULL);
	SetPINMODE_OUT(IOCON_INDEX_PIO0_1, PUSH_PULL);
	SetPINMODE_OUT(IOCON_INDEX_PIO0_2, PUSH_PULL);
	SetPINMODE_OUT(IOCON_INDEX_PIO0_3, PUSH_PULL);

	SetPIN(FILA_0, 0);
	SetPIN(FILA_1, 0);
	SetPIN(FILA_2, 0);
	SetPIN(FILA_3, 0);

	SetDIR(COL_0, ENTRADA);
	SetDIR(COL_1, ENTRADA);
	SetDIR(COL_2, ENTRADA);
	SetDIR(COL_3, ENTRADA);

	SetPINMODE_IN(IOCON_INDEX_PIO0_4, PULL_UP);
	SetPINMODE_IN(IOCON_INDEX_PIO0_5, PULL_UP);
	SetPINMODE_IN(IOCON_INDEX_PIO0_6, PULL_UP);
	SetPINMODE_IN(IOCON_INDEX_PIO0_7, PULL_UP);

	// FAlta inicializar leds pero alta paja


	// Inicializamos Interrupcion externa
	PINTSEL_3 &= ~(0x1F);	// Ponemos los primeros 5 bits en 0
	PINTSEL_3 |= 31;		// Elegimos el pin 0,31

	ISEL &= ~(1<<3);		// Elegimos interrupcion por flanco
	IENF |= (1<<3);			// Ponemos que sea flanco descendente

	ISER0 |= (1<<27);		// Habilitamos la EINT3 en NVIC
}

void initSysTick(void){

	SYST_RVR = 12000 - 1;
	SYST_CVR = 0;
	CLKSOURCE = 1;
	TICKINT = 1;
	ENABLE = 1;
}

void Inicializar(void){

	initGPIO();
	initUART();
	initSysTick();
	Inicializar_Maquinas();
}

