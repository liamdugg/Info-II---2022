/**
*	\file       AP_FuncionesMDE.h
*	\brief      Prototipos, defines, etc. de los Eventos y Acciones asociadas a la M de E
*	\details    Descripcion detallada del archivo
*	\author     Nahuel
*	\date       26-01-2023 18:02:26
*/

#ifndef INC_AP_FUNCIONESMDEE_H_
#define INC_AP_FUNCIONESMDEE_H_

/************************************************************************************************************
 *** INCLUDES GLOBALES
 ************************************************************************************************************/

/************************************************************************************************************
 *** DEFINES GLOBALES
 ************************************************************************************************************/
#define		TRUE		1
#define		FALSE		0
#define		ON		1
#define		OFF		0

/************************************************************************************************************
 *** VARIABLES GLOBALES PUBLICAS
 ************************************************************************************************************/

/************************************************************************************************************
 *** PROTOTIPO DE FUNCIONES GLOBALES
 ************************************************************************************************************/
#include <stdint.h>
/*-------------------------------------------- EVENTOS ----------------------------------------------------*/

int s_SetTemp ( void );

/*-------------------------------------------- ACCIONES ----------------------------------------------------*/

void m_Apagar_Alarma(void);
void m_Enviar_Trama_Temp();
uint8_t parseo_temp(int tipo, int sensor);
void m_Enviar_Trama_Temp_sens();
void f_Enviar_trama_set ( int cant);
void f_Enviar_trama_set_sens( int cant );
void m_Iniciar_timer();
void m_Prender_Alarma();


/*------------------------------------------TEMPORIZADORES -------------------------------------------------*/


#endif /* INC_AP_FUNCIONESMDEE_H_ */
