//************************************************************************************************
// Archivo:				OS_GPIO_DRIVER.c
//
// Descripcion:
//
// Realizado por:		Ing. Fresno Gustavo (13/09/11)
//
//************************************************************************************************

#include <dr_gpio.h>
#include "dr_7seg.h"
#include "LPC845.h"

// Buffer Display 7 Segmentos
uint8_t	DISPLAY_7SEG_Buffer[CANTIDAD_DIGITOS];

// Driver Display 7 Segmentos -> se ejecuta en la ISR del SysTick
void DISPLAY_7SEG_Barrido_v2(void)
{
	static uint8_t	DISPLAY_7SEG_Indice = 0;
	uint8_t	datoBCD;

	uint32_t aux = 1 << 21 | 1 << 22 |  1 << 20  | 1 << 23; // Pines BCD A/B/C/D

	GPIO->SET[0] = aux ;

	if( DISPLAY_7SEG_Indice >= CANTIDAD_DIGITOS )	// Reset del Contador
	{
		SetPIN(BCD_RST, 0);
		SetPIN(BCD_RST, 1);
		DISPLAY_7SEG_Indice = 0;
	}
	else
	{
		SetPIN(BCD_RST, 0);
		SetPIN(BCD_CK, 0);
		SetPIN(BCD_CK, 1);
	}

	datoBCD = DISPLAY_7SEG_Buffer[CANTIDAD_DIGITOS - DISPLAY_7SEG_Indice - 1];

	// Verifico los pines que tengo que poner en 0 en base al digito / datoBCD actual

	aux = 0;

	if ( ! ( datoBCD & 1 ) )
		aux |= 1 << 20;
	if ( ! (( datoBCD >> 1 )  & 1 ) )
		aux |= 1 << 23;
	if ( ! (( datoBCD >> 2 )  & 1 ) )
		aux |= 1 << 22;
	if ( ! (( datoBCD >> 3 )  & 1 ) )
		aux |= 1 << 21;

	GPIO->CLR[0] = aux ;

	DISPLAY_7SEG_Indice++;
}


void DISPLAY_7SEG_Barrido(void)
{
	static uint8_t digito = CANTIDAD_DIGITOS;

	SetPIN (BCD_A, 1);
	SetPIN (BCD_B, 1);
	SetPIN (BCD_C, 1);
	SetPIN (BCD_D, 1);

	SetPIN (BCD_A, (DISPLAY_7SEG_Buffer [ digito-1 ]  	 & (uint8_t) 0x01));
	SetPIN (BCD_B, (DISPLAY_7SEG_Buffer [ digito-1 ] >>1 & (uint8_t) 0x01));
	SetPIN (BCD_C, (DISPLAY_7SEG_Buffer [ digito-1 ] >>2 & (uint8_t) 0x01));
	SetPIN (BCD_D, (DISPLAY_7SEG_Buffer [ digito-1 ] >>3 & (uint8_t) 0x01));

	if(!digito) {	//a cada comienzo de ciclo reseteo
		SetPIN(BCD_RST, 0);
		SetPIN(BCD_RST, 1);
		digito = CANTIDAD_DIGITOS;
	}
	else {	//para desplazarse entre dígitos usamos CLK
		SetPIN(BCD_RST, 0);
		SetPIN(BCD_CK, 0);
		SetPIN(BCD_CK, 1);
	}

	digito--;
}


void DISPLAY_7SEG_Print(uint32_t Dato)
{
	uint32_t	i;

	for(i = 0 ; i < CANTIDAD_DIGITOS ; i++)
	{
		DISPLAY_7SEG_Buffer[i] = Dato % 10; //Tabla_Digitos_BCD_7seg[Dato % 10];
		Dato /= 10;
	}
}

void DISPLAY_7SEG_Print_v2(uint16_t valor, uint8_t display)
{
	uint8_t i, auxDisplay[CANTIDAD_DIGITOS/2];

	for(i = 0; i < CANTIDAD_DIGITOS/2; i++){
		auxDisplay[i] = valor % 10;
		valor /= 10;
	}

	switch(display){
		case DSP_ROJO:
			DISPLAY_7SEG_Buffer[2] = auxDisplay[2];
			DISPLAY_7SEG_Buffer[1] = auxDisplay[1];
			DISPLAY_7SEG_Buffer[0] = auxDisplay[0];
			break;
		case DSP_VERDE:
			DISPLAY_7SEG_Buffer[5] = auxDisplay[2];
			DISPLAY_7SEG_Buffer[4] = auxDisplay[1];
			DISPLAY_7SEG_Buffer[3] = auxDisplay[0];
			break;
		default:
			break;
	}
}
