#include "Regs_LPC845.h"
#include "timer.h"

volatile 	uint32_t Tmr_Run[ N_TIMERS ];
volatile 	uint8_t  TMR_Events[ N_TIMERS ];
void 	 	(* TMR_handlers [N_TIMERS]) (void);
volatile 	uint8_t  TMR_StandBy[ N_TIMERS ];
volatile 	uint8_t  Tmr_Base[ N_TIMERS ];

// Decrementa los contadores de los timers en ejecucion. Debe ser llamada periodicamente con la base de tiempos
void AnalizarTimers(void){

	uint32_t i;
	for(i=0; i< N_TIMERS ; i++){
		if(Tmr_Run[i]){
			if (!TMR_StandBy[i]){
				Tmr_Run[ i ]--;
				if(!Tmr_Run[ i ])
					TMR_Events[ i ] = 1;
			}
		}
	}
}

// Llama a los callbacks de los timers vencidos. Debe llamarse desde el lazo principal del programa
void TimerEvent(void){

	uint8_t i;
	for(i=0; i < N_TIMERS; i++){
		if(TMR_Events[i]){
			TMR_handlers[i]();
			TMR_Events[i] = 0;
		}
	}
}

// SysTick_Handler configurado con 12000 ticks a 12MHz --> Interrumpe cada 1ms
#define 	DECIMAS			100 //100 veces 1ms = 100ms = 1 decima de segundo
#define 	SEGUNDOS		10 //1 segundo = 10 decimas de segundos
#define 	MINUTOS			60 //60 segundos = 1 minutos

// Inicializa un timer
void TimerStart(uint8_t event, uint32_t time, Timer_Handler handler , uint8_t base ){

	switch (base){
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

	if(time != 0){	//el tiempo no es 0, lo cargo	
		Tmr_Run[event] = time;
		TMR_Events[event] = 0;
	}

	else{	//el tiempo es cero, el timer vence automáticamente
		Tmr_Run[event] = 0;
		TMR_Events[event] = 1;
	}

	TMR_handlers[event] = handler;
}

// Reinicia el timer con el valor time (no lo resetea)
void SetTimer( uint8_t event, uint32_t time ){

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

//Devuelve el valor al vuelo del timer en cuestion
uint32_t GetTimer(uint8_t event){

	uint32_t time = Tmr_Run[event];

	switch (Tmr_Base[event]){
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

// Detiene o Arranca el timer, NO lo resetea
void StandByTimer( uint8_t event , uint8_t accion){
	TMR_StandBy[event] = accion;
}

// Detiene el timer
void TimerStop(uint8_t event){
	Tmr_Run[event] = 0;
	TMR_Events[event] = 0;
	TMR_handlers[event] = NULL;
	Tmr_Base[event] = 0;
	TMR_StandBy[event] = RUN;
}

// Detiene todos los timers
void TimerClose(void){

	uint32_t i;
	
	for(i=0; i < N_TIMERS; i++)
		TimerStop(i);
}

extern volatile uint16_t delay;

uint32_t SysTickInic(uint32_t ticks){

	if ((ticks - 1UL) > 0xFFFFFF)
		return (1UL); // Reload value impossible

	SYST_RVR = (uint32_t)(ticks - 1UL);
	SYST_CVR = 0;
	CLKSOURCE = 1;
	ENABLE = 1;
	TICKINT = 1;

	return (0UL);
}

/*void SysTick_Handler(void){
	AnalizarTimers();
}
*/
