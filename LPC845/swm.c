#include <swm.h>
#include "Regs_LPC845.h"

void swm_power_on(void) {
	SYSCON -> SYSAHBCLKCTRL0 |= (1 << 7);
}

void swm_power_off(void) {
	SYSCON -> SYSAHBCLKCTRL0 &= ~(1 << 7);
}

void swm_select_usart0_txd(uint32_t port, uint32_t pin) {
	
	SWM_PINASSIGN0 &= ~(0x000000FF); 				// aseguro un 0 en los primeros 8 bits
	SWM_PINASSIGN0 |= (port  * 32) + pin; 			// asigno el pin como uart Tx
}

void swm_select_usart0_rxd(uint32_t port, uint32_t pin) {
	SWM_PINASSIGN0 &= ~(0x000000FF << 8); 			// aseguro un 0 en los siguientes 8 bits
	SWM_PINASSIGN0 |= ((port  * 32) + pin) << 8;	// asigno el pin como uart Rx
}
