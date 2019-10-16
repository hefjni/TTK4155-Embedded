#include <avr/io.h>
#include "BitMacros.h"

void SPI_Init(void)
{
	/* Set MOSI and SCK output, all others input */
	DDRB = (1<<PB4)|(1<<PB5)|(1<<PB7);
	/* Enable SPI, Master, set clock rate fck/16 */
	SPCR = (1<<SPE)|(1<<MSTR)|(1<<SPR0);
	
	set_bit(PORTB,PB4);
}
void SPI_Transmit(char cData)
{
	/* Start transmission */
	SPDR = cData;
	/* Wait for transmission complete */
	while(!(SPSR & (1<<SPIF)))
	;
}

char SPI_Receive(void){
	
	SPDR = 0x00;
	
	while(!(SPSR & (1<<SPIF)))
	;
	/* Return data register */
	return SPDR;
}