#include "AP_Inicializacion.h"
#include "AP_MDE.h"

/************************************************************************************************************
 *** DEFINES PRIVADOS AL MODULO
 ************************************************************************************************************/

/************************************************************************************************************
 *** PROTOTIPO DE FUNCIONES PRIVADAS AL MODULO
 ************************************************************************************************************/
static void Inicializar_Embotelladora( void ) ;

/************************************************************************************************************
 *** FUNCIONES PRIVADAS AL MODULO
 ************************************************************************************************************/

static void Inicializar_Embotelladora( void ){

	botonON = 0;
	botella = 0;
	Timers[0] = 0;
	Timers[1] = 0;
	Timers[2] = 0;
	botonOFF = 0;
	datoRx = 0;
	contador = 0;
}

void Init_GPIO(){

	SYSCON->SYSAHBCLKCTRL0 |= (1<<6);

	SetDIR(BTN_OFF, ENTRADA);
	SetPINMODE_IN(IOCON_INDEX_PIO0_0, PULL_DOWN);

	SetDIR(BTN_ON, ENTRADA);
	SetPINMODE_IN(IOCON_INDEX_PIO0_1, PULL_DOWN);

	SetDIR(SENSOR, ENTRADA);
	SetPINMODE_IN(IOCON_INDEX_PIO0_5, PULL_DOWN);

	SetDIR(LED, SALIDA);
	SetPINMODE_OUT(IOCON_INDEX_PIO0_2, PUSH_PULL);
	SetPIN(BTN_OFF, APAGADO);

	SetDIR(CINTA, SALIDA);
	SetPINMODE_OUT(IOCON_INDEX_PIO0_3, PUSH_PULL);
	SetPIN(BTN_OFF, APAGADO);

	SetDIR(PISTON, SALIDA);
	SetPINMODE_OUT(IOCON_INDEX_PIO0_4, PUSH_PULL);
	SetPIN(BTN_OFF,APAGADO);

}

void Init_Systick(){

	SYST_RVR = 12000-1;

	ENABLE = 1;
	TICKINT = 1;
	CLKSOURCE = 1;

	SYST_CVR = 0;
}

void Init_UART(){

	SYSCON->SYSAHBCLKCTRL0 |= (1<<14);

	SYSCON->FCLKSEL[0] &= ~(0x7);
	SYSCON->FCLKSEL[0] |= (1<<2);

	SYSCON->PRESETCTRL0 &= ~(1<<14);
	SYSCON->PRESETCTRL0 |= (1<<14);

	SYSCON->SYSAHBCLKCTRL0 |= (1<<7);
	SWM_PINASSIGN0 &= ~(0xFFFF);
	SWM_PINASSIGN0 |= 6;				// No es necesario
	SWM_PINASSIGN0 |= (7 << 8);
	SYSCON->SYSAHBCLKCTRL0 |= (1<<7);

	USART0->CFG |= (1<<0);
	USART0->CFG &= ~(3<<2);
	USART0->CFG |= (1<<2);
	USART0->CFG &= ~(3<<4);
	USART0->CFG &= ~(1<<6);

	USART0->BRG = 77;

	USART0->INTENSET |= (1<<0);
	ISER0 |= (1<<3);
}

void Inicializar( void ){

	Inicializar_Embotelladora( );
	Init_GPIO();
	Init_UART();
	Init_Systick();
}

