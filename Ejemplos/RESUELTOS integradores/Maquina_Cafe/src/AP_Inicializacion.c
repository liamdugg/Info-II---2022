/************************************************************************************************************
 *** INCLUDES
 ************************************************************************************************************/
#include "AP_Inicializacion.h"
#include "AP_MDE.h"
#include "Regs_LPC845.h"
#include "Fun_GPIO.h"
#include "AP_FuncionesMDE.h"

static void Inicializar_maquinaCafe( void ) ;

static void Inicializar_maquinaCafe( void )
{
    //!< Coloque aqui su codigo
	moneda = 0;
	eleccion = 0;
    return ;
}

void Init_Systick(void){

	SYST_RVR = 12000-1;
	CLKSOURCE = 1;
	TICKINT = 1;
	ENABLE = 1;
}

void Init_GPIO(void){

	SYSCON->SYSAHBCLKCTRL0 |= SYSCON_SYSAHBCLKCTRL0_GPIO0_MASK;

	PINTSEL_0 |= (1 << 0);	// Selecciono el pin GPIO0,0 para asociarlo a PININT0
	ISEL &= ~(1 << 0);		// Configuro la interrupcion como flanco
	ENRL |= (1 << 0);		// Configuro el flanco como rising edge
	ISER0 |= (1 << 24);		// Habilito INTS en NVIC para el PININT0

	SetDIR(DEV_COIN_PORT, DEV_COIN_PIN, SALIDA);
	SetPINMODE_OUT(IOCON_INDEX_PIO0_1, PUSH_PULL);
	SetPIN(DEV_COIN_PORT,DEV_COIN_PIN, OFF);

	SetDIR(IN_COIN_PORT, IN_COIN_PORT, ENTRADA);
	SetPINMODE_IN(IOCON_INDEX_PIO0_0, PULL_DOWN);
	SetPIN(IN_COIN_PORT, IN_COIN_PORT, 1);  // con 1 apagado, por ser pullup
}

void Inicializar( void )
{

	Init_Systick();
	Init_GPIO();
	Inicializar_maquinaCafe( );
    return ;
}

