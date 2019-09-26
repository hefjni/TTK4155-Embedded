#include <stdlib.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdint.h>

#include "Joystick.h"
#include "ADC.h"
#include "BitMacros.h"
#include "UART.h"


volatile joystick_position_t position;
volatile int x_pos;
volatile int y_pos;
volatile sliders_position_t sliders;
volatile state contr_state;

uint8_t joy_x_V_min = 0;
uint8_t joy_x_V_max = 255;
uint8_t joy_y_V_min = 0;
uint8_t joy_y_V_max = 255;

volatile int x_offset;
volatile int y_offset;

uint8_t slide_left_V_min = 0;
uint8_t slide_left_V_max = 255;
uint8_t slide_right_V_min = 0;
uint8_t slide_right_V_max = 255;


// timer0 overflow
ISR(TIMER0_OVF_vect){
	channel_t channel;
	char data_char = get_ADC_data();
	int32_t data = (int32_t)data_char;
	
	switch(contr_state){
		case(JOYSTICK_X):
		x_pos = ((data-x_offset)*200 )/ (joy_x_V_max - joy_x_V_min);
		contr_state = JOYSTICK_Y;
		channel = CHANNEL2;
		break;
		case(JOYSTICK_Y):
		y_pos = ((data-y_offset)*200 )/ (joy_y_V_max - joy_y_V_min);
		contr_state = LEFT_SLIDER;
		channel = CHANNEL3;
		break;
		case(LEFT_SLIDER):
		sliders.left = (data * 200)/ (slide_left_V_max - slide_left_V_min)  - 100;
		contr_state = RIGHT_SLIDER;
		channel = CHANNEL4;
		break;
		case(RIGHT_SLIDER):
		sliders.right = (data * 200) / (slide_right_V_max - slide_right_V_min) - 100;
		contr_state = JOYSTICK_X;
		channel = CHANNEL1;
		break;
	}
	ADC_start_read(channel);
}

void joystick_auto_calibrate(){
	
	ADC_start_read(CHANNEL1);
	_delay_ms(1);
	x_offset = (int)get_ADC_data();
	
	ADC_start_read(CHANNEL2);
	_delay_ms(1);
	y_offset = (int)get_ADC_data();
	
}

void joystick_init(int prescaler){
	
	// Button inputs:
	clear_bit(DDRB, PB0);	//Joystick button
	set_bit(PORTB, PB0);	//Set pull-up resistor
	clear_bit(DDRB, PB1);	//Right button
	clear_bit(DDRB, PB2);	//Left button
	
	joystick_auto_calibrate();
	
	contr_state = JOYSTICK_X;
	ADC_start_read(CHANNEL1);
	
	//-------------INITIALIZE TIMER INPUT-----------------
	
	// Disable global interrupts
	cli();
	
	// enable timer overflow interrupt for Timer0
	TIMSK=(1<<TOIE0);
	
	// start timer0 with /256 prescaler
	if (prescaler == 256){
		TCCR0 = (1<<CS02);
	}
	else if (prescaler == 1024){
		TCCR0 = (1<<CS02) | (1<<CS00);
	}
	
	// Enable global interrupts
	sei();
	
	//---------------------------------------------------

}

void joystick_manual_calibrate(){
	return;
}

int joystick_button(usb_button_t button){
	
	switch (button) {
		case JOYSTICKBUTTON :
		return !test_bit(PINB, PINB0);
		case LBUTTON :
		return test_bit(PINB, PINB2);
		case RBUTTON :
		return test_bit(PINB, PINB1);
		default:
		printf("Not valid button");
		return EXIT_FAILURE;
	}

}


joystick_position_t joystick_get_position() {
	joystick_position_t return_pos;
	return_pos.x = x_pos;
	return_pos.y = y_pos;
	return return_pos ;
}


joystick_direction_t joystick_get_direction() {
	
	joystick_position_t current_pos = joystick_get_position();
	
	int x = x_pos;
	int y = y_pos;

	if (abs(x) >= abs(y)){
		if (abs(x) < 10){
			return NEUTRAL;
		}
		else if (x < 0){
			return LEFT;
		}
		else {
			return RIGHT;
		}
	}
	else{
		if (abs(y) < 65){
			return NEUTRAL;
		}
		else if (y < 0){
			return DOWN;
		}
		else {
			return UP;
		}
	}
}

int slider_get_left(void){
	return sliders.left;
}
int slider_get_right(void){
	return sliders.right;
}

//void joystickTest(void){
	//volatile char* adc_ch1 = (char*) 0x1400;
	//uint16_t ext_ram_size = 0x400;
	//int i = 5;
//
//
	//while(1){
		//adc_ch1[0] = i;
		//_delay_ms(60);
		//uint8_t retreived_value = adc_ch1[0];
		//printf("Adresse: %d , data: %d \n\r",0x1400 + i, retreived_value);
	//}
//}