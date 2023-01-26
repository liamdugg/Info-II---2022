/**
*	\file       AP_MDE.c
*	\brief      Maquina/s de Estado
*	\details    Descripcion detallada del archivo
*	\author     Fede Bua
*	\date       18-09-2021 17:26:28
*/
/************************************************************************************************************
 *** INCLUDES
 ************************************************************************************************************/
#include "AP_MDE.h"
#include "AP_FuncionesMDE.h"
/************************************************************************************************************
 *** DEFINES PRIVADOS AL MODULO
 ************************************************************************************************************/
#define		RESET		0	
//Maquina: Luces
#define		ROJO		1	// < Maquina: Luces >
#define		AMARILLO		2	// < Maquina: Luces >
#define		VERDE		3	// < Maquina: Luces >
#define		DETENIDO		4	// < Maquina: Luces >

/************************************************************************************************************
 *** MACROS PRIVADAS AL MODULO
 ************************************************************************************************************/


/************************************************************************************************************
 *** PROTOTIPO DE FUNCIONES PRIVADAS AL MODULO
 ************************************************************************************************************/
static int Luces ( int );

/************************************************************************************************************
 *** VARIABLES GLOBALES PUBLICAS
 ************************************************************************************************************/
volatile int flag_amarillo ;		//
volatile int flag_verde ;		//
volatile int flag_rojo ;		//
volatile int flag_boton ;		//
volatile int flag_boton_repetido ;		//

/************************************************************************************************************
 *** FUNCIONES PRIVADAS AL MODULO
 ************************************************************************************************************/

/**
*	\fn      static int Luces ( int Estado )
*	\brief   Coloque aqui su descripcion
*	\details Amplie la descripcion
*	\author  Fede
*	\date    18-09-2021 17:26:28
*   \param   [in] Estado: caso dentro de la maquina (estado actual)
*	\return  int : estado siguiente
*/

static int Luces ( int  Estado )
{

	static int reiniciado = 1;
    switch ( Estado )
    {

        case RESET :
            m_prender_rojo();
            m_init_timer_rojo_30s();
            m_limpiar_flags();

            Estado = ROJO;

            break;

        case ROJO :
            if ( flag_amarillo == 1 )
            {
                m_prender_amarillo();
                m_init_timer_amarillo_5s();
                m_limpiar_flags();
                reiniciado = 0;

                Estado = AMARILLO;
            }

            if ( flag_boton == 1 && reiniciado == 0)
            {
                m_detener_timers(); //CUIDADO EL ORDEN!
                m_init_timer_boton_2s();
                m_limpiar_flags();

                Estado = DETENIDO;
            }

            break;

        case AMARILLO :
            if ( flag_verde == 1 )
            {
                m_prender_verde();
                m_init_timer_verde_20s();
                m_limpiar_flags();

                Estado = VERDE;
            }

            if ( flag_boton == 1 )
            {
                m_detener_timers(); //CUIDADO EL ORDEN!
                m_init_timer_boton_2s();
                m_limpiar_flags();

                Estado = DETENIDO;
            }

            break;

        case VERDE :
            if ( flag_rojo == 1 )
            {
                m_prender_rojo();
                m_init_timer_rojo_30s();
                m_limpiar_flags();

                Estado = ROJO;
            }

            if ( flag_boton == 1 )
            {
                m_detener_timers(); //CUIDADO EL ORDEN!
                m_init_timer_boton_2s();
                m_limpiar_flags();

                Estado = DETENIDO;
            }

            break;

        case DETENIDO :
            if ( flag_boton == 1 && flag_boton_repetido == 1 )
            {
                m_limpiar_flags();
                m_init_timer_rojo_30s();
                m_prender_rojo();
                reiniciado = 1;

                Estado = ROJO;
            }

            break;

        default:
            Estado = RESET ;
            break;

    }
    return Estado ;
}

/************************************************************************************************************
 *** FUNCIONES GLOBALES AL MODULO
 ************************************************************************************************************/

/**
*	\fn      void MaquinaDeEstados ( void )
*	\brief   Coloque aqui su descripcion
*	\details Amplie la descripcion
*	\author  Fede
*	\date    18-09-2021 17:26:28
*   \param   void
*	\return  void
*/
void MaquinaDeEstados ( void )
{
    static int estados_Luces = RESET;

    // Coloque su codigo aqui

    estados_Luces = Luces( estados_Luces );


    return ;
}

