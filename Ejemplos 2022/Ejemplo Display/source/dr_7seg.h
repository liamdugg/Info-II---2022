#ifndef OS_DISPLAY_7SEG_DRIVER_H_
#define OS_DISPLAY_7SEG_DRIVER_H_
#include "stdint.h"

#define		BCD_A		0,20
#define		BCD_B		0,23
#define		BCD_C		0,22
#define		BCD_D		0,21

#define		BCD_RST		0,18
#define		BCD_CK		0,19

#define		CANTIDAD_DIGITOS	6

#define		DSP_ROJO	0
#define		DSP_VERDE	1

void DISPLAY_7SEG_Inicializar(void);
void DISPLAY_7SEG_Barrido(void);
void DISPLAY_7SEG_Barrido_v2(void);
void DISPLAY_7SEG_Print(uint32_t);
void DISPLAY_7SEG_Print_v2(uint16_t, uint8_t );

#endif /* OS_DISPLAY_7SEG_DRIVER_H_ */
