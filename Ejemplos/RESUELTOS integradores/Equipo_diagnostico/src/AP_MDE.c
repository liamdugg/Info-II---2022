/************************************************************************************************************
 *** INCLUDES
 ************************************************************************************************************/
#include "AP_MDE.h"
#include "AP_FuncionesMDE.h"

/************************************************************************************************************
 *** DEFINES PRIVADOS AL MODULO
 ************************************************************************************************************/
#define		RESET			0
//Maquina: DIAGNOSTICO
#define		ESPERANDO		1	// < Maquina: DIAGNOSTICO >
#define		INICIO			2	// < Maquina: DIAGNOSTICO >
#define		PARAMETRO		3	// < Maquina: DIAGNOSTICO >

//Maquina: TRAMA
#define		ESPERANDO		1	// < Maquina: TRAMA >
#define		INICIO			2	// < Maquina: TRAMA >
#define		DATO1			3	// < Maquina: TRAMA >
#define		DATO2			4	// < Maquina: TRAMA >
#define		VERIFICACION	5	// < Maquina: TRAMA >
#define		FIN				6	// < Maquina: TRAMA >


/************************************************************************************************************
 *** MACROS PRIVADAS AL MODULO
 ************************************************************************************************************/

/************************************************************************************************************
 *** PROTOTIPO DE FUNCIONES PRIVADAS AL MODULO
 ************************************************************************************************************/
static int DIAGNOSTICO ( int );
static int TRAMA ( int );

/************************************************************************************************************
 *** VARIABLES GLOBALES PUBLICAS
 ************************************************************************************************************/
int flag_tim1 ;		//
int x ;		//
int trama_MOD ;		//
int error_MOD;
int flag_tim10s ;		//
int flag_tim_ms ;		//
int cant ;
int cant_param ;		//
int dato ;		//
extern int error_parametros;
uint8_t buffer_rx[2];
uint8_t orden_MOD[6];
uint8_t error_param[6];
uint8_t verificador;


/************************************************************************************************************
 *** FUNCIONES PRIVADAS AL MODULO
 ************************************************************************************************************/

static int DIAGNOSTICO ( int  Estado )
{
    switch ( Estado )
    {

        case RESET :

            Estado = ESPERANDO;
            cant = 0;
            break;

        case ESPERANDO :
            if ( s_get_TeclaTest() )
            {
                f_Enviar_Trama(Mod);
                f_Iniciar_Timer(5000);

                Estado = INICIO;
            }

            break;

        case INICIO :
            if ( flag_tim1 == 1 )
            {
                f_Informe(1,NULL,NULL);
                Estado = ESPERANDO;
            }

            if ( trama_MOD == 1 )
            {
                f_Enviar_Trama(orden_MOD[cant]);
                cant++;
                f_Iniciar_timer_ms(120);
                f_Iniciar_Timer10s(10000);

                Estado = PARAMETRO;
            }
            if(error_MOD == 1)
            {
                f_Informe(1,"mod",(char *)buffer_rx);
                Estado = ESPERANDO;
            }
            break;

        case PARAMETRO :
            if ( flag_tim_ms == 1 && cant < cant_param )
            {
                f_Enviar_Trama(orden_MOD[cant]);
                flag_tim_ms = 0;
                cant++;
                f_Iniciar_timer_ms(120);
                f_Iniciar_Timer10s(10000);

                Estado = PARAMETRO;
            }
            if ( flag_tim10s == 1 )
            {
            	f_Informe(2,NULL,NULL);
            	Estado = ESPERANDO;
            }

            if ( cant == cant_param )
            {
                Verificar_Informe();
                f_Stop_timer();

                Estado = ESPERANDO;
            }

            break;

        default:
            Estado = RESET ;
            break;

    }
    return Estado ;
}



static int TRAMA ( int  Estado )
{
   	if(!flag_tim10s)
    {
    	if(error_parametros == 0)
    	{
    		switch ( Estado )
    		{

				case RESET :

					Estado = ESPERANDO;

					break;

				case ESPERANDO :
					if ( s_get_TeclaTest() || trama_MOD == 1 )
					{
						Estado = INICIO;
					}

					break;

				case INICIO :
					dato = popRx();
					if ( dato == '#')
					{
						Estado = DATO1;
					}

					break;

				case DATO1 :
					dato = popRx();
					if ( (dato >= '0' && dato <= '9') || dato == 'O' || dato == 'E' ||dato == 'N')
					{
						buffer_rx[0] = dato;
						Estado = DATO2;
					}
					else
					{
						Estado = INICIO;
						error_param[cant] = 1;
					}

					break;

				case DATO2 :
					dato = popRx();
					if ((dato >= '0' && dato <= '9') || dato == 'K' || dato == 'R' ||dato == 'A')
					{
						buffer_rx[1] = dato;
						Estado = VERIFICACION;
					}
					else
					{
						Estado = INICIO;
						error_param[cant] = 1;
					}

					break;

				case VERIFICACION :
					dato = popRx();
					if(dato != -1)
						verificador = dato;

					Estado = FIN;
					break;

				case FIN :
					if ( dato == '*' && trama_MOD == 0 )
					{
						f_Analizar_Trama();

						Estado = ESPERANDO;
					}

					if ( trama_MOD == 1 && dato == '*' )
					{
						f_Analizar_respuesta();

						Estado = INICIO;
					}

					break;

				default:
					Estado = RESET ;
					break;

    		}
    	}
    }
   	else Estado = RESET;

	return Estado ;
}

/************************************************************************************************************
 *** FUNCIONES GLOBALES AL MODULO
 ************************************************************************************************************/

void MaquinaDeEstados ( void )
{
    static int estados_DIAGNOSTICO = RESET;
    static int estados_TRAMA = RESET;

    // Coloque su codigo aqui

    estados_DIAGNOSTICO = DIAGNOSTICO( estados_DIAGNOSTICO );
    estados_TRAMA = TRAMA( estados_TRAMA );


    return ;
}

