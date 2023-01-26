#include "AP_FuncionesMDE.h"
#include "Regs_LPC845.h"
#include "AP_Inicializacion.h"
#include "Teclado.h"
#include "timer.h"

#define CAFE	0
#define CORTADO	1
#define TE		2

#define E0		-1
#define E1		-2
#define	E2		-3
#define E3		-4

#define O1		1
#define O2		2
#define O3		3

extern int moneda;
extern int eleccion;

void PININT0_IRQHandler(void){
	RISE |= (1 << 0);
	moneda = 1;
}

void SysTick_Handler(void){
	AnalizarTimers();
	driverTeclado();
}

int m_dev_mon(void){
	SetPIN(DEV_COIN_PORT,DEV_COIN_PIN, 0);
	return E0;
}

void m_dev_mon_off(void){
	SetPIN(DEV_COIN_PORT,DEV_COIN_PIN, 1);
}

int m_preparar_pedido(int pedido){

	if(pedido == CAFE)
		return O1;

	else if(pedido == CORTADO)
		return O2;

	else if(pedido == TE)
		return O3;

	return 0;
}

int hayStock(int pedido){

	static uint32_t cafe = 10;
	static uint32_t cortado = 8;
	static uint32_t te = 5;

	switch(pedido){

		case CAFE:

			if(cafe){
				cafe--;
				return 1;
			}

			else return E1;
			break;

		case CORTADO:

			if(cortado){
				cortado--;
				return 1;
			}

			else return E2;
			break;

		case TE:

			if(te){
				te--;
				return 1;
			}

			else return E3;
			break;

	}

	return E0;
}



