#include "Regs_LPC845.h"
#include "Fun_GPIO.h"

// Pines asignados a cada fila / columna de la matriz
#define FILA0	0,1
#define FILA1	0,2
#define COL0	0,3
#define COL1	0,4

#define NO_KEY	255
#define TECLA1	'1'
#define TECLA2	'2'
#define TECLA3	'3'
#define TECLA4  '#'

#define	REPOSO		0
#define	DETECCION	1

#define TICKS_DEBOUNCE 50

uint8_t barridoTeclado(void);
void debounceTeclado(uint8_t tecla);
uint8_t getKey();
void driverTeclado(void);