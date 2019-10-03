#include <avr/io.h>
#include "OLED.h"
#include "fonts.h"

volatile char* ext_oled_cmd = OLED_COMMAND_ADDRESS;
volatile char* ext_oled_data = OLED_DATA_ADDRESS;
volatile oled_position_t position;
volatile int fontSize = 8;
void XMEM_Init(){
	MCUCR |= (1<<SRE);//Enable MCU external memory
	SFIOR |= (1<<XMM2); // External Memory Enabled
}
void OLED_Init()
{
	write_c(0xae); // display off
	write_c(0xa1); //segment remap
	write_c(0xda); //common pads hardware: alternative
	write_c(0x12);
	write_c(0xc8); //common output scan direction:com63~com0
	write_c(0xa8); //multiplex ration mode:63
	write_c(0x3f);
	write_c(0xd5); //display divide ratio/osc. freq. mode
	write_c(0x80);
	write_c(0x81); //contrast control
	write_c(0x50);
	write_c(0xd9); //set pre-charge period
	write_c(0x21);
	write_c(0x20); //Set Memory Addressing Mode
	write_c(0x02);
	write_c(0xdb); //VCOM deselect level mode
	write_c(0x30);
	write_c(0xad); //master configuration
	write_c(0x00);
	write_c(0xa4); //out follows RAM content
	write_c(0xa6); //set normal display
	write_c(0xaf); // display on
	//write_c(0xa5);
}

	
	

void OLED_pos(uint8_t row,uint8_t col){
	
	
	
}

void write_c(uint8_t command){
	ext_oled_cmd[0] = command;
}

void write_data(uint8_t data){
	ext_oled_data[0] = data;
}
void Test_OLED(void)
{	void XMEM_Init();
	
    while(1)
    {
	  
      write_data(0b01111100);
	  write_data(0b01111110);
	  write_data(0b00010011);
	  write_data(0b00010011);
	  write_data(0b01111110);
	  write_data(0b01111100);
	  write_data(0b00000000);
	  write_data(0b00000000);
	 write_c(0xb1);
	  write_data(0b01111111);
	  write_data(0b01111111);
	  write_data(0b00001000);
	  write_data(0b00001000);
	  write_data(0b01111111);
	  write_data(0b01111111);
	  write_data(0b00000000);
	  write_data(0b00000000);
	  _delay_ms(2000);
	 
    }
}
int oled_put_char(unsigned char c){
	uint8_t printChar = c-32;
	
	for (int i=0; i < fontSize; i++) {
		write_data(pgm_read_word(&font8[printChar][i]));
		position.col += fontSize;
		//oled_is_out_of_bounds();
	}
	
	return 0;
}
