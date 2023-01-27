/**
*	\file       AP_Inicializacion.c
*	\brief      Funciones de inicializacion de todo el proyecto
*	\details    Descripcion detallada del archivo
*	\author     Nahuel
*	\date       26-01-2023 18:02:26
*/

/************************************************************************************************************
 *** INCLUDES
 ************************************************************************************************************/
#include "AP_Inicializacion.h"
#include "AP_MDE.h"
#include "uart.h"
#include "Fun_GPIO.h"
#include "adc.h"
#include "swm.h"

/************************************************************************************************************
 *** DEFINES PRIVADOS AL MODULO
 ************************************************************************************************************/

/************************************************************************************************************
 *** PROTOTIPO DE FUNCIONES PRIVADAS AL MODULO
 ************************************************************************************************************/
static void Inicializar_Sensado_Temp( void ) ;

/************************************************************************************************************
 *** FUNCIONES PRIVADAS AL MODULO
 ************************************************************************************************************/

/**
*	\fn      void Inicializar_Sensado_Temp( void )
*	\brief   Inicializacion de las diferentes maquinas de estado
*	\details Amplie la descripcion
*	\author  Nahuel
*	\date    26-01-2023 18:02:26
*   \param   void
*	\return  void
*/
static void Inicializar_Sensado_Temp( void )
{
    //!< Coloque aqui su codigo
	Flag_tim = 0 ;
	Dato_recibido = 0 ;
	TempOk = 0 ;

    return ;
}

static void Inicializar_GPIO(void)
{
	// Habilito el clock para GPIO canal 0
	SYSCON->SYSAHBCLKCTRL0 |= (1<<6);

	//Uso al PIN0_0 como Salida (Alarma)

	SetDIR(0, 0, SALIDA);
	SetPINMODE_OUT(IOCON_INDEX_PIO0_0, PUSH_PULL);
	SetPIN(0, 0, 0);
}

static void Inicializar_ADC(void)
{
    // Energizo el ADC
    SYSCON->PDRUNCFG &= ~(1<<4);

    // Habilito el Cloclk para el ADC
    SYSCON->SYSAHBCLKCTRL0 |= (1<<24);

    // Habilito el Cloclk para la SWM
    SYSCON->SYSAHBCLKCTRL0 |= (1<<7);

    // Habilito un pin para el adc
    // Canal 0 del ADC		Port 0 Pin 7
    // Canal 1 del ADC		PIO0_6
    // Canal 2 del ADC		PIO0_14

    SWM_PINENABLE0 &= ~(1<<14);
    SWM_PINENABLE0 &= ~(1<<15);
    SWM_PINENABLE0 &= ~(1<<16);

    // Apago el Cloclk para la SWM ya que no lo voy usar otra vez
    SYSCON->SYSAHBCLKCTRL0 &= ~(1<<7);

    // quiero muestrear a 100kHz = freq
    // 30MHz/DIVISOR = freq x 25
    // DIVISOR = 30MHz / 2,5MHz
    // DIVISOR = 12 --> 1100
    ADC_CTRL &= ~(0xff); // limpio el registro control
    ADC_CTRL |= (12);

    // Habilito el modo continuo (BURST)
    // ADC_CTRL |= (1<<27);

    // Seleccione cual de los canales va a ser muestreado por el ADC
    ADC_SEQA_CTRL |= (0xFFF); // limpio el registro control
    ADC_SEQA_CTRL &= ~(1<<0); // selecciono el canal 0

    // Selecciono para que la interrupcion se ejecute al muestrear todos los canales
    ADC_SEQA_CTRL |= (1<<0);

    // Habilito las interrupciones para la secuencia A del ADC
    ADC_SEQA_CTRL |= (1<<31);

    // Habilito en el NVIC las interrupciones del ADC
    ISER0 |= (1<<16);
}

static void Inicializar_UART(void)
{
	UART_Init();
}

void Inicializacion_Systick(void)
{
	SYST_RVR = 12000-1; // 1ms a 12MHz

	ENABLE = 1;
	CLKSOURCE = 0;
	TICKINT = 1;
}


/************************************************************************************************************
 *** FUNCIONES GLOBALES AL MODULO
 ************************************************************************************************************/

/**
*	\fn      void Inicializar( void )
*	\brief   Inicializacion de las diferentes maquinas de estado
*	\details Amplie la descripcion
*	\author  Nahuel
*	\date    26-01-2023 18:02:26
*   \param   void
*	\return  void
*/
void Inicializar( void )
{
    //Coloque aqui su codigo
	Inicializar_Sensado_Temp( );
	Inicializar_UART();
	Inicializar_GPIO();
	Inicializacion_Systick();
	Inicializar_ADC();
	
    return ;
}

