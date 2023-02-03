/************************************************************************************************************
 *** INCLUDES
 ************************************************************************************************************/
#include "AP_Inicializacion.h"
#include "AP_MDE.h"

/************************************************************************************************************
 *** DEFINES PRIVADOS AL MODULO
 ************************************************************************************************************/

/************************************************************************************************************
 *** PROTOTIPO DE FUNCIONES PRIVADAS AL MODULO
 ************************************************************************************************************/
static void Inicializar_Museo(void);
void initSystick(void);
void initUART(void);
void initExtInt(void);
void initGPIO(void);
/************************************************************************************************************
 *** FUNCIONES PRIVADAS AL MODULO
 ************************************************************************************************************/

static void Inicializar_Museo( void )
{
	tramaOn = 0 ;
	flagIR = 0 ;
	apagarAlarma = 0 ;
	tiempoAlarma = 0 ;
	tiempoBalanza = 0 ;
	errorBalanza = 0 ;
	tiempoCamara = 0 ;
    return ;
}

void initSystick(void){

	SYST_RVR = 12000 - 1;
	SYST_CVR = 0;

	TICKINT = 1;
	CLKSOURCE = 1;
	ENABLE = 1;
}

void initExtInt(void){

	SYSCON_SYSAHBCLKCTRL0 |= (1<<28);

	PINTSEL_0 &= ~(0x3F << 0);
	PINTSEL_0 |= (0<<0);

	PINTSEL_1 &= ~(0x3F << 0);
	PINTSEL_1 |= (1<<0);

	ISEL &= ~(0xFF);

	IENF &= ~(0xFF);
	IENF |= 3;

	ISER0 |= (1<<24) | (1<<25);
}

void initUART(void){

	// HAY QUE INICIALIZAR 3 UART PERO HACEMOS 1 SOLA
	SYSCON_SYSAHBCLKCTRL0 |= (1<<14);
	SYSCON_UART0CLKSEL = 0;

	SYSCON_PRESETCTRL0 = 0;
	SYSCON_PRESETCTRL0 = 1;

	SYSCON_SYSAHBCLKCTRL0 |= (1<<7);
	SWM_PINASSIGN0 &= ~(0xFFFF);
	SWM_PINASSIGN0 |= (3<<0);
	SWM_PINASSIGN0 |= (4<<8);
	SYSCON_SYSAHBCLKCTRL0 &= ~(1<<7);

	USART0->CFG &= ~(0xFFFFFFFF); // Con esto ya configuramos paridad y bit de stop
	USART0->CFG |= (1<<0);
	USART0->CFG |= (1<<2);

	USART0->BRG = 77;
	USART0->INTENSET |= (1<<0) | (1<<2);

	ISER0 |= (1<<3);
}

void initGPIO(void){
	// YA INICIALIZADO
	// POR LA CONSIGNA
}

/************************************************************************************************************
 *** FUNCIONES GLOBALES AL MODULO
 ************************************************************************************************************/

void Inicializar(void){
	Inicializar_Museo();
	initSystick();
	initUART();
	initExtInt();
	initGPIO();
}

