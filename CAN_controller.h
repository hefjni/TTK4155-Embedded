/*
 * CAN_controller.h
 *
 * Created: 16.10.2019 13:26:47
 *  Author: henrikfn
 */ 


#ifndef CAN_CONTROLLER_H_
#define CAN_CONTROLLER_H_

uint8_t mcp_2515_read(uint8_t address);
void CAN_write(uint8_t address, uint8_t data);



#endif /* CAN_CONTROLLER_H_ */