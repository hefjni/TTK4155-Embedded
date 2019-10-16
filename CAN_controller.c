/*
 * CAN_controller.c
 *
 * Created: 16.10.2019 13:26:33
 *  Author: henrikfn
 */ 
uint8_t CAN_read(uint8_t address){
	// set CS low - Activate slave
	
	// send command - Using SPI - using SPI function write
	// send address - using SPI - using SPI function write
	
	// store data read at "data", which is later returned - using SPI function for read
	
	// set CS high - deActivate slave
	return data;
}

void CAN_write(uint8_t address, uint8_t data){
	// set CS low - Activate slave
	
	// send command - Using SPI - using SPI function write
	// send address - using SPI - using SPI function write
	
	// write data to slave using SPI function write
	
	// set CS high - deActivate slave
}