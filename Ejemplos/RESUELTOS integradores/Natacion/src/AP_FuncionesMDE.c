/**
*	\file       AP_FuncionesMDE.c
*	\brief      Funciones de Eventos y Acciones asociadas a las Maquinas de estados
*	\details    Descripcion detallada del archivo
*	\author     Nahuel
*	\date       29-01-2023 21:05:56
*/

/************************************************************************************************************
 *** INCLUDES
 ************************************************************************************************************/
#include "AP_FuncionesMDE.h"


int Tiempo;
extern int tiempo_carrera;

int time_stop;

extern int Timer_2s;

int buffer_tiempos[5];


#define LANZA1			1
#define LANZA2			2
#define LANZA3			3
#define LANZA4			4
#define LANZA5			5

#define LLEGADA1		6
#define LLEGADA2		7
#define LLEGADA3		8
#define LLEGADA4		9
#define LLEGADA5		10

#define MAX_TRAMA		7

#define TIEMPO_STOP		5000


uint8_t Inicio(void)
{
	uint8_t tecla = 0;

	tecla = getKey();

	if(tecla >= LANZA1  && tecla <= LANZA5)
	{
		return 1;
	}

	return 0;
}

uint8_t llegada(void)
{
	uint8_t tecla = 0;


	tecla = getKey();

	switch(tecla)
	{

		case LLEGADA1:
				return LLEGADA1 - 6;
				break;

		case LLEGADA2:
				return LLEGADA2 - 6;
				break;

		case LLEGADA3:
				return LLEGADA3 - 6;
				break;

		case LLEGADA4:
				return LLEGADA4 - 6;
				break;

		case LLEGADA5:
				return LLEGADA5 - 6;
				break;

		case NO_KEY:
				return NO_KEY;
				break;

		default :
				return NO_KEY;
				break;
	}

	return NO_KEY;
}


void f_Deneter_Timer ( uint8_t nadador )
{

    buffer_tiempos[nadador] = Tiempo;

    return ;
}


void f_Display_Corredor ( void )
{
	static int i = 0;
	if(buffer_tiempos[i] == 0)
	{
		Display((i+1)*100000);
	}
	else
		Display(parseo_tiempo(i));

	i++;
	i %= 5;

}

/**
*	\fn      void f_Envio_trama ( void )
*	\brief   Coloque aqui su descripcion
*	\details Amplie la descripcion
*	\author  Nahuel
*	\date    29-01-2023 21:05:56
*   \param   void
*	\return  void
*/


void f_Envio_trama ( int nadador )
{
	uint8_t buffer_trama[MAX_TRAMA];
	// 3,456 * 60 * 10 = 2073,6 decimas


	int tiempo_dec = (int)buffer_tiempos[nadador]/100;

	int pos0 = 0 , aux = 0;


	buffer_trama[0] = '$';
	buffer_trama[1] = nadador + '1';

	pos0 = tiempo_dec%10;
	aux = tiempo_dec/10;
	buffer_trama[5]	= (uint8_t)(pos0 + '0');

	pos0 = aux%10;
	aux /= 10;
	buffer_trama[4]	= (uint8_t)(pos0 + '0');

	pos0 = aux%10;
	aux /= 10;
	buffer_trama[3]	= (uint8_t)(pos0 + '0');

	pos0 = aux%10;
	aux /= 10;
	buffer_trama[2]	= (uint8_t)(pos0 + '0');

	buffer_trama[6] = '#';

	Transmitir(buffer_trama, MAX_TRAMA);

}

/**
*	\fn      void f_Iniciar_Display_Carrera ( void )
*	\brief   Coloque aqui su descripcion
*	\details Amplie la descripcion
*	\author  Nahuel
*	\date    29-01-2023 21:05:56
*   \param   void
*	\return  void
*/


void f_Iniciar_Display_Carrera ( void )
{
    // Coloque aqui su codigo

    return ;
}

/**
*	\fn      void f_Iniciar_Timer_2s ( void )
*	\brief   Coloque aqui su descripcion
*	\details Amplie la descripcion
*	\author  Nahuel
*	\date    29-01-2023 21:05:56
*   \param   void
*	\return  void
*/


void f_Iniciar_Timer_2s ( void )
{
	Timer_2s = 2000;
    return ;
}

void PININT0_IRQHandler(void)
{
	FALL |= (1<<3);

	Pulsador = 1;
}

void SysTick_Handler(void)
{

	if(Pulsador == 0)
	{
		driverTeclado();
		if(tiempo_carrera)
			Tiempo++;

		// maquina display
		if(Timer_2s)
			Timer_2s--;
	}else
		time_stop++;

	if(time_stop == TIEMPO_STOP)
		Pulsador = 0;

	// stop


}

/*------------------------------------------TEMPORIZADORES -------------------------------------------------*/


uint32_t parseo_tiempo(int nadador)
{
	int tiempo_total = buffer_tiempos[nadador];
	float minuto, segundo, decima;


	int tiempo_display = 0;

	minuto  = tiempo_total/60000;		//3,5456

	segundo = (minuto - (int)minuto) * 60;			//(.5456)*60 -- 32.736

	decima  = (segundo - (int)segundo) * 10;			//7.36

	tiempo_display = (int)nadador*100000 + (int)minuto*1000 + (int)segundo*10 + decima; // 	103327

	return (uint32_t)tiempo_display;

}




