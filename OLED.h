/*
 * OLED.h
 *
 * Created: 03.10.2019 14:39:13
 *  Author: muhamawa
 */ 


#ifndef OLED_H_
#define OLED_H_
#include <util/delay.h>
#include <avr/io.h>


typedef struct {
	int row, col;
} oled_position_t;

#define OLED_COMMAND_ADDRESS  0x1000
#define OLED_DATA_ADDRESS 0x1200

void OLED_Init();
void OLED_pos(uint8_t row,uint8_t col);
void XMEM_Init();
void write_data(uint8_t data);
void OLED_pos(uint8_t row,uint8_t col);
void write_c(uint8_t command);
void Test_OLED(void);


#endif /* OLED_H_ */