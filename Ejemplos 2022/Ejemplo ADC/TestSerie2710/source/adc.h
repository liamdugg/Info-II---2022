/*
 * adc.h
 *
 *  Created on: 26 abr. 2021
 *      Author: root
 */

#ifndef ADC_H_
#define ADC_H_
#include "peripherals.h"
#include "fsl_adc.h"

#define MAX_MUESTRAS	128

#define ADC_DEMO_CH	0

/***********************************************************************************************************************************
 *** VARIABLES GLOBALES
 **********************************************************************************************************************************/
extern volatile uint32_t valorADC1[ MAX_MUESTRAS ];
extern volatile uint32_t valorADC2[ MAX_MUESTRAS ];
extern volatile uint32_t valorADC5[ MAX_MUESTRAS ];

int16_t Potenciometro ( void );
uint8_t temperatura(void);

#endif /* ADC_H_ */
