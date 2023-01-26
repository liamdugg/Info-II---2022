#include <systick.h>

#include <stdint.h>

#define		SYSTICK_SYST_CSR		(*((volatile uint32_t *)(0xE000E010)))
#define		SYSTICK_SYST_RVR		(*((volatile uint32_t *)(0xE000E014)))

#define		SYSTICK_SYST_CSR_ENABLE_MASK	(1 << 0)
#define		SYSTICK_SYST_CSR_TICKINT_MASK	(1 << 1)
#define		SYSTICK_SYST_CSR_CLKSOURCE_MASK	(1 << 2)

static volatile uint64_t __tick = 0;

void SysTick_Handler(void) {
	__tick++;
}

void systick_init(void) {
	SYSTICK_SYST_RVR = 12000; // Configuramos el tiempo de cuenta de systick a 1ms (f_systick ~= f_cpu / RELOAD)
	SYSTICK_SYST_CSR |= SYSTICK_SYST_CSR_CLKSOURCE_MASK | SYSTICK_SYST_CSR_TICKINT_MASK;
	SYSTICK_SYST_CSR |= SYSTICK_SYST_CSR_ENABLE_MASK;
}

uint64_t systick_tick_time(void) {
	uint64_t tick;
	SYSTICK_SYST_CSR &= ~SYSTICK_SYST_CSR_ENABLE_MASK;
	tick = __tick;
	SYSTICK_SYST_CSR |= SYSTICK_SYST_CSR_ENABLE_MASK;
	return tick;
}
