#include <stdlib.h>
#include <stdint.h>
#include "SRAM_driver.h"

#ifndef SRAM_FIRST_ADDRESS
#define SRAM_FIRST_ADDRESS 0x1800 // macro
#endif

int SRAM_write(uint16_t address, char data){
	
	if (address > 0x7FF){    // 0x7FF is max
		printf("SRAM error\n");
		return EXIT_FAILURE;
	}
	
	volatile char* ext_ram = SRAM_FIRST_ADDRESS;//Pointer to where we write
	ext_ram[address] = data;
	
	return 0;
}

char SRAM_read(uint16_t address){
	
	if (address > 0x7FF){  // 0x7FF is max
		printf("SRAM error\n");
		return EXIT_FAILURE;
	}
	
	volatile char* ext_ram = SRAM_FIRST_ADDRESS;
	return ext_ram[address];
	
}