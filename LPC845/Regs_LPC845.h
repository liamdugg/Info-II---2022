/*
 * LPC845Regs.h
 *
 *  Created on: 28 jul. 2021
 *      Author: socco
 */

#ifndef LPC845_H_
#define LPC845_H_

typedef signed char 	int8_t;
typedef unsigned char 	uint8_t;
typedef short 			int16_t;
typedef unsigned short 	uint16_t;
typedef int 			int32_t;
typedef unsigned int 	uint32_t;

#define   __I     	volatile const       /*!< Defines 'read only' permissions */

#define     __O     volatile             /*!< Defines 'write only' permissions */
#define     __IO    volatile             /*!< Defines 'read / write' permissions */

/* following defines should be used for structure members */
#define     __IM     volatile const      /*! Defines 'read only' structure member permissions */
#define     __OM     volatile            /*! Defines 'write only' structure member permissions */
#define     __IOM    volatile            /*! Defines 'read / write' structure member permissions */

/* ----------------------------------------------------------------------------
   -- SYSCON Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup SYSCON_Peripheral_Access_Layer SYSCON Peripheral Access Layer
 * @{
 */

/** SYSCON - Register Layout Typedef */
typedef struct {
  __IO uint32_t SYSMEMREMAP;                       /**< System Remap register, offset: 0x0 */
       uint8_t RESERVED_0[4];
  __IO uint32_t SYSPLLCTRL;                        /**< PLL control, offset: 0x8 */
  __I  uint32_t SYSPLLSTAT;                        /**< PLL status, offset: 0xC */
       uint8_t RESERVED_1[16];
  __IO uint32_t SYSOSCCTRL;                        /**< system oscillator control, offset: 0x20 */
  __IO uint32_t WDTOSCCTRL;                        /**< Watchdog oscillator control, offset: 0x24 */
  __IO uint32_t FROOSCCTRL;                        /**< FRO oscillator control, offset: 0x28 */
       uint8_t RESERVED_2[4];
  __IO uint32_t FRODIRECTCLKUEN;                   /**< FRO direct clock source update enable register, offset: 0x30 */
       uint8_t RESERVED_3[4];
  __IO uint32_t SYSRSTSTAT;                        /**< System reset status register, offset: 0x38 */
       uint8_t RESERVED_4[4];
  __IO uint32_t SYSPLLCLKSEL;                      /**< System PLL clock source select register, offset: 0x40 */
  __IO uint32_t SYSPLLCLKUEN;                      /**< System PLL clock source update enable register, offset: 0x44 */
  __IO uint32_t MAINCLKPLLSEL;                     /**< Main clock source select register, offset: 0x48 */
  __IO uint32_t MAINCLKPLLUEN;                     /**< Main clock source update enable register, offset: 0x4C */
  __IO uint32_t MAINCLKSEL;                        /**< Main clock source select register, offset: 0x50 */
  __IO uint32_t MAINCLKUEN;                        /**< Main clock source update enable register, offset: 0x54 */
  __IO uint32_t SYSAHBCLKDIV;                      /**< System clock divider register, offset: 0x58 */
       uint8_t RESERVED_5[4];
  __IO uint32_t CAPTCLKSEL;                        /**< CAPT clock source select register, offset: 0x60 */
  __IO uint32_t ADCCLKSEL;                         /**< ADC clock source select register, offset: 0x64 */
  __IO uint32_t ADCCLKDIV;                         /**< ADC clock divider register, offset: 0x68 */
  __IO uint32_t SCTCLKSEL;                         /**< SCT clock source select register, offset: 0x6C */
  __IO uint32_t SCTCLKDIV;                         /**< SCT clock divider register, offset: 0x70 */
  __IO uint32_t EXTCLKSEL;                         /**< external clock source select register, offset: 0x74 */
       uint8_t RESERVED_6[8];
  __IO uint32_t SYSAHBCLKCTRL0;                    /**< System clock group 0 control register, offset: 0x80 */
  __IO uint32_t SYSAHBCLKCTRL1;                    /**< System clock group 1 control register, offset: 0x84 */
  __IO uint32_t PRESETCTRL0;                       /**< Peripheral reset group 0 control register, offset: 0x88 */
  __IO uint32_t PRESETCTRL1;                       /**< Peripheral reset group 1 control register, offset: 0x8C */
  __IO uint32_t FCLKSEL[11];                       /**< peripheral clock source select register. FCLK0SEL~FCLK4SEL are for UART0~UART4 clock source select register. FCLK5SEL~FCLK8SEL are for I2C0~I2C3 clock source select register. FCLK9SEL~FCLK10SEL are for SPI0~SPI1 clock source select register., array offset: 0x90, array step: 0x4 */
       uint8_t RESERVED_7[20];
  struct {                                         /* offset: 0xD0, array step: 0x10 */
    __IO uint32_t FRGDIV;                            /**< fractional generator N divider value register, array offset: 0xD0, array step: 0x10 */
    __IO uint32_t FRGMULT;                           /**< fractional generator N multiplier value register, array offset: 0xD4, array step: 0x10 */
    __IO uint32_t FRGCLKSEL;                         /**< FRG N clock source select register, array offset: 0xD8, array step: 0x10 */
         uint8_t RESERVED_0[4];
  } FRG[2];
  __IO uint32_t CLKOUTSEL;                         /**< CLKOUT clock source select register, offset: 0xF0 */
  __IO uint32_t CLKOUTDIV;                         /**< CLKOUT clock divider registers, offset: 0xF4 */
       uint8_t RESERVED_8[4];
  __IO uint32_t EXTTRACECMD;                       /**< External trace buffer command register, offset: 0xFC */
  __I  uint32_t PIOPORCAP[2];                      /**< POR captured PIO N status register(PIO0 has 32 PIOs, PIO1 has 22 PIOs), array offset: 0x100, array step: 0x4 */
       uint8_t RESERVED_9[44];
  __IO uint32_t IOCONCLKDIV6;                      /**< Peripheral clock 6 to the IOCON block for programmable glitch filter, offset: 0x134 */
  __IO uint32_t IOCONCLKDIV5;                      /**< Peripheral clock 6 to the IOCON block for programmable glitch filter, offset: 0x138 */
  __IO uint32_t IOCONCLKDIV4;                      /**< Peripheral clock 4 to the IOCON block for programmable glitch filter, offset: 0x13C */
  __IO uint32_t IOCONCLKDIV3;                      /**< Peripheral clock 3 to the IOCON block for programmable glitch filter, offset: 0x140 */
  __IO uint32_t IOCONCLKDIV2;                      /**< Peripheral clock 2 to the IOCON block for programmable glitch filter, offset: 0x144 */
  __IO uint32_t IOCONCLKDIV1;                      /**< Peripheral clock 1 to the IOCON block for programmable glitch filter, offset: 0x148 */
  __IO uint32_t IOCONCLKDIV0;                      /**< Peripheral clock 0 to the IOCON block for programmable glitch filter, offset: 0x14C */
  __IO uint32_t BODCTRL;                           /**< BOD control register, offset: 0x150 */
  __IO uint32_t SYSTCKCAL;                         /**< System tick timer calibration register, offset: 0x154 */
       uint8_t RESERVED_10[24];
  __IO uint32_t IRQLATENCY;                        /**< IRQ latency register, offset: 0x170 */
  __IO uint32_t NMISRC;                            /**< NMI source selection register, offset: 0x174 */
  __IO uint32_t PINTSEL[8];                        /**< Pin interrupt select registers N, array offset: 0x178, array step: 0x4 */
       uint8_t RESERVED_11[108];
  __IO uint32_t STARTERP0;                         /**< Start logic 0 pin wake-up enable register 0, offset: 0x204 */
       uint8_t RESERVED_12[12];
  __IO uint32_t STARTERP1;                         /**< Start logic 0 pin wake-up enable register 1, offset: 0x214 */
       uint8_t RESERVED_13[24];
  __IO uint32_t PDSLEEPCFG;                        /**< Deep-sleep configuration register, offset: 0x230 */
  __IO uint32_t PDAWAKECFG;                        /**< Wake-up configuration register, offset: 0x234 */
  __IO uint32_t PDRUNCFG;                          /**< Power configuration register, offset: 0x238 */
       uint8_t RESERVED_14[444];
  __I  uint32_t DEVICE_ID;                         /**< Part ID register, offset: 0x3F8 */
} SYSCON_Type;


/*! @name SYSAHBCLKCTRL0 - System clock group 0 control register */
/*! @{ */
#define SYSCON_SYSAHBCLKCTRL0_GPIO0_MASK         (0x40U)
#define SYSCON_SYSAHBCLKCTRL0_GPIO0_SHIFT        (6U)
#define SYSCON_SYSAHBCLKCTRL0_GPIO1_MASK         (0x100000U)
#define SYSCON_SYSAHBCLKCTRL0_GPIO1_SHIFT        (20U)



/* SYSCON - Peripheral instance base addresses */
/** Peripheral SYSCON base address */
#define SYSCON_BASE                              (0x40048000u)
/** Peripheral SYSCON base pointer */
#define SYSCON                                   ((SYSCON_Type *)SYSCON_BASE)
/** Array initializer of SYSCON peripheral base addresses */



/* ----------------------------------------------------------------------------
   -- IOCON Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup IOCON_Peripheral_Access_Layer IOCON Peripheral Access Layer
 * @{
 */

/** IOCON - Register Layout Typedef */
typedef struct {
  __IO uint32_t PIO[56];                           /**< Digital I/O control for pins PIO0_17..Digital I/O control for pins PIO1_10, array offset: 0x0, array step: 0x4 */
} IOCON_Type;

/* ----------------------------------------------------------------------------
   -- IOCON Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup IOCON_Register_Masks IOCON Register Masks
 * @{
 */

/*! @name PIO - Digital I/O control for pins PIO0_17..Digital I/O control for pins PIO1_10 */
/*! @{ */
#define IOCON_PIO_MODE_MASK                      (0x18U)
#define IOCON_PIO_MODE_SHIFT                     (3U)
/*! MODE - Selects function mode (on-chip pull-up/pull-down resistor control).
 *  0b00..Inactive. Inactive (no pull-down/pull-up resistor enabled).
 *  0b01..Pull-down. Pull-down resistor enabled.
 *  0b10..Pull-up. Pull-up resistor enabled.
 *  0b11..Repeater. Repeater mode.
 */
#define IOCON_PIO_MODE(x)                        (((uint32_t)(((uint32_t)(x)) << IOCON_PIO_MODE_SHIFT)) & IOCON_PIO_MODE_MASK)
#define IOCON_PIO_HYS_MASK                       (0x20U)
#define IOCON_PIO_HYS_SHIFT                      (5U)
/*! HYS - Hysteresis.
 *  0b0..Disable
 *  0b1..Enable
 */
#define IOCON_PIO_HYS(x)                         (((uint32_t)(((uint32_t)(x)) << IOCON_PIO_HYS_SHIFT)) & IOCON_PIO_HYS_MASK)
#define IOCON_PIO_INV_MASK                       (0x40U)
#define IOCON_PIO_INV_SHIFT                      (6U)
/*! INV - Invert input
 *  0b0..Input not inverted (HIGH on pin reads as 1; LOW on pin reads as 0).
 *  0b1..Input inverted (HIGH on pin reads as 0, LOW on pin reads as 1).
 */
#define IOCON_PIO_INV(x)                         (((uint32_t)(((uint32_t)(x)) << IOCON_PIO_INV_SHIFT)) & IOCON_PIO_INV_MASK)
#define IOCON_PIO_I2CMODE_MASK                   (0x300U)
#define IOCON_PIO_I2CMODE_SHIFT                  (8U)
/*! I2CMODE - Selects I2C mode.
 *  0b00..Standard mode/ Fast-mode I2C.
 *  0b01..Standard GPIO functionality. Requires external pull-up for GPIO output function.
 *  0b10..Fast-mode Plus I2C
 *  0b11..Reserved
 */
#define IOCON_PIO_I2CMODE(x)                     (((uint32_t)(((uint32_t)(x)) << IOCON_PIO_I2CMODE_SHIFT)) & IOCON_PIO_I2CMODE_MASK)
#define IOCON_PIO_OD_MASK                        (0x400U)
#define IOCON_PIO_OD_SHIFT                       (10U)
/*! OD - Open-drain mode.
 *  0b0..Disable.
 *  0b1..Open-drain mode enabled. Remark: This is not a true open-drain mode.
 */
#define IOCON_PIO_OD(x)                          (((uint32_t)(((uint32_t)(x)) << IOCON_PIO_OD_SHIFT)) & IOCON_PIO_OD_MASK)
#define IOCON_PIO_S_MODE_MASK                    (0x1800U)
#define IOCON_PIO_S_MODE_SHIFT                   (11U)
/*! S_MODE - Digital filter sample mode.
 *  0b00..Bypass input filter.
 *  0b01..1 clock cycle. Input pulses shorter than one filter clock are rejected.
 *  0b10..2 clock cycles. Input pulses shorter than two filter clocks are rejected.
 *  0b11..3 clock cycles. Input pulses shorter than three filter clocks are rejected.
 */
#define IOCON_PIO_S_MODE(x)                      (((uint32_t)(((uint32_t)(x)) << IOCON_PIO_S_MODE_SHIFT)) & IOCON_PIO_S_MODE_MASK)
#define IOCON_PIO_CLK_DIV_MASK                   (0xE000U)
#define IOCON_PIO_CLK_DIV_SHIFT                  (13U)
/*! CLK_DIV - Select peripheral clock divider for input filter sampling clock. Value 0x7 is reserved.
 *  0b000..IOCONCLKDIV0
 *  0b001..IOCONCLKDIV1
 *  0b010..IOCONCLKDIV2
 *  0b011..IOCONCLKDIV3
 *  0b100..IOCONCLKDIV4
 *  0b101..IOCONCLKDIV5
 *  0b110..IOCONCLKDIV6
 */
#define IOCON_PIO_CLK_DIV(x)                     (((uint32_t)(((uint32_t)(x)) << IOCON_PIO_CLK_DIV_SHIFT)) & IOCON_PIO_CLK_DIV_MASK)
#define IOCON_PIO_DACMODE_MASK                   (0x10000U)
#define IOCON_PIO_DACMODE_SHIFT                  (16U)
/*! DACMODE - DAC mode enable.
 *  0b0..Disable.
 *  0b1..Enable.
 */
#define IOCON_PIO_DACMODE(x)                     (((uint32_t)(((uint32_t)(x)) << IOCON_PIO_DACMODE_SHIFT)) & IOCON_PIO_DACMODE_MASK)
/*! @} */

/* The count of IOCON_PIO */
#define IOCON_PIO_COUNT                          (56U)


/*!
 * @}
 */ /* end of group IOCON_Register_Masks */


/* IOCON - Peripheral instance base addresses */
/** Peripheral IOCON base address */
#define IOCON_BASE                               (0x40044000u)
/** Peripheral IOCON base pointer */
#define IOCON                                    ((IOCON_Type *)IOCON_BASE)
/** Array initializer of IOCON peripheral base addresses */
#define IOCON_BASE_ADDRS                         { IOCON_BASE }
/** Array initializer of IOCON peripheral base pointers */
#define IOCON_BASE_PTRS                          { IOCON }

#define    IOCON_INDEX_PIO0_17       ( 0)
#define    IOCON_INDEX_PIO0_13       ( 1)
#define    IOCON_INDEX_PIO0_12       ( 2)
#define    IOCON_INDEX_PIO0_5        ( 3)
#define    IOCON_INDEX_PIO0_4        ( 4)
#define    IOCON_INDEX_PIO0_3        ( 5)
#define    IOCON_INDEX_PIO0_2        ( 6)
#define    IOCON_INDEX_PIO0_11       ( 7)
#define    IOCON_INDEX_PIO0_10       ( 8)
#define    IOCON_INDEX_PIO0_16       ( 9)
#define    IOCON_INDEX_PIO0_15       (10)
#define    IOCON_INDEX_PIO0_1        (11)
#define    IOCON_INDEX_PIO0_9        (13)
#define    IOCON_INDEX_PIO0_8        (14)
#define    IOCON_INDEX_PIO0_7        (15)
#define    IOCON_INDEX_PIO0_6        (16)
#define    IOCON_INDEX_PIO0_0        (17)
#define    IOCON_INDEX_PIO0_14       (18)
#define    IOCON_INDEX_PIO0_28       (20)
#define    IOCON_INDEX_PIO0_27       (21)
#define    IOCON_INDEX_PIO0_26       (22)
#define    IOCON_INDEX_PIO0_25       (23)
#define    IOCON_INDEX_PIO0_24       (24)
#define    IOCON_INDEX_PIO0_23       (25)
#define    IOCON_INDEX_PIO0_22       (26)
#define    IOCON_INDEX_PIO0_21       (27)
#define    IOCON_INDEX_PIO0_20       (28)
#define    IOCON_INDEX_PIO0_19       (29)
#define    IOCON_INDEX_PIO0_18       (30)
#define    IOCON_INDEX_PIO1_8        (31)
#define    IOCON_INDEX_PIO1_9        (32)
#define    IOCON_INDEX_PIO1_12       (33)
#define    IOCON_INDEX_PIO1_13       (34)
#define    IOCON_INDEX_PIO0_31       (35)
#define    IOCON_INDEX_PIO1_0        (36)
#define    IOCON_INDEX_PIO1_1        (37)
#define    IOCON_INDEX_PIO1_2        (38)
#define    IOCON_INDEX_PIO1_14       (39)
#define    IOCON_INDEX_PIO1_15       (40)
#define    IOCON_INDEX_PIO1_3        (41)
#define    IOCON_INDEX_PIO1_4        (42)
#define    IOCON_INDEX_PIO1_5        (43)
#define    IOCON_INDEX_PIO1_16       (44)
#define    IOCON_INDEX_PIO1_17       (45)
#define    IOCON_INDEX_PIO1_6        (46)
#define    IOCON_INDEX_PIO1_18       (47)
#define    IOCON_INDEX_PIO1_19       (48)
#define    IOCON_INDEX_PIO1_7        (49)
#define    IOCON_INDEX_PIO0_29       (50)
#define    IOCON_INDEX_PIO0_30       (51)
#define    IOCON_INDEX_PIO1_20       (52)
#define    IOCON_INDEX_PIO1_21       (53)
#define    IOCON_INDEX_PIO1_11       (54)
#define    IOCON_INDEX_PIO1_10       (55)


/*!
 * @}
 */ /* end of group IOCON_Peripheral_Access_Layer */




/* ----------------------------------------------------------------------------
   -- GPIO Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup GPIO_Peripheral_Access_Layer GPIO Peripheral Access Layer
 * @{
 */

/** GPIO - Register Layout Typedef */
typedef struct {
  __IO uint8_t B[2][32];                           /**< Byte pin registers for all port 0 and 1 GPIO pins, array offset: 0x0, array step: index*0x20, index2*0x1 */
       uint8_t RESERVED_0[4032];
  __IO uint32_t W[2][32];                          /**< Word pin registers for all port 0 and 1 GPIO pins, array offset: 0x1000, array step: index*0x80, index2*0x4 */
       uint8_t RESERVED_1[3840];
  __IO uint32_t DIR[2];                            /**< Direction registers, array offset: 0x2000, array step: 0x4 */
       uint8_t RESERVED_2[120];
  __IO uint32_t MASK[2];                           /**< Mask register, array offset: 0x2080, array step: 0x4 */
       uint8_t RESERVED_3[120];
  __IO uint32_t PIN[2];                            /**< Port pin register, array offset: 0x2100, array step: 0x4 */
       uint8_t RESERVED_4[120];
  __IO uint32_t MPIN[2];                           /**< Masked port register, array offset: 0x2180, array step: 0x4 */
       uint8_t RESERVED_5[120];
  __IO uint32_t SET[2];                            /**< Write: Set register for port Read: output bits for port, array offset: 0x2200, array step: 0x4 */
       uint8_t RESERVED_6[120];
  __O  uint32_t CLR[2];                            /**< Clear port, array offset: 0x2280, array step: 0x4 */
       uint8_t RESERVED_7[120];
  __O  uint32_t NOT[2];                            /**< Toggle port, array offset: 0x2300, array step: 0x4 */
       uint8_t RESERVED_8[120];
  __O  uint32_t DIRSET[2];                         /**< Set pin direction bits for port, array offset: 0x2380, array step: 0x4 */
       uint8_t RESERVED_9[120];
  __O  uint32_t DIRCLR[2];                         /**< Clear pin direction bits for port, array offset: 0x2400, array step: 0x4 */
       uint8_t RESERVED_10[120];
  __O  uint32_t DIRNOT[2];                         /**< Toggle pin direction bits for port, array offset: 0x2480, array step: 0x4 */
} GPIO_Type;

#define SALIDA		1
#define ENTRADA 	0

#define NO_PULL	0x00
#define PULL_DOWN	0x01
#define PULL_UP	0x02
#define REP		0x03

#define PUSH_PULL	0x00
#define OPEN_DRAIN	0x01



/* ----------------------------------------------------------------------------
   -- GPIO Register Masks
   ---------------------------------------------------------------------------- */



/* GPIO - Peripheral instance base addresses */
/** Peripheral GPIO base address */
#define GPIO_BASE                                (0x0A0000000u)
/** Peripheral GPIO base pointer */
#define GPIO                                     ((GPIO_Type *)GPIO_BASE)

/*!
 * @}
 */ /* end of group GPIO_Peripheral_Access_Layer */


#endif /* LPC845_H_ */
