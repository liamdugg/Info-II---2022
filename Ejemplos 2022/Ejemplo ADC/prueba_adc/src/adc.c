#include <adc.h>

#include <stdint.h>

#include <swm.h>

#define		ADC_CTRL						(*((volatile uint32_t *)(0x4001C000)))
#define		ADC_SEQA_CTRL					(*((volatile uint32_t *)(0x4001C008)))
#define		ADC_SEQB_CTRL					(*((volatile uint32_t *)(0x4001C00C)))

// ATENCION: Este registro esta definido como puntero, no como contenido de puntero.
// De esta manera, podriamos hacer ADC_DAT[5] para acceder a los datos del canal 5
#define		ADC_DAT							(((volatile uint32_t *)(0x4001C020)))

#define		ADC_INTEN						(*((volatile uint32_t *)(0x4001C064)))
#define		ADC_FLAGS						(*((volatile uint32_t *)(0x4001C068)))

#define		NVIC_ISER0						(*((volatile uint32_t *)(0xE000E100)))
#define		NVIC_ISER0_ADC_SEQA_MASK		(1 << 16)
#define		NVIC_ICER0						(*((volatile uint32_t *)(0xE000E180)))
#define		NVIC_ICER0_ADC_SEQA_MASK		(1 << 16)

#define		SYSCON_ADC_CLK_DIV				(*((volatile uint32_t *)(0x40048068)))

#define		SYSCON_SYSAHBCLKCTRL0			(*((volatile uint32_t *)(0x40048080)))
#define		SYSCON_SYSAHBCLKCTRL0_ADC_MASK	((uint32_t)(1 << 24))

#define		SYSCON_PDRUNCFG					(*((volatile uint32_t *)(0x40048238)))
#define		SYSCON_PDRUNCFG_ADC_MASK		(1 << 4)

static volatile uint32_t __adc_finished = 0;
static volatile uint32_t __adc_result_0;
static volatile uint32_t __adc_result_1;

static void __adc_set_clkdiv(uint8_t div) {
	ADC_CTRL &= ~0x000000FF;
	ADC_CTRL |= div;
}

static void __adc_seqa_set_channels(uint16_t channels) {
	ADC_SEQA_CTRL &= ~0x000003FF;
	ADC_SEQA_CTRL |= (channels & 0x03FF);
}

static void __adc_seqa_set_mode_end_of_conversion(void) {
	ADC_SEQA_CTRL &= ~(1 << 30);
}

static void __adc_seqa_set_mode_end_of_sequence(void) {
	ADC_SEQA_CTRL |= (1 << 30);
}

static void __adc_seqa_enable_sequence(void) {
	ADC_SEQA_CTRL |= (1 << 31);
}

static void __adc_inten_enable_seqa(void) {
	ADC_INTEN |= (1 << 0);
}

void adc_init(void) {
	// Primero habilitamos alimentacion del periferico
	SYSCON_PDRUNCFG &= ~SYSCON_PDRUNCFG_ADC_MASK;

	// Habilitamos clock del periferico
	SYSCON_SYSAHBCLKCTRL0 |= SYSCON_SYSAHBCLKCTRL0_ADC_MASK;

	// Fijamos divisor del clock del ADC a nivel SYSCON en 1
	SYSCON_ADC_CLK_DIV = 1;

	// Habilitamos pines 0_7 y 0_6 como canales de ADC 0 y 1 respectivamente
	swm_power_on();
	swm_enable_adc(0);
	swm_enable_adc(1);
	swm_power_off();

	// Seleccionamos divisor del clock a nivel del periferico en 1

	// NOTA 1: Si bien se coloca cero en el divisor, recordar que la division es
	// por ese valor +1

	// NOTA 2: Con el FRO a 12MHz, y ambos divisores (SYSCON y periferico) en 1, la
	// frecuencia de conversion obtenida es de 12MHz / 25 = 480KHz. Con lo que una
	// conversion tomara ~2.08usec
	__adc_set_clkdiv(0);

	// Configuramos secuencia de conversion A para canales 0 y 1
	__adc_seqa_set_channels(0b000000000011);

	// Configuramos modo para que la interrupcion se efectue al finalizar toda la secuencia
	__adc_seqa_set_mode_end_of_sequence();

	// Habilitamos secuencia de conversion A
	__adc_seqa_enable_sequence();

	// Habilitamos interrupciones para fin de conversion de secuencia A
	__adc_inten_enable_seqa();

	// Habilitamos interrupciones en el NVIC
	NVIC_ISER0 |= NVIC_ISER0_ADC_SEQA_MASK;
}

void adc_start_conversion(void) {
	ADC_SEQA_CTRL |= (1 << 26);
}

uint32_t adc_finished(uint16_t *channel_0, uint16_t *channel_1) {
	// NOTA: Guardo el valor actual del NVIC_ISER dado que de no hacerlo, por alguna razon
	// que al momento no logro descifrar, tambien inhabilita las interrupciones del periferico
	// USART pero luego no vuelve a habilitarlas
	uint32_t ret = 0;
	uint32_t aux = NVIC_ISER0;

	NVIC_ICER0 |= NVIC_ICER0_ADC_SEQA_MASK;
	if (__adc_finished) {
		__adc_finished = 0;
		*channel_0 = (__adc_result_0 >> 4) & 0x3FF;
		*channel_1 = (__adc_result_1 >> 4) & 0x3FF;
		ret = 1;
	}
	NVIC_ISER0 |= aux | NVIC_ISER0_ADC_SEQA_MASK;

	return ret;
}

void ADC_SEQA_IRQHandler(void) {
	__adc_result_0 = ADC_DAT[0];
	__adc_result_1 = ADC_DAT[1];
	// Esta interrupcion va a ser generada cuando se haya convertido una secuencia completa de los dos canales
	// Para limpiar el flag de interrupcion en estos casos, hay que escribir un 1 en SEQA_INT del registro FLAGS
	ADC_FLAGS |= (1 << 28);
	__adc_finished = 1;
	// El resultado se encuentra en los bits 15:4 de los registros, pero esa conversion la haremos en la funcion adc_finished
}
