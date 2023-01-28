#include "Regs_LPC845.h"
#include "adc.h"
#include "swm.h"

uint8_t adc_flag;
uint32_t resultadoADC;

void ADC_Init(void)
{
    // Energizo el ADC
    SYSCON->PDRUNCFG &= ~(1<<4);

    // Habilito el Clock para el ADC
    SYSCON->SYSAHBCLKCTRL0 |= (1<<24);

    // Habilito el Clock para la SWM
    SYSCON->SYSAHBCLKCTRL0 |= (1<<7);

    // Habilito un pin para el adc Port 0 Pin 7
    // Canal 0 del ADC

    SWM_PINENABLE0 &= ~(1<<14);

    // Apago el Cloclk para la SWM ya que no lo voy usar otra vez
    SYSCON->SYSAHBCLKCTRL0 &= ~(1<<7);

    // quiero muestrear a 100kHz = freq
    // 30MHz/DIVISOR = freq x 25
    // DIVISOR = 30MHz / 2,5MHz
    // DIVISOR = 12 --> 1100
    ADC_CTRL &= ~(0xff); // limpio el registro control
    ADC_CTRL |= (12);

    // Habilito el modo continuo (BURST)
    // ADC_CTRL |= (1<<27);

    // Seleccione cual de los canales va a ser muestreado por el ADC
    ADC_SEQA_CTRL |= (0xFFF); // limpio el registro control
    ADC_SEQA_CTRL &= ~(1<<0); // selecciono el canal 0

    // Selecciono para que la interrupcion se ejecute al muestrear todos los canales
    ADC_SEQA_CTRL |= (1<<0);

    // Habilito las interrupciones para la secuencia A del ADC
    ADC_SEQA_CTRL |= (1<<31);

    // Habilito en el NVIC las interrupciones del ADC
    ISER0 |= (1<<16);

}

void Start_ADC(void)
{
    ADC_SEQA_CTRL |= (1<<26);
}

void ADC_SEQA_IRQHandler(void) 
{
    static uint8_t posicion = 0;
    static uint32_t buffer_muestras[TAM_BUFFER_ADC];
    uint32_t auxiliar = 0;

    // me guardo del registro ADC0_DAT el valor de la conversion
    buffer_muestras[posicion] = (ADC_DAT[0] >> 4) & (0xFFF);
    posicion++;
    if (posicion == TAM_BUFFER_ADC)
    {
        for(int i = 0; i < TAM_BUFFER_ADC; i++)
            auxiliar  += buffer_muestras[i];

        resultadoADC = auxiliar/TAM_BUFFER_ADC;
        posicion = 0;
        adc_flag = 1;
    }
    ADC_FLAGS |= (1 << 28); 
}
