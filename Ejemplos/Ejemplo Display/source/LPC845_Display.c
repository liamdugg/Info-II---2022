/*
 * Copyright 2016-2021 NXP
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of NXP Semiconductor, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/**
 * @file    LPC845_Display.c
 * @brief   Application entry point.
 */

#include <dr_gpio.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "LPC845.h"
#include "timer.h"
#include "stick.h"
#include "dr_7seg.h"

volatile uint8_t ledTimeoutFlag = 0;

/*
 * @brief   Application entry point.
 */
int main(void) {

	unsigned int i = 0;

    /* Init board hardware. */
    BOARD_InitBootPins();
    BOARD_InitBootClocks();
    BOARD_InitBootPeripherals();

    SysTick_Config(SystemCoreClock/250);

    LED_VERDE_OFF;
    DISPLAY_7SEG_Print(888888);

    TimerStart(1, 20, timer1Handler, DEC);

    while(1) {
    	// Chequeo Timers para ejecutar las funciones asociadas a cada evento temportizado
    	TimerEvent();

    	// Lógica Aplicación (podrían ser una o más MdE)
    	if(ledTimeoutFlag) {
    		ledTimeoutFlag = 0;
    	    DISPLAY_7SEG_Print(i);
            i++;
    	}

    	if(!GetPIN(TECLA_USR)) {
    		DISPLAY_7SEG_Print_v2(888, DSP_ROJO);
    	}

    	if(!GetPIN(TECLA_ISP)) {
    		DISPLAY_7SEG_Print_v2(111, DSP_VERDE);
    	}

    }
    return 0 ;
}
