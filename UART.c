#include <stdio.h>
#include <avr/io.h>
#include "UART.h"


void USART_Init( unsigned int ubrr )
{/* Set baud rate */
	UBRR0H = (unsigned char)(ubrr>>8);//load upper 8 bits of ubbr into UBBRH
	UBRR0L = (unsigned char)ubrr;
	/* Enable receiver and transmitter */
	UCSR0B = (1<<RXEN0)|(1<<TXEN0); // = implies all the other bits are reset
	/* Set frame format: 8data, 2stop bit */
	UCSR0C = (1<<URSEL0)|(1<<USBS0)|(3<<UCSZ00); // UCSZ00 =1?
	fdevopen(USART_Transmit, USART_Receive);
}

void USART_Transmit( unsigned char data )
{/* Wait for empty transmit buffer */
	while ( !( UCSR0A & (1<<UDRE0)) )// Keep waiting till UDRE0 = 1
	;
	/* Put data into buffer, sends the data */
	UDR0 = data;
}


unsigned char USART_Receive( void )
{/* Wait for data to be received */
	while ( !(UCSR0A & (1<<RXC0)) ) // Loop keeps running till RXC0 =1
	;
	/* Get and return received data from buffer */
	return UDR0;
}
