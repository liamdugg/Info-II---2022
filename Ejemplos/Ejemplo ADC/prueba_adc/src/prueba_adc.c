#include <cr_section_macros.h>

#include <adc.h>
#include <usart.h>
#include <systick.h>

int main(void) {
	adc_init();
	systick_init();
	usart_init();

	uint64_t last_tick = 0;
	uint16_t adc_0, adc_1;

	while (1) {
		// Cada 1000 msegs
		if (systick_tick_time() - last_tick > 1000) {
			last_tick = systick_tick_time();
			adc_start_conversion();
		}

		if (adc_finished(&adc_0, &adc_1)) {
			usart_send(((adc_0 / 1000) % 10) + '0');
			usart_send(((adc_0 / 100) % 10) + '0');
			usart_send(((adc_0 / 10) % 10) + '0');
			usart_send(((adc_0 / 1) % 10) + '0');

			usart_send(',');

			usart_send(((adc_1 / 1000) % 10) + '0');
			usart_send(((adc_1 / 100) % 10) + '0');
			usart_send(((adc_1 / 10) % 10) + '0');
			usart_send(((adc_1 / 1) % 10) + '0');

			usart_send('\r');
			usart_send('\n');
		}
	}

    return 0;
}
