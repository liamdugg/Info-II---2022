/*
 * registers.h
 *
 *  Created on: Aug 15, 2022
 *      Author: asantini
 */

#ifndef REGISTERS_H_
#define REGISTERS_H_

typedef struct {
	unsigned int PIO1_0 : 1;
	unsigned int PIO1_1 : 1;
	unsigned int PIO1_2 : 1;
	unsigned int PIO1_3 : 1;
	unsigned int PIO1_4 : 1;
	unsigned int PIO1_5 : 1;
	unsigned int PIO1_6 : 1;
	unsigned int PIO1_7 : 1;
	unsigned int PIO1_8 : 1;
	unsigned int PIO1_9 : 1;
	unsigned int PIO1_10 : 1;
	unsigned int PIO1_11 : 1;
	unsigned int PIO1_12 : 1;
	unsigned int PIO1_13 : 1;
	unsigned int PIO1_14 : 1;
	unsigned int PIO1_15 : 1;
	unsigned int PIO1_16 : 1;
	unsigned int PIO1_17 : 1;
	unsigned int PIO1_18 : 1;
	unsigned int PIO1_19 : 1;
	unsigned int PIO1_20 : 1;
	unsigned int PIO1_21 : 1;
}GPIO_PORT1_t;

typedef struct{
	unsigned int : 1;
	unsigned int : 1;
	unsigned int : 1;
	unsigned int : 1;
	unsigned int : 1;
	unsigned int I2C0 : 1;
	unsigned int GPIO0 : 1;
	unsigned int : 1;
	unsigned int SCT : 1;
	unsigned int WKT : 1;
	unsigned int MRT : 1;
	unsigned int SPI0 : 1;
	unsigned int SPI1 : 1;
	unsigned int CRC : 1;
	unsigned int UART0 : 1;
	unsigned int UART1 : 1;
	unsigned int UART2 : 1;
	unsigned int WWDT : 1;
	unsigned int IOCON : 1;
	unsigned int ACMP : 1;
	unsigned int GPIO1 : 1;
	unsigned int I2C1 : 1;
	unsigned int I2C2 : 1;
	unsigned int I2C3 : 1;
	unsigned int ADC : 1;
	unsigned int CTIMER0 : 1;
	unsigned int MTB : 1;
	unsigned int DAC0 : 1;
	unsigned int GPIO_INT : 1;
	unsigned int DMA : 1;
	unsigned int UART3 : 1;
	unsigned int UART4 : 1;
}SYSCON_SYSAHBCLKCTRL0_t;

#define SYSCON_BASE_ADDR (0x40048000)
#define GPIO_BASE_ADDR (0xA0000000)

#define SYSCON_SYSAHBCLKCTRL0_ADDR ((volatile SYSCON_SYSAHBCLKCTRL0_t *)(SYSCON_BASE_ADDR + 0x80))

#define GPIO_DIR1_ADDR ((volatile GPIO_PORT1_t *)(GPIO_BASE_ADDR + 0x2004))
#define GPIO_PIN1_ADDR ((volatile GPIO_PORT1_t *)(GPIO_BASE_ADDR + 0x2104))
#define GPIO_CLR1_ADDR ((volatile GPIO_PORT1_t *)(GPIO_BASE_ADDR + 0x2284))
#define GPIO_SET1_ADDR ((volatile GPIO_PORT1_t *)(GPIO_BASE_ADDR + 0x2204))


#endif /* REGISTERS_H_ */
