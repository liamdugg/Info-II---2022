#include "main.h"

volatile 	uint32_t Tmr_Run[ N_TIMERS ];
volatile 	uint8_t  TMR_Events[ N_TIMERS ];
void 	 	(* TMR_handlers [N_TIMERS]) (void);
volatile 	uint8_t  TMR_StandBy[ N_TIMERS ];
volatile 	uint8_t  Tmr_Base[ N_TIMERS ];


/**
	\fn void Timer_Check(void)
	\brief Decremento periodico de los contadores
 	\details Decrementa los contadores de los timers en ejecucion. Debe ser llamada periodicamente con la base de tiempos
	\return void
*/
void AnalizarTimers(void)
{
	uint32_t i;
	for(i=0; i< N_TIMERS ; i++)
	{
		if(Tmr_Run[ i ])
		{
			if ( !TMR_StandBy[ i ] )
			{
				Tmr_Run[ i ]--;
				if(!Tmr_Run[ i ])
					TMR_Events[ i ] = 1;
			}
		}
	}
}

/**
	\fn void Timer_Event(void)
	\brief Chequeo de timers vencidos
 	\details Llama a los callbacks de los timers vencidos. Debe llamarse desde el lazo principal del programa
	\return void
*/
void TimerEvent(void)
{
	uint8_t i;
	for( i=0 ; i < N_TIMERS ; i++ )
	{
		if(TMR_Events[ i ])
		{
			TMR_handlers[ i ]( );
			TMR_Events[ i ] = 0;
		}
	}
}

/***********************************************************************************************************************************
 *** DEFINES PRIVADOS AL MODULO
 **********************************************************************************************************************************/
//SysTick_Handler configurado con 12000 ticks a 12MHz --> Interrumpe cada 1ms
#define 	DECIMAS			100 //100 veces 1ms = 100ms = 1 decima de segundo
#define 	SEGUNDOS		10 //1 segundo = 10 decimas de segundos
#define 	MINUTOS			60 //60 segundos = 1 minutos

/***********************************************************************************************************************************
 *** FUNCIONES GLOBALES AL MODULO
 **********************************************************************************************************************************/

/**
	\fn void TimerStart(uint8_t event, timer_t t, void (*handler)(void))
	\brief Inicia un timer
 	\details Inicia el timer \a e al transcurrir el tiempo especificado por \a t se llama a la funcion apuntada por \a handler
 	\param [in] event Numero de evento entre 0 y 31
 	\param [in] t Tiempo del evento. Dependiente de la base de tiempos
 	\param [in] handler Callback del evento
	\return void
*/
void TimerStart(uint8_t event, uint32_t time, Timer_Handler handler , uint8_t base )
{
	switch ( base )
	{
		case DEC:
			time *= DECIMAS;
			break;
		case SEG:
			time *= ( SEGUNDOS * DECIMAS );
			break;
		case MINU:
			time *= ( MINUTOS * SEGUNDOS * DECIMAS );
			break;
	}

	Tmr_Base[event] = base;

	if(time != 0)	//el tiempo no es 0, lo cargo
	{
		Tmr_Run[event] = time;
		TMR_Events[event] = 0;
	}
	else	//el tiempo es cero, el timer vence automáticamente
	{
		Tmr_Run[event] = 0;
		TMR_Events[event] = 1;
	}
	TMR_handlers[event] = handler;
}

/**
	\fn void SetTimer( uint8_t event , timer_t t )
	\brief Inicia un timer
 	\details Reinicia el timer con el valor t (no lo resetea)
 	\param [in] event Numero de evento entre 0 y 31
 	\param [in] t Tiempo del evento. Dependiente de la base de tiempos
 	\return void
*/
void SetTimer( uint8_t event, uint32_t time )
{
	switch ( Tmr_Base[event] )
	{
		case DEC:
			time *= DECIMAS;
			break;
		case SEG:
			time *= ( SEGUNDOS * DECIMAS );
			break;
		case MINU:
			time *= ( MINUTOS * SEGUNDOS * DECIMAS );
			break;
	}
	Tmr_Run[event] = time;
}

/**
	\fn  GetTimer( uint8_t event )
	\brief Toma el valor al vuelo del timer en cuestion
 	\details Lee el timer
 	\param [in] event Numero de evento entre 0 y 31
 	\return valor del timer
*/
uint32_t GetTimer( uint8_t event )
{
	uint32_t time = Tmr_Run[event];

	switch ( Tmr_Base[event] )
	{
		case DEC:
			time /= DECIMAS;
			break;
		case SEG:
			time /= ( SEGUNDOS * DECIMAS );
			break;
		case MINU:
			time /= ( MINUTOS * SEGUNDOS * DECIMAS );
			break;
	}
	return time;
}

/**
	\fn  StandByTimer( uint8_t event , uint8_t accion)
	\brief Detiene/Arranca el timer, NO lo resetea
 	\details lo pone o lo saca de stand by
 	\param [in] event Numero de evento entre 0 y 31
 	\param [in] accion RUN lo arranca, PAUSE lo pone en stand by
 	\return void
*/
void StandByTimer( uint8_t event , uint8_t accion)
{
	TMR_StandBy[ event ] = accion;
}

/**
	\fn void Timer_Stop(Eventos e)
	\brief Detiene un timer
 	\details Detiene el timer \a e
 	\param [in] e Numero de evento entre 0 y 31
	\return void
*/
void TimerStop(uint8_t event)
{
	Tmr_Run[ event ] = 0;
	TMR_Events[ event ] = 0;
	TMR_handlers[ event ] = NULL;
	Tmr_Base[ event ] = 0;
	TMR_StandBy[ event ] = RUN;
}

/**
	\fn void Timer_Close(void)
	\brief Detiene los timers
 	\details Detiene todos los timers
	\return void
*/
void TimerClose(void)
{
	uint32_t i;

	for( i=0 ; i < N_TIMERS ; i++ )
		TimerStop( i );
}


extern volatile uint16_t delay;

uint32_t SysTickInic ( uint32_t ticks )
{
	if ((ticks - 1UL) > 0xFFFFFF)
    {
      return (1UL);                                                   /* Reload value impossible */
    }
	SYST_RVR = (uint32_t)(ticks - 1UL);
	SYST_CVR = 0;

	CLKSOURCE = 1;
	ENABLE = 1;
	TICKINT = 1;

	return (0UL);
}

/*
 * @brief   ISR de SysTick
 */
void SysTick_Handler(void)
{
	AnalizarTimers();
}
