#include <avr/io.h>
#define F_CPU 5000000
#include "UART.h"
#include "SRAM_driver.h"
#include "ADC.h"
#include <util/delay.h>

int main(void)
{
	while(1)
	{
		SRAM_Init();
		SRAM_test();
		joystickTest();
	}
}
//int main(void)
//{
	//
	//USART_Init( MYUBRR);
	//DDRB |= (0<<PB2) |(0<<PB3);
	//while(1)
	//{
		//_delay_ms(1000);
		//if (bit_is_set (PINB,PB2))
		//printf("\rRight Button ON\n");
		//else
		//printf("\rRight Button OFF\n");
		//if (bit_is_set (PINB,PB3))
		//printf("\rLeft Button ON\n");
		//else
		//printf("\rLeft Button OFF\n");
	//}
//}