/************************************************************************************************************
 *** INCLUDES
 ************************************************************************************************************/
#include "AP_FuncionesMDE.h"
#include "AP_Inicializacion.h"
#include <string.h>
/************************************************************************************************************
 *** DEFINES PRIVADOS AL MODULO
 ************************************************************************************************************/
#define	LED_RED		0,0
#define	SENSOR		0,1


/************************************************************************************************************
 *** VARIABLES GLOBALES PUBLICAS
 ************************************************************************************************************/
uint32_t dato_adc;
uint32_t Tiempo;
int stop;

extern int FlagTim;
extern int SensorProx;
extern int error;

extern uint8_t nombres[20];
extern uint8_t pasaporte[MAX_NUMP];

extern int cant; // nombres

/************************************************************************************************************
 *** FUNCIONES GLOBALES AL MODULO
 ************************************************************************************************************/

/*-------------------------------------------- EVENTOS ----------------------------------------------------*/

/*-------------------------------------------- ACCIONES ----------------------------------------------------*/

void f_ApagarLedRojo ( void )
{
	SetPIN(LED_RED, OFF);

    return ;
}



void f_Enviar_trama ( void )
{
    Transmitir("$", 1);
    Transmitir(nombres,cant);
    Transmitir(pasaporte,MAX_NUMP);
    Transmitir("&", 1);

    return ;
}



void f_Iniciar_Timer ( uint32_t time )
{
    Tiempo = time;
	stop = 0;
    return ;
}

void f_Apagar_Timer(void)
{
	stop = 1;
	Tiempo = 0;
}

void set_intensidad(void)
{
    uint32_t porcentaje;
    porcentaje = dato_adc*100/4095;

    PWM &= ~(0x7F << 3);

    PWM |= ((uint8_t)porcentaje << 3);
}

void f_LuzDimmer_ON ( void )
{
	set_intensidad();
    return ;
}



void f_PrenderLedRojo ( void )
{
	SetPIN(LED_RED, ON);
    return ;
}



void f_luzDimmer_OFF ( void )
{
    PWM &= ~(0x7F << 3);
    return ;
}

uint8_t checksum(uint8_t *nombres, uint8_t *numID)
{
	uint8_t sum=0;
	for(int i = 0; i<strlen((char *)nombres);i++)
		sum += nombres[i];

	for(int i = 0; i<strlen((char *)numID);i++)
			sum += numID[i];

	return sum;
}

void ADC_SEQA_IRQHandler(void)
{
    dato_adc = (uint32_t)(ADC_DAT[1] >> 4);
}

void SysTick_Handler(void)
{
	if(!stop)
	{
		if(Tiempo != 0)
			Tiempo--;
		else
			FlagTim = 1;
	}

	if(!error)
	{
		if(GetPIN(SENSOR))
		{
			SensorProx = 1;
			f_LuzDimmer_ON();
		}
		else
		{
			SensorProx = 0;
			f_luzDimmer_OFF();
		}
	}
}


/*------------------------------------------TEMPORIZADORES -------------------------------------------------*/

