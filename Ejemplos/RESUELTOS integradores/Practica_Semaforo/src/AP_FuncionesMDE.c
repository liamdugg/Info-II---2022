/**
*	\file       AP_FuncionesMDE.c
*	\brief      Funciones de Eventos y Acciones asociadas a las Maquinas de estados
*	\details    Descripcion detallada del archivo
*	\author     Nahuel
*	\date       23-01-2023 18:05:23
*/

/************************************************************************************************************
 *** INCLUDES
 ************************************************************************************************************/
#include "AP_FuncionesMDE.h"
#include "Fun_GPIO.h"


/************************************************************************************************************
 *** DEFINES PRIVADOS AL MODULO
 ************************************************************************************************************/

extern int Tiempo;
/************************************************************************************************************
 *** VARIABLES GLOBALES PUBLICAS
 ************************************************************************************************************/

/************************************************************************************************************
 *** FUNCIONES GLOBALES AL MODULO
 ************************************************************************************************************/

/*-------------------------------------------- EVENTOS ----------------------------------------------------*/

/*-------------------------------------------- ACCIONES ----------------------------------------------------*/
	//definimos 3 pines (LEDS) como salida
	// USO P0.2 amariilo,  P1.12 rojo, P0.13 verde

void m_Iniciar_Timer(uint32_t time)
{
	Tiempo = time;
}

void m_Prender_Amarillo()
{
	//USO P0.2 amarillo
	SetPIN(0, 2,  ENCENDIDO);
	SetPIN(1, 12, APAGADO);
	SetPIN(0, 13, APAGADO);

}

void m_Prender_Rojo()
{
	SetPIN(0, 2,  APAGADO);
	SetPIN(1, 12, ENCENDIDO);
	SetPIN(0, 13, APAGADO);
}

void m_Prender_Verde()
{
	SetPIN(0, 2,  APAGADO);
	SetPIN(1, 12, APAGADO);
	SetPIN(0, 13, ENCENDIDO);
}

void m_Apagar_Leds()
{
	SetPIN(0, 2,  APAGADO);
	SetPIN(1, 12, APAGADO);
	SetPIN(0, 13, APAGADO);
}

//defino a una tecla de entrada
// USO P0.3
uint32_t Estado_Tecla()
{
	uint32_t valor = GetPIN(0, 3);
	return valor;
}



/*------------------------------------------TEMPORIZADORES -------------------------------------------------*/

