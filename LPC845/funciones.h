#include "Regs_LPC176x.h"

#define   IN          0
#define   OUT         1
#define   OPENDRAIN   1
#define   NOPENDRAIN  0

//PROTOTIPOS DE FUNCIONES

//Establece el estado de un pin para un determinado puerto | Registro GPIO
void setPin(uint8_t puerto, uint8_t pin, uint8_t estado);

//Devuelve el estado de un pin de un determinado puerto | Registro GPIO
uint8_t getPin(uint8_t puerto, uint8_t pin);

//Selecciona el modo (funcion) de los puertos || Registro PINSEL
void setPINSEL(uint8_t puerto, uint8_t pin, uint8_t funcion);

//Establece un pin de un determinado puerto como sentrada o salida | Registro GPIO
void setDIR(uint8_t puerto, uint8_t pin, uint8_t modo);

//Establece el modo de entrada del pin | Registro PINMODE
void setPINMODE(uint8_t puerto, uint8_t pin, uint8_t modo);

//Establece el modo de salida del pin | Registro PINMODE_OD
void setPINMODEOD(uint8_t puerto, uint8_t pin, uint8_t modo);


//FUNCIONES

void setPin(uint8_t puerto, uint8_t pin, uint8_t estado){

    if(estado == 1){  
      GPIO_BASE[puerto*8 + 5] = GPIO0_BASE[puerto*8 + 5] | ( 1 << pin );
    }

    else{
        GPIO_BASE[puerto*8 + 5] = GPIO0_BASE[puerto*8 + 5] & (~( 1 << pin) );
    }
}


uint8_t getPin(uint8_t puerto, uint8_t pin){

  return (uint8_t) ( (GPIO_BASE[puerto*8 + 5] >> pin) & 1);
}


void setPINSEL(uint8_t puerto, uint8_t pin, uint8_t funcion){
  
  uint8_t offset = 0;
  if(pin >= 16){
    pin = pin - 16;
    offset = 1;
  }

  PINSEL[puerto*2 + offset] = PINSEL[puerto*2 + offset] & ( ~ ( 3 << (pin*2) ) );
  PINSEL[puerto*2 + offset] = PINSEL[puerto*2 + offset] | (funcion << (pin*2) );  
}


void setDIR(uint8_t puerto, uint8_t pin, uint8_t modo){

  if(modo == OUT){
    GPIO0_BASE[puerto*8] = GPIO0_BASE[puerto*8] | (1 << pin);
  }

  else{
    GPIO0_BASE[puerto*8] = GPIO0_BASE[puerto*8] & (~ (1 << pin) );
  }
}


void setPINMODE(uint8_t puerto, uint8_t pin, uint8_t modo){

  uint8_t offset = 0;
  if(pin >= 16){
    pin = pin - 16;
    offset = 1;
  }

  PINMODE[puerto*2 + offset] = PINMODE[puerto*2 + offset] & ( ~ (3 << (pin*2) ) );
  PINMODE[puerto*2 + offset] = PINMODE[puerto*2 + offset] | (modo << (pin*2) );
}


void setPINMODEOD(uint8_t puerto, uint8_t pin, uint8_t modo){

  if(modo == OPENDRAIN){
    PINMODE_OD[puerto] = PINMODE_OD[puerto] | (1 << pin);
  }

  else{
    PINMODE_OD[puerto] = PINMODE_OD[puerto] & ( ~ (1 << pin) );
  }
}
