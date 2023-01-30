/**
*	\file       AP_Inicializacion.c
*	\brief      Funciones de inicializacion de todo el proyecto
*	\details    Descripcion detallada del archivo
*	\author     Nahuel
*	\date       29-01-2023 21:05:56
*/

/************************************************************************************************************
 *** INCLUDES
 ************************************************************************************************************/
#include "AP_Inicializacion.h"



/************************************************************************************************************
 *** DEFINES PRIVADOS AL MODULO
 ************************************************************************************************************/

/************************************************************************************************************
 *** PROTOTIPO DE FUNCIONES PRIVADAS AL MODULO
 ************************************************************************************************************/
static void Inicializar_Pileta( void ) ;
static void Inicializar_Display_nadando( void ) ;

/************************************************************************************************************
 *** FUNCIONES PRIVADAS AL MODULO
 ************************************************************************************************************/


static void Inicializar_Pileta( void )
{
    //!< Coloque aqui su codigo
	Pulsador = 0 ;
	fin_carrera = 0 ;

    return ;
}


static void Inicializar_Display_nadando( void )
{
    //!< Coloque aqui su codigo
	Display_Carrera = 0 ;
	Timer_2s = 0 ;
	Pulsador = 0 ;
	fin_carrera = 0 ;

    return ;
}

static void Init_Gpio(void)
{

}

static void Init_Display()
{
	// ya iniciliamos como salida a los pines
    SetDIR(BCD_A,SALIDA);
    SetDIR(BCD_B,SALIDA);
    SetDIR(BCD_C,SALIDA);
    SetDIR(BCD_D,SALIDA);
    SetDIR(BCD_RST,SALIDA);
    SetDIR(BCD_CK,SALIDA);

    SetPINMODE_OUT(IOCON_INDEX_PIO0_20, PUSH_PULL);
    SetPINMODE_OUT(IOCON_INDEX_PIO0_23, PUSH_PULL);
    SetPINMODE_OUT(IOCON_INDEX_PIO0_22, PUSH_PULL);
    SetPINMODE_OUT(IOCON_INDEX_PIO0_21, PUSH_PULL);
    SetPINMODE_OUT(IOCON_INDEX_PIO0_18, PUSH_PULL);
    SetPINMODE_OUT(IOCON_INDEX_PIO0_19, PUSH_PULL);

    SetPIN(BCD_A,APAGADO);
    SetPIN(BCD_B,APAGADO);
    SetPIN(BCD_C,APAGADO);
    SetPIN(BCD_D,APAGADO);
    SetPIN(BCD_RST,APAGADO);
    SetPIN(BCD_CK,APAGADO);
}

static void Init_Systick()
{
	SYST_RVR = 12000 - 1;

	ENABLE = 1;
	TICKINT = 1;
	CLKSOURCE = 1;
	SYST_CVR = 0;
}

static void Init_UART()
{
	SYSCON->SYSAHBCLKCTRL0 |= 1<<14; // uart
	SYSCON->SYSAHBCLKCTRL0 |= 1<<7; // SWM

	SYSCON -> PDRUNCFG |= 1;
	SYSCON -> FCLKSEL[0] |= 1;

	//reset
	SYSCON -> PRESETCTRL0 |= 1<<14;

	SWM_PINASSIGN0 &= ~(0xFFFF);
	SWM_PINASSIGN0 |= (1);		//defino el pin para RX
	SWM_PINASSIGN0 |= (2<<8);	//defino el pin para TX


	SYSCON->SYSAHBCLKCTRL0 &= ~(1<<7);		//APAGO	SWM

	// Habilitamos USART0
	USART0->CFG |= (1 << 0);

	// Fijamos 8 bits de datos

	USART0->CFG &= ~(3 << 2);
	USART0->CFG |=  (1 << 2);

	// Fijamos sin paridad
	USART0->CFG &= ~(3 << 4);

	// Fijamos 1 bit de stop
	USART0->CFG &= ~(1 << 6);

	// Configuramos baudrate 9600
	// BRGVAL = (FCLK/((OSRVAL + 1) x baud rate)) – 1
	// BRGVAL = (12MHz / ((15 + 1) * 9600)) - 1
	// BRGVAL = 77,125
	// BRGVAL = 77

	USART0->BRG = 77;

	// Habilitamos interrupciones RXRDY y TXRDY
	USART0->INTENSET |= (1 << 0) | (1 << 2);

	// Habilitamos interrupciones de USART0 en NVIC
	ISER0 |= (1 << 3);
}

static void Init_EXINT(void)
{
	SYSCON->SYSAHBCLKCTRL0 |= (1<<28);

	ISER0 |= (1<<27);

	PINTSEL_0 &= ~(0x3F); //P0.0

	ISEL &= ~(0xFF); // por flanco

	IENF &= ~(0xFF);
	IENF |= (1<3);

}

void Inicializar( void )
{
    //Coloque aqui su codigo


	Inicializar_Pileta( );

	Inicializar_Display_nadando( );

	Init_Gpio();
	Init_Display();
	Init_Systick();
	Init_UART();
	Init_EXINT();
	
    return ;
}

