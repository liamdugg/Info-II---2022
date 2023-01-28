#include <swm.h>

#define		SWM_PINASSIGN0				(*((volatile uint32_t *)(0x4000C000)))

#define		SYSCON_SYSAHBCLKCTRL0		(*((volatile uint32_t *)(0x40048080)))

void swm_power_on(void) {
	SYSCON_SYSAHBCLKCTRL0 |= (1 << 7);
}

void swm_power_off(void) {
	SYSCON_SYSAHBCLKCTRL0 &= ~(1 << 7);
}

void swm_select_usart0_txd(uint32_t port, uint32_t pin) {
	SWM_PINASSIGN0 &= ~(0x000000FF);
	SWM_PINASSIGN0 |= (port  * 32) + pin;
}

void swm_select_usart0_rxd(uint32_t port, uint32_t pin) {
	SWM_PINASSIGN0 &= ~(0x000000FF << 8);
	SWM_PINASSIGN0 |= ((port  * 32) + pin) << 8;
}
