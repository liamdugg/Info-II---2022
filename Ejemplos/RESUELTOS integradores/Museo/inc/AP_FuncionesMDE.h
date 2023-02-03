/**
*	\file       AP_FuncionesMDE.h
*	\brief      Prototipos, defines, etc. de los Eventos y Acciones asociadas a la M de E
*	\details    Descripcion detallada del archivo
*	\author     Liam
*	\date       01-02-2023 21:14:08
*/

#ifndef INC_AP_FUNCIONESMDEE_H_
#define INC_AP_FUNCIONESMDEE_H_

#include "AP_Inicializacion.h"

#define	TRUE			1
#define	FALSE			0
#define	ON				1
#define	OFF				0

#define	TRAMA_BAL		0
#define	TRAMA_CAM		1

#define ALARMA_S		0
#define ALARMA_A		1

#define PIN_ALARMA_S	0,10
#define PIN_ALARMA_A	0,11

#define TIM_BAL			0
#define	TIM_CAM			1
#define TIM_ALARMA		2



/*-------------------------------------------- ACCIONES ----------------------------------------------------*/

void f_activarAlarma(uint8_t alarma);
void f_apagarAlarma(uint8_t alarma);
void f_enviarTrama(uint8_t tipoTrama);
void f_prenderCamara(void);
void f_startTimer(uint8_t timer, uint32_t tiempo );
void f_stopTimer(uint8_t timer);

/*------------------------------------------TEMPORIZADORES -------------------------------------------------*/


#endif /* INC_AP_FUNCIONESMDEE_H_ */
