
#include <stdlib.h>
#include <stdint.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include "BitMacros.h"
#include "ADC.h"
#include "Joystick.h"

#ifndef ADC_ADDRESS
#define ADC_ADDRESS 0x1400
#endif

volatile char* ext_adc = ADC_ADDRESS;	//Create a pointer to the array of all addresses we will write to. ADC starting at 0x1400.
volatile char ADC_data;



void ADC_init(void){
	
	//INITIALIZE INTERRUPT ON PIN PD3
	// Button input
	clear_bit(DDRD, PD3);
	set_bit(PORTD, PD3);	//Set pull-up resistor
	// Disable global interrupts
	cli();
	// Interrupt on falling edge PD3
	set_bit(MCUCR, ISC11);
	clear_bit(MCUCR, ISC10);
	// Enable interrupt on PD3
	set_bit(GICR,INT1);
	// Enable global interrupts
	sei();
}

char get_ADC_data(void){
	ADC_data = ext_adc[0x00];
	_delay_us(60);
	return ADC_data;
}

void ADC_start_read(channel_t channel){
	
	char data = 0x00;
	
	switch (channel) {
		case CHANNEL1 :
		data = 0x04;
		break;
		case CHANNEL2 :
	
		data = 0x05;
		break;
		case CHANNEL3 :
		
		data = 0x06;
		break;
		case CHANNEL4 :
		
		data = 0x07;
		break;
		default:
		printf("Not valid channel");
		return EXIT_FAILURE;
	}
	
	ext_adc[0x00] = data;
	
}
void ADC_Test(void){
	volatile char* adc_ch1 = (char*) 0x1400;
	int i = 5;


	while(1){
		adc_ch1[0] = i;
		_delay_ms(60);
		uint8_t retreived_value = adc_ch1[0];
		printf("Adresse: %d , data: %d \n\r",0x1400 + i, retreived_value);
	}
}