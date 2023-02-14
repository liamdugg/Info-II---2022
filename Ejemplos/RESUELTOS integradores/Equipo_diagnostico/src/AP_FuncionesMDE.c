/**
*	\file       AP_FuncionesMDE.c
*	\brief      Funciones de Eventos y Acciones asociadas a las Maquinas de estados
*	\details    Descripcion detallada del archivo
*	\author     Nahuel
*	\date       13-02-2023 22:06:42
*/

/************************************************************************************************************
 *** INCLUDES
 ************************************************************************************************************/
#include "AP_FuncionesMDE.h"

/************************************************************************************************************
 *** DEFINES PRIVADOS AL MODULO
 ************************************************************************************************************/


/************************************************************************************************************
 *** VARIABLES GLOBALES PUBLICAS
 ************************************************************************************************************/
int Tiempo;
int Tiempoms;
int Tiempo10;

int stop;
extern int flag_tim1 ;
extern int flag_tim_ms;
extern int flag_tim10s;
extern uint8_t buffer_rx[2];
uint8_t respuesta_error[3];
extern uint8_t orden_MOD[6];
extern uint8_t error_param[6];
int error_parametros;
extern int cant ;
extern int trama_MOD;
extern int error_MOD;
extern int cant_param;
extern uint8_t verificador;
/************************************************************************************************************
 *** FUNCIONES GLOBALES AL MODULO
 ************************************************************************************************************/

/*-------------------------------------------- EVENTOS ----------------------------------------------------*/



int s_get_TeclaTest ( void )
{
    int res = 0 ;


    return res ;
}

/*-------------------------------------------- ACCIONES ----------------------------------------------------*/

void cargar_buff_MOD(int parametros)
{
	if(parametros == 0)
	{
		orden_MOD[0] = Temp;
		orden_MOD[1] = Hum;
		orden_MOD[2] = Tor;
		orden_MOD[3] = Sort;
		cant_param = 4;
	}
	else if(parametros == 2)
	{
		orden_MOD[0] = Rem;
		orden_MOD[1] = Rest;
		orden_MOD[2] = Vari;
		orden_MOD[3] = Crest;
		orden_MOD[4] = Sort;
		orden_MOD[5] = Yli;
		cant_param = 6;
	}
	else if(parametros == 4)
	{
		orden_MOD[0] = Temp;
		orden_MOD[1] = Hum;
		orden_MOD[2] = Rem;
		orden_MOD[3] = Crest;
		orden_MOD[4] = Sort;
		orden_MOD[5] = Yli;
		cant_param = 6;
	}
	else if(parametros == 18)
	{
		orden_MOD[0] = Temp;
		orden_MOD[1] = Hum;
		orden_MOD[2] = Tor;
		orden_MOD[3] = Rem;
		orden_MOD[4] = Rest;
		orden_MOD[5] = Vari;
		cant_param = 6;
	}
	else if(parametros >= 18 && parametros <= 31)
	{
		orden_MOD[0] = Temp;
		orden_MOD[1] = Hum;
		orden_MOD[2] = Crest;
		orden_MOD[3] = Yli;
		cant_param = 4;
	}
}


void f_Analizar_Trama ( void )
{
	int parametros;

	parametros = (buffer_rx[0] - '0')*10 + (buffer_rx[1] - '0');

	if(parametros == 0 || parametros == 2 || parametros == 4 || parametros == 18 || (parametros >= 20 && parametros <= 31))
	{
		cargar_buff_MOD(parametros);
		trama_MOD = 1;
	}
	else
		error_MOD = 1;

}

void f_Analizar_respuesta ( void )
{
	int parametros;
	int valor_verif;

	parametros = (buffer_rx[0] - '0')*10 + (buffer_rx[1] - '0');
	valor_verif = ((buffer_rx[0] - '0') + (buffer_rx[1] - '0'))%10;

	switch(orden_MOD[cant])
	{
		case Temp:
			if(verificador != (uint8_t)valor_verif)
			{
				error_param[cant] = 1;
				respuesta_error[0] = 2;//case x = 2
				respuesta_error[1] = buffer_rx[0];
				respuesta_error[2] = buffer_rx[1];
				error_parametros = 1;
			}
			else if(parametros<18 || parametros> 35)
			{
				error_param[cant] = 1;
				respuesta_error[0] = 1;//case x = 1
				respuesta_error[1] = buffer_rx[0];
				respuesta_error[2] = buffer_rx[1];
				error_parametros = 1;
			}

		break;
		case Hum:

			//Repetir o caso con condicion numerica o con OK
		break;
		case Tor:
			if(buffer_rx[0] != 'O' || buffer_rx[0] != 'K')
			{
				error_param[cant] = 1;
				respuesta_error[0] = 1;//case x = 2
				respuesta_error[1] = buffer_rx[0];
				respuesta_error[2] = buffer_rx[1];
				error_parametros = 1;
			}
		break;
		case Rem:

		break;
		case Rest:

		break;
		case Vari:

		break;
		case Crest:

		break;
		case Sort:

		break;
		case Yli:

		break;
		default:
		break;
	}

}

void f_Enviar_Trama (uint8_t tipo)
{
	pushTx('#');
	pushTx(tipo);
	pushTx('*');

}



void f_Informe ( int x, char *s1, char *s2)
{
    // Coloque aqui su codigo

    return ;
}

void Verificar_Informe(void)
{
	char comando_error[2];
	char orden_mod;
	int error = (int)respuesta_error[0];
	comando_error[0] = respuesta_error[1];
	comando_error[1] = respuesta_error[2];

	for(int i = 0; i < cant_param; i++)
	{
		if(error_param[i] == 1)
		{
			orden_mod = (char)orden_MOD[i];
			f_Informe(error,&orden_mod, comando_error);
			return;
		}
	}
	f_Informe(0,NULL, NULL);
}


void f_Iniciar_Timer ( int tiempo )
{
    Tiempo = tiempo;

    return ;
}


void f_Iniciar_Timer10s ( int tiempo)
{
    Tiempo10 = tiempo;

    return ;
}




void f_Iniciar_timer_ms ( int tiempo )
{
   Tiempoms = tiempo;

    return ;
}




void f_Stop_timer ( void )
{
    stop = 1;

    return ;
}


void SysTick_Handler(void)
{
	if(!stop)
	{
		if(Tiempo)
			Tiempo--;
		else if(Tiempo == 0)
			flag_tim1 = 1;

		if(Tiempo10)
			Tiempo10--;
		else if(Tiempo10 == 0)
			flag_tim10s = 1;

		if(Tiempoms)
			Tiempoms--;
		else if(Tiempoms == 0)
			flag_tim_ms = 1;
	}
}

/*------------------------------------------TEMPORIZADORES -------------------------------------------------*/

