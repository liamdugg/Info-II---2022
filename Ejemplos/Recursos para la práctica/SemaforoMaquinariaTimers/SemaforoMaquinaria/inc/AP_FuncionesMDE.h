/**
*	\file       AP_FuncionesMDE.h
*	\brief      Prototipos, defines, etc. de los Eventos y Acciones asociadas a la M de E
*	\details    Descripcion detallada del archivo
*	\author     Fede
*	\date       18-09-2021 17:26:28
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
void m_detener_timers(void);
void m_init_timer_amarillo_5s(void);
void m_init_timer_boton_2s(void);
void m_init_timer_rojo_30s(void);
void m_init_timer_verde_20s(void);
void m_limpiar_flags(void);
void m_prender_amarillo(void);
void m_prender_rojo(void);
void m_prender_verde(void);

#endif /* INC_AP_FUNCIONESMDEE_H_ */
