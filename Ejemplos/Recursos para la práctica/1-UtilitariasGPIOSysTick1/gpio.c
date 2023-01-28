/*
 * gpio.c
 *
 *  Created on: 5 ago. 2021
 *      Author: root
 */
#include "main.h"


/**
	\fn  	void SetPIN(uint32_t Puerto, uint32_t Pin, uint32_t Estado)
	\brief 	Escribe un valor en pin de GPIO
 	\author Ing. Gabriel Soccodato
 	\date 	28 de Julio de 2021
 	\param 	uint32_t Puerto: puerto de  GPIO
 	\param 	uint32_t Pin: puerto de  Pin de puerto GPIO
 	\param 	uint32_t Estado: estado que quiero que tome el pin
 	\return void
*/
void SetPIN(uint32_t Puerto, uint32_t Pin, uint32_t Estado)
{
	if(Estado)
		GPIO->SET[Puerto] = (1 << Pin);
	else
		GPIO->CLR[Puerto] = (1 << Pin);
}

/**
	\fn  	void SetDIR(uint32_t Puerto, uint32_t Pin, uint32_t Direccion)
	\brief 	Configura la dirección de unb puerto de GPIO como entrada o salida
 	\author Ing. Gabriel Soccodato
 	\date 	28 de Julio de 2021
 	\param 	uint32_t Puerto: puerto de  GPIO
 	\param 	uint32_t Pin: puerto de  Pin de puerto GPIO
 	\param 	uint32_t Direccion: dirección que debe tener el pin; SALIDA o ENTRADA
 	\return void
*/
void SetDIR(uint32_t Puerto, uint32_t Pin, uint32_t Direccion)
{
	if(Direccion)
		GPIO->DIRSET[Puerto] = (1 << Pin);
	else
		GPIO->DIRCLR[Puerto] = (1 << Pin);
}


/**
	\fn  	uint32_t GetPIN(uint32_t Puerto, uint32_t Pin)
	\brief 	Lee entrada de GPIO
 	\author Ing. Gabriel Soccodato
 	\date 	28 de Julio de 2021
 	\param 	uint32_t Puerto: puerto de  GPIO
 	\param 	uint32_t Pin: puerto de  Pin de puerto GPIO
 	\return estado del pin; puede ser 0 o 1
*/
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



/**
	\fn  	void SetPINMODE_IN(uint32_t Pin, uint32_t Modo)
	\brief 	Configura el modo eléctrico de una entrada
 	\author Ing. Gabriel Soccodato
 	\date 	28 de Julio de 2021
 	\param 	uint32_t Pin: offset del registro del pin en IOCON
 	\param 	uint32_t Modo: Modo de entrada; NO_PULL, PULL_DOWN, PULL_UP y REP
 	\return void
*/
void SetPINMODE_IN(uint32_t PuertoPin, uint32_t Modo){
    IOCON->PIO[PuertoPin] = ((IOCON->PIO[PuertoPin] & (~(IOCON_PIO_MODE_MASK))) | IOCON_PIO_MODE(Modo));
}

/**
	\fn  	void SetPINMODE_OUT(uint32_t Pin, uint32_t Modo)
	\brief 	Configura el modo eléctrico de una salida
 	\author Ing. Gabriel Soccodato
 	\date 	28 de Julio de 2021
 	\param 	uint32_t Pin: offset del registro del pin en IOCON
 	\param 	uint32_t Modo: Modo de salida; PUSH_PULL, OPEN_DRAIN
 	\return void
*/
void SetPINMODE_OUT(uint32_t PuertoPin, uint32_t Modo){
    IOCON->PIO[PuertoPin] = ((IOCON->PIO[PuertoPin] & (~(IOCON_PIO_OD_MASK))) | IOCON_PIO_OD(Modo));
}
