#include "Teclado.h"
#include "Regs_LPC845.h"

// EJEMPLO DE TECLADO MATRICIAL DE 2X2 -- ADAPTAR A LO QUE SEA NECESARIO

uint8_t bufKey;

void initTeclado(void){

	// SI NO SE HABILITO EL CLOCK PARA GPIO HABILITAR ACA
	// SYSCON->SYSAHBCLKCTRL0 = 1;
	// SYSCON->SYSAHBCLKCTRL1 = 1;

	SetDIR(FILA0, SALIDA);
	SetPINMODE_OUT(IOCON_INDEX_PIO0_1, PUSH_PULL);
	SetPIN(FILA0, 1); // APAGADO

	SetDIR(FILA1, SALIDA);
	SetPINMODE_OUT(IOCON_INDEX_PIO0_2, PUSH_PULL);
	SetPIN(FILA1, 1); // APAGADO

	SetDIR(COL0, ENTRADA);
	SetPINMODE_IN(IOCON_INDEX_PIO0_2, PULL_UP);
	
	SetDIR(COL1, ENTRADA);
	SetPINMODE_IN(IOCON_INDEX_PIO0_2, PULL_UP);
}

uint8_t barridoTeclado(void){

	// HABILITAMOS 1 FILA y LAS OTRAS SE DESHABILITAN
	SetPIN(FILA0,0);
	SetPIN(FILA1,1);
	// GIURA HACE EL SET PIN 2 VECES PARA HACER TIEMPO Y QUE LLEGUE LA PULSACION DE LA TECLA A TIEMPO

	if(!GetPIN(COL0)) return TECLA1;
	if(!GetPIN(COL1)) return TECLA2;

	// CAMBIAMOS LA FILA HABILITADA
	SetPIN(FILA0,1);
	SetPIN(FILA1,0);
	
	if(!GetPIN(COL0)) return TECLA3;
	if(!GetPIN(COL1)) return TECLA4;

	return NO_KEY;
}

void debounceTeclado(uint8_t tecla){

	static uint8_t estado = REPOSO;
	static uint8_t teclaVieja = NO_KEY;
	static uint8_t cont = 0;

	switch (estado){

		case REPOSO:
			
			cont = 0;
			teclaVieja = NO_KEY;

			if(tecla != NO_KEY){
				teclaVieja = tecla;
				estado = DETECCION;
			}

			break;
		
		case DETECCION:

			if(tecla == teclaVieja && cont < TICKS_DEBOUNCE){
				cont++;
				estado = DETECCION;
			}
			
			else if(cont == TICKS_DEBOUNCE){
				bufKey = teclaVieja;
				estado = REPOSO;
			}

			else if(tecla != teclaVieja && tecla != NO_KEY){
				cont = 0;
				teclaVieja = tecla;
			}

			else 
				estado = REPOSO;
			
			break;
		
		default:
			estado = REPOSO;
			break;
	}

}

uint8_t getKey(){
	
	uint8_t tecla = NO_KEY;

	if(bufKey != NO_KEY){
		tecla = bufKey;
		bufKey = NO_KEY;
	}

	return tecla;
}

void driverTeclado(void){
	uint8_t tecla = NO_KEY;
	tecla = barridoTeclado();
	debounceTeclado(tecla);
}