#include "Regs_LPC845.h"
#include "Fun_GPIO.h"

uint8_t barridoTeclado(void);
void debounceTeclado(uint8_t tecla);
uint8_t getKey();
void driverTeclado(void);