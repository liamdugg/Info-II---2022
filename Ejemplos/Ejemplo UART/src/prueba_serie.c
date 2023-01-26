#include <stdio.h>

#include <usart.h>

int main(void) {
	usart_init();

	usart_send('A');

    while (1) {
    	int32_t val = usart_read();
    	if (val != -1) {
    		usart_send(val);
    		usart_send(val);
    		usart_send(val);
    		usart_send(val);
    	}
    }

    return 0 ;
}
