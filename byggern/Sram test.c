
/*
 * Byggern.c
 *
 * Created: 05.09.2019 16:00:19
 *  Author: henrikfn
 */ 

#include <stdlib.h>
#include <avr/io.h>
#include <stdio.h>
#include "UART.h"


void SRAM_Init(void)
{
	MCUCR |= (1<<SRE);//Enable MCU external memory 
    SFIOR |= (1<<XMM2); // External Memory Enabled
	
}

void SRAM_test(void)
{
	USART_Init ( MYUBRR );
	volatile char *ext_ram = (char *) 0x1800; // Start address for the SRAM
	uint16_t ext_ram_size= 0x800;
	uint16_t write_errors= 0;
	uint16_t retrieval_errors= 0;
	printf("Starting SRAM test...\n");// rand() stores some internal state, so calling this function in a loop will yield different seeds each time (unless srand() is called before this function)
	uint16_t seed = rand();
	// Write phase: Immediately check that the correct value was stored
	srand(seed);
	for (uint16_t i = 0; i < ext_ram_size; i++)
	{   uint8_t some_value = rand();
		ext_ram[i] = some_value;
		uint8_t retreived_value = ext_ram[i];
		if (retreived_value != some_value)
		{ printf("\nWrite phase error: ext_ram[%4d] = %02X (should be %02X)\r", i, retreived_value, some_value);
			write_errors++;
		}
	}
	// Retrieval phase: Check that no values were changed during or after the write phase
	srand(seed);// reset the PRNG to the state it had before the write phase
	for (uint16_t i = 0; i < ext_ram_size; i++)
	{ uint8_t some_value = rand();
		uint8_t retreived_value = ext_ram[i];
		if (retreived_value != some_value)
		{   printf("\nRetrieval phase error: ext_ram[%4d] = %02X (should be %02X)\r", i, retreived_value, some_value);
			retrieval_errors++;
		}
	}
	printf("SRAM test completed with \n%4d errors in write phase and \n%4d errors in retrieval phase\r\n\n", write_errors, retrieval_errors);
}


void main( void )

{
	SRAM_Init();
	SRAM_test();
}