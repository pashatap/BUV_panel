/*
 * SPI_flash.h
 *
 *  Created on: Mar 9, 2022
 *      Author: Motor
 */

#ifndef INC_SPI_FLASH_H_
#define INC_SPI_FLASH_H_

#include "stm32f4xx.h"

typedef struct
{
	uint8_t header[4];
	uint8_t buff[256];
	uint8_t auxiliary_array[260];
	uint8_t Command;
	uint32_t Addres;
} SPI_IO;

void SPI_command_transmit(uint8_t command);
void SPI_recieve_256(uint32_t pointer_DB);
void SPI_transmit_256(uint32_t pointer_DB);

void Flash_Erase();
void delay_flash();

#endif /* INC_SPI_FLASH_H_ */
