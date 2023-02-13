#include "Regs_LPC845.h"
#include "adc.h"

#define LED     1,5
#define DIV     600000

#define PWM_BASE    0x40000000
#define PWM         (*((volatile uint32_t *)(PWM_BASE)))

uint32_t dato_adc;

void init_PWM  (void)
{
    PWM = 0;
    PWM &= ~(1<<0);
    PWM |= 50<<3; //50%

    PWM |= 37<<10;

    // f = 30M/DIV
    // DIV = 30M/f
    // f =   1/T = 1/2ms = 500Hz
    // DIV = 30M/500 = 60000
    PWM |= 60000<<15;
}

void set_intensidad()
{
    uint32_t porcentaje;
    porcentaje = dato_adc*100/4095;

    PWM &= ~(0x7F << 3);

    PWM |= ((uint8_t)porcentaje << 3);
}
void ADC_SEQA_IRQHandler(void)
{
    dato_adc = (uint32_t)(ADC_DAT[1] >> 4); 
}
