#include <cr_section_macros.h>

#include <stdint.h>

#include <leds.h>
#include <registers.h>

#define		PINTSEL0				(*((volatile uint32_t *)(0x40048178)))
#define		SYSAHBCLKCTRL0			(*((volatile uint32_t *)(0x40048080)))

#define		GPIO_INT_BIT			(28)
#define		GPIO_INT_ENABLE_MASK	(1 << GPIO_INT_BIT)
#define		GPIO_INT_DISBLE_MASK	~GPIO_INT_ENABLE_MASK

#define		NVIC_ISER0				(*((volatile uint32_t *)(0xE000E100)))

#define		PININT_ISEL				(*((volatile uint32_t *)(0xA0004000)))
#define		PININT_ENRL				(*((volatile uint32_t *)(0xA0004004)))
#define		PININT_RISE				(*((volatile uint32_t *)(0XA000401C)))

#define		SYSTICK_SYST_CSR		(*((volatile uint32_t *)(0xE000E010)))
#define		SYSTICK_SYST_RVR		(*((volatile uint32_t *)(0xE000E014)))

#define		SYSTICK_SYST_CSR_ENABLE_MASK	(1 << 0)
#define		SYSTICK_SYST_CSR_TICKINT_MASK	(1 << 1)
#define		SYSTICK_SYST_CSR_CLKSOURCE_MASK	(1 << 2)

#define		TECLA_ON						(1)
#define		TECLA_OFF						(0)

#define		TIMER_VENCIDO					(2)
#define		TIMER_CORRIENDO					(1)
#define		TIMER_DETENIDO					(0)

#define		APAGADO							(0)
#define		ENCENDIDO						(1)

volatile uint32_t tecla = TECLA_OFF;
volatile uint32_t vencio_timer = TIMER_DETENIDO;
volatile uint32_t contador_timer = 0;

void SysTick_Handler(void) {
	if (vencio_timer == TIMER_CORRIENDO) {
		contador_timer++;

		if (contador_timer == 200) {
			vencio_timer = TIMER_VENCIDO;
			contador_timer = 0;
		}
	}
}

void PININT0_IRQHandler(void) {
	PININT_RISE |= (1 << 0);
	tecla = TECLA_ON;
}

void configLeds(void) {
	SYSCON_SYSAHBCLKCTRL0_ADDR->GPIO1=1;

	GPIO_DIR1_ADDR->PIO1_0=1;
	GPIO_SET1_ADDR->PIO1_0=1;

	GPIO_DIR1_ADDR->PIO1_1=1;
	GPIO_SET1_ADDR->PIO1_1=1;

	GPIO_DIR1_ADDR->PIO1_2=1;
	GPIO_SET1_ADDR->PIO1_2=1;
}

void configTimer(void) {
	SYSTICK_SYST_RVR = 120000; // Configuramos el tiempo de cuenta de systick a 10ms (f_systick ~= f_cpu / RELOAD)
	SYSTICK_SYST_CSR |= SYSTICK_SYST_CSR_CLKSOURCE_MASK | SYSTICK_SYST_CSR_TICKINT_MASK;
	SYSTICK_SYST_CSR |= SYSTICK_SYST_CSR_ENABLE_MASK;
}

void pinint_set_rising_edge_mode(uint32_t channel) {
	PININT_ISEL &= ~(1 << channel);
}

void configPint(void) {
	PINTSEL0 |= 4; // Configuramos la GPIO0_4 como fuente del canal PININT0
	SYSAHBCLKCTRL0 |= GPIO_INT_ENABLE_MASK; // Habilitamos clock del periferico PININT

	// Seleccionar fuente de interrupcion:
	// *Flanco* / nivel
	pinint_set_rising_edge_mode(0);

	// Configuramos tipo de flanco:
	// *Ascendente* / descendente
	PININT_ENRL |= (1 << 0);

	NVIC_ISER0 |= (1 << 24); // Habilitamos interrupcion de PININT0 en el NVIC
}

uint32_t getTecla(void) {
	// Para hacer que esto sea seguro:
	// Inhabilito interrupcion que afecta a tecla (PININT0)
	// Guardamos en valor auxiliar el valor de tecla
	// Habilitamos interrupcion que afecta a tecla (PININT0)
	uint32_t aux = tecla;
	tecla = TECLA_OFF;
	return aux;
}

void arrancarTimer(void) {
	// Para hacerlo de forma segura, inhabilitamos la interrupcion de systick (TICKINT)
	// Arrancamos el timer
	// Habilitamos la interrupcion de systick (TICKINT)
	vencio_timer = TIMER_CORRIENDO;
	contador_timer = 0;
}

void stopTimer(void) {
	// Para hacerlo de forma segura, inhabilitamos la interrupcion de systick (TICKINT)
	// Detenemos el timer
	// Habilitamos la interrupcion de systick (TICKINT)
	vencio_timer = TIMER_DETENIDO;
	contador_timer = 0;
}

uint32_t vencioTimer(void) {
	return vencio_timer == TIMER_VENCIDO ? 1 : 0;
}

int main(void) {
	configLeds();
	configTimer();
	configPint();

    while(1) {
    	static uint8_t estado = APAGADO;

    	switch (estado) {
    	case APAGADO:
    		if (getTecla() == TECLA_ON) {
    			SET_LED(LED_GREEN);
    			arrancarTimer();
    			estado = ENCENDIDO;
    		}

    		break;
    	case ENCENDIDO:
    		if (vencioTimer()) {
    			CLEAR_LED(LED_GREEN);
    			stopTimer();
    			estado = APAGADO;
    		}

    	    break;

    	default:
    		CLEAR_LED(LED_GREEN);
    		stopTimer();
    	    break;
    	}
    }

    return 0 ;
}
