#ifndef INC_AP_FUNCIONESMDEE_H_
#define INC_AP_FUNCIONESMDEE_H_

/************************************************************************************************************
 *** INCLUDES GLOBALES
 ************************************************************************************************************/
#include "AP_Inicializacion.h"
#include "AP_MDE.h"
/************************************************************************************************************
 *** DEFINES GLOBALES
 ************************************************************************************************************/
#define		TRUE		1
#define		FALSE		0
#define		ON			1
#define		OFF			0

#define 	TIM1		0
#define 	TIM2		1
#define 	TIM3 		2

void f_apagarCinta(void);
void f_apagarPiston(void);
void f_apagarSistema(void);
void f_prenderCinta(void);
void f_prenderLedOn(void);
void f_prenderPiston(void);
void f_setTiempos(uint8_t *valores);
void f_startTimer(int timer);
void f_stopTimers(void);
void f_barridoTeclado(void);
uint8_t f_getSensor(void);


#endif /* INC_AP_FUNCIONESMDEE_H_ */
