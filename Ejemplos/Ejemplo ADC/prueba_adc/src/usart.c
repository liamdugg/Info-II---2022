#include <usart.h>

#include <swm.h>

#define		NVIC_ISER0					(*((volatile uint32_t *)(0xE000E100)))
#define		NVIC_CLR0					(*((volatile uint32_t *)(0xE000E180)))

#define		SYSCON_SYSAHBCLKCTRL0		(*((volatile uint32_t *)(0x40048080)))
#define		SYSCON_PRESETCTRL0			(*((volatile uint32_t *)(0x40048088)))
#define		SYSCON_UART0CLKSEL			(*((volatile uint32_t *)(0x40048090)))

#define		USART0_CFG					(*((volatile uint32_t *)(0x40064000)))
#define		USART0_CTL					(*((volatile uint32_t *)(0x40064004)))
#define		USART0_STAT					(*((volatile uint32_t *)(0x40064008)))
#define		USART0_INTENSET				(*((volatile uint32_t *)(0x4006400C)))
#define		USART0_INTENCLR				(*((volatile uint32_t *)(0x40064010)))
#define		USART0_RXDAT				(*((volatile uint32_t *)(0x40064014)))
#define		USART0_RXDATSTAT			(*((volatile uint32_t *)(0x40064018)))
#define		USART0_TXDAT				(*((volatile uint32_t *)(0x4006401C)))
#define		USART0_BRG					(*((volatile uint32_t *)(0x40064020)))

#define 	USART_STAT_RXRDY_MASK		(1 << 0)
#define		USART_STAT_TXRDY_MASK		(1 << 2)

#define		RX_BUFF_SIZE				(64)
#define		TX_BUFF_SIZE				(64)

static volatile uint8_t __rx_buff[RX_BUFF_SIZE];
static volatile uint32_t __rx_empty = 1;
static volatile uint32_t __rx_full = 0;
static volatile uint32_t __rx_in_idx = 0;
static volatile uint32_t __rx_out_idx = 0;

static volatile uint8_t __tx_buff[TX_BUFF_SIZE];
static volatile uint32_t __tx_empty = 1;
static volatile uint32_t __tx_full = 0;
static volatile uint32_t __tx_in_idx = 0;
static volatile uint32_t __tx_out_idx = 0;

static uint32_t __usart_push_rx(uint8_t dato) {
	uint32_t ret = 0;

	if (!__rx_full) {
		ret = 1;
		__rx_buff[__rx_in_idx] = dato;
		__rx_empty = 0;
		__rx_in_idx = (__rx_in_idx + 1) % RX_BUFF_SIZE;

		if (__rx_in_idx == __rx_out_idx) {
			__rx_full = 1;
		}
	}

	return ret;
}

static uint32_t __usart_pop_rx(uint8_t *dato) {
	uint32_t ret = 0;

	if (!__rx_empty) {
		ret = 1;
		*dato = __rx_buff[__rx_out_idx];
		__rx_full = 0;
		__rx_out_idx = (__rx_out_idx + 1) % RX_BUFF_SIZE;

		if (__rx_in_idx == __rx_out_idx) {
			__rx_empty = 1;
		}
	}

	return ret;
}

static uint32_t __usart_push_tx(uint8_t dato) {
	uint32_t ret = 0;

	if (!__tx_full) {
		ret = 1;
		__tx_buff[__tx_in_idx] = dato;
		__tx_empty = 0;
		__tx_in_idx = (__tx_in_idx + 1) % TX_BUFF_SIZE;

		if (__tx_in_idx == __tx_out_idx) {
			__tx_full = 1;
		}
	}

	return ret;
}

static uint32_t __usart_pop_tx(uint8_t *dato) {
	uint32_t ret = 0;

	if (!__tx_empty) {
		ret = 1;
		*dato = __tx_buff[__tx_out_idx];
		__tx_full = 0;
		__tx_out_idx = (__tx_out_idx + 1) % TX_BUFF_SIZE;

		if (__tx_in_idx == __tx_out_idx) {
			__tx_empty = 1;
		}
	}

	return ret;
}

void usart_init() {
	// Habilitamos clock para la USART0
	SYSCON_SYSAHBCLKCTRL0 |= (1 << 14);

	// Seleccionamos fuente de clock para la USART0
	SYSCON_UART0CLKSEL = 0;

	// Efectuamos el reset del periferico USART0
	SYSCON_PRESETCTRL0 &= ~(1 << 14);
	SYSCON_PRESETCTRL0 &= ~(1 << 14);
	SYSCON_PRESETCTRL0 &= ~(1 << 14);
	SYSCON_PRESETCTRL0 |= (1 << 14);
	SYSCON_PRESETCTRL0 |= (1 << 14);
	SYSCON_PRESETCTRL0 |= (1 << 14);

	// Configuramos los pines a utilizar de la USART0
	swm_power_on();
	swm_select_usart0_rxd(0, 24);
	swm_select_usart0_txd(0, 25);
	swm_power_off();

	// Habilitamos USART0
	USART0_CFG |= (1 << 0);

	// Fijamos 8 bits de datos
	USART0_CFG &= ~(3 << 2);
	USART0_CFG |= (1 << 2);

	// Fijamos sin paridad
	USART0_CFG &= ~(3 << 4);

	// Fijamos 1 bit de stop
	USART0_CFG &= ~(1 << 6);

	// Configuramos baudrate 9600
	// BRGVAL = (FCLK/((OSRVAL + 1) x baud rate)) – 1
	// BRGVAL = (12MHz / ((15 + 1) * 9600)) - 1
	// BRGVAL = 77,125
	// BRGVAL = 77
	USART0_BRG = 77;

	// Habilitamos interrupciones RXRDY y TXRDY
	USART0_INTENSET |= (1 << 0) | USART_STAT_TXRDY_MASK;

	// Habilitamos interrupciones de USART0 en NVIC
	NVIC_ISER0 |= (1 << 3);
}

int32_t usart_read() {
	uint8_t dato;
	uint32_t ret;
	NVIC_CLR0 |= (1 << 3);
	ret = __usart_pop_rx(&dato);
	NVIC_ISER0 |= (1 << 3);
	return ret ? dato : -1;
}

int32_t usart_send(uint8_t dato) {
	uint32_t ret;
	NVIC_CLR0 |= (1 << 3);
	ret = __usart_push_tx(dato);
	USART0_INTENSET |= USART_STAT_TXRDY_MASK;
	NVIC_ISER0 |= (1 << 3);
	return ret;
}

void UART0_IRQHandler(void) {
	if (USART0_STAT & USART_STAT_RXRDY_MASK) {
		uint32_t dato = USART0_RXDAT; // Explicitamos lectura del registro para borrar el bit de recepcion lista
		dato &= 0xFF; // Truncamos el valor leido para que quede dentro del rango de 8 bits
		uint32_t ret = __usart_push_rx((uint8_t) dato);
		// No utilizamos ret para nuestra aplicacion
		(void) ret;
	}

	if (USART0_STAT & USART_STAT_TXRDY_MASK) {
		if (__tx_empty) {
			USART0_INTENCLR |= USART_STAT_TXRDY_MASK;
		} else {
			uint8_t dato;
			__usart_pop_tx(&dato);
			USART0_TXDAT = dato;
		}
	}
}
