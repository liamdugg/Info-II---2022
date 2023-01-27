/**
*	\file       AP_FuncionesMDE.c
*	\brief      Funciones de Eventos y Acciones asociadas a las Maquinas de estados
*	\details    Descripcion detallada del archivo
*	\author     Nahuel
*	\date       26-01-2023 18:02:26
*/

#include "AP_FuncionesMDE.h"
#include "AP_Inicializacion.h"
#include "Regs_LPC845.h"


#define ENTERO		1
#define DECIMAL		0

#define		SENSORES			3
#define		DATOS_CENTRAL		5
#define		DATOS_SET			6

int tiempo;
extern uint8_t Trama_central[SENSORES][DATOS_CENTRAL];
extern uint8_t Trama_Set[SENSORES][DATOS_SET];
extern uint32_t resultadoADC[3];

int s_SetTemp ( void )
{
    int res = 0 ;

    // Coloque aqui su codigo

    return res ;
}

void m_Prender_Alarma()
{
	SetPIN(0, 0, 1);
}


void m_Apagar_Alarma(void)
{
	SetPIN(0, 0, 0);
}

void m_Enviar_Trama_Temp()
{
    Transmitir(">12<", 4);//sensor1
    Transmitir(">22<", 4);//sensor2
    Transmitir(">32<", 4);//sensor3
}


uint8_t parseo_temp(int tipo, int sensor)
{
	int entero=0;
	uint8_t decimal=0;

	if(tipo == ENTERO)
	{
		entero = (int)((resultadoADC[sensor]-20)/1000);
		return (uint8_t)entero;

	}
	else if(tipo == DECIMAL)
	{
		decimal = (((float)((resultadoADC[sensor]-20)/1000) - (float)entero)*10);
		return (uint8_t)decimal;
	}
	return 0;
}

void m_Enviar_Trama_Temp_sens()
{
	uint8_t Trama_temp_sen[3][5];

	Trama_temp_sen[0][0] = '<';
	Trama_temp_sen[0][1] = '1';
	Trama_temp_sen[0][2] = parseo_temp(ENTERO,0);
	Trama_temp_sen[0][3] = parseo_temp(DECIMAL,0);
	Trama_temp_sen[0][4] = '>';
	Transmitir(Trama_temp_sen[0], 5);

	Trama_temp_sen[1][0] = '<';
	Trama_temp_sen[1][1] = '2';
	Trama_temp_sen[1][2] = parseo_temp(ENTERO,1);
	Trama_temp_sen[1][3] = parseo_temp(DECIMAL,1);
	Trama_temp_sen[1][4] = '>';
	Transmitir(Trama_temp_sen[1], 5);

	Trama_temp_sen[2][0] = '<';
	Trama_temp_sen[2][1] = '3';
	Trama_temp_sen[2][2] = parseo_temp(ENTERO,2);
	Trama_temp_sen[2][3] = parseo_temp(DECIMAL,2);
	Trama_temp_sen[2][4] = '>';
	Transmitir(Trama_temp_sen[2], 5);

}

void f_Enviar_trama_set ( int cant )
{
	uint8_t buffer_set[6] = {0};

	buffer_set[0] = '>';
	buffer_set[1] = '1';
	buffer_set[2] = '3';
	buffer_set[3] = 25;		// valor entero de la temperatura para setear
	buffer_set[4] = 1;		// decimales de la temperatura
	buffer_set[5] = '<';
    Transmitir(buffer_set, cant);//sensor1

	buffer_set[0] = '>';
	buffer_set[1] = '2';
	buffer_set[2] = '3';
	buffer_set[3] = 99;		// valor entero de la temperatura para setear
	buffer_set[4] = 8;		// decimales de la temperatura
	buffer_set[5] = '<';
    Transmitir(buffer_set, cant);//sensor2

	buffer_set[0] = '>';
	buffer_set[1] = '3';
	buffer_set[2] = '3';
	buffer_set[3] = 50;		// valor entero de la temperatura para setear
	buffer_set[4] = 0;		// decimales de la temperatura
	buffer_set[5] = '<';
    Transmitir(buffer_set, cant);//sensor1

    return ;
}

void f_Enviar_trama_set_sens( int cant )
{
	uint8_t buffer_set[6] = {0};

	buffer_set[0] = Trama_Set[0][0];
	buffer_set[1] = Trama_Set[0][1];;
	buffer_set[2] = Trama_Set[0][2];
	buffer_set[3] = Trama_Set[0][3];
	buffer_set[4] = Trama_Set[0][4];
	buffer_set[5] = Trama_Set[0][5];
    Transmitir(buffer_set, cant);//sensor1

	buffer_set[0] = Trama_Set[1][0];
	buffer_set[1] = Trama_Set[1][1];;
	buffer_set[2] = Trama_Set[1][2];
	buffer_set[3] = Trama_Set[1][3];
	buffer_set[4] = Trama_Set[1][4];
	buffer_set[5] = Trama_Set[1][5];
    Transmitir(buffer_set, cant);//sensor2

	buffer_set[0] = Trama_Set[2][0];
	buffer_set[1] = Trama_Set[2][1];;
	buffer_set[2] = Trama_Set[2][2];
	buffer_set[3] = Trama_Set[2][3];
	buffer_set[4] = Trama_Set[2][4];
	buffer_set[5] = Trama_Set[2][5];
    Transmitir(buffer_set, cant);//sensor3

    return ;
}


void m_Iniciar_timer()
{
	tiempo = 1000; //1000 ticks de 1ms son 1 SEGUNDO
}

void SysTick_Handler(void)
{
	if(!tiempo)
		tiempo--;
	else
		Flag_tim = 1;
}



