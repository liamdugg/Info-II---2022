/************************************************************************************************************
 *** INCLUDES
 ************************************************************************************************************/
#include "AP_MDE.h"
#include "AP_FuncionesMDE.h"
#include "timer.h"
#include "Teclado.h"

/************************************************************************************************************
 *** DEFINES PRIVADOS AL MODULO
 ************************************************************************************************************/
#define		RESET			0
#define		ESPERANDO		1
#define		VALIDANDO		2
#define		DETECTANDO		3

#define		TIMER_COIN		0
#define		TIMER_DEV		1

static int maquinaCafe (int);
extern uint8_t bufKey;
/************************************************************************************************************
 *** VARIABLES GLOBALES PUBLICAS
 ************************************************************************************************************/

int moneda;
int eleccion;

/************************************************************************************************************
 *** FUNCIONES PRIVADAS AL MODULO
 ************************************************************************************************************/

static int maquinaCafe ( int  Estado )
{
    switch ( Estado )
    {

        case RESET :
            moneda = 0;
            eleccion = 0;

            Estado = ESPERANDO;

            break;

        case ESPERANDO :

            if (moneda == 1)
            {
                TimerStart(TIMER_COIN, 5, NULL, SEG);
                moneda = 0;
                eleccion++;
                Estado = DETECTANDO;
            }

            break;

        case DETECTANDO :

			if (moneda == 1 && eleccion <= 3 )
			{
				SetTimer(TIMER_COIN, 5);
				moneda = 0;
				eleccion++;

				Estado = DETECTANDO;
			}

			if(bufKey == '1' || bufKey == '2' || bufKey == '3'){

				TimerStop(TIMER_COIN);

				if(hayStock(eleccion)){
					Estado = VALIDANDO;
				}

				else{
					m_dev_mon();
					TimerStart(TIMER_DEV, 2, m_dev_mon_off, SEG);
					Estado = RESET;
				}
			}

			if ( TMR_Events[TIMER_COIN] == 1 || eleccion > 3 ){

				TimerEvent(); // LIMPIA FLAG DEL TIMER
				m_dev_mon();
				TimerStart(TIMER_DEV, 2, m_dev_mon_off, SEG);
				Estado = RESET;
			}

			break;

        case VALIDANDO :

            if(bufKey == '#'){
            	m_preparar_pedido(eleccion);
            	Estado = RESET;
            }

            break;


        default:
            Estado = RESET ;
            break;

    }
    return Estado ;
}

void MaquinaDeEstados ( void )
{
    static int estados_maquinaCafe = RESET;

    // Coloque su codigo aqui

    estados_maquinaCafe = maquinaCafe( estados_maquinaCafe );


    return ;
}

