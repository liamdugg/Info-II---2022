#include <swm.h>

#define		SWM_PINASSIGN0				(*((volatile uint32_t *)(0x4000C000)))
#define		SWM_PINENABLE0				(*((volatile uint32_t *)(0x4000C1C0)))

#define		SYSCON_SYSAHBCLKCTRL0		(*((volatile uint32_t *)(0x40048080)))

// La siguiente funcion macro nos permite tener todas las mascaras de canales necesarios en una unica definicion
#define		SWM_PINENABLE0_ADC_MASK(x)		(1 << (14 + x))

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

void swm_enable_adc(uint8_t channel) {
	SWM_PINENABLE0 &= ~SWM_PINENABLE0_ADC_MASK(channel);
}
