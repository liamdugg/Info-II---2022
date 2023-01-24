/**
*	\file       AP_MDE.c
*	\brief      Maquina/s de Estado
*	\details    Descripcion detallada del archivo
*	\author     Nahuel
*	\date       23-01-2023 18:05:23
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
//Maquina: Semaforo
#define		ESPERANDO	1
#define		ROJO		2	// < Maquina: Semaforo >
#define		AMARILLO		3	// < Maquina: Semaforo >
#define		VERDE		4	// < Maquina: Semaforo >
#define		SEGUNDOS	1000


#define		APRETADO	0


/************************************************************************************************************
 *** MACROS PRIVADAS AL MODULO
 ************************************************************************************************************/



/************************************************************************************************************
 *** PROTOTIPO DE FUNCIONES PRIVADAS AL MODULO
 ************************************************************************************************************/
static int Semaforo ( int );

/************************************************************************************************************
 *** VARIABLES GLOBALES PUBLICAS
 ************************************************************************************************************/
int Tiempo;		//
uint8_t tim_flag;

/************************************************************************************************************
 *** FUNCIONES PRIVADAS AL MODULO
 ************************************************************************************************************/

/**
*	\fn      static int Semaforo ( int Estado )
*	\brief   Coloque aqui su descripcion
*	\details Amplie la descripcion
*	\author  Nahuel
*	\date    23-01-2023 18:05:23
*   \param   [in] Estado: caso dentro de la maquina (estado actual)
*	\return  int : estado siguiente
*/

static int Semaforo ( int  Estado )
{
    switch ( Estado )
    {

        case RESET :
        	m_Apagar_Leds();
        	tim_flag = 0;
        	Estado = ESPERANDO;

            break;

        case ESPERANDO:

        	if(Estado_Tecla() == APRETADO)
        	{
                m_Prender_Rojo();
                m_Iniciar_Timer(30*SEGUNDOS);
                Estado = ROJO;
        	}


        case ROJO :
            if (tim_flag == 1)
            {
            	tim_flag = 0;
                m_Iniciar_Timer(5*SEGUNDOS);
                m_Prender_Amarillo();

                Estado = AMARILLO;
            }

            break;

        case AMARILLO :
            if (tim_flag == 1)
            {
            	tim_flag = 0;
                m_Iniciar_Timer(20*SEGUNDOS);
                m_Prender_Verde();

                Estado = VERDE;
            }

            break;

        case VERDE :
            if (tim_flag == 1)
            {
            	tim_flag = 0;
                m_Prender_Rojo();
                m_Iniciar_Timer(30*SEGUNDOS);

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
*	\author  Nahuel
*	\date    23-01-2023 18:05:23
*   \param   void
*	\return  void
*/
void MaquinaDeEstados ( void )
{
    static int estados_Semaforo = RESET;

    // Coloque su codigo aqui

    estados_Semaforo = Semaforo( estados_Semaforo );


    return ;
}

void SysTick_Handler(void)
{
	//AnalizarTimers();
	if(Tiempo)
		Tiempo--;
	else
		tim_flag = 1;
}

