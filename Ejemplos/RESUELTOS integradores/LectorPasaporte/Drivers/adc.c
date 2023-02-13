#include "Regs_LPC845.h"
#include "adc.h"
#include "swm.h"

uint8_t adc_flag;
uint32_t resultadoADC;

void ADC_Init(void)
{
    // Energizo el ADC
    SYSCON->PDRUNCFG &= ~(1<<4);

    // Habilito el Cloclk para el ADC
    SYSCON->SYSAHBCLKCTRL0 |= (1<<24);

    // Habilito el Cloclk para la SWM
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

