/**
*	\file       AP_Inicializacion.c
*	\brief      Funciones de inicializacion de todo el proyecto
*	\details    Descripcion detallada del archivo
*	\author     Nahuel
*	\date       23-01-2023 18:05:23
*/

/************************************************************************************************************
 *** INCLUDES
 ************************************************************************************************************/
#include "AP_Inicializacion.h"
#include "AP_MDE.h"
#include "Fun_GPIO.h"

/************************************************************************************************************
 *** DEFINES PRIVADOS AL MODULO
 ************************************************************************************************************/

extern int tim_flag;




/************************************************************************************************************
 *** PROTOTIPO DE FUNCIONES PRIVADAS AL MODULO
 ************************************************************************************************************/
static void Inicializar_Semaforo( void ) ;

/************************************************************************************************************
 *** FUNCIONES PRIVADAS AL MODULO
 ************************************************************************************************************/

/**
*	\fn      void Inicializar_Semaforo( void )
*	\brief   Inicializacion de las diferentes maquinas de estado
*	\details Amplie la descripcion
*	\author  Nahuel
*	\date    23-01-2023 18:05:23
*   \param   void
*	\return  void
*/
static void Inicializar_Semaforo( void )
{
    //!< Coloque aqui su codigo
	Tiempo = 0 ;
	tim_flag = 0;

    return ;
}

static void Inicilizar_GPIO(void)
{
	//definimos 3 pines (LEDS) como salida
	// USO P0.2,  P1.12, P0.13

	//defino a una tecla de entrada
	// USO P0.3

	//Habilito los pines GPIO del puerto 0 y 1
	SYSCON -> SYSAHBCLKCTRL0 |= SYSCON_SYSAHBCLKCTRL0_GPIO0_MASK| SYSCON_SYSAHBCLKCTRL0_GPIO0_MASK;

	// Modifidico los registros del GPIO
	//P0.2	LED ROJO
	SetDIR(0, 2, SALIDA);
	SetPINMODE_OUT(IOCON_INDEX_PIO0_2, PUSH_PULL);
	SetPIN(0, 2, APAGADO);

	//P1.12	LED AMARILLO
	SetDIR(1, 12, SALIDA);
	SetPINMODE_OUT(IOCON_INDEX_PIO1_12, PUSH_PULL);
	SetPIN(1, 12, APAGADO);

	//P0.2	LED VERDE
	SetDIR(0, 13, SALIDA);
	SetPINMODE_OUT(IOCON_INDEX_PIO0_13, PUSH_PULL);
	SetPIN(0, 13, APAGADO);

	//P0.3	BOTON
	SetDIR(0, 3, ENTRADA);
	SetPINMODE_IN(IOCON_INDEX_PIO0_3, PULL_UP);

	return ;
}

static void Inicializar_Systick(void)
{

	// el valor que cargo en RVR para que interumpa cada 1ms
	// Fclk = 12M ,   Interrupcion = 1ms
	// Valor en RVR = 12M * 1ms = 12000

	SYST_RVR = 12000 - 1; // int cada 1 ms

	ENABLE = 1;
	TICKINT = 1;
	CLKSOURCE = 1;
}


/************************************************************************************************************
 *** FUNCIONES GLOBALES AL MODULO
 ************************************************************************************************************/

/**
*	\fn      void Inicializar( void )
*	\brief   Inicializacion de las diferentes maquinas de estado
*	\details Amplie la descripcion
*	\author  Nahuel
*	\date    23-01-2023 18:05:23
*   \param   void
*	\return  void
*/
void Inicializar( void )
{
    //Coloque aqui su codigo

	Inicializar_Semaforo( );
	Inicilizar_GPIO();
	Inicializar_Systick();
	
    return ;
}

