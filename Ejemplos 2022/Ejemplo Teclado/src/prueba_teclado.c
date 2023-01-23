#include <cr_section_macros.h>

#include <stdio.h>
#include <stdint.h>

#include <registers.h>

/*
 * Usaremos un teclado matricial de 3x3
 *
 * Activo alto
 * Las salidas estan en las filas
 *
 * Fila 1 -> GPIO 0,16
 * Fila 2 -> GPIO 0,17
 * Fila 3 -> GPIO 0,18
 * Colu 1 -> GPIO 0,19
 * Colu 2 -> GPIO 0,20
 * Colu 3 -> GPIO 0,21
 */

#define		MAT_KBRD_FILAS		3
#define		MAT_KBRD_COLUMNAS	3

#define		MAT_KBRD_NO_KEY		0xFF

#define		MAT_KBRD_R1_PORT	0
#define		MAT_KBRD_R1_PIN		16

#define		MAT_KBRD_R2_PORT	0
#define		MAT_KBRD_R2_PIN		17

#define		MAT_KBRD_R3_PORT	0
#define		MAT_KBRD_R3_PIN		18

#define		MAT_KBRD_C1_PORT	0
#define		MAT_KBRD_C1_PIN		19

#define		MAT_KBRD_C2_PORT	0
#define		MAT_KBRD_C2_PIN		20

#define		MAT_KBRD_C3_PORT	0
#define		MAT_KBRD_C3_PIN		21

#define		MAT_KBRD_R1		MAT_KBRD_R1_PORT,MAT_KBRD_R1_PIN
#define		MAT_KBRD_R2		MAT_KBRD_R2_PORT,MAT_KBRD_R2_PIN
#define		MAT_KBRD_R3		MAT_KBRD_R3_PORT,MAT_KBRD_R3_PIN

#define		MAT_KBRD_C1		MAT_KBRD_C1_PORT,MAT_KBRD_C1_PIN
#define		MAT_KBRD_C2		MAT_KBRD_C2_PORT,MAT_KBRD_C2_PIN
#define		MAT_KBRD_C3		MAT_KBRD_C3_PORT,MAT_KBRD_C3_PIN

#define		SYSTICK_SYST_CSR		(*((volatile uint32_t *)(0xE000E010)))
#define		SYSTICK_SYST_RVR		(*((volatile uint32_t *)(0xE000E014)))

#define		SYSTICK_SYST_CSR_ENABLE_MASK	(1 << 0)
#define		SYSTICK_SYST_CSR_TICKINT_MASK	(1 << 1)
#define		SYSTICK_SYST_CSR_CLKSOURCE_MASK	(1 << 2)

#define		SYSAHBCLKCTRL0			(*((volatile uint32_t *)(0x40048080)))

#define		GPIO_DIR0		(*((volatile uint32_t *)(0xA0002000)))
#define		GPIO_DIR1		(*((volatile uint32_t *)(0xA0002004)))

#define		GPIO_PIN0		(*((volatile uint32_t *)(0xA0002100)))
#define		GPIO_PIN1		(*((volatile uint32_t *)(0xA0002104)))

#define		IOCON_BASE_ADDR	(0x40044000)
#define		IOCON_PIN0_0	(*(volatile uint32_t *)(IOCON_BASE_ADDR + 0x044))
#define		IOCON_PIN0_1	(*(volatile uint32_t *)(IOCON_BASE_ADDR + 0x02C))
#define		IOCON_PIN0_2	(*(volatile uint32_t *)(IOCON_BASE_ADDR + 0x018))
#define		IOCON_PIN0_3	(*(volatile uint32_t *)(IOCON_BASE_ADDR + 0x014))
#define		IOCON_PIN0_4	(*(volatile uint32_t *)(IOCON_BASE_ADDR + 0x010))
#define		IOCON_PIN0_5	(*(volatile uint32_t *)(IOCON_BASE_ADDR + 0x00C))

#define		IOCON_PIN0_19	(*(volatile uint32_t *)(IOCON_BASE_ADDR + 0x074))
#define		IOCON_PIN0_20	(*(volatile uint32_t *)(IOCON_BASE_ADDR + 0x070))
#define		IOCON_PIN0_21	(*(volatile uint32_t *)(IOCON_BASE_ADDR + 0x06C))

#define		TIEMPO_SYSTICK_US	(10 * 1000)
#define		TIEMPO_ANTIRREBOTE_US	(50 * 1000)
#define		CONTADOR_MAX		(TIEMPO_ANTIRREBOTE_US / TIEMPO_SYSTICK_US)

typedef struct {
	uint32_t port;
	uint32_t pin;
} portpin_t;

typedef struct {
	uint32_t fila;
	uint32_t columna;
} tecla_t;

portpin_t filas_teclado[MAT_KBRD_FILAS] = {
		{ .port = MAT_KBRD_R1_PORT, .pin = MAT_KBRD_R1_PIN },
		{ .port = MAT_KBRD_R2_PORT, .pin = MAT_KBRD_R2_PIN },
		{ .port = MAT_KBRD_R3_PORT, .pin = MAT_KBRD_R3_PIN },
};

portpin_t columnas_teclado[MAT_KBRD_COLUMNAS] = {
		{ .port = MAT_KBRD_C1_PORT, .pin = MAT_KBRD_C1_PIN },
		{ .port = MAT_KBRD_C2_PORT, .pin = MAT_KBRD_C2_PIN },
		{ .port = MAT_KBRD_C3_PORT, .pin = MAT_KBRD_C3_PIN },
};

void gpio_config_dir(uint32_t puerto, uint32_t pin, uint32_t dir) {
	if (!dir) {
		// Entrada
		if (!puerto) {
			// Puerto 0
			GPIO_DIR0 &= ~(1 << pin);
		} else {
			// Puerto 1
			GPIO_DIR1 &= ~(1 << pin);
		}
	} else {
		// Salida
		if (!puerto) {
			// Puerto 0
			GPIO_DIR0 |= (1 << pin);
		} else {
			// Puerto 1
			GPIO_DIR1 |= (1 << pin);
		}
	}
}

uint32_t gpio_read_pin(uint32_t puerto, uint32_t pin) {
	if (!puerto) {
		// Puerto 0
		if (GPIO_PIN0 & (1 << pin)) {
			return 1;
		} else {
			return 0;
		}
	} else {
		// Puerto 1
		// Otra forma!!!:
//		return (GPIO_PIN1 & (1 << pin)) >> pin;

		if (GPIO_PIN1 & (1 << pin)) {
			return 1;
		} else {
			return 0;
		}
	}
}

void gpio_write_pin(uint32_t puerto, uint32_t pin, uint32_t valor) {
	if (!puerto) {
		// Puerto 0
		if (!valor) {
			GPIO_PIN0 &= ~(1 << pin);
		} else {
			GPIO_PIN0 |= (1 << pin);
		}
	} else {
		// Puerto 1
		if (!valor) {
			GPIO_PIN1 &= ~(1 << pin);
		} else {
			GPIO_PIN1 |= (1 << pin);
		}
	}
}

void config_matrix_keyboard(void) {
	SYSCON_SYSAHBCLKCTRL0_ADDR->GPIO0=1;
	SYSCON_SYSAHBCLKCTRL0_ADDR->GPIO1=1;

	// Habilitamos IOCON para poder utilizar los pulls
	SYSCON_SYSAHBCLKCTRL0_ADDR->IOCON=1;

	// Habilitamos pull-down de las columnas
	IOCON_PIN0_19 &= ~(0x03 << 3); // Garantizamos los ceros en los lugares que necesitamos
	IOCON_PIN0_19 |= (0x01 << 3); // Para luego garantizar el valor completo

	IOCON_PIN0_20 &= ~(0x03 << 3);
	IOCON_PIN0_20 |= (0x01 << 3);

	IOCON_PIN0_21 &= ~(0x03 << 3);
	IOCON_PIN0_21 |= (0x01 << 3);

	gpio_config_dir(MAT_KBRD_R1, 1);
	gpio_config_dir(MAT_KBRD_R2, 1);
	gpio_config_dir(MAT_KBRD_R3, 1);
	gpio_config_dir(MAT_KBRD_C1, 0);
	gpio_config_dir(MAT_KBRD_C2, 0);
	gpio_config_dir(MAT_KBRD_C3, 0);
}

void config_systick(void) {
	SYSTICK_SYST_RVR = 120000; // Configuramos el tiempo de cuenta de systick a 10ms (f_systick ~= f_cpu / RELOAD)
	SYSTICK_SYST_CSR |= SYSTICK_SYST_CSR_CLKSOURCE_MASK | SYSTICK_SYST_CSR_TICKINT_MASK;
	SYSTICK_SYST_CSR |= SYSTICK_SYST_CSR_ENABLE_MASK;
}

void mtx_kbd_barrido(tecla_t *tecla) {
	uint32_t tecla_presionada = 0;
	uint32_t fila, columna;

	tecla->fila = MAT_KBRD_NO_KEY;
	tecla->columna = MAT_KBRD_NO_KEY;

	for (fila = 0; fila < MAT_KBRD_FILAS; fila++) {
		// Fijamos todas las salidas en estado bajo
		gpio_write_pin(filas_teclado[fila].port, filas_teclado[fila].pin, 0);
	}

	for (fila = 0; (fila < MAT_KBRD_FILAS) && (tecla_presionada == 0); fila++) {
		// Fijamos la fila de esta ronda del barrido a estado alto
		gpio_write_pin(filas_teclado[fila].port, filas_teclado[fila].pin, 1);
		gpio_write_pin(filas_teclado[fila].port, filas_teclado[fila].pin, 1);
		gpio_write_pin(filas_teclado[fila].port, filas_teclado[fila].pin, 1);

		for (columna = 0; (columna < MAT_KBRD_COLUMNAS) && (tecla_presionada == 0); columna++) {
			if (gpio_read_pin(columnas_teclado[columna].port, columnas_teclado[columna].pin)) {
				tecla_presionada = 1;
				tecla->fila = fila;
				tecla->columna = columna;
			}
		}

		// Volvemos la fila de esta ronda del barrido a estado bajo
		gpio_write_pin(filas_teclado[fila].port, filas_teclado[fila].pin, 0);
		gpio_write_pin(filas_teclado[fila].port, filas_teclado[fila].pin, 0);
		gpio_write_pin(filas_teclado[fila].port, filas_teclado[fila].pin, 0);
	}
}

uint32_t buffer_tecla = MAT_KBRD_NO_KEY;
uint32_t validada = MAT_KBRD_NO_KEY;
uint32_t anterior = MAT_KBRD_NO_KEY;
uint32_t cont = 0;

uint32_t decodificar_tecla(const tecla_t *tecla) {
	static const uint32_t decodificador[MAT_KBRD_FILAS][MAT_KBRD_COLUMNAS] = {
			{ 7, 8, 9 },
			{ 4, 5, 6 },
			{ 1, 2, 3 },
	};

	if ((tecla->fila < MAT_KBRD_FILAS) && (tecla->columna < MAT_KBRD_COLUMNAS)) {
		return decodificador[tecla->fila][tecla->columna];
	}

	return MAT_KBRD_NO_KEY;
}

void mtx_kbd_debounce(const tecla_t *tecla_nueva) {
	uint32_t nueva = decodificar_tecla(tecla_nueva);

	if (validada == nueva) {
		anterior = nueva;
		cont = 0;
	} else {
		if (anterior == nueva) {
			cont++;

			if (cont >= CONTADOR_MAX) {
				buffer_tecla = nueva;
				validada = nueva;
				cont = 0;
			}
		} else {
			anterior = nueva;
			cont = 0;
		}
	}
}

uint32_t getTecla(void) {
	// Para hacer las cosas seguras, en este punto tendriamos que inhabilitar la interrupcion de systick
	uint32_t ret = buffer_tecla;
	buffer_tecla = MAT_KBRD_NO_KEY;
	// Para hacer las cosas seguras, en este punto tendriamos que volver a habilitar la interrupcion de systick
	return ret;
}

void SysTick_Handler(void) {
	tecla_t tecla_nueva;
	mtx_kbd_barrido(&tecla_nueva);
	mtx_kbd_debounce(&tecla_nueva);
}

int main(void) {
	uint32_t tecla = MAT_KBRD_NO_KEY;

	config_matrix_keyboard();
	config_systick();

    while(1) {
    	tecla = getTecla();

    	if (tecla != MAT_KBRD_NO_KEY) {
    		printf("Tecla presionada: %d\n", tecla);
    	}
    }

    return 0 ;
}
