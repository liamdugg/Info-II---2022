/**
*	\file       AP_Inicializacion.c
*	\brief      Funciones de inicializacion de todo el proyecto
*	\details    Descripcion detallada del archivo
*	\author     Fede
*	\date       18-09-2021 17:26:28
*/

/************************************************************************************************************
 *** INCLUDES
 ************************************************************************************************************/
#include "AP_Inicializacion.h"
#include "AP_MDE.h"

/************************************************************************************************************
 *** DEFINES PRIVADOS AL MODULO
 ************************************************************************************************************/

/************************************************************************************************************
 *** PROTOTIPO DE FUNCIONES PRIVADAS AL MODULO
 ************************************************************************************************************/
static void Inicializar_Luces( void ) ;

/************************************************************************************************************
 *** FUNCIONES PRIVADAS AL MODULO
 ************************************************************************************************************/

/**
*	\fn      void Inicializar_Luces( void )
*	\brief   Inicializacion de las diferentes maquinas de estado
*	\details Amplie la descripcion
*	\author  Fede
*	\date    18-09-2021 17:26:28
*   \param   void
*	\return  void
*/
static void Inicializar_Luces( void )
{
    //!< Coloque aqui su codigo
	flag_amarillo = 0 ;
	flag_boton = 0 ;
	flag_verde = 0 ;
	flag_rojo = 0 ;
	flag_boton_repetido = 0 ;

    return ;
}

/************************************************************************************************************
 *** FUNCIONES GLOBALES AL MODULO
 ************************************************************************************************************/

/**
*	\fn      void Inicializar( void )
*	\brief   Inicializacion de las diferentes maquinas de estado
*	\details Amplie la descripcion
*	\author  Fede
*	\date    18-09-2021 17:26:28
*   \param   void
*	\return  void
*/
void Inicializar( void )
{
	inicializacion_hw(); //Drivers
	Inicializar_Luces( ); //Buffers
    return;
}

