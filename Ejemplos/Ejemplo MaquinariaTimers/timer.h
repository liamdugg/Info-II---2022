/*
 * timer.h
 *
 *  Created on: 16 ago. 2021
 *      Author: socco
 */

#ifndef TIMER_H_
#define TIMER_H_


#include "LPC845.h"

uint32_t SysTickInic ( uint32_t ticks );



#ifndef 	NULL
#define 	NULL				(( void *) 0)
#endif

/***********************************************************************************************************************************
 *** DEFINES GLOBALES
 **********************************************************************************************************************************/
#define 	N_TIMERS		30

/***********************************************************************************************************************************
 *** MACROS GLOBALES
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** TIPO DE DATOS GLOBALES
 **********************************************************************************************************************************/
typedef void (*Timer_Handler)(void);

/***********************************************************************************************************************************
 *** VARIABLES GLOBALES
 **********************************************************************************************************************************/
extern volatile 	uint32_t Tmr_Run[ N_TIMERS ];
extern volatile 	uint8_t  TMR_Events[ N_TIMERS ];
extern void 	 	(* TMR_handlers [N_TIMERS]) (void);
extern volatile 	uint8_t  TMR_StandBy[ N_TIMERS ];
extern volatile 	uint8_t  Tmr_Base[ N_TIMERS ];

/***********************************************************************************************************************************
 *** PROTOTIPOS DE FUNCIONES GLOBALES
 **********************************************************************************************************************************/
void AnalizarTimers(void);
void TimerEvent(void);


/***********************************************************************************************************************************
 *** DEFINES GLOBALES
 **********************************************************************************************************************************/
#define 	DEC			0
#define 	SEG			1
#define 	MINU		2

#define 	RUN			0
#define 	PAUSE		1

/***********************************************************************************************************************************
 *** MACROS GLOBALES
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** TIPO DE DATOS GLOBALES
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** VARIABLES GLOBALES
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** PROTOTIPOS DE FUNCIONES GLOBALES
 **********************************************************************************************************************************/

void TimerStart(uint8_t event, uint32_t time, Timer_Handler handler , uint8_t base );
void SetTimer( uint8_t event, uint32_t time );
uint32_t GetTimer( uint8_t event );
void StandByTimer( uint8_t event , uint8_t accion);
void TimerStop(uint8_t event);
void TimerClose(void);




#endif /* TIMER_H_ */
