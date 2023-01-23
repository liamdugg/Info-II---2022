/*
 * botones.c
 *
 *  Created on: 18 sep. 2021
 *      Author: Federico
 */
#include "AP_MDE.h"
#include "stick.h"
void chequear_boton(){
	if(GetPIN(TECLA_USR) == 0)
		flag_boton = 1;
	else
		flag_boton = 0;

}
