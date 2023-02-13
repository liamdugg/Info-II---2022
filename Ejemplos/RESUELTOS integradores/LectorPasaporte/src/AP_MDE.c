/************************************************************************************************************
 *** INCLUDES
 ************************************************************************************************************/
#include "AP_MDE.h"
#include "AP_FuncionesMDE.h"
#include "AP_Inicializacion.h"
/************************************************************************************************************
 *** DEFINES PRIVADOS AL MODULO
 ************************************************************************************************************/
#define		RESET		0	
//Maquina: Sensor
#define		ESPERANDO		1	// < Maquina: Sensor >
#define		DETECCION		2	// < Maquina: Sensor >
#define		REINTENTO		3	// < Maquina: Sensor >

//Maquina: Analisis_Trama
#define		ESPERANDO		1	// < Maquina: Analisis_Trama >
#define		NOMBRES			2	// < Maquina: Analisis_Trama >
#define		INICIO			3	// < Maquina: Analisis_Trama >
#define		Npasaporte		4	// < Maquina: Analisis_Trama >
#define		CHECKSUM		5	// < Maquina: Analisis_Trama >
#define		FIN				6	// < Maquina: Analisis_Trama >


/************************************************************************************************************
 *** MACROS PRIVADAS AL MODULO
 ************************************************************************************************************/

/************************************************************************************************************
 *** PROTOTIPO DE FUNCIONES PRIVADAS AL MODULO
 ************************************************************************************************************/
static int Sensor ( int );
static int Analisis_Trama ( int );

/************************************************************************************************************
 *** VARIABLES GLOBALES PUBLICAS
 ************************************************************************************************************/
int SensorProx ;		//
int FlagTim ;		//
int TramaOK ;		//
uint8_t dato ;		//
int cont ;		//
int error ;		//
int cant;

uint32_t num;
uint8_t nombres[20];
uint8_t pasaporte[MAX_NUMP];

/************************************************************************************************************
 *** FUNCIONES PRIVADAS AL MODULO
 ************************************************************************************************************/

static int Sensor ( int  Estado )
{
    switch ( Estado )
    {

        case RESET :

            Estado = ESPERANDO;
            cant = 0;

            break;

        case ESPERANDO :
            if ( SensorProx == 1 )
            {
                f_LuzDimmer_ON();
                f_Iniciar_Timer(15000);

                Estado = DETECCION;
            }

            break;

        case DETECCION :
            if ( FlagTim == 1 )
            {
                f_PrenderLedRojo();
                f_Iniciar_Timer(20000);
                FlagTim = 0;
                error = 1;

                Estado = REINTENTO;
            }

            if ( TramaOK == 1 )
            {
                f_Enviar_trama();
                f_Apagar_Timer();

                Estado = ESPERANDO;
            }

            break;

        case REINTENTO :
            if ( FlagTim == 1 )
            {
                f_ApagarLedRojo();
                f_luzDimmer_OFF();
                FlagTim = 0;
                error = 0;

                Estado = ESPERANDO;
            }

            break;

        default:
            Estado = RESET ;
            break;

    }
    return Estado ;
}


static int Analisis_Trama ( int  Estado )
{
	if(!error)
	{
		switch ( Estado )
		{

			case RESET :

				Estado = ESPERANDO;

				break;

			case ESPERANDO :
				if ( SensorProx == 1 )
				{
					Estado = INICIO;
				}

				break;

			case INICIO :
				dato = (uint8_t)popRx();
				if ( dato == '#' )
				{
					Estado = Npasaporte;
				}

				break;

			case NOMBRES :
				dato = (uint8_t)popRx();
				if ( dato >= 'a' && dato <= 'z')
				{
					nombres[cant] = dato;
					cant++;
				}
				if( dato >= '0' && dato <= '9')
				{
					cont = 0;
					pasaporte[cont] = dato;
					Estado = Npasaporte;
					cont++;
				}

				break;

			case Npasaporte :

				if( cont < MAX_NUMP)
				{
					dato = (uint8_t)popRx();
					if (dato >= '0' && dato <= '9')
					{
						pasaporte[cont] = dato;
						cont++;
					}
				}
				if ( cont == 8 )
				{
					Estado = CHECKSUM;
				}

				break;

			case CHECKSUM :

				dato = (uint8_t)popRx();
				num = checksum(nombres,pasaporte);
				if(num == dato)
				{
					Estado = INICIO;
					TramaOK = 1;
				}

				break;
			default:
				Estado = RESET ;
				break;

		}
	}
	else if(error)
	{
		Estado = RESET;
	}
    return Estado ;
}


void MaquinaDeEstados ( void )
{
    static int estados_Sensor = RESET;
    static int estados_Analisis_Trama = RESET;

    // Coloque su codigo aqui

    estados_Sensor = Sensor( estados_Sensor );
    estados_Analisis_Trama = Analisis_Trama( estados_Analisis_Trama );


    return ;
}

