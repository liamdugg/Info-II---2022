#ifndef INC_AP_FUNCIONESMDEE_H_
#define INC_AP_FUNCIONESMDEE_H_

/************************************************************************************************************
 *** INCLUDES GLOBALES
 ************************************************************************************************************/
#include "AP_Inicializacion.h"
/************************************************************************************************************
 *** DEFINES GLOBALES
 ************************************************************************************************************/
#define		TRUE		1
#define		FALSE		0
#define		ON			1
#define		OFF			0

/************************************************************************************************************
 *** VARIABLES GLOBALES PUBLICAS
 ************************************************************************************************************/

/************************************************************************************************************
 *** PROTOTIPO DE FUNCIONES GLOBALES
 ************************************************************************************************************/

/*-------------------------------------------- EVENTOS ----------------------------------------------------*/


/*-------------------------------------------- ACCIONES ----------------------------------------------------*/

void f_ApagarLedRojo ( void );
void f_Enviar_trama ( void );
void f_Iniciar_Timer ( uint32_t );
void f_Apagar_Timer(void);
void set_intensidad(void);
void f_LuzDimmer_ON ( void );
void f_PrenderLedRojo ( void );
void f_luzDimmer_OFF ( void );
uint8_t checksum(uint8_t *, uint8_t *);

/*------------------------------------------TEMPORIZADORES -------------------------------------------------*/


#endif /* INC_AP_FUNCIONESMDEE_H_ */
