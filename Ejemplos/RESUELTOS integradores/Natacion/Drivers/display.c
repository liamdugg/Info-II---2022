#include "display.h"
#include "Regs_LPC845.h"
#include "Fun_GPIO.h"

// Buffer Display 7 Segmentos
uint8_t	DISPLAY_7SEG_Buffer[CANTIDAD_DIGITOS];

void init_Display(void)
{
    SetDIR(BCD_A,SALIDA);
    SetDIR(BCD_B,SALIDA);
    SetDIR(BCD_C,SALIDA);
    SetDIR(BCD_D,SALIDA);
    SetDIR(BCD_RST,SALIDA);
    SetDIR(BCD_CK,SALIDA);

    SetPINMODE_OUT(IOCON_INDEX_PIO0_20, PUSH_PULL);
    SetPINMODE_OUT(IOCON_INDEX_PIO0_23, PUSH_PULL);
    SetPINMODE_OUT(IOCON_INDEX_PIO0_22, PUSH_PULL);
    SetPINMODE_OUT(IOCON_INDEX_PIO0_21, PUSH_PULL);
    SetPINMODE_OUT(IOCON_INDEX_PIO0_18, PUSH_PULL);
    SetPINMODE_OUT(IOCON_INDEX_PIO0_19, PUSH_PULL);

    SetPIN(BCD_A,APAGADO);
    SetPIN(BCD_B,APAGADO);
    SetPIN(BCD_C,APAGADO);
    SetPIN(BCD_D,APAGADO);
    SetPIN(BCD_RST,APAGADO);
    SetPIN(BCD_CK,APAGADO);
}

void Barrido_Display(void)
{
	static uint8_t digito = 0;

	SetPIN (BCD_A, 1);
	SetPIN (BCD_B, 1);
	SetPIN (BCD_C, 1);
	SetPIN (BCD_D, 1);

	SetPIN (BCD_A, (DISPLAY_7SEG_Buffer [ digito ]  	 & (uint8_t) 0x01));
	SetPIN (BCD_B, (DISPLAY_7SEG_Buffer [ digito ] >>1 & (uint8_t) 0x01));
	SetPIN (BCD_C, (DISPLAY_7SEG_Buffer [ digito ] >>2 & (uint8_t) 0x01));
	SetPIN (BCD_D, (DISPLAY_7SEG_Buffer [ digito ] >>3 & (uint8_t) 0x01));

    // el clock es para el contador que vaya cambiando de cuadradito de display
	if(!digito) {	//a cada comienzo de ciclo reseteo
		SetPIN(BCD_RST, 0);
		SetPIN(BCD_RST, 1);
	}
	else {	//para desplazarse entre dígitos usamos CLK
		SetPIN(BCD_CK, 0);
		SetPIN(BCD_CK, 1);
	}

	digito++;
    digito %= CANTIDAD_DIGITOS;
}

void Display(uint32_t Dato) //103327
{
	uint32_t i;

	for(i = 0 ; i < CANTIDAD_DIGITOS ; i++)
	{
		DISPLAY_7SEG_Buffer[i] = Dato % 10; //Tabla_Digitos_BCD_7seg[Dato % 10];
		Dato /= 10;
	}
}
