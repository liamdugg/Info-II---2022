/**
*	\file       AP_MDE.c
*	\brief      Maquina/s de Estado
*	\details    Descripcion detallada del archivo
*	\author     Liam
*	\date       01-02-2023 21:14:08
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
//Maquina: Museo
#define		REPOSO		1	// < Maquina: Museo >
#define		ON		2	// < Maquina: Museo >
#define		INFRAROJO		3	// < Maquina: Museo >

//Maquina: SensorIR
#define		REPOSO		1	// < Maquina: SensorIR >
#define		ALARMA_S		2	// < Maquina: SensorIR >
#define		ALARMA_A		3	// < Maquina: SensorIR >

//Maquina: Balanza
#define		Reposo		1	// < Maquina: Balanza >
#define		MIDIENDO		2	// < Maquina: Balanza >
#define		ERROR		3	// < Maquina: Balanza >
#define		CAMARA		4	// < Maquina: Balanza >

/************************************************************************************************************
 *** MACROS PRIVADAS AL MODULO
 ************************************************************************************************************/

/************************************************************************************************************
 *** PROTOTIPO DE FUNCIONES PRIVADAS AL MODULO
 ************************************************************************************************************/
static int Museo ( int );
static int SensorIR ( int );
static int Balanza ( int );

/************************************************************************************************************
 *** VARIABLES GLOBALES PUBLICAS
 ************************************************************************************************************/
int tramaOn ;		//
int flagIR ;		//
int apagarAlarma ;		//
int tiempoS ;		//
int tiempoBalanza ;		//
int errorBalanza ;		//
int tiempoCamara ;		//

/************************************************************************************************************
 *** FUNCIONES PRIVADAS AL MODULO
 ************************************************************************************************************/

/**
*	\fn      static int Museo ( int Estado )
*	\brief   Coloque aqui su descripcion
*	\details Amplie la descripcion
*	\author  Liam
*	\date    01-02-2023 21:14:08
*   \param   [in] Estado: caso dentro de la maquina (estado actual)
*	\return  int : estado siguiente
*/

static int Museo ( int  Estado )
{
    switch ( Estado )
    {

        case RESET :

            Estado = REPOSO;

            break;

        case REPOSO :
            if ( tramaOn == 1 )
            {
                f_configSistema();

                Estado = ON;
            }

            break;

        case ON :
            if ( flagIR == 1 )
            {

                Estado = INFRAROJO;
            }

            break;

        case INFRAROJO :
            if ( flagIR == 0 )
            {

                Estado = ON;
            }

            break;

        default:
            Estado = RESET ;
            break;

    }
    return Estado ;
}

/**
*	\fn      static int SensorIR ( int Estado )
*	\brief   Coloque aqui su descripcion
*	\details Amplie la descripcion
*	\author  Liam
*	\date    01-02-2023 21:14:08
*   \param   [in] Estado: caso dentro de la maquina (estado actual)
*	\return  int : estado siguiente
*/

static int SensorIR ( int  Estado )
{
    switch ( Estado )
    {

        case RESET :

            Estado = REPOSO;

            break;

        case REPOSO :
            if ( flagIR == 1 )
            {
                f_activarAlarmaS();
                f_startTimer();

                Estado = ALARMA_S;
            }

            break;

        case ALARMA_S :
            if ( apagarAlarma == 1 )
            {
                apagarAlarma = 0;
                flagIR = 0;
                f_stopTimer();
                f_apagarAlarmaS();

                Estado = REPOSO;
            }

            if ( tiempoS == 0 )
            {
                f_activarAlarmaS();

                Estado = ALARMA_A;
            }

            break;

        case ALARMA_A :
            if ( apagarAlarma == 1 )
            {
                f_apagarAlarmaS();
                apagarAlarma = 0;
                flagIR = 0;

                Estado = REPOSO;
            }

            break;

        default:
            Estado = RESET ;
            break;

    }
    return Estado ;
}

/**
*	\fn      static int Balanza ( int Estado )
*	\brief   Coloque aqui su descripcion
*	\details Amplie la descripcion
*	\author  Liam
*	\date    01-02-2023 21:14:08
*   \param   [in] Estado: caso dentro de la maquina (estado actual)
*	\return  int : estado siguiente
*/

static int Balanza ( int  Estado )
{
    switch ( Estado )
    {

        case RESET :

            Estado = Reposo;

            break;

        case Reposo :
            if ( tramaOn == 1 )
            {
                f_startTimer();
                f_enviarTrama();

                Estado = MIDIENDO;
            }

            break;

        case MIDIENDO :
            if ( tiempoBalanza == 0 && errorBalanza == 0 )
            {
                f_startTimer();
                f_enviarTrama();

                Estado = MIDIENDO;
            }

            if ( errorBalanza == 1 )
            {
                f_startTimer();

                Estado = ERROR;
            }

            break;

        case ERROR :
            if ( errorBalanza == 0 )
            {

                Estado = MIDIENDO;
            }

            if ( tiempoCamara == 0 )
            {
                f_prenderCamara();

                Estado = CAMARA;
            }

            break;

        case CAMARA :
            if ( apagarAlarma == 1 )
            {
                f_startTimer();
                f_enviarTrama();

                Estado = MIDIENDO;
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
*	\author  Liam
*	\date    01-02-2023 21:14:08
*   \param   void
*	\return  void
*/
void MaquinaDeEstados ( void )
{
    static int estados_Museo = RESET;
    static int estados_SensorIR = RESET;
    static int estados_Balanza = RESET;

    // Coloque su codigo aqui

    estados_Museo = Museo( estados_Museo );
    estados_SensorIR = SensorIR( estados_SensorIR );
    estados_Balanza = Balanza( estados_Balanza );


    return ;
}

