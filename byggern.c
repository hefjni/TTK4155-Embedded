#define F_CPU 4915200UL	// or this 5000000
#include <util/delay.h>
#include <avr/io.h>
#include <stdio.h>

#include "UART.h"
#include "SRAM.h"
#include "ADC.h"
#include "Joystick.h"
#include "BitMacros.h"
#include "OLED.h"
#include "EX4.h"
#include "SPI.h"
#include "CAN_controller.h"
#include "Menu.h"
#include "MCP2515.h"
#include "CAN.h"



void ex3(void){
	
	
	//int prescaler = 1024;
	//joystick_init(prescaler);
	joystick_position_t position;
	joystick_direction_t direction;
	
	position = joystick_get_position();
	direction = joystick_get_direction();
	switch (direction)
	{
		case 0 : printf("\rJoystick direction: RIGHT\n" );
		break;
		case 1 : printf("\rJoystick direction: LEFT\n" );
		break;
		case 2 : printf("\rJoystick direction: UP\n" );
		break;
		case 3 : printf("\rJoystick direction: DOWN\n" );
		break;
		case 4 : printf("\rJoystick direction: NEUTRAL\n" );
		break;
		
	}
	//printf("\rjoystick: x: %d slider:left: %d \n", position.x, slider_get_left());
	//printf("\rjoystick: y: %d slider:right: %d \n\n", position.y, slider_get_right());
	
	read_touch_button();
	_delay_ms(500);

	
}

void ex4(void){
	
	oled_menu_selection();
	_delay_ms(200);
	//read_touch_button ();
}

void ex5(void){
char rdata;
	mcp_2515_init(MODE_LOOPBACK);
	while(1){
		
		
		
		mcp_2515_write(MCP_LOAD_TX0,'J');
		_delay_ms(200);
		rdata = mcp_2515_read(MCP_READ_RX0);
		printf("D:%c\n\r",rdata);
		
	}

	
}


int main(void)

{
	USART_Init( MYUBRR);
	int var1= 5;
	
	SRAM_Init();
	ADC_init();
	SRAM_test();
	oled_init();
	int prescaler = 1024;
	joystick_init(prescaler);
	oled_menu_init();
	ex5();
	
	
	
while(1){
		
		
		
	}
}	