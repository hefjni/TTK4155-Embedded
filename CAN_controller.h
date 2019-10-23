/*
 * CAN_controller.h
 *
 * Created: 16.10.2019 13:26:47
 *  Author: henrikfn
 */ 


#ifndef CAN_CONTROLLER_H_
#define CAN_CONTROLLER_H_



uint8_t mcp_2515_read(uint8_t address);
void mcp_2515_write(uint8_t address, uint8_t data);
void mcp_2515_reset();
void mcp_2515_request_to_send(char buffer);
void mcp_2515_bit_modify(uint8_t adress, uint8_t mask, uint8_t data);
uint8_t mcp_2515_read_status();
uint8_t mcp_2515_init(uint8_t mode);
void mcp_2515_set_mode(uint8_t mode);



#endif /* CAN_CONTROLLER_H_ */