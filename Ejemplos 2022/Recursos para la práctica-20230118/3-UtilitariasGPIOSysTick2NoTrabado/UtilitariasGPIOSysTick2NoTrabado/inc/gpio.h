/*
 * gpio.h
 *
 *  Created on: 5 ago. 2021
 *      Author: root
 */

#ifndef GPIO_H_
#define GPIO_H_

#define SALIDA		1
#define ENTRADA 	0

#define NO_PULL		0x00
#define PULL_DOWN	0x01
#define PULL_UP		0x02
#define REP			0x03

#define PUSH_PULL	0x00
#define OPEN_DRAIN	0x01

void SetPIN(uint32_t, uint32_t, uint32_t);
void SetDIR(uint32_t, uint32_t, uint32_t);
uint32_t GetPIN(uint32_t, uint32_t);
void SetPINMODE_IN(uint32_t, uint32_t);
void SetPINMODE_OUT(uint32_t, uint32_t);


#endif /* GPIO_H_ */
