#include "AP_FuncionesMDE.h"


extern int Timers[3];
extern int Tiempos[3];
extern int Flag_Timers[3];
int flag_stop = 0;

void f_apagarCinta (void){
	SetPIN(CINTA, APAGADO);
}

void f_apagarPiston(void){
	SetPIN(PISTON, APAGADO);
}

void f_apagarSistema(void){
	SetPIN(CINTA, APAGADO);
	SetPIN(PISTON, APAGADO);
	SetPIN(LED, APAGADO);
	f_stopTimers();
}

void f_prenderCinta(void){
	SetPIN(CINTA, ENCENDIDO);
}

void f_prenderLedOn(void){
	SetPIN(LED, APAGADO);
}

void f_prenderPiston(void){
	SetPIN(PISTON, ENCENDIDO);
}

void f_setTiempos(uint8_t *valores){

	Tiempos[0] = (int)valores[0] + (int)(valores[1] << 8);
	Tiempos[1] = (int)valores[2] + (int)(valores[3] << 8);
	Tiempos[2] = (int)valores[4] + (int)(valores[5] << 8);
}

void f_startTimer(int timer){

	switch(timer){
		case TIM1: Timers[0] = Tiempos[0]; break;
		case TIM2: Timers[1] = Tiempos[1]; break;
		case TIM3: Timers[1] = Tiempos[2]; break;
		default: break;
	}
}

void f_barridoTeclado(void){
	// Chequeamos si el boton esta en 1 porque es pull-down
	if(GetPIN(BTN_ON) == 1) botonON = 1;
	else if(GetPIN(BTN_OFF) == 1) botonOFF = 1;
}

void SysTick_Handler(void){

	if(!flag_stop){

		f_barridoTeclado();

		if(Timers[0] != 0)
			Timers[0]--;

		else Flag_Timers[0] = 1;

		if(Timers[1] != 0)
			Timers[1]--;

		else Flag_Timers[1] = 1;

		if(Timers[2] != 0)
			Timers[2]--;

		else Flag_Timers[2] = 1;
	}
}

void f_stopTimers(){

	flag_stop = 1;
	Timers[0] = 0;
	Timers[1] = 0;
	Timers[2] = 0;
}

uint8_t f_getSensor(void){
	return (uint8_t)GetPIN(SENSOR);
}

