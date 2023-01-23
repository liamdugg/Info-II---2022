/*
 * adc.c
 *
 *  Created on: 26 abr. 2021
 *      Author: root
 */

#include "fsl_common.h"
#include "adc.h"


/***********************************************************************************************************************************
 *** VARIABLES GLOBALES PUBLICAS
 **********************************************************************************************************************************/
volatile uint32_t valorADC1[ MAX_MUESTRAS ];

volatile uint8_t ADCFlag = 1;
adc_result_info_t adcResultInfoStruct;




/**
	\fn  	int16_t ADC_Promedio( uint8_t canal )
	\brief 	Retorna el valor cuentas asociado a un canal
 	\author Ing. Marcelo Trujillo
 	\date 	29 de oct. de 2017
 	\param 	void
	\return lectura de entrada analogica 2
*/
int16_t ADC_Promedio( uint8_t canal )
{
	int32_t promedio = 0 , i ;

	for ( i = 0 ; i < MAX_MUESTRAS ; i++ )
		promedio += valorADC1[ i ];

	promedio /= MAX_MUESTRAS;

	return promedio;
}


uint8_t temperatura(void){
	int32_t valorPromedio;

	valorPromedio = ADC_Promedio(ADC_DEMO_CH);
	valorPromedio *= 100;
	valorPromedio /= 4095;
	return valorPromedio;
}



/**
	\fn  	int16_t Potenciometro ( void )
	\brief 	Retorna el valor de tension asociado al potenciometro
 	\author Ing. Marcelo Trujillo
 	\date 	29 de oct. de 2017
	\return lectura del pote (rango 0 a 3.3V )
*/
int16_t Potenciometro ( void )
{
	int32_t cuentas;

	cuentas = ADC_Promedio( ADC_DEMO_CH );
	return (uint16_t)cuentas;
}

/* ADC0_SEQA_IRQn interrupt handler */
void ADC0_ADC_SEQ_A_IRQHANDLER(void) {
  /* Get status flags */
//	ADCFlag = 1;

	static uint32_t muestra = 0;

	if (kADC_ConvSeqAInterruptFlag == (kADC_ConvSeqAInterruptFlag & ADC_GetStatusFlags(ADC0_PERIPHERAL)))
	{
		/* Place your interrupt code here */
		ADC_GetChannelConversionResult(ADC0_PERIPHERAL,ADC_DEMO_CH, &adcResultInfoStruct);
		valorADC1[muestra] = adcResultInfoStruct.result;
		muestra++;                                        	// para disminuir el ruido
		muestra %= MAX_MUESTRAS;
  	/* Clear status flags */
		ADC_ClearStatusFlags(ADC0_PERIPHERAL, kADC_ConvSeqAInterruptFlag);
	}

  /* Add for ARM errata 838869, affects Cortex-M4, Cortex-M4F
     Store immediate overlapping exception return operation might vector to incorrect interrupt. */
  #if defined __CORTEX_M && (__CORTEX_M == 4U)
    __DSB();
  #endif
}
