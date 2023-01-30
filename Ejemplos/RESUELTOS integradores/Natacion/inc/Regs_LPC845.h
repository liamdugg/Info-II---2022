#ifndef LPC845_H_
#define LPC845_H_

typedef signed char 	int8_t;
typedef unsigned char 	uint8_t;
typedef short 			int16_t;
typedef unsigned short 	uint16_t;
typedef int 			int32_t;
typedef unsigned int 	uint32_t;

#define     __I     volatile const      /*!< Defines 'read only' permissions */
#define     __R   	volatile const      /*!< Defines 'read only' permissions */

#define     __O     volatile            /*!< Defines 'write only' permissions */
#define     __IO    volatile            /*!< Defines 'read / write' permissions */
#define     __RW    volatile            /*!< Defines 'read / write' permissions */

/* following defines should be used for structure members */
#define     __IM    volatile const      /*! Defines 'read only' structure member permissions */
#define     __OM    volatile            /*! Defines 'write only' structure member permissions */
#define     __IOM   volatile            /*! Defines 'read / write' structure member permissions */


/*-------------------------- SYSTICK --------------------------*/
#define 	SYSTICK		( (systick_t *) 0xE000E010UL )

typedef struct{

     union{
          __RW uint32_t SYST_CSR;
          struct{
               __RW uint32_t ENABLE:1;
               __RW uint32_t TICKINT:1;
               __RW uint32_t CLKSOURCE:1;
               __RW uint32_t RESERVED0:13; //bit 3 a 15
               __RW uint32_t COUNTFLAG:1;
               __RW uint32_t RESERVED1:15; //bit 17 a 31
          }bits;
     };

     __RW uint32_t SYST_RVR;
     __RW uint32_t SYST_CVR;
     __R uint32_t  SYST_CALIB;
}systick_t;

#define	SYST_CSR		SYSTICK->SYST_CSR
#define	ENABLE		SYSTICK->bits.ENABLE
#define	TICKINT		SYSTICK->bits.TICKINT
#define	CLKSOURCE		SYSTICK->bits.CLKSOURCE
#define	COUNTFLAG		SYSTICK->bits.COUNTFLAG
#define	SYST_RVR		SYSTICK->SYST_RVR
#define	SYST_CVR		SYSTICK->SYST_CVR
#define	SYST_CALIB	SYSTICK->SYST_CALIB

/*-------------------------- SYSCON --------------------------*/
typedef struct {
  __IO uint32_t SYSMEMREMAP;                       /**< System Remap register, offset: 0x0 */
       uint8_t  RESERVED_0[4];
  __IO uint32_t SYSPLLCTRL;                        /**< PLL control, offset: 0x8 */
  __I  uint32_t SYSPLLSTAT;                        /**< PLL status, offset: 0xC */
       uint8_t  RESERVED_1[16];
  __IO uint32_t SYSOSCCTRL;                        /**< system oscillator control, offset: 0x20 */
  __IO uint32_t WDTOSCCTRL;                        /**< Watchdog oscillator control, offset: 0x24 */
  __IO uint32_t FROOSCCTRL;                        /**< FRO oscillator control, offset: 0x28 */
       uint8_t  RESERVED_2[4];
  __IO uint32_t FRODIRECTCLKUEN;                   /**< FRO direct clock source update enable register, offset: 0x30 */
       uint8_t  RESERVED_3[4];
  __IO uint32_t SYSRSTSTAT;                        /**< System reset status register, offset: 0x38 */
       uint8_t  RESERVED_4[4];
  __IO uint32_t SYSPLLCLKSEL;                      /**< System PLL clock source select register, offset: 0x40 */
  __IO uint32_t SYSPLLCLKUEN;                      /**< System PLL clock source update enable register, offset: 0x44 */
  __IO uint32_t MAINCLKPLLSEL;                     /**< Main clock source select register, offset: 0x48 */
  __IO uint32_t MAINCLKPLLUEN;                     /**< Main clock source update enable register, offset: 0x4C */
  __IO uint32_t MAINCLKSEL;                        /**< Main clock source select register, offset: 0x50 */
  __IO uint32_t MAINCLKUEN;                        /**< Main clock source update enable register, offset: 0x54 */
  __IO uint32_t SYSAHBCLKDIV;                      /**< System clock divider register, offset: 0x58 */
       uint8_t  RESERVED_5[4];
  __IO uint32_t CAPTCLKSEL;                        /**< CAPT clock source select register, offset: 0x60 */
  __IO uint32_t ADCCLKSEL;                         /**< ADC clock source select register, offset: 0x64 */
  __IO uint32_t ADCCLKDIV;                         /**< ADC clock divider register, offset: 0x68 */
  __IO uint32_t SCTCLKSEL;                         /**< SCT clock source select register, offset: 0x6C */
  __IO uint32_t SCTCLKDIV;                         /**< SCT clock divider register, offset: 0x70 */
  __IO uint32_t EXTCLKSEL;                         /**< external clock source select register, offset: 0x74 */
       uint8_t  RESERVED_6[8];
  __IO uint32_t SYSAHBCLKCTRL0;                    /**< System clock group 0 control register, offset: 0x80 */
  __IO uint32_t SYSAHBCLKCTRL1;                    /**< System clock group 1 control register, offset: 0x84 */
  __IO uint32_t PRESETCTRL0;                       /**< Peripheral reset group 0 control register, offset: 0x88 */
  __IO uint32_t PRESETCTRL1;                       /**< Peripheral reset group 1 control register, offset: 0x8C */
  __IO uint32_t FCLKSEL[11];                       /**< peripheral clock source select register. FCLK0SEL~FCLK4SEL are for UART0~UART4 clock source select register. FCLK5SEL~FCLK8SEL are for I2C0~I2C3 clock source select register. FCLK9SEL~FCLK10SEL are for SPI0~SPI1 clock source select register., array offset: 0x90, array step: 0x4 */
       uint8_t  RESERVED_7[20];
  struct {                                         /* offset: 0xD0, array step: 0x10 */
    __IO uint32_t FRGDIV;                          /**< fractional generator N divider value register, array offset: 0xD0, array step: 0x10 */
    __IO uint32_t FRGMULT;                         /**< fractional generator N multiplier value register, array offset: 0xD4, array step: 0x10 */
    __IO uint32_t FRGCLKSEL;                       /**< FRG N clock source select register, array offset: 0xD8, array step: 0x10 */
         uint8_t  RESERVED_0[4];
  } FRG[2];
  __IO uint32_t CLKOUTSEL;                         /**< CLKOUT clock source select register, offset: 0xF0 */
  __IO uint32_t CLKOUTDIV;                         /**< CLKOUT clock divider registers, offset: 0xF4 */
       uint8_t  RESERVED_8[4];
  __IO uint32_t EXTTRACECMD;                       /**< External trace buffer command register, offset: 0xFC */
  __I  uint32_t PIOPORCAP[2];                      /**< POR captured PIO N status register(PIO0 has 32 PIOs, PIO1 has 22 PIOs), array offset: 0x100, array step: 0x4 */
       uint8_t  RESERVED_9[44];
  __IO uint32_t IOCONCLKDIV6;                      /**< Peripheral clock 6 to the IOCON block for programmable glitch filter, offset: 0x134 */
  __IO uint32_t IOCONCLKDIV5;                      /**< Peripheral clock 6 to the IOCON block for programmable glitch filter, offset: 0x138 */
  __IO uint32_t IOCONCLKDIV4;                      /**< Peripheral clock 4 to the IOCON block for programmable glitch filter, offset: 0x13C */
  __IO uint32_t IOCONCLKDIV3;                      /**< Peripheral clock 3 to the IOCON block for programmable glitch filter, offset: 0x140 */
  __IO uint32_t IOCONCLKDIV2;                      /**< Peripheral clock 2 to the IOCON block for programmable glitch filter, offset: 0x144 */
  __IO uint32_t IOCONCLKDIV1;                      /**< Peripheral clock 1 to the IOCON block for programmable glitch filter, offset: 0x148 */
  __IO uint32_t IOCONCLKDIV0;                      /**< Peripheral clock 0 to the IOCON block for programmable glitch filter, offset: 0x14C */
  __IO uint32_t BODCTRL;                           /**< BOD control register, offset: 0x150 */
  __IO uint32_t SYSTCKCAL;                         /**< System tick timer calibration register, offset: 0x154 */
       uint8_t  RESERVED_10[24];
  __IO uint32_t IRQLATENCY;                        /**< IRQ latency register, offset: 0x170 */
  __IO uint32_t NMISRC;                            /**< NMI source selection register, offset: 0x174 */
  __IO uint32_t PINTSEL[8];                        /**< Pin interrupt select registers N, array offset: 0x178, array step: 0x4 */
       uint8_t  RESERVED_11[108];
  __IO uint32_t STARTERP0;                         /**< Start logic 0 pin wake-up enable register 0, offset: 0x204 */
       uint8_t  RESERVED_12[12];
  __IO uint32_t STARTERP1;                         /**< Start logic 0 pin wake-up enable register 1, offset: 0x214 */
       uint8_t  RESERVED_13[24];
  __IO uint32_t PDSLEEPCFG;                        /**< Deep-sleep configuration register, offset: 0x230 */
  __IO uint32_t PDAWAKECFG;                        /**< Wake-up configuration register, offset: 0x234 */
  __IO uint32_t PDRUNCFG;                          /**< Power configuration register, offset: 0x238 */
       uint8_t  RESERVED_14[444];
  __I  uint32_t DEVICE_ID;                         /**< Part ID register, offset: 0x3F8 */
} SYSCON_Type;

#define SYSCON_SYSAHBCLKCTRL0_GPIO0_MASK         (0x40U)
#define SYSCON_SYSAHBCLKCTRL0_GPIO0_SHIFT        (6U)
#define SYSCON_SYSAHBCLKCTRL0_GPIO1_MASK         (0x100000U)
#define SYSCON_SYSAHBCLKCTRL0_GPIO1_SHIFT        (20U)

#define SYSCON_BASE                              (0x40048000u)                  // SYSCON base address
#define SYSCON                                   ((SYSCON_Type *)SYSCON_BASE)   // SYSCON base pointer

/*-------------------------- IOCON --------------------------*/
typedef struct {
  __IO uint32_t PIO[56];                           /**< Digital I/O control for pins PIO0_17..Digital I/O control for pins PIO1_10, array offset: 0x0, array step: 0x4 */
} IOCON_Type;

// MODE - Inactive 00 | Pull-down 01 | Pull-up 10 | 11 Repeater
#define IOCON_PIO_MODE_MASK                      (0x18U)
#define IOCON_PIO_MODE_SHIFT                     (3U)
#define IOCON_PIO_MODE(x)                        (((uint32_t)(((uint32_t)(x)) << IOCON_PIO_MODE_SHIFT)) & IOCON_PIO_MODE_MASK)

// HYSTERESIS - Disable 0 | Enable 1
#define IOCON_PIO_HYS_MASK                       (0x20U)
#define IOCON_PIO_HYS_SHIFT                      (5U)
#define IOCON_PIO_HYS(x)                         (((uint32_t)(((uint32_t)(x)) << IOCON_PIO_HYS_SHIFT)) & IOCON_PIO_HYS_MASK)

// INVERT - No Invert 0 (HIGH on pin reads as 1; LOW on pin reads as 0).| Invert 1 (HIGH on pin reads as 0, LOW on pin reads as 1).
#define IOCON_PIO_INV_MASK                       (0x40U)
#define IOCON_PIO_INV_SHIFT                      (6U)
#define IOCON_PIO_INV(x)                         (((uint32_t)(((uint32_t)(x)) << IOCON_PIO_INV_SHIFT)) & IOCON_PIO_INV_MASK)

// I2CMODE - Modo Standard/Fast-Mode I2C 00 | Standard GPIO  01 (requires external pull-up for GPIO output function) | Fast mode plus I2C 10 | Reserved 11
#define IOCON_PIO_I2CMODE_MASK                   (0x300U)
#define IOCON_PIO_I2CMODE_SHIFT                  (8U)
#define IOCON_PIO_I2CMODE(x)                     (((uint32_t)(((uint32_t)(x)) << IOCON_PIO_I2CMODE_SHIFT)) & IOCON_PIO_I2CMODE_MASK)

// OPEN DRAIN - Disable 0 | Enable 1
#define IOCON_PIO_OD_MASK                        (0x400U)
#define IOCON_PIO_OD_SHIFT                       (10U)
#define IOCON_PIO_OD(x)                          (((uint32_t)(((uint32_t)(x)) << IOCON_PIO_OD_SHIFT)) & IOCON_PIO_OD_MASK)

// DIGITAL FILTER SAMPLE MODE - Bypass input filter 00 | 1 clock cycle 01 | 2 clock cycles 10 | 3 clock cycles 11
#define IOCON_PIO_S_MODE_MASK                    (0x1800U)
#define IOCON_PIO_S_MODE_SHIFT                   (11U)
#define IOCON_PIO_S_MODE(x)                      (((uint32_t)(((uint32_t)(x)) << IOCON_PIO_S_MODE_SHIFT)) & IOCON_PIO_S_MODE_MASK)

// CLK DIV - 000 IOCONCLKDIV0 | 001 IOCONCLKDIV1 | 010 IOCONCLKDIV2 | 011 IOCONCLKDIV3 | 0b100 IOCONCLKDIV4 | 101 IOCONCLKDIV5 | 110 IOCONCLKDIV6
#define IOCON_PIO_CLK_DIV_MASK                   (0xE000U)
#define IOCON_PIO_CLK_DIV_SHIFT                  (13U)
#define IOCON_PIO_CLK_DIV(x)                     (((uint32_t)(((uint32_t)(x)) << IOCON_PIO_CLK_DIV_SHIFT)) & IOCON_PIO_CLK_DIV_MASK)

// DACMODE - Disable 0 | Enable 1
#define IOCON_PIO_DACMODE_MASK                   (0x10000U)
#define IOCON_PIO_DACMODE_SHIFT                  (16U)
#define IOCON_PIO_DACMODE(x)                     (((uint32_t)(((uint32_t)(x)) << IOCON_PIO_DACMODE_SHIFT)) & IOCON_PIO_DACMODE_MASK)

#define IOCON_PIO_COUNT                          (56U)                          // The count of IOCON_PIO

#define IOCON_BASE                               (0x40044000u)                  // IOCON base address
#define IOCON                                    ((IOCON_Type *)IOCON_BASE)     // IOCON base pointer

#define IOCON_BASE_ADDRS                         { IOCON_BASE }                 // Array initializer of IOCON peripheral base addresses
#define IOCON_BASE_PTRS                          { IOCON }                      // Array initializer of IOCON peripheral base pointers

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

/*-------------------------- GPIO --------------------------*/
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

#define GPIO_BASE                                (0x0A0000000u)           // GPIO base address
#define GPIO                                     ((GPIO_Type *)GPIO_BASE) // GPIO base pointer

/*-------------------------- INTERRUPCIONES --------------------------*/

// ISER0 - Habilita las interrupciones para un modulo en el NVIC
#define ISER0_BASE       (0xE000E100)
#define ISER0            (*(volatile uint32_t *)(ISER0_BASE))

// PINTSELx - Selecciona que pin se utiliza para las interrupciones
#define PINTSEL_BASE     (0x40048178)

#define PINTSEL_0        (*(volatile uint32_t *)(PINTSEL_BASE + 0))
#define PINTSEL_1        (*(volatile uint32_t *)(PINTSEL_BASE + 0x04))
#define PINTSEL_2        (*(volatile uint32_t *)(PINTSEL_BASE + 0x08))
#define PINTSEL_3        (*(volatile uint32_t *)(PINTSEL_BASE + 0x0C))
#define PINTSEL_4        (*(volatile uint32_t *)(PINTSEL_BASE + 0x10))
#define PINTSEL_5        (*(volatile uint32_t *)(PINTSEL_BASE + 0x14))
#define PINTSEL_6        (*(volatile uint32_t *)(PINTSEL_BASE + 0x18))
#define PINTSEL_7        (*(volatile uint32_t *)(PINTSEL_BASE + 0x1C))

// ISEL - Selecciona si la interrupcion es por flanco o nivel
#define ISEL_BASE        (0xA0004000)
#define ISEL             (*(volatile uint32_t *)PINTSEL_BASE)

// ENRL - Habilita o deshabilita el Rising Edge
#define ENRL_BASE        (0xA0004004)
#define ENRL             (*(volatile uint32_t *)ENRL_BASE)

// ENAF - Habilita o deshabilita el Falling Edge
#define ENAF_BASE        (0xA0004010)
#define ENAF             (*(volatile uint32_t *)ENAF_BASE)

// RISE - Pone flag en 1 si detecta un rising edge
#define RISE_BASE        (0XA000401C)
#define RISE             (*(volatile uint32_t *)RISE)

#endif /* LPC845_H_ */