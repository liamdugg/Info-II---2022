#ifndef USART_H_
#define USART_H_

#include <stdint.h>

void usart_init();

int32_t usart_read();

int32_t usart_send(uint8_t dato);

#endif /* USART_H_ */
