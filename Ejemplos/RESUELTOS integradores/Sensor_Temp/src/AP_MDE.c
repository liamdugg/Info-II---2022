/**
*	\file       AP_MDE.c
*	\brief      Maquina/s de Estado
*	\details    Descripcion detallada del archivo
*	\author     Nahuel
*	\date       26-01-2023 18:02:26
*/
/************************************************************************************************************
 *** INCLUDES
 ************************************************************************************************************/
#include "AP_MDE.h"
#include "AP_FuncionesMDE.h"
#include "Regs_LPC845.h"
#include "uart.h"

/************************************************************************************************************
 *** DEFINES PRIVADOS AL MODULO
 ************************************************************************************************************/
#define		RESET		0	
//Maquina: Sensado_Temp
#define		CENTRAL		1	// < Maquina: Sensado_Temp >
#define		DISPOSITIVOS		2	// < Maquina: Sensado_Temp >
#define		CONFIGURACION		3	// < Maquina: Sensado_Temp >

#define		SENSORES			3
#define		DATOS_CENTRAL		5
#define		DATOS_SET			6

/************************************************************************************************************
 *** MACROS PRIVADAS AL MODULO
 ************************************************************************************************************/


/************************************************************************************************************
 *** PROTOTIPO DE FUNCIONES PRIVADAS AL MODULO
 ************************************************************************************************************/
static int Sensado_Temp ( int );

/************************************************************************************************************
 *** VARIABLES GLOBALES PUBLICAS
 ************************************************************************************************************/
int Flag_tim ;		//
int Dato_recibido ;		//
int TempOk ;		//
int Set ;		//
int Temp;

int envios;

uint8_t Trama_central[SENSORES][DATOS_CENTRAL];
uint8_t Trama_Set[SENSORES][DATOS_SET];


/************************************************************************************************************
 *** FUNCIONES PRIVADAS AL MODULO
 ************************************************************************************************************/

/**
*	\fn      static int Sensado_Temp ( int Estado )
*	\brief   Coloque aqui su descripcion
*	\details Amplie la descripcion
*	\author  Nahuel
*	\date    26-01-2023 18:02:26
*   \param   [in] Estado: caso dentro de la maquina (estado actual)
*	\return  int : estado siguiente
*/

static int Sensado_Temp ( int  Estado )
{
    switch ( Estado )
    {

        case RESET :
        	m_Iniciar_timer();
            Set = 0;
            TempOk = 1;
            Dato_recibido = 0;

            Estado = CENTRAL;

            break;

        case CENTRAL :
            if ( Flag_tim == 1 && Set == 0 )
            {
                m_Enviar_Trama_Temp();
                Temp = 1;
                envios = 0;

                Estado = DISPOSITIVOS;
            }

            if ( s_SetTemp() )
            {
                f_Enviar_trama_set(6);
                Set = 1;
                Estado = CONFIGURACION;
            }

            break;

        case DISPOSITIVOS :


        	if(Temp == 1 && envios < SENSORES)
        	{
        		for(int i = 0; i < DATOS_CENTRAL; i++)
        		{
        			Trama_central[envios][i] = popRx();
        		}
        		envios++;
        	}

            if ( envios == SENSORES && TempOk == 1 )
            {
            	envios = 0;
                m_Enviar_Trama_Temp_sens();
                m_Iniciar_timer();
                m_Apagar_Alarma();

                Estado = CENTRAL;
            }

            if ( TempOk == 0 )
            {
                m_Prender_Alarma();

                Estado = DISPOSITIVOS;
            }

            break;

        case CONFIGURACION :
            if (envios <= SENSORES)
            {
        		for(int i = 0; i < DATOS_SET; i++)
        		{
        			Trama_Set[envios][i] = popRx();
        		}
    			envios++;
            }
            if(envios == SENSORES)
            {
            	envios = 0;
                f_Enviar_trama_set_sens(6);
                m_Iniciar_timer();

                Estado = CENTRAL;
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
*	\date    26-01-2023 18:02:26
*   \param   void
*	\return  void
*/
void MaquinaDeEstados ( void )
{
    static int estados_Sensado_Temp = RESET;

    // Coloque su codigo aqui

    estados_Sensado_Temp = Sensado_Temp( estados_Sensado_Temp );


    return ;
}

