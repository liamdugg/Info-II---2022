#include "Regs_LPC845.h"

#define		BCD_A		0,20
#define		BCD_B		0,23
#define		BCD_C		0,22
#define		BCD_D		0,21

#define		BCD_RST		0,18
#define		BCD_CK		0,19

#define		CANTIDAD_DIGITOS	6

#define		DSP_ROJO	0
#define		DSP_VERDE	1

void init_Display(void);
void Barrido_Display(void);
void Display(uint32_t Dato);