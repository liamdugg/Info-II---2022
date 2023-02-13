#include "uart.h"

static volatile uint8_t BufferRx[RXBUFFER_SIZE];
static volatile uint32_t inx_rx_in = 0;
static volatile uint32_t inx_rx_out = 0;

static volatile uint8_t BufferTx[TXBUFFER_SIZE];
static volatile uint32_t inx_tx_in = 0;
static volatile uint32_t inx_tx_out = 0;

int txStart;

void pushTx (uint8_t dato) {
      BufferTx [inx_tx_in] = dato;
      inx_tx_in++;
       inx_tx_in %= TXBUFFER_SIZE;
       if (txStart == 0) {  
              txStart = 1;	
             START_TX;
       }
}

int16_t popTx(void)
{
    int16_t dato = -1;

    if (inx_tx_in != inx_tx_out )
    {
        dato = BufferTx[inx_tx_out ] ;
        inx_tx_out ++;
        inx_tx_out  %= TXBUFFER_SIZE;
    }
    return dato;
}

void pushRx(uint8_t dato)
{
    BufferRx[inx_rx_in] = dato;
    inx_rx_in++;
    inx_rx_in % RXBUFFER_SIZE;
}

int16_t popRx (void) {
       int16_t dato = -1;
      if (inx_rx_in != inx_rx_out )
      {
            dato = BufferRx[inx_rx_out ] ;
            inx_rx_out ++;
            inx_rx_out  %= RXBUFFER_SIZE;
      }
      return dato;
}

void UART0_IRQHandler (void)  
{
      int16_t auxTemporal;

      uint32_t stat = USART0->STAT;
	
	if(stat & (1 << 0))
    {
		auxTemporal = (int32_t) USART0->RXDAT;    
		pushRx((uint8_t) auxTemporal);         
	}
	if(stat & (1 << 2))
    {
		auxTemporal = popTx(); 
		if(auxTemporal >= 0)
			USART0->TXDAT=(uint8_t)auxTemporal;
            else
            {	
          		USART0->INTENCLR = (1 << 2); 
			    txStart = 0;  
	        }
	}
}

int16_t Transmitir (const void * datos , uint8_t cant)
{
	uint8_t i;

    if(cant == 0){
        cant = strlen(datos);
    }

	for ( i = 0 ; i < cant ; i++ ){
		pushTx( * ( ( uint8_t * ) ( datos + i ) ) );
    }
}

void UART_Init(void) {
	// Habilitamos clock para la USART0
    SYSCON->SYSAHBCLKCTRL0 |= (1 << 14);

	// Seleccionamos fuente de clock para la USART0
    SYSCON->FCLKSEL[0] &= ~(0x111); 
	//SYSCON_UART0CLKSEL = 0;

	// Efectuamos el reset del periferico USART0

    //lo repite 3 veces para asegurar que se reinicie (creo)
    SYSCON->PRESETCTRL0 &= ~(1<<14);
    SYSCON->PRESETCTRL0 &= ~(1<<14);
    SYSCON->PRESETCTRL0 &= ~(1<<14);
    SYSCON->PRESETCTRL0 |= (1<<14);
    SYSCON->PRESETCTRL0 |= (1<<14);
    SYSCON->PRESETCTRL0 |= (1<<14);

	// Configuramos los pines a utilizar de la USART0
	swm_power_on();
	swm_select_usart0_rxd(0, 24);
	swm_select_usart0_txd(0, 25);
	swm_power_off();

	// Habilitamos USART0
    USART0->CFG |= (1 << 0);

	// Fijamos 8 bits de datos

    USART0->CFG &= ~(3 << 2);
    USART0->CFG |=  (1 << 2);

	// Fijamos sin paridad
	USART0->CFG &= ~(3 << 4);

	// Fijamos 1 bit de stop
	USART0->CFG &= ~(1 << 6);

	// Configuramos baudrate 9600
	// BRGVAL = (FCLK/((OSRVAL + 1) x baud rate)) – 1
	// BRGVAL = (12MHz / ((15 + 1) * 9600)) - 1
	// BRGVAL = 77,125
	// BRGVAL = 77

    USART0->BRG = 77;

	// Habilitamos interrupciones RXRDY y TXRDY
    USART0->INTENSET |= (1 << 0) | (1 << 2);

	// Habilitamos interrupciones de USART0 en NVIC
    ISER0 |= (1 << 3);
}