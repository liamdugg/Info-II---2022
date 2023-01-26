#ifndef SWM_H_
#define SWM_H_

#include <stdint.h>

void swm_power_on(void);
void swm_power_off(void);

void swm_select_usart0_txd(uint32_t port, uint32_t pin);
void swm_select_usart0_rxd(uint32_t port, uint32_t pin);

#endif /* SWM_H_ */
