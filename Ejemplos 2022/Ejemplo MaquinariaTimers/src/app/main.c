/**
*	\file       main.c
*	\brief      Proyecto: Semaforo_v2
*	\details    Descripcion detallada del archivo
*	\author     Fede Bua
*	\date       18-09-2021 17:26:28
*/

/************************************************************************************************************
 *** INCLUDES
 ************************************************************************************************************/

#include "AP_MDE.h"
#include "AP_Inicializacion.h"
#include "timer.h"


int main(void) {

	 Inicializar( );

	    while ( 1 )
	    {
	        MaquinaDeEstados();
	        chequear_boton();
	        TimerEvent();
	    }
	    return 1;

}

