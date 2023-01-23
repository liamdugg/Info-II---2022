/*
 * timer.c
 *
 *  Created on: 16 ago. 2021
 *      Author: socco
 */
#include "main.h"


extern volatile uint16_t delay;

uint32_t SysTickInic ( uint32_t ticks )
{
	if ((ticks - 1UL) > 0xFFFFFF)
    {
      return (1UL);                                                   /* Reload value impossible */
    }
	SYST_RVR = (uint32_t)(ticks - 1UL);
	SYST_CVR = 0;

	CLKSOURCE = 1;
	ENABLE = 1;
	TICKINT = 1;

	return (0UL);
}


/*
 * @brief   ISR de SysTick
 */
void SysTick_Handler(void)
{
	if(delay)
		delay--;
}
