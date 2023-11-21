
#include "stm32f4xx.h"

typedef struct
{

	uint32_t PORT;						// Ссылка на порт
	uint8_t MB_Addr;					// Адрес Slave
	uint8_t RX_buff_pointer;
	uint8_t LenLongMessage;

	uint16_t TX_incr;
	uint16_t TX_count;

	uint16_t Roll;
	uint16_t Roll_max;
	uint16_t schet;

	int16_t Registers[255]; 			// Внутренние регистры
	int16_t Input_Registers[255]; 		// Регистры функции 0x04
	uint8_t TX_buff[255];				// Буфер выходного набора байт
	uint8_t RX_buff[255];				// Буфер входного набора байт
	uint8_t CRC_Calc_out_table[3]; 		// Буфер контрольной суммы

	uint16_t StartAddr;
	uint16_t Quanity;
	int16_t TempRegister;

	int16_t Transmit_delay;

} UART_Slave_DB;

typedef struct
{

	uint32_t Leach_DB;					// Ссылка на основную БД
	uint8_t MB_Addr;					// Адрес Slave Leach
	int16_t Registers[255]; 			// Внутренние регистры
	int16_t Input_Registers[255]; 		// Регистры функции 0x04

} UART_Leech;






/*
CRC_16_Modbus(uint8_t Buffer[], uint8_t Len, uint32_t pointer_out);
void Slave_PORT_Processor(uint32_t pointer_DB);
void Slave_Processor(uint32_t pointer_DB);
void Slave_Leech(uint32_t pointer_Leech);
void Slave_Clock_1ms(uint32_t pointer_DB);
*/
