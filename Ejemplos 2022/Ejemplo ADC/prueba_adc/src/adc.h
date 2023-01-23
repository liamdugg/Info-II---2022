#ifndef ADC_H_
#define ADC_H_

#include <stdint.h>

#define		ENABLE_SINGLESTEP		(0)

void adc_init(void);

void adc_start_conversion(void);

uint32_t adc_finished(uint16_t *channel_0, uint16_t *channel_1);

#endif /* ADC_H_ */
