#ifndef TIMER_H_
#define TIMER_H_

uint32_t SysTickInic (uint32_t ticks);

#ifndef 	NULL
#define 	NULL	(( void *) 0)
#endif

#define 	N_TIMERS		30

typedef void (*Timer_Handler)(void);

extern volatile 	uint32_t Tmr_Run[ N_TIMERS ];
extern volatile 	uint8_t  TMR_Events[ N_TIMERS ];
extern void 	 	(* TMR_handlers [N_TIMERS]) (void);
extern volatile 	uint8_t  TMR_StandBy[ N_TIMERS ];
extern volatile 	uint8_t  Tmr_Base[ N_TIMERS ];

void AnalizarTimers(void);
void TimerEvent(void);

#define 	DEC			0
#define 	SEG			1
#define 	MINU		2
#define 	RUN			0
#define 	PAUSE		1

void TimerStart(uint8_t event, uint32_t time, Timer_Handler handler , uint8_t base );
void SetTimer( uint8_t event, uint32_t time );
uint32_t GetTimer( uint8_t event );
void StandByTimer( uint8_t event , uint8_t accion);
void TimerStop(uint8_t event);
void TimerClose(void);

#endif /* TIMER_H_ */
