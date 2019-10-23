/*
 * CAN_controller.c
 *
 * Created: 16.10.2019 13:26:33
 *  Author: henrikfn
 */ 

#include <stdint.h>
#include <avr/io.h>
#include <avr/delay.h>
#include "SPI.h"
#include "BitMacros.h"
#include "MCP2515.h"
#include "CAN_controller.h"

void activate_slave(void){
	clear_bit(PORTB,PB4);
}

void deactivate_slave(void){
	set_bit(PORTB,PB4);
}

void mcp_2515_set_mode(uint8_t mode){
	mcp_2515_write(MCP_CANCTRL, mode);
}

uint8_t mcp_2515_init(uint8_t mode){
	
	uint8_t val;
	SPI_init();
	mcp_2515_reset();
	
	val = mcp_2515_read(MCP_CANSTAT);
	uint8_t mode_bits = (val & MODE_MASK); //
	//printf("mode bits: %04X\r\n", mode_bits);
	//printf("val: %04X\r\n", mode_bits);
	if(mode_bits != MODE_CONFIG){
		printf("MCP2515 is NOT in Configuration mode after reset! Its config bits are %x\n", mode_bits);
		printf("\n!\n");
		return 1;
	}
	
	mcp_2515_set_mode(mode);
	
	val = mcp_2515_read(MCP_CANSTAT);
	mode_bits = (val & MODE_MASK);
	
	if(mode_bits != mode){
		
		printf("MCP2515 is NOT in correct mode after reset! Its config bits are %x\n", mode_bits);
		printf("\n!\n");
		return 1;
	}
	//printf("----------------\r\n");
	//printf("val: %04X\r\n", mode_bits);
	//printf("mode bits: %04X\r\n", mode_bits);
	//printf("val: %04X\r\n", mode_bits);
	
	return 0;
}

void mcp_2515_reset(){

	activate_slave();
	SPI_transmit(MCP_RESET); // command for reset
	deactivate_slave();
	_delay_ms(20);	//a small delay
}

uint8_t mcp_2515_read(uint8_t address){
	activate_slave(); // set CS low - Activate slave
	uint8_t data;
	SPI_transmit(MCP_READ);   // send command - Using SPI - using SPI function transmit
	SPI_transmit(address);    	// send address - using SPI - using SPI function transmit
	data = SPI_receive();    // store data read at "data", which is later returned - using SPI function for read	
	
	deactivate_slave(); // set CS high - deActivate slave
	return data;

}

void mcp_2515_write(uint8_t address, uint8_t data){
	activate_slave(); // set CS low - Activate slave


	SPI_transmit(MCP_WRITE);   // send command - Using SPI - using SPI function write
	SPI_transmit(address);    	// send address - using SPI - using SPI function write
	SPI_transmit(data);   // store data read at "data", which is later returned - using SPI function for read
	
	deactivate_slave(); // set CS high - deActivate slave
	
	
}


void mcp_2515_request_to_send(char buffer) {
	activate_slave();
	
	SPI_transmit(buffer);
	
	deactivate_slave();
}

void mcp_2515_bit_modify(uint8_t address, uint8_t mask, uint8_t data) {
	activate_slave();
	
	SPI_transmit(0x05);
	SPI_transmit(address);
	SPI_transmit(mask);
	SPI_transmit(data);
	
	deactivate_slave();
}

uint8_t mcp_2515_read_status() {
	activate_slave();
	
	SPI_transmit(MCP_READ_STATUS); // command for read status
	uint8_t status = SPI_receive();
	
	deactivate_slave();
	
	return status;
}

