#include "AP_MDE.h"
#include "AP_FuncionesMDE.h"
#include "AP_Inicializacion.h"

#define		RESET		0	

//Maquina: Teclado
#define		APAGADO		1	// < Maquina: Teclado >
#define		ENCENDIDO	2	// < Maquina: Teclado >
#define		CORRIENDO	3	// < Maquina: Teclado >
#define		ERROR		4	// < Maquina: Teclado >
#define		CONFIG		5

//Maquina: Parpadeo
#define		APAGADO		1	// < Maquina: Parpadeo >
#define		ENCENDIDO	2	// < Maquina: Parpadeo >


static int Teclado(int);
static int Parpadeo(int);

int parpadear;
int finMusica;
int prender;
int tramaOK;
int tiempo;

extern uint8_t flagtecla;

static int Teclado(int Estado){

	switch (Estado){

        case RESET:
            Estado = APAGADO;
            break;

        case APAGADO:

        	if(prender){
        		prender = 0;
                f_enviarTramaOn();
                Estado = CONFIG;
            }

            break;


        case CONFIG:

        	if(!tramaOK){
        		checkTrama();
        	}

        	if(tramaOK){
        		tramaOK = 0;
        		f_setTimer();
        		f_guardarTeclas();
        		f_pasarNota();
        		Estado = CORRIENDO;
        	}

        	break;

        case CORRIENDO:

        	if(teclaOK() == 1)
                f_pasarNota();

        	else if( (flagtecla == 1 && !teclaOK()) || TMR_Events[TIM_TECLA]==1){
            	TMR_Events[TIM_TECLA] = 0;
            	parpadear = 1;
                Estado = ERROR;
            }

            if(finMusica == 1){
                Estado = APAGADO;
            }
            break;

        case ERROR:

        	if(parpadear == 0){
                Estado = APAGADO;
            }

            if(teclaOK){
                parpadear = 0;
                Estado = CORRIENDO;
            }

            break;

        default:
            Estado = RESET;
            break;

    }
    return Estado;
}

static int Parpadeo(int Estado){

    switch(Estado){

        case RESET :
            Estado = APAGADO;
            break;

        case APAGADO:

        	if(parpadear == 1){
                f_startTimer3S();
                f_startTimer500ms();
                f_prenderLED();
                parpadear = 2;
                Estado = ENCENDIDO;
            }

            if (TMR_Events[TIM_500ms]==1){
            	TMR_Events[TIM_500ms]= 0;
            	f_prenderLED();
                Estado = ENCENDIDO;
            }

            if(teclaOK == 1){
            	TimerClose();
            }

            break;

        case ENCENDIDO :

        	if (TMR_Events[TIM_500ms]==1){

            	TMR_Events[TIM_500ms]= 0;
                f_apagarLED();
                f_startTimer500ms();
                Estado = APAGADO;
            }

            if (TMR_Events[TIM_3S]==1){
            	TMR_Events[TIM_3S]= 0;
            	parpadear = 0;
                f_apagarLED();
                Estado = APAGADO;
            }

            if(teclaOK == 1){
                f_apagarLED();
                TimerClose();
                Estado = APAGADO;
            }

            break;

        default:
            Estado = RESET;
            break;

    }
    return Estado ;
}


void MaquinaDeEstados ( void ){
    static int estados_Teclado = RESET;
    static int estados_Parpadeo = RESET;

    // Coloque su codigo aqui
    estados_Teclado = Teclado( estados_Teclado );
    estados_Parpadeo = Parpadeo( estados_Parpadeo );
    return ;
}

