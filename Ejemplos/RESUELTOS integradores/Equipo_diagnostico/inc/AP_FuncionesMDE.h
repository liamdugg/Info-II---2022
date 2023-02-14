/**
*	\file       AP_FuncionesMDE.h
*	\brief      Prototipos, defines, etc. de los Eventos y Acciones asociadas a la M de E
*	\details    Descripcion detallada del archivo
*	\author     Nahuel
*	\date       13-02-2023 22:06:42
*/

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
#define		ON		1
#define		OFF		0

#define	Mod		0
#define	Temp	1
#define	Hum		2
#define	Tor		3
#define	Rem		4
#define	Rest	5
#define	Vari	6
#define	Crest	7
#define	Sort	8
#define	Yli		9
/************************************************************************************************************
 *** VARIABLES GLOBALES PUBLICAS
 ************************************************************************************************************/

/************************************************************************************************************
 *** PROTOTIPO DE FUNCIONES GLOBALES
 ************************************************************************************************************/

/*-------------------------------------------- EVENTOS ----------------------------------------------------*/

int s_get_TeclaTest ( void );

/*-------------------------------------------- ACCIONES ----------------------------------------------------*/
void cargar_buff_MOD(int parametros);
void f_Analizar_Trama ( void );
void f_Analizar_respuesta ( void );
void f_Enviar_Trama ( uint8_t tipo );
void f_Informe ( int x, char *s1, char *s2);
void Verificar_Informe(void);
void f_Iniciar_Timer ( int tiempo );
void f_Iniciar_Timer10s (int tiempo );
void f_Iniciar_timer_ms ( int tiempo );
void f_Stop_timer ( void );

/*------------------------------------------TEMPORIZADORES -------------------------------------------------*/


#endif /* INC_AP_FUNCIONESMDEE_H_ */
