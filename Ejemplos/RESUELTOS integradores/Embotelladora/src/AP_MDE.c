#include "AP_MDE.h"
#include "AP_FuncionesMDE.h"

#define		RESET				0
//Maquina: Embotelladora
#define		REPOSO				1	// < Maquina: Embotelladora >
#define		ANDANDO				2	// < Maquina: Embotelladora >
#define		BOTELLA_DETECTADA	3	// < Maquina: Embotelladora >

//Maquina: Recepcion_Trama
#define		REPOSO		1	// < Maquina: Recepcion_Trama >
#define		INICIO		2	// < Maquina: Recepcion_Trama >
#define		FIN			3	// < Maquina: Recepcion_Trama >

static int Embotelladora ( int );
static int Recepcion_Trama ( int );

int botonON;
int botella;
int Timers[3];
int Tiempos[3];
int Flag_Timers[3];
int botonOFF;
int contador;
extern int flag_stop;
int16_t datoRx;
uint8_t bufferTrama[6];

static int Embotelladora(int Estado){

    switch (Estado){

        case RESET:
            Estado = REPOSO;
            break;

        case REPOSO:
            if(botonON == 1){
            	botonON = 0;
            	flag_stop = 0;
                f_prenderCinta();
                f_prenderLedOn();
                botonON = 0;
                Estado = ANDANDO;
            }

            break;

        case ANDANDO:

        	if(f_getSensor()){
                f_startTimer(TIM1);
                botella = 0;
                Estado = BOTELLA_DETECTADA;
            }

            if(botonOFF == 1){
            	botonOFF = 0;
                f_apagarSistema();
                Estado = REPOSO;
            }

            break;

        case BOTELLA_DETECTADA:

        	if(Flag_Timers[TIM1] == 1){
        		Flag_Timers[TIM1] = 0;
            	f_apagarCinta();
                f_prenderPiston();
                f_startTimer(TIM2);
                Estado = BOTELLA_DETECTADA;
            }

            if(Flag_Timers[TIM2] == 1){
            	Flag_Timers[TIM2] = 0;
                f_startTimer(TIM3);
                f_apagarPiston();
                Estado = BOTELLA_DETECTADA;
            }

            if(Flag_Timers[TIM3] == 1){
            	Flag_Timers[TIM3] = 0;
            	f_prenderCinta();
                Estado = ANDANDO;
            }

            if(botonOFF == 1){
            	botonOFF = 0;
                f_apagarSistema();
                Estado = REPOSO;
            }

            break;

        default:
            Estado = RESET;
            break;
    }

    return Estado;
}


static int Recepcion_Trama(int Estado){

	switch(Estado){

        case RESET:
            Estado = REPOSO;
		break;

        case REPOSO:
            if(popRx() == '$'){
                Estado = INICIO;
            }

		break;

        case INICIO:

        	if(contador < 6){

        		datoRx = popRx();

				if(datoRx >= 0){
					bufferTrama[contador] = (uint8_t) datoRx;
					contador++;
				}

				else Estado = REPOSO;
        	}

			else if(contador == 6){
				contador = 0;
            	Estado = FIN;
            }

		break;

        case FIN:

        	if(popRx() == '#'){
                f_setTiempos(bufferTrama);
                Estado = REPOSO;
            }

		break;

        default:
            Estado = RESET ;
		break;

    }
    return Estado ;
}


void MaquinaDeEstados(void){

	static int estados_Embotelladora = RESET;
    static int estados_Recepcion_Trama = RESET;

    estados_Embotelladora = Embotelladora( estados_Embotelladora );
    estados_Recepcion_Trama = Recepcion_Trama( estados_Recepcion_Trama );
}

