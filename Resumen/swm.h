#ifndef SWM_H_
#define SWM_H_

#define		SWM_PINASSIGN0				(*((volatile uint32_t *)(0x4000C000)))
#define		SWM_PINENABLE0				(*((volatile uint32_t *)(0x4000C1C0)))
#define		SYSCON_SYSAHBCLKCTRL0		(*((volatile uint32_t *)(0x40048080)))

void swm_power_on(void);
void swm_power_off(void);

void swm_select_usart0_txd(uint32_t port, uint32_t pin);
void swm_select_usart0_rxd(uint32_t port, uint32_t pin);

#endif /* SWM_H_ */
