/*
 * gpio.c
 *
 *  Created on: 5 ago. 2021
 *      Author: root
 */
#include "main.h"



void SetPIN(uint32_t Puerto, uint32_t Pin, uint32_t Estado)
{
	if(Estado)
		GPIO->SET[Puerto] = (1 << Pin);
	else
		GPIO->CLR[Puerto] = (1 << Pin);
}

void SetDIR(uint32_t Puerto, uint32_t Pin, uint32_t Direccion)
{
	if(Direccion)
		GPIO->DIRSET[Puerto] = (1 << Pin);
	else
		GPIO->DIRCLR[Puerto] = (1 << Pin);
}

uint32_t GetPIN(uint32_t Puerto, uint32_t Pin)
{
	if(GPIO->PIN[Puerto] & (1 << Pin))
	{
		// Entro por 1
		return 1;
	}
	else
	{
		// Entro por 0
		return 0;
	}
}





void SetPINMODE_IN(uint32_t Pin, uint32_t Modo){
    IOCON->PIO[Pin] = ((IOCON->PIO[Pin] & (~(IOCON_PIO_MODE_MASK))) | IOCON_PIO_MODE(Modo));
}

void SetPINMODE_OUT(uint32_t Pin, uint32_t Modo){
    IOCON->PIO[Pin] = ((IOCON->PIO[Pin] & (~(IOCON_PIO_OD_MASK))) | IOCON_PIO_OD(Modo));
}
