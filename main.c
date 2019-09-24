#include <avr/io.h>
#define F_CPU 4915200UL	// or this 5000000
#include <util/delay.h>
#include "UART.h"
#include "SRAM_driver.h"
#include "ADC.h"
#include "Joystick.h"
#include "BitMacros.h"






int main(void)

{   


	USART_Init( MYUBRR);

	ADC_init();
	int prescaler = 1024;
	joystick_init(prescaler);

	
	DDRB |= (0<<PB2) |(0<<PB3);

	joystick_position_t position;
	joystick_direction_t direction;

	while(1)
	{ 
		direction = joystick_get_direction();
		

		printf("\rJoystick: x: %d Slider:left: %d \n", position.x, slider_get_left());
		printf("\rJoystick: y: %d Slider:right: %d \n\n", position.y, slider_get_right());

		//printf("\tJoystick Direction: %d",direction, "\n" );
		//printf("\tSlider Right: %d",position.x,"\n" );
		//printf("\tSlider Left: %d",position.y,"\n" );
		_delay_ms(1000);
		//if (bit_is_set (PINB,PB2))
		//printf("\rRight Button ON\n");
		//else
		//printf("\rRight Button OFF\n");
		//if (bit_is_set (PINB,PB3))
		//printf("\rLeft Button ON\n");
		//else
		//printf("\rLeft Button OFF\n");
	}
}
