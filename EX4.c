#include <stdint.h>
#include <stdio.h>
#include <stdarg.h>

#include "EX4.h"
#include "fonts.h"
#include "BitMacros.h"
//#include "font_4x6.h"
//#include "font_5x7.h"
//#include "font_5x7w.h"
//#include "font_8x8.h"

static FILE mystdout = FDEV_SETUP_STREAM(oled_put_char, NULL, _FDEV_SETUP_WRITE);
static FILE myinvstdout = FDEV_SETUP_STREAM(oled_inv_put_char, NULL, _FDEV_SETUP_WRITE);

#ifndef oled_command_address
#define oled_command_address  0x1000
#endif

#ifndef oled_data_address
#define oled_data_address 0x1200
#endif

typedef enum{horizontal_mode, vertical_mode, page_mode} adressing_mode;

volatile char* ext_oled_cmd = oled_command_address;
volatile char* ext_oled_data = oled_data_address;

volatile oled_position_t position;

volatile int fontsize = 8;
//const char* const font[] progmem = {font_4x6, font_5x7, font_5x7w, font_8x8};
//int current_font = font_8x8;

void oled_is_out_of_bounds() {
	if (position.col > 127) {
		position.col -= 128;
		position.row += 1;
		if (position.row > 7) {
			position.row = 0;
		}
	}
}

//void switch_font(fontname name) {
	//current_font = name;
	//switch(name){
		//case(font_4x6):
		//fontsize = 4;
		//case(font_5x7):
		//fontsize = 5;
		//case(font_5x7w):
		//fontsize = 5;
		//case(font_8x8):
		//fontsize = 8;
	//}
//}

void write_command(uint8_t command){
	ext_oled_cmd[0] = command;
}

void write_data(uint8_t data){
	ext_oled_data[0] = data;
}

int oled_put_char(unsigned char c){
	uint8_t printchar = c-32; // Chooses character (position in table) from fonts array
	
	for (int i=0; i < fontsize; i++) {
		write_data(pgm_read_word(&font8[printchar][i])); // pgm_read_word reads double word (64 bits/8 bytes)
		position.col += fontsize;
		oled_is_out_of_bounds();
	}
	
	return 0;
}

int oled_inv_put_char(unsigned char c){
	uint8_t printchar = c-32;
	
	for (int i=0; i < fontsize; i++) {
		write_data(~pgm_read_word(&font8[printchar][i]));
		position.col += fontsize;
		oled_is_out_of_bounds();
	}
	
	return 0;
}

void oled_set_adressing_mode(adressing_mode mode) {
	write_command(0x20);
	write_command(mode);
}

// ------------------ functions declared in header below this line---------------------

void oled_printf(char* data, ...){
	va_list args; // accept varying number of arguments
	va_start(args, data);
	vfprintf(&mystdout, data, args);
	va_end(args);
	
}

void oled_inv_printf(char* data, ...){
	va_list args;
	va_start(args, data);
	vfprintf(&myinvstdout, data, args);
	va_end(args);
	
}

int long_string(char* data){
	if (strlen(data)*fontsize > 128){
		return 1;
	}
	return 0;
}

void oled_align_centre(char* title) {
	oled_goto_column(64- fontsize*strlen(title)/2);
}



void oled_init(){
	write_command(0xae); // display off
	write_command(0xa1); //segment remap
	write_command(0xda); //common pads hardware: alternative
	write_command(0x12);
	write_command(0xc8); //common output scan direction:com63~com0
	write_command(0xa8); //multiplex ration mode:63
	write_command(0x3f);
	write_command(0xd5); //display divide ratio/osc. freq. mode
	write_command(0x80);
	write_command(0x81); //contrast control
	write_command(0x50);
	write_command(0xd9); //set pre-charge period
	write_command(0x21);
	write_command(0x20); //Set Memory Addressing Mode
	write_command(0x02);
	write_command(0xdb); //VCOM deselect level mode
	write_command(0x30);
	write_command(0xad); //master configuration
	write_command(0x00);
	write_command(0xa4); //out follows RAM content
	write_command(0xa6); //set normal display
	write_command(0xaf); // display on
	//write_command(0xa5);
oled_reset();
	
}

void oled_reset(){
	
	for (int line = 0; line < 8; line++) {
		oled_clear_line(line);
	}
	oled_home();
}

void oled_home(){
	oled_pos(0,0);
}

void oled_goto_line(int line){
	if (line > 7 || line < 0) {
		return 0;
	}
	else {
		position.row = line;
		oled_set_adressing_mode(page_mode);
		write_command(0xb0 + line);
		oled_set_adressing_mode(horizontal_mode);
	}
}

void oled_goto_column(int column){
	if (column > 127 || column < 0) {
		return 0;
	}
	else {
		position.col = column;
		oled_set_adressing_mode(page_mode);
		
		int numlow = column % 16;
		int numhigh = column / 16;
		
		write_command(numlow);
		write_command(16 + numhigh);
		oled_set_adressing_mode(horizontal_mode);
	}
	
}

void oled_goto_letter(int letterplace){
	if (letterplace <= 0) {
		oled_goto_column(0);
	}
	else {
		oled_goto_column(letterplace*fontsize-1);
	}
}

void oled_clear_line(int line){
	oled_pos(line, 0);
	
	for (int col = 0; col < 128; col++) {
		write_data(0b00000000);
	}
	oled_goto_line(line);
}

void oled_fill_line(int line){
	oled_pos(line,0);
	
	for (int col =0; col < 128; col++) {
		write_data(~0b00000000);
	}
	oled_goto_line(line);
}

void oled_pos(int row, int column){
	oled_goto_line(row);
	oled_goto_column(column);
}

void PrintMenu()
{	int taps = 0;
	joystick_direction_t JoyPos = joystick_get_direction();
	oled_pos(0,25);
	oled_printf ("MAIN MENU");
	oled_pos(1,0);
	oled_printf ("1.Play Game");
	oled_pos(2,0);
	oled_printf ("2.View Score");
	oled_pos(3,0);
	oled_printf ("3.Difficulty");
	oled_pos(4,0);
	oled_printf("4.Joy Calibrate");

	if (JoyPos== DOWN)
				{oled_pos(1,0);
				oled_inv_printf ("1.Play Game");}
				
					



			
			

}