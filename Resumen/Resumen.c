#include "Fun_GPIO.h"
#include "Regs_LPC845.h"
#include "swm.h"
#include "adc.h"
#include "uart.h"

/* -------------------- GPIO -------------------- */
#define PIN_X	0
#define PORT_X	0

void initGPIO(void){

	// Habilitar el clock a la GPIO0 o GPIO1 dependiendo el caso
	SYSCON->SYSAHBCLKCTRL0 |= (1<<6);
	
	// Configuracion para pin de entrada
	SetDIR(PORT_X, PIN_X, ENTRADA);
	SetPINMODE_IN(IOCON_INDEX_PIO0_0, PULL_UP);

	// Configuracion para pin de salida
	SetDIR(PORT_X, PIN_X, SALIDA);
	SetPINMODE_OUT(IOCON_INDEX_PIO0_0, PUSH_PULL);
	SetPIN(PORT_X, PIN_X, APAGADO);
}

/* -------------------- EXT_INT -------------------- */

void initExtInt(void){

	// Tenemos 8 canales de interrupcion externa (PININT0 a PININT7)

	// Habilitamos el clock
	SYSCON->SYSAHBCLKCTRL0 |= (1<<28);

	// En el registro pintsel_x elegimos que pin asignar a las interrupciones
	PINTSEL_0 &= ~(0x3F);
	PINTSEL_0 |= 24; 	// Escribiendo 24 asignamos pin 24 puerto 0

	// En isel seleccionamos si la int es por flanco (0) o nivel (1)
	ISEL &= ~(1<<0);
	
	// Elegimos que tipo de flanco queremos
	IENR |= (1<<0); // Si queremos rising
	IENF |= (1<<0); // Si queremos falling

	// Habilitamos interrupciones en el NVIC
	ISER0 |= (1<<24);
}

void PININT0_IRQHandler(void){
	
	// Realizar accion

	// Limpiar flag
	IST |= (1<<0);
}

/* -------------------- TECLADO MATRICIAL -------------------- */
#define FILA0	0,0
#define FILA1	0,1
#define FILA2	0,2
#define COL0	0,3
#define COL1	0,4
#define COL2	0,5

#define NO_KEY	255
#define TECLA_0	0
#define TECLA_1	1
#define TECLA_2	2
#define TECLA_3	3
#define TECLA_4	4
#define TECLA_5	5
#define TECLA_6	6
#define TECLA_7	7
#define TECLA_8	8

#define ON		0
#define OFF		1

#define INICIO			0
#define VERIFICANDO 	1
#define MAX_REBOTES		10	// de acuerdo al systick

uint8_t bufKey;

void initTeclado(void){

	// Inicializamos columnas como entradas (en este caso pull-up)
	SetDIR(COL0, ENTRADA);
	SetPINMODE_IN(IOCON_INDEX_PIO0_3, PULL_UP);
	
	SetDIR(COL1, ENTRADA);
	SetPINMODE_IN(IOCON_INDEX_PIO0_4, PULL_UP);
	
	SetDIR(COL2, ENTRADA);
	SetPINMODE_IN(IOCON_INDEX_PIO0_5, PULL_UP);

	// Inicializamos las filas como salidas
	SetDIR(FILA0, SALIDA);
	SetPINMODE_OUT(IOCON_INDEX_PIO0_0, PUSH_PULL);
	SetPIN(FILA0, OFF);

	SetDIR(FILA1, SALIDA);
	SetPINMODE_OUT(IOCON_INDEX_PIO0_1, PUSH_PULL);
	SetPIN(FILA1, OFF);

	SetDIR(FILA2, SALIDA);
	SetPINMODE_OUT(IOCON_INDEX_PIO0_2, PUSH_PULL);
	SetPIN(FILA2, OFF);
}

uint8_t barridoTeclado(void){

	// Prendemos una fila y vemos el valor de las columnas
	SetPIN(FILA0, ON);
	SetPIN(FILA1, OFF);
	SetPIN(FILA2, OFF);
	if(!GetPIN(COL0)) return TECLA_0;
	if(!GetPIN(COL1)) return TECLA_1;
	if(!GetPIN(COL2)) return TECLA_2;

	SetPIN(FILA0, OFF);
	SetPIN(FILA1, ON);
	SetPIN(FILA2, OFF);
	if(!GetPIN(COL0)) return TECLA_3;
	if(!GetPIN(COL1)) return TECLA_4;
	if(!GetPIN(COL2)) return TECLA_5;

	SetPIN(FILA0, OFF);
	SetPIN(FILA1, OFF);
	SetPIN(FILA2, ON);
	if(!GetPIN(COL0)) return TECLA_6;
	if(!GetPIN(COL1)) return TECLA_7;
	if(!GetPIN(COL2)) return TECLA_8;

	return NO_KEY;
}

void debounceTeclado(uint8_t tecla){

	static uint8_t teclaVieja = NO_KEY;
	static int estado;
	static int rebotes;

	switch (estado){
	
		case INICIO:

			if(tecla != NO_KEY){
				teclaVieja = tecla;
				estado = VERIFICANDO;
			}
			break;
		
		case VERIFICANDO:

			if(rebotes == MAX_REBOTES){
				bufKey = tecla;
				estado = INICIO;
			}

			if(tecla == teclaVieja){
				rebotes++;
			}

			else if(tecla != NO_KEY){
				teclaVieja = tecla;
				rebotes = 0;
			}

			else{
				rebotes = 0;
				teclaVieja = NO_KEY;
				estado = INICIO;
			}
			
			break;
		
		default:
			estado = INICIO;
			break;
		}
}

void DriverTeclado(void){
	uint8_t tecla;
	tecla = barridoTeclado();
	debounceTeclado(tecla);
}

uint8_t getKey(void){

	uint8_t tecla = NO_KEY;

	if(bufKey != NO_KEY){
		tecla = bufKey;
		bufKey = NO_KEY;
	}

	return tecla;
}

/* -------------------- TECLADO MATRICIAL -------------------- */
#define SEG_A	0,0
#define SEG_B	0,1
#define SEG_C	0,2
#define SEG_D	0,3
#define SEG_E	0,4
#define SEG_F	0,5
#define SEG_G	0,6

#define DIG_1	0,7
#define DIG_2	0,8
#define DIG_3	0,9

#define DIGITO1		1
#define	DIGITO2		2
#define DIGITO3		3

#define CANT_DIGITOS 	3

const uint8_t Tabla_Digitos_BCD_7seg[ ] = { 0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x07, 0x7f, 0x67};

uint8_t msgDisplay[CANT_DIGITOS];

void display(int mensaje){

	// Arranca desde el numero menos significativo
	for(int i=0; i< CANT_DIGITOS; i++, mensaje/=10){
		msgDisplay[i] = Tabla_Digitos_BCD_7seg[mensaje%10];
	}
}

void barridoDisplay(){

	static uint8_t digitoActual = 0;
	uint8_t aux;

	// APAGAMOS LOS DIGITOS
	SetPIN(DIG_1, APAGADO);
	SetPIN(DIG_2, APAGADO);
	SetPIN(DIG_3, APAGADO);

	aux = msgDisplay[digitoActual];
	SetPIN(SEG_A, (aux >> 0) & 0x1);
	SetPIN(SEG_B, (aux >> 1) & 0x1);
	SetPIN(SEG_C, (aux >> 2) & 0x1);
	SetPIN(SEG_D, (aux >> 3) & 0x1);
	SetPIN(SEG_E, (aux >> 4) & 0x1);
	SetPIN(SEG_F, (aux >> 5) & 0x1);
	SetPIN(SEG_G, (aux >> 6) & 0x1);

	switch (digitoActual){
		case DIGITO1: SetPIN(DIG_1, ENCENDIDO); break;
		case DIGITO2: SetPIN(DIG_2, ENCENDIDO); break;
		case DIGITO3: SetPIN(DIG_3, ENCENDIDO); break;
		default:break;
	}

	digitoActual++;
	digitoActual %= CANT_DIGITOS;
}

/* -------------------- ADC -------------------- */

void initADC(void){

	// Energizamos el ADC	
	SYSCON->PDRUNCFG &= ~(1<<4);

	// Seleccionamos el CLK
	SYSCON->ADCCLKSEL &= ~(3<<0);

	// Habilitamos el CLK
	SYSCON->SYSAHBCLKCTRL0 |= (1<<24);

	// Elijo los canales que quiero habilitar
	SYSCON->SYSAHBCLKCTRL0 |= (1<<7);
	SWM_PINENABLE0 &= ~(1<<14); // Habilito ch0 (pin 0,7)
	SWM_PINENABLE0 &= ~(1<<15); // Habilito ch1 (pin 0,6)
	SYSCON->SYSAHBCLKCTRL0 &= ~(1<<7);

	// Seleccionamos el DIV del ADC
	SYSCON->ADCCLKDIV &= ~(0xFF);
	SYSCON->ADCCLKDIV |= 1;
	
	// quiero muestrear a 100kHz = freq
    // 30MHz/DIVISOR = freq x 25
    // DIVISOR = 30MHz / 2,5MHz
    // DIVISOR = 12 --> 1100
	ADC_CTRL &= ~(0xFF);
	ADC_CTRL |= (12<<0);

	// Usamos SEQ_A canales 0 y 1
	ADC_SEQA_CTRL |= (3<<0);
	ADC_SEQA_CTRL &= ~(7<<12);

	// Activa modo burst
	ADC_SEQA_CTRL |= (1<<27);
	// Activa modo single step
	ADC_SEQA_CTRL |= (1<<28);
	// Seleccion de modo | 0 end of conversion | 1 end of seq
	ADC_SEQA_CTRL |= (1<<30);
	// Enable SEQ
	ADC_SEQA_CTRL |= (1<<31);

	// Habilito interrupciones de SEQ A
	ADC_INTEN |= (1<<0);
	ISER0 |= (1<<16);
}

void ADC_SEQA_IRQHandler(void){

	uint32_t dato_ch0, dato_ch1;

	dato_ch0 = (uint32_t)((ADC_DAT[0] >> 4) & 0xFFF);
	dato_ch1 = (uint32_t)((ADC_DAT[1] >> 4) & 0xFFF);

	// Limpio el flag de interrupcion de la SEQ_A
	ADC_FLAGS |= (1 << 28);
}

/* -------------------- UART -------------------- */

void initUART(void){

	// HAY UART de 0 a 4 ahora lo hacemos para la 0

	// Habilitamos el clk
	SYSCON->SYSAHBCLKCTRL0 |= (1<<14);
	
	// Seleccionamos el clk
	SYSCON->FCLKSEL[0] &= ~(7<<0);
	SYSCON->FCLKSEL[0] |= 4;

	// Reseteamos la UART0
	SYSCON->PRESETCTRL0 &= ~(1<<14);
	SYSCON->PRESETCTRL0 |= (1<<14);

	// Seleccionamos los pines de Tx y Rx
	// Elegimos en este caso los pines 0,10 y 0,11
	SYSCON->SYSAHBCLKCTRL0 |= (1<<7);
	SWM_PINASSIGN0 &= ~(0xFFFF);
	SWM_PINASSIGN0 |= 10;		
	SWM_PINASSIGN0 |= (11<<8);
	SYSCON->SYSAHBCLKCTRL0 &= ~(1<<7);

	// Habilitamos la UART0
	USART0->CFG |= (1<<0);

	// 8 bits de datos
	USART0->CFG &= ~(3<<2);
	USART0->CFG |= (1<<2);
	// Sin paridad
	USART0->CFG &= ~(3<<4);
	// 1 bit de stop
	USART0->CFG &= ~(1<<6);
	// Com asincronica
	USART0->CFG &= ~(1<<11);

	// Configuramos baudrate 9600
	// BRGVAL = (FCLK/((OSRVAL + 1) x baud rate)) – 1
	// BRGVAL = (12MHz / ((15 + 1) * 9600)) - 1
	// BRGVAL = 77
	USART0->BRG &= 77;

	// Habilitamos ints de Rx y Tx
	USART0->INTENSET |= (1<<0) | (1<<2);
	ISER0 |= (1<<3);
}

static volatile uint8_t BufferRx[RXBUFFER_SIZE];
static volatile uint32_t rx_in = 0;
static volatile uint32_t rx_out = 0;

static volatile uint8_t BufferTx[TXBUFFER_SIZE];
static volatile uint32_t tx_in = 0;
static volatile uint32_t tx_out = 0;

int txStart;

int16_t popRx(void){

	int16_t dato = -1;

	if(rx_out != rx_in){
		
		dato =  BufferRx[rx_out];
		rx_out++;
		rx_out %= RXBUFFER_SIZE;
	}

	return dato;
}

void pushRx(uint8_t dato){

	BufferRx[rx_in] = dato;
	rx_in++;
	rx_in %= RXBUFFER_SIZE;
}

int16_t popTx(void){

	int16_t dato = -1;

	if(tx_out != tx_in){
		dato = BufferTx[tx_out];
		tx_out++;
		tx_out %= TXBUFFER_SIZE;
	}

	return dato;
}

void pushTx(uint8_t dato){
	
	BufferTx[tx_in] = dato;
	tx_in++;
	tx_in %= TXBUFFER_SIZE;

	if(txStart == 0){
		txStart = 1;
		USART0->INTENSET = (1 << 2);
	}
}

void UART0_IRQHandler(vodi){

	// Chequeamos si la interrupcion es rx o tx
	uint32_t flag = USART0->INTSTAT;
	int16_t dato;

	if(flag & 0x1){ // INT RX
		dato = (int32_t)USART0->RXDAT;
		pushRx((uint8_t)dato);
	}

	if((flag>>2) & 0x1){ // INT TX

		dato = popTx();

		if(dato >= 0) 
			USART0->TXDAT = (uint8_t)dato;
		
		else{
			USART0->INTENCLR |= (1<<2);
			txStart = 0;
		}
	}
}

void Transmitir(uint8_t * datos, int cantDatos){

	for(int i = 0; i< cantDatos; i++){
		pushTx(datos[i]);
	}
}

/* -------------------- Systick -------------------- */
void initSystick(void){
	
	// Quiero contar 1 tick cada 1ms con un clock de 12MHz
	// f = 12Mhz --> 1 tick = 1/12MHz = 83,33 nS
	// 83,33 nS -> 1 tick
	// 1 ms     -> x = 12000,48
	SYST_RVR = 12000-1;
	
	ENABLE = 1;
	CLKSOURCE = 1;
	TICKINT = 1;
	SYST_CVR = 0;
}

int timer;

void SysTick_Handler(void){
	
	timer++; // Si quiero contar el tiempo	
	barridoDisplay();
	DriverTeclado();
}
