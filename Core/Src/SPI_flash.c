/*
 * SPI_flash.c
 *
 *  Created on: Mar 9, 2022
 *      Author: Motor
 */

#include "SPI_flash.h"
#include "stm32f4xx.h"

#define TransferON  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_RESET); // Вкл  SPI
#define TransferOFF HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_SET);   // Выкл SPI

extern __IO SPI_HandleTypeDef hspi1;


void SPI_command_transmit(uint8_t command)
{
	delay_flash();
	TransferON;
	delay_flash();
	HAL_SPI_Transmit(&hspi1, &command, 1, 50);
	delay_flash();
	TransferOFF;
}

void SPI_recieve_256(uint32_t pointer_DB)
{
	struct {SPI_IO a;} *SPI = pointer_DB;

	//delay_flash();
	TransferON;
	//delay_flash();

	SPI->a.Command = 0x03;

	SPI->a.auxiliary_array[0] = SPI->a.Command;
	memcpy(&SPI->a.header[0], &SPI->a.Addres, 3);

	SPI->a.auxiliary_array[3] = SPI->a.header[0];
	SPI->a.auxiliary_array[2] = SPI->a.header[1];
	SPI->a.auxiliary_array[1] = SPI->a.header[2];

	HAL_SPI_TransmitReceive(&hspi1, &SPI->a.auxiliary_array, pointer_DB, 260, 100);
	//delay_flash();
	TransferOFF;
}

void SPI_transmit_256(uint32_t pointer_DB)
{
	SPI_command_transmit(0x06); // WREN
	struct {SPI_IO a;} *SPI = pointer_DB;

	delay_flash();
	TransferON;
	delay_flash();

	SPI->a.Command = 0x02;

	SPI->a.header[0] = SPI->a.Command;
	memcpy(&SPI->a.auxiliary_array[0], &SPI->a.Addres, 3);

	SPI->a.header[3] = SPI->a.auxiliary_array[0];
	SPI->a.header[2] = SPI->a.auxiliary_array[1];
	SPI->a.header[1] = SPI->a.auxiliary_array[2];

	HAL_SPI_Transmit(&hspi1, pointer_DB, 260, 100);
	delay_flash();
	TransferOFF;
}

void Flash_Erase()
{
	HAL_Delay(1);
    SPI_command_transmit(0x06); // WREN
    HAL_Delay(1);
    SPI_command_transmit(0x60); // CHIP ERASE
    HAL_Delay(5000);
    SPI_command_transmit(0x66); // RSTEN
    HAL_Delay(1);
    SPI_command_transmit(0x99); // RST
    HAL_Delay(1);
    SPI_command_transmit(0x7A); // EPR
    HAL_Delay(1);
    SPI_command_transmit(0x06); // WREN
    HAL_Delay(1);
}


void delay_flash()
{
	uint32_t time = 5000;
	while(time){time--;}
}









