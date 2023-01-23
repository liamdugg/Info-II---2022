#include <stdio.h>

#define  __I  volatile const  /*Defines 'read only' permission */
#define  __O  volatile      /*Defines 'write only' permission */
#define  __IO volatile      /*Defines 'read / write' permission */

typedef signed char int8_t;
typedef unsigned char uint8_t;
typedef short int16_t;
typedef unsigned short uint16_t;
typedef int int32_t;
typedef unsigned int uint32_t;

// GPIO
#define	 GPIO_BASE  0xA0000000u
#define	 GPIO  ((GPIO_Type* )  0xA0000000)

// IOCON
#define IOCON_BASE	(0x40044000u)
#define IOCON	((IOCON_Type *)IOCON_BASE)
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

typedef struct {
  __IO uint8_t B[2][32];                           
       uint8_t RESERVED_0[4032];
  __IO uint32_t W[2][32];                          
       uint8_t RESERVED_1[3840];
  __IO uint32_t DIR[2];                            
       uint8_t RESERVED_2[120];
  __IO uint32_t MASK[2];                           
       uint8_t RESERVED_3[120];
  __IO uint32_t PIN[2];                            
       uint8_t RESERVED_4[120];
  __IO uint32_t MPIN[2];                         
       uint8_t RESERVED_5[120];
  __IO uint32_t SET[2]; 
       uint8_t RESERVED_6[120];
  __O  uint32_t CLR[2];                            
       uint8_t RESERVED_7[120];
  __O  uint32_t NOT[2];                            
       uint8_t RESERVED_8[120];
  __O  uint32_t DIRSET[2];                         
       uint8_t RESERVED_9[120];
  __O  uint32_t DIRCLR[2];                         
       uint8_t RESERVED_10[120];
  __O  uint32_t DIRNOT[2];
} GPIO_Type;

typedef struct {
  __IO uint32_t PIO[56];                           
} IOCON_Type;
