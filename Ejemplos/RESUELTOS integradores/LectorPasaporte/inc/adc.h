#include <stdint.h>

#define		ADC_CTRL						(*((volatile uint32_t *)(0x4001C000)))
#define		ADC_SEQA_CTRL					(*((volatile uint32_t *)(0x4001C008)))
#define		ADC_SEQB_CTRL					(*((volatile uint32_t *)(0x4001C00C)))

#define		ADC_FLAGS						(*((volatile uint32_t *)(0x4001C068)))

#define		ADC_DAT							(((volatile uint32_t *)(0x4001C020)))
#define		ADC_SEQA_GDAT					(*((volatile uint32_t *)(0x4001C010)))
#define		ADC_SEQB_GDAT					(*((volatile uint32_t *)(0x4001C014)))

#define     TAM_BUFFER_ADC                  10

void ADC_Init(void);
void Start_ADC(void);
void ADC_SEQA_IRQHandler(void) ;