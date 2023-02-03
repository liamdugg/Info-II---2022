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
#define		ONN			2	// < Maquina: Museo >
#define		INFRAROJO	3	// < Maquina: Museo >

//Maquina: SensorIR
#define		REPOSO		1	// < Maquina: SensorIR >
#define		ALARMA_1	2	// < Maquina: SensorIR >
#define		ALARMA_2	3	// < Maquina: SensorIR >

//Maquina: Balanza
#define		REPOSO		1	// < Maquina: Balanza >
#define		MIDIENDO	2	// < Maquina: Balanza >
#define		ERROR		3	// < Maquina: Balanza >
#define		CAMARA		4	// < Maquina: Balanza >

#define 	INICIO			1
#define		LECTURA_ID		2
#define		LECTURA_PESO	3
#define		FIN				4

#define		SEC			1000
#define		MIN			60*SEC

/************************************************************************************************************
 *** MACROS PRIVADAS AL MODULO
 ************************************************************************************************************/

/************************************************************************************************************
 *** PROTOTIPO DE FUNCIONES PRIVADAS AL MODULO
 ************************************************************************************************************/
static int Museo ( int );
static int SensorIR ( int );
static int Balanza ( int );
static int Trama(int);

/************************************************************************************************************
 *** VARIABLES GLOBALES PUBLICAS
 ************************************************************************************************************/
int tramaOn;
int flagIR;
int apagarAlarma;
int errorBalanza;
int tiempoAlarma;
int tiempoBalanza;
int tiempoCamara;
int16_t datoRx;

extern uint8_t idEquipo;
extern uint8_t pesoMax;
uint8_t pesoActual;
/************************************************************************************************************
 *** FUNCIONES PRIVADAS AL MODULO
 ************************************************************************************************************/
static int Museo (int Estado)
{
    switch ( Estado ){

        case RESET :

            Estado = REPOSO;
            break;

        case REPOSO:

            if(tramaOn == 1)
                Estado = ONN;
            break;

        case ONN:

            if(flagIR == 1)
            	Estado = INFRAROJO;
            break;

        case INFRAROJO :

            if (flagIR==0)
                Estado = ONN;
            break;

        default:
            Estado = RESET;
            break;

    }

    return Estado;
}

static int SensorIR (int  Estado ){

	switch ( Estado){

        case RESET :
            Estado = REPOSO;
            break;

        case REPOSO :

        	if(flagIR == 1){
                f_activarAlarma(ALARMA_S);
                f_startTimer(TIM_ALARMA, 1*MIN);
                Estado = ALARMA_1;
            }

            break;

        case ALARMA_1:

        	if (apagarAlarma == 1 ){
                apagarAlarma = 0;
                flagIR = 0;
                f_stopTimer(TIM_ALARMA);
                f_apagarAlarma(ALARMA_S);
                Estado = REPOSO;
            }

            if ( tiempoAlarma == 0){
            	f_apagarAlarma(ALARMA_S);
                f_activarAlarma(ALARMA_A);
                Estado = ALARMA_2;
            }

            break;

        case ALARMA_2:

            if ( apagarAlarma == 1 ){
                f_apagarAlarma(ALARMA_A);
                apagarAlarma = 0;
                flagIR = 0;
                Estado = REPOSO;
            }

            break;

        default:
            Estado = RESET;
            break;

    }

    return Estado;
}

static int Balanza (int  Estado){

	switch ( Estado ){

        case RESET :
            Estado = REPOSO;
            break;

        case REPOSO:

            if (tramaOn == 1){
                f_startTimer(TIM_BAL, 1*SEG);
                f_enviarTrama(TRAMA_BAL);
                Estado = MIDIENDO;
            }

            break;

        case MIDIENDO:

            if(tiempoBalanza == 0 && errorBalanza == 0){
            	f_startTimer(TIM_BAL, 1*SEG);
				f_enviarTrama(TRAMA_BAL);
                Estado = MIDIENDO;
            }

            if(errorBalanza == 1){
                f_startTimer(TIM_CAM, 5*SEG);
                Estado = ERROR;
            }

            break;

        case ERROR :

            if(errorBalanza == 0){
            	f_stopTimer(TIM_CAM);
            	f_startTimer(TIM_BAL, 1*SEG);
				f_enviarTrama(TRAMA_BAL);
                Estado = MIDIENDO;
            }

            if (tiempoCamara == 0){
                f_prenderCamara();
                Estado = CAMARA;
            }

            break;

        case CAMARA:

            if (apagarAlarma == 1){
            	f_startTimer(TIM_BAL, 1*SEG);
				f_enviarTrama(TRAMA_BAL);
                Estado = MIDIENDO;
            }

            break;

        default:
            Estado = RESET;
            break;

    }

    return Estado ;
}

static int Trama(int Estado){

	switch(Estado){

		case RESET:
			Estado = REPOSO;
			break;

		case INICIO:

			if(!tramaOn && popRx() == '$')
				Estado = LECTURA_ID;

			if(tramaOn && popRx() == '$')
				Estado = LECTURA_PESO;
			break;

		case LECTURA_ID:

			datoRx = popRx();

			if(datoRx >= '0' && datoRx <= '9'){
				idEquipo = (uint8_t)datoRx;
				Estado = LECTURA_PESO;
			}

			else Estado = INICIO;
			break;

		case LECTURA_PESO:

			datoRx = popRx();

			if(!tramaOn && (datoRx >= '0' && datoRx <= '9') ){
				pesoMax = (uint8_t)datoRx;
				Estado = FIN;
			}

			else if(tramaOn && (datoRx >= '0' && datoRx <= '9') ){
				pesoActual = (uint8_t)datoRx;
				Estado = FIN;
			}

			else Estado = INICIO;
			break;

		case FIN:

			datoRx = popRx();

			if(!tramaOn && datoRx=='#'){
				tramaOn = 1;
				Estado = INICIO;
			}

			else if(tramaOn && datoRx=='#'){

				if(pesoActual == pesoMax)
					errorBalanza = 0;

				else if(pesoActual != pesoMax)
					errorBalanza = 1;

				Estado = INICIO;
			}

			Estado = INICIO;
			break;

		default:
			Estado = RESET;
			break;
	}

	return Estado;
}
/************************************************************************************************************
 *** FUNCIONES GLOBALES AL MODULO
 ************************************************************************************************************/

void MaquinaDeEstados ( void )
{
    static int estados_Museo = RESET;
    static int estados_SensorIR = RESET;
    static int estados_Balanza = RESET;
    static int estados_Trama = RESET;

    estados_Trama = Trama(estados_Trama);
    estados_Museo = Museo( estados_Museo );
    estados_SensorIR = SensorIR( estados_SensorIR );
    estados_Balanza = Balanza( estados_Balanza );
    return ;
}

