/**
*	\file       AP_Inicializacion.c
*	\brief      Funciones de inicializacion de todo el proyecto
*	\details    Descripcion detallada del archivo
*	\author     Liam
*	\date       01-02-2023 21:14:08
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
static void Inicializar_Museo( void ) ;
static void Inicializar_SensorIR( void ) ;
static void Inicializar_Balanza( void ) ;

/************************************************************************************************************
 *** FUNCIONES PRIVADAS AL MODULO
 ************************************************************************************************************/

/**
*	\fn      void Inicializar_Museo( void )
*	\brief   Inicializacion de las diferentes maquinas de estado
*	\details Amplie la descripcion
*	\author  Liam
*	\date    01-02-2023 21:14:08
*   \param   void
*	\return  void
*/
static void Inicializar_Museo( void )
{
    //!< Coloque aqui su codigo
	tramaOn = 0 ;
	flagIR = 0 ;

    return ;
}

/**
*	\fn      void Inicializar_SensorIR( void )
*	\brief   Inicializacion de las diferentes maquinas de estado
*	\details Amplie la descripcion
*	\author  Liam
*	\date    01-02-2023 21:14:08
*   \param   void
*	\return  void
*/
static void Inicializar_SensorIR( void )
{
    //!< Coloque aqui su codigo
	flagIR = 0 ;
	apagarAlarma = 0 ;
	tiempoS = 0 ;

    return ;
}

/**
*	\fn      void Inicializar_Balanza( void )
*	\brief   Inicializacion de las diferentes maquinas de estado
*	\details Amplie la descripcion
*	\author  Liam
*	\date    01-02-2023 21:14:08
*   \param   void
*	\return  void
*/
static void Inicializar_Balanza( void )
{
    //!< Coloque aqui su codigo
	tramaOn = 0 ;
	tiempoBalanza = 0 ;
	errorBalanza = 0 ;
	tiempoCamara = 0 ;
	apagarAlarma = 0 ;

    return ;
}

/************************************************************************************************************
 *** FUNCIONES GLOBALES AL MODULO
 ************************************************************************************************************/

/**
*	\fn      void Inicializar( void )
*	\brief   Inicializacion de las diferentes maquinas de estado
*	\details Amplie la descripcion
*	\author  Liam
*	\date    01-02-2023 21:14:08
*   \param   void
*	\return  void
*/
void Inicializar( void )
{
    //Coloque aqui su codigo


	Inicializar_Museo( );

	Inicializar_SensorIR( );

	Inicializar_Balanza( );

	
    return ;
}

