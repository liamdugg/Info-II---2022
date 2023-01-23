#include <cr_section_macros.h>
#include <stdint.h>

#define		PINTSEL0				(*((volatile uint32_t *)(0x40048178)))
#define		SYSAHBCLKCTRL0			(*((volatile uint32_t *)(0x40048080)))

#define		GPIO_INT_BIT			(28)
#define		GPIO_INT_ENABLE_MASK	(1 << GPIO_INT_BIT)
#define		GPIO_INT_DISBLE_MASK	~GPIO_INT_ENABLE_MASK

#define		ISER0					(*((volatile uint32_t *)(0xE000E100)))

#define		ISEL					(*((volatile uint32_t *)(0xA0004000)))
#define		ENRL					(*((volatile uint32_t *)(0xA0004004)))
#define		RISE					(*((volatile uint32_t *)(0XA000401C)))

volatile uint32_t contador = 0;

void PININT0_IRQHandler(void) {
	RISE |= (1 << 0);
	contador++;
}

void pinint_set_rising_edge_mode(uint32_t channel) {
	ISEL &= ~(1 << channel);
}

int main(void) {
	PINTSEL0 |= 4; // Configuramos la GPIO0_4 como fuente del canal PININT0
	SYSAHBCLKCTRL0 |= GPIO_INT_ENABLE_MASK; // Habilitamos clock del periferico PININT

	// Seleccionamos que las interrupciones van a ser por FLANCO
	// (Con un 1 serian por nivel)
	pinint_set_rising_edge_mode(0);

	// Seleccionamos si el flanco va a ser ASCENDENTE (1) o DESCENDENTE (0)
	ENRL |= (1 << 0);

	ISER0 |= (1 << 24); // Habilitamos interrupcion de PININT0 en el NVIC

    while(1) {

    }

    return 0 ;
}
