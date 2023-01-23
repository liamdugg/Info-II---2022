#ifndef SYSTICK_H_
#define SYSTICK_H_

#include <stdint.h>

void systick_init(void);

uint64_t systick_tick_time(void);

#endif /* SYSTICK_H_ */
