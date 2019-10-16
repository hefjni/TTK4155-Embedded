/*
 * SPI.h
 *
 * Created: 16.10.2019 12:29:26
 *  Author: henrikfn
 */ 


#ifndef SPI_H_
#define SPI_H_

void SPI_Init(void);
void SPI_Transmit(char cData);
char SPI_receive(void);


#endif /* SPI_H_ */