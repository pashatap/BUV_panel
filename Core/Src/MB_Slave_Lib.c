
#include "MB_Slave_Lib.h"


// Поддерживаются функции 0x03, 0x04, 0x06, 0x10, 0x17


CRC_16_Modbus(uint8_t Buffer[], uint8_t Len, uint32_t pointer_out) //Рассчёт CRC
{
	uint8_t OutTable[3];

	uint16_t  i;
	uint8_t  j;
	uint16_t TempByte, CurrentCRC = 0xFFFF;

	uint8_t HiByte;
	uint8_t LoByte;
	//make byte 16 bit format

	for ( i = 0; i < Len; i++ )
	{
	  TempByte = Buffer[i];

	  for ( j = 0; j < 8; j++ )
	  {
		  if ( (CurrentCRC & 0x0001) == (TempByte & 0x0001) )
		  {
			  //right shift crc
			  CurrentCRC >>= 1;
			  //right shift data
			  TempByte >>= 1;
		  }
		  else
		  {
			  CurrentCRC >>= 1;
			  TempByte >>= 1;
			  CurrentCRC = CurrentCRC ^ 0xA001; /* 1000 0100 0000 1000 = x^16 + x^12 + x^5 + 1 */
		  }
	  }
	}

	HiByte = 0x00FF & CurrentCRC;
	CurrentCRC = 0xFF00 & CurrentCRC;
	CurrentCRC = CurrentCRC >> 8;
	LoByte = 0x00FF & CurrentCRC;

	OutTable[0] = HiByte;
	OutTable[1] = LoByte;
	OutTable[2] = 0;


	if( (Buffer[Len] == HiByte) & (Buffer[Len+1] == LoByte) )
	{
		OutTable[2] = 1;
	}

	memcpy(pointer_out, &OutTable, 3);
}

void Slave_PORT_Processor(uint32_t pointer_DB)
{

	struct {UART_Slave_DB a;} *Slave_DB = pointer_DB;
	struct {USART_TypeDef a;} *USART_port = Slave_DB->a.PORT;

	if(USART_port->a.SR & 0x80) // если прерывание по передаче
	{
		if(Slave_DB->a.TX_count)
		{
			GPIOF->BSRR = GPIO_PIN_8;		//Tx On

			Slave_DB->a.Roll++;
			if(Slave_DB->a.Roll > Slave_DB->a.Roll_max)
			{

				Slave_DB->a.Roll= 0;

				if(Slave_DB->a.TX_count < Slave_DB->a.TX_incr)
				{
					Slave_DB->a.TX_count = 0;
					USART_port->a.CR1 = 0x202c;
					GPIOF->BSRR = GPIO_PIN_8 << 16;	//Tx Off
				}
				else
				{
					USART_port->a.DR = Slave_DB->a.TX_buff[Slave_DB->a.TX_incr];
					Slave_DB->a.TX_incr++;
				}

			}

		}
	}

	if(!Slave_DB->a.TX_count)
	{
		if( (USART_port->a.SR & 0x20) ) // если прерывание по приёму
		{

			if(Slave_DB->a.schet > 3){Slave_DB->a.RX_buff_pointer = 0;}
			Slave_DB->a.RX_buff[Slave_DB->a.RX_buff_pointer] = 0x000000FF & (USART_port->a.DR);
			Slave_DB->a.RX_buff_pointer++;
			Slave_DB->a.schet=0;
		}

		USART_port->a.CR1 |= 0x20;
	}

}

void Slave_Processor(uint32_t pointer_DB)
{

	struct {UART_Slave_DB a;} *Slave_DB = pointer_DB;
	struct {USART_TypeDef a;} *USART_port = Slave_DB->a.PORT;

	if( Slave_DB->a.RX_buff[0] == Slave_DB->a.MB_Addr )
	{
		if( Slave_DB->a.RX_buff_pointer == 8 )
		{

				if ((Slave_DB->a.RX_buff[1] == 3) | (Slave_DB->a.RX_buff[1] == 4) | (Slave_DB->a.RX_buff[1] == 6))
					{
						Slave_DB->a.CRC_Calc_out_table[2] = 0;
						if(Slave_DB->a.RX_buff[1] <= 6) {CRC_16_Modbus(Slave_DB->a.RX_buff, 6, &Slave_DB->a.CRC_Calc_out_table);} //Проверка CRC

						if(Slave_DB->a.CRC_Calc_out_table[2]) //Если CRC OK
						{

							if(Slave_DB->a.RX_buff[1] == 6) // обработка функции 0x06
							{

								Slave_DB->a.StartAddr = Slave_DB->a.RX_buff[2];
								Slave_DB->a.StartAddr = Slave_DB->a.StartAddr << 8;
								Slave_DB->a.StartAddr = Slave_DB->a.StartAddr | Slave_DB->a.RX_buff[3];

								Slave_DB->a.Registers[Slave_DB->a.StartAddr] = Slave_DB->a.RX_buff[4];
								Slave_DB->a.Registers[Slave_DB->a.StartAddr] = Slave_DB->a.Registers[Slave_DB->a.StartAddr] << 8;
								Slave_DB->a.Registers[Slave_DB->a.StartAddr] = Slave_DB->a.Registers[Slave_DB->a.StartAddr] | Slave_DB->a.RX_buff[5];

								for(int i=0;i<8;i++)
								{
									Slave_DB->a.TX_buff[i] = Slave_DB->a.RX_buff[i];
								}

								Slave_DB->a.TX_count = 8;
								Slave_DB->a.TX_incr = 0;
								Slave_DB->a.RX_buff_pointer = 0;

							}

							if((Slave_DB->a.RX_buff[1] == 3) | (Slave_DB->a.RX_buff[1] == 4)) // обработка функции 0x03 и 0x04
							{

								Slave_DB->a.TX_buff[0] = Slave_DB->a.RX_buff[0];
								Slave_DB->a.TX_buff[1] = Slave_DB->a.RX_buff[1];

								Slave_DB->a.StartAddr = Slave_DB->a.RX_buff[2];
								Slave_DB->a.StartAddr = Slave_DB->a.StartAddr << 8;
								Slave_DB->a.StartAddr = Slave_DB->a.StartAddr | Slave_DB->a.RX_buff[3];

								Slave_DB->a.Quanity = Slave_DB->a.RX_buff[4];
								Slave_DB->a.Quanity = Slave_DB->a.Quanity << 8;
								Slave_DB->a.Quanity = Slave_DB->a.Quanity | Slave_DB->a.RX_buff[5];

								Slave_DB->a.TX_buff[2] = Slave_DB->a.Quanity * 2;

								if(Slave_DB->a.RX_buff[1] == 4)
								{
									for(int i=0;i<Slave_DB->a.TX_buff[2];i=i+2)
									{
										Slave_DB->a.TX_buff[i+4] = Slave_DB->a.Input_Registers[Slave_DB->a.StartAddr + (i/2)] & 0x00FF;
										Slave_DB->a.TempRegister = Slave_DB->a.Input_Registers[Slave_DB->a.StartAddr + (i/2)] & 0xFF00;
										Slave_DB->a.TempRegister = Slave_DB->a.TempRegister >> 8;
										Slave_DB->a.TX_buff[i+3] = Slave_DB->a.TempRegister & 0x00FF;
									}
								}
								else
								{
									for(int i=0;i<Slave_DB->a.TX_buff[2];i=i+2)
									{
										Slave_DB->a.TX_buff[i+4] = Slave_DB->a.Registers[Slave_DB->a.StartAddr + (i/2)] & 0x00FF;
										Slave_DB->a.TempRegister = Slave_DB->a.Registers[Slave_DB->a.StartAddr + (i/2)] & 0xFF00;
										Slave_DB->a.TempRegister = Slave_DB->a.TempRegister >> 8;
										Slave_DB->a.TX_buff[i+3] = Slave_DB->a.TempRegister & 0x00FF;
									}
								}

								uint8_t LenMess;
								LenMess = Slave_DB->a.TX_buff[2] + 5;
								CRC_16_Modbus(Slave_DB->a.TX_buff, (LenMess - 2), &Slave_DB->a.CRC_Calc_out_table);
								Slave_DB->a.TX_buff[LenMess - 1] = Slave_DB->a.CRC_Calc_out_table[1];
								Slave_DB->a.TX_buff[LenMess - 2] = Slave_DB->a.CRC_Calc_out_table[0];

								Slave_DB->a.TX_count = LenMess;
								Slave_DB->a.TX_incr = 0;
								Slave_DB->a.RX_buff_pointer = 0;


							}

						}
					}

				if( Slave_DB->a.RX_buff[1] == 16 ) // зондирование для функции 0x10
				{
					Slave_DB->a.Quanity = Slave_DB->a.RX_buff[6];
					Slave_DB->a.LenLongMessage = Slave_DB->a.Quanity + 9;
				}
		}

		if( Slave_DB->a.RX_buff_pointer == 11 )
		{
			if( Slave_DB->a.RX_buff[1] == 23 ) // зондирование для функции 0x17
				{
					Slave_DB->a.Quanity = Slave_DB->a.RX_buff[10];
					Slave_DB->a.LenLongMessage = Slave_DB->a.Quanity + 13;
				}
		}


		if( Slave_DB->a.RX_buff[1] == 16 ) // обработка функции 0x10
		{
			if( (Slave_DB->a.RX_buff_pointer == Slave_DB->a.LenLongMessage) )
			{
				Slave_DB->a.CRC_Calc_out_table[2] = 0;
				if(Slave_DB->a.RX_buff[1] == 16) {CRC_16_Modbus(Slave_DB->a.RX_buff, (Slave_DB->a.LenLongMessage-2), &Slave_DB->a.CRC_Calc_out_table);} //Проверка CRC

				if(Slave_DB->a.CRC_Calc_out_table[2]) //Если CRC OK
				{

					Slave_DB->a.StartAddr = Slave_DB->a.RX_buff[2];
					Slave_DB->a.StartAddr = Slave_DB->a.StartAddr << 8;
					Slave_DB->a.StartAddr = Slave_DB->a.StartAddr | Slave_DB->a.RX_buff[3];

					for(int i=0;i<Slave_DB->a.RX_buff[6];i=i+2)
					{
						Slave_DB->a.Registers[Slave_DB->a.StartAddr + (i/2)] = Slave_DB->a.RX_buff[i+7];
						Slave_DB->a.Registers[Slave_DB->a.StartAddr + (i/2)] = Slave_DB->a.Registers[Slave_DB->a.StartAddr + (i/2)] << 8;
						Slave_DB->a.Registers[Slave_DB->a.StartAddr + (i/2)] = Slave_DB->a.Registers[Slave_DB->a.StartAddr + (i/2)] | Slave_DB->a.RX_buff[i+8];
					}

					for(int i=0;i<6;i++)
					{Slave_DB->a.TX_buff[i] = Slave_DB->a.RX_buff[i];}

					CRC_16_Modbus(Slave_DB->a.TX_buff, 6, &Slave_DB->a.CRC_Calc_out_table);
					Slave_DB->a.TX_buff[6] = Slave_DB->a.CRC_Calc_out_table[0];
					Slave_DB->a.TX_buff[7] = Slave_DB->a.CRC_Calc_out_table[1];

					Slave_DB->a.TX_count = 8;
					Slave_DB->a.TX_incr = 0;
					Slave_DB->a.RX_buff_pointer = 0;
				}
			}
		}

		if( Slave_DB->a.RX_buff[1] == 23 ) // обработка функции 0x17
		{
			if( (Slave_DB->a.RX_buff_pointer == Slave_DB->a.LenLongMessage) )
			{
				Slave_DB->a.CRC_Calc_out_table[2] = 0;
				if(Slave_DB->a.RX_buff[1] == 23) {CRC_16_Modbus(Slave_DB->a.RX_buff, (Slave_DB->a.LenLongMessage-2), &Slave_DB->a.CRC_Calc_out_table);} //Проверка CRC

				if(Slave_DB->a.CRC_Calc_out_table[2]) //Если CRC OK
				{
					// Приём регистров
					Slave_DB->a.StartAddr = Slave_DB->a.RX_buff[6];
					Slave_DB->a.StartAddr = Slave_DB->a.StartAddr << 8;
					Slave_DB->a.StartAddr = Slave_DB->a.StartAddr | Slave_DB->a.RX_buff[7];

					for(int i=0;i<Slave_DB->a.RX_buff[10];i=i+2)
					{
						Slave_DB->a.Registers[Slave_DB->a.StartAddr + (i/2)] = Slave_DB->a.RX_buff[i+11];
						Slave_DB->a.Registers[Slave_DB->a.StartAddr + (i/2)] = Slave_DB->a.Registers[Slave_DB->a.StartAddr + (i/2)] << 8;
						Slave_DB->a.Registers[Slave_DB->a.StartAddr + (i/2)] = Slave_DB->a.Registers[Slave_DB->a.StartAddr + (i/2)] | Slave_DB->a.RX_buff[i+12];
					}

					// Формирование ответа
					Slave_DB->a.TX_buff[0] = Slave_DB->a.RX_buff[0];
					Slave_DB->a.TX_buff[1] = Slave_DB->a.RX_buff[1];

					Slave_DB->a.Quanity = Slave_DB->a.RX_buff[4];
					Slave_DB->a.Quanity = Slave_DB->a.Quanity << 8;
					Slave_DB->a.Quanity = Slave_DB->a.Quanity | Slave_DB->a.RX_buff[5];

					Slave_DB->a.TX_buff[2] = Slave_DB->a.Quanity * 2;

					Slave_DB->a.StartAddr = Slave_DB->a.RX_buff[2];
					Slave_DB->a.StartAddr = Slave_DB->a.StartAddr << 8;
					Slave_DB->a.StartAddr = Slave_DB->a.StartAddr | Slave_DB->a.RX_buff[3];

					for(int i=0;i<Slave_DB->a.TX_buff[2];i=i+2)
					{
						Slave_DB->a.TX_buff[i+4] = Slave_DB->a.Registers[Slave_DB->a.StartAddr + (i/2)] & 0x00FF;
						Slave_DB->a.TempRegister = Slave_DB->a.Registers[Slave_DB->a.StartAddr + (i/2)] & 0xFF00;
						Slave_DB->a.TempRegister = Slave_DB->a.TempRegister >> 8;
						Slave_DB->a.TX_buff[i+3] = Slave_DB->a.TempRegister & 0x00FF;
					}

					uint8_t LenMess;
					LenMess = Slave_DB->a.TX_buff[2] + 5;
					CRC_16_Modbus(Slave_DB->a.TX_buff, (LenMess - 2), &Slave_DB->a.CRC_Calc_out_table);
					Slave_DB->a.TX_buff[LenMess - 1] = Slave_DB->a.CRC_Calc_out_table[1];
					Slave_DB->a.TX_buff[LenMess - 2] = Slave_DB->a.CRC_Calc_out_table[0];

					Slave_DB->a.TX_count = LenMess;
					Slave_DB->a.TX_incr = 0;
					Slave_DB->a.RX_buff_pointer = 0;
				}
			}
		}
	}
}

void Slave_Leech(uint32_t pointer_Leech)
{

	struct {UART_Leech a;} *Leach_DB = pointer_Leech;

	struct {UART_Slave_DB a;} *Slave_DB = Leach_DB->a.Leach_DB;
	struct {USART_TypeDef a;} *USART_port = Slave_DB->a.PORT;


	if( Slave_DB->a.RX_buff[0] == Leach_DB->a.MB_Addr )
	{
		if( Slave_DB->a.RX_buff_pointer == 8 )
		{
			if ((Slave_DB->a.RX_buff[1] == 3) | (Slave_DB->a.RX_buff[1] == 4) | (Slave_DB->a.RX_buff[1] == 6))
			{
				Slave_DB->a.CRC_Calc_out_table[2] = 0;
				if(Slave_DB->a.RX_buff[1] <= 6) {CRC_16_Modbus(Slave_DB->a.RX_buff, 6, &Slave_DB->a.CRC_Calc_out_table);} //Проверка CRC

				if(Slave_DB->a.CRC_Calc_out_table[2]) //Если CRC OK
				{
					if(Slave_DB->a.RX_buff[1] == 6) // обработка функции 0x06
					{

						Slave_DB->a.StartAddr = Slave_DB->a.RX_buff[2];
						Slave_DB->a.StartAddr = Slave_DB->a.StartAddr << 8;
						Slave_DB->a.StartAddr = Slave_DB->a.StartAddr | Slave_DB->a.RX_buff[3];

						Leach_DB->a.Registers[Slave_DB->a.StartAddr] = Slave_DB->a.RX_buff[4];
						Leach_DB->a.Registers[Slave_DB->a.StartAddr] = Leach_DB->a.Registers[Slave_DB->a.StartAddr] << 8;
						Leach_DB->a.Registers[Slave_DB->a.StartAddr] = Leach_DB->a.Registers[Slave_DB->a.StartAddr] | Slave_DB->a.RX_buff[5];

						for(int i=0;i<8;i++)
						{
							Slave_DB->a.TX_buff[i] = Slave_DB->a.RX_buff[i];
						}

						Slave_DB->a.TX_count = 8;
						Slave_DB->a.TX_incr = 0;
						Slave_DB->a.RX_buff_pointer = 0;

					}

					if((Slave_DB->a.RX_buff[1] == 3) | (Slave_DB->a.RX_buff[1] == 4)) // обработка функции 0x03 и 0x04
					{

						Slave_DB->a.TX_buff[0] = Slave_DB->a.RX_buff[0];
						Slave_DB->a.TX_buff[1] = Slave_DB->a.RX_buff[1];

						Slave_DB->a.StartAddr = Slave_DB->a.RX_buff[2];
						Slave_DB->a.StartAddr = Slave_DB->a.StartAddr << 8;
						Slave_DB->a.StartAddr = Slave_DB->a.StartAddr | Slave_DB->a.RX_buff[3];

						Slave_DB->a.Quanity = Slave_DB->a.RX_buff[4];
						Slave_DB->a.Quanity = Slave_DB->a.Quanity << 8;
						Slave_DB->a.Quanity = Slave_DB->a.Quanity | Slave_DB->a.RX_buff[5];

						Slave_DB->a.TX_buff[2] = Slave_DB->a.Quanity * 2;

						if(Slave_DB->a.RX_buff[1] == 4)
						{
							for(int i=0;i<Slave_DB->a.TX_buff[2];i=i+2)
							{
								Slave_DB->a.TX_buff[i+4] = Leach_DB->a.Input_Registers[Slave_DB->a.StartAddr + (i/2)] & 0x00FF;
								Slave_DB->a.TempRegister = Leach_DB->a.Input_Registers[Slave_DB->a.StartAddr + (i/2)] & 0xFF00;
								Slave_DB->a.TempRegister = Slave_DB->a.TempRegister >> 8;
								Slave_DB->a.TX_buff[i+3] = Slave_DB->a.TempRegister & 0x00FF;
							}
						}
						else
						{
							for(int i=0;i<Slave_DB->a.TX_buff[2];i=i+2)
							{
								Slave_DB->a.TX_buff[i+4] = Leach_DB->a.Registers[Slave_DB->a.StartAddr + (i/2)] & 0x00FF;
								Slave_DB->a.TempRegister = Leach_DB->a.Registers[Slave_DB->a.StartAddr + (i/2)] & 0xFF00;
								Slave_DB->a.TempRegister = Slave_DB->a.TempRegister >> 8;
								Slave_DB->a.TX_buff[i+3] = Slave_DB->a.TempRegister & 0x00FF;
							}
						}

						uint8_t LenMess;
						LenMess = Slave_DB->a.TX_buff[2] + 5;
						CRC_16_Modbus(Slave_DB->a.TX_buff, (LenMess - 2), &Slave_DB->a.CRC_Calc_out_table);
						Slave_DB->a.TX_buff[LenMess - 1] = Slave_DB->a.CRC_Calc_out_table[1];
						Slave_DB->a.TX_buff[LenMess - 2] = Slave_DB->a.CRC_Calc_out_table[0];

						Slave_DB->a.TX_count = LenMess;
						Slave_DB->a.TX_incr = 0;
						Slave_DB->a.RX_buff_pointer = 0;


					}

				}
			}


			if( Slave_DB->a.RX_buff[1] == 16 ) // зондирование для функции 0x10
			{
				Slave_DB->a.Quanity = Slave_DB->a.RX_buff[6];
				Slave_DB->a.LenLongMessage = Slave_DB->a.Quanity + 9;
			}

		}


		if( Slave_DB->a.RX_buff_pointer == 11 )
		{
			if( Slave_DB->a.RX_buff[1] == 23 ) // зондирование для функции 0x17
				{
					Slave_DB->a.Quanity = Slave_DB->a.RX_buff[10];
					Slave_DB->a.LenLongMessage = Slave_DB->a.Quanity + 13;
				}
		}


		if( Slave_DB->a.RX_buff[1] == 16 ) // обработка функции 0x10
		{
			if( (Slave_DB->a.RX_buff_pointer == Slave_DB->a.LenLongMessage) )
			{
				Slave_DB->a.CRC_Calc_out_table[2] = 0;
				if(Slave_DB->a.RX_buff[1] == 16) {CRC_16_Modbus(Slave_DB->a.RX_buff, (Slave_DB->a.LenLongMessage-2), &Slave_DB->a.CRC_Calc_out_table);} //Проверка CRC

				if(Slave_DB->a.CRC_Calc_out_table[2]) //Если CRC OK
				{
					Slave_DB->a.StartAddr = Slave_DB->a.RX_buff[2];
					Slave_DB->a.StartAddr = Slave_DB->a.StartAddr << 8;
					Slave_DB->a.StartAddr = Slave_DB->a.StartAddr | Slave_DB->a.RX_buff[3];

					for(int i=0;i<Slave_DB->a.RX_buff[6];i=i+2)
					{
						Leach_DB->a.Registers[Slave_DB->a.StartAddr + (i/2)] = Slave_DB->a.RX_buff[i+7];
						Leach_DB->a.Registers[Slave_DB->a.StartAddr + (i/2)] = Leach_DB->a.Registers[Slave_DB->a.StartAddr + (i/2)] << 8;
						Leach_DB->a.Registers[Slave_DB->a.StartAddr + (i/2)] = Leach_DB->a.Registers[Slave_DB->a.StartAddr + (i/2)] | Slave_DB->a.RX_buff[i+8];
					}

					for(int i=0;i<6;i++)
					{Slave_DB->a.TX_buff[i] = Slave_DB->a.RX_buff[i];}

					CRC_16_Modbus(Slave_DB->a.TX_buff, 6, &Slave_DB->a.CRC_Calc_out_table);
					Slave_DB->a.TX_buff[6] = Slave_DB->a.CRC_Calc_out_table[0];
					Slave_DB->a.TX_buff[7] = Slave_DB->a.CRC_Calc_out_table[1];

					Slave_DB->a.TX_count = 8;
					Slave_DB->a.TX_incr = 0;
					Slave_DB->a.RX_buff_pointer = 0;
				}
			}
		}

		if( Slave_DB->a.RX_buff[1] == 23 ) // обработка функции 0x17
		{
			if( (Slave_DB->a.RX_buff_pointer == Slave_DB->a.LenLongMessage) )
			{
				Slave_DB->a.CRC_Calc_out_table[2] = 0;
				if(Slave_DB->a.RX_buff[1] == 23) {CRC_16_Modbus(Slave_DB->a.RX_buff, (Slave_DB->a.LenLongMessage-2), &Slave_DB->a.CRC_Calc_out_table);} //Проверка CRC

				if(Slave_DB->a.CRC_Calc_out_table[2]) //Если CRC OK
				{
					// Приём регистров
					Slave_DB->a.StartAddr = Slave_DB->a.RX_buff[6];
					Slave_DB->a.StartAddr = Slave_DB->a.StartAddr << 8;
					Slave_DB->a.StartAddr = Slave_DB->a.StartAddr | Slave_DB->a.RX_buff[7];

					for(int i=0;i<Slave_DB->a.RX_buff[10];i=i+2)
					{
						Leach_DB->a.Registers[Slave_DB->a.StartAddr + (i/2)] = Slave_DB->a.RX_buff[i+11];
						Leach_DB->a.Registers[Slave_DB->a.StartAddr + (i/2)] = Leach_DB->a.Registers[Slave_DB->a.StartAddr + (i/2)] << 8;
						Leach_DB->a.Registers[Slave_DB->a.StartAddr + (i/2)] = Leach_DB->a.Registers[Slave_DB->a.StartAddr + (i/2)] | Slave_DB->a.RX_buff[i+12];
					}

					// Формирование ответа
					Slave_DB->a.TX_buff[0] = Slave_DB->a.RX_buff[0];
					Slave_DB->a.TX_buff[1] = Slave_DB->a.RX_buff[1];

					Slave_DB->a.Quanity = Slave_DB->a.RX_buff[4];
					Slave_DB->a.Quanity = Slave_DB->a.Quanity << 8;
					Slave_DB->a.Quanity = Slave_DB->a.Quanity | Slave_DB->a.RX_buff[5];

					Slave_DB->a.TX_buff[2] = Slave_DB->a.Quanity * 2;

					Slave_DB->a.StartAddr = Slave_DB->a.RX_buff[2];
					Slave_DB->a.StartAddr = Slave_DB->a.StartAddr << 8;
					Slave_DB->a.StartAddr = Slave_DB->a.StartAddr | Slave_DB->a.RX_buff[3];

					for(int i=0;i<Slave_DB->a.TX_buff[2];i=i+2)
					{
						Slave_DB->a.TX_buff[i+4] = Leach_DB->a.Registers[Slave_DB->a.StartAddr + (i/2)] & 0x00FF;
						Slave_DB->a.TempRegister = Leach_DB->a.Registers[Slave_DB->a.StartAddr + (i/2)] & 0xFF00;
						Slave_DB->a.TempRegister = Slave_DB->a.TempRegister >> 8;
						Slave_DB->a.TX_buff[i+3] = Slave_DB->a.TempRegister & 0x00FF;
					}

					uint8_t LenMess;
					LenMess = Slave_DB->a.TX_buff[2] + 5;
					CRC_16_Modbus(Slave_DB->a.TX_buff, (LenMess - 2), &Slave_DB->a.CRC_Calc_out_table);
					Slave_DB->a.TX_buff[LenMess - 1] = Slave_DB->a.CRC_Calc_out_table[1];
					Slave_DB->a.TX_buff[LenMess - 2] = Slave_DB->a.CRC_Calc_out_table[0];

					Slave_DB->a.TX_count = LenMess;
					Slave_DB->a.TX_incr = 0;
					Slave_DB->a.RX_buff_pointer = 0;
				}
			}
		}
	}
}

void Slave_Clock_1ms(uint32_t pointer_DB)
{

	struct {UART_Slave_DB a;} *Slave_DB = pointer_DB;
	struct {USART_TypeDef a;} *USART_port = Slave_DB->a.PORT;

	Slave_DB->a.schet++;
	if(Slave_DB->a.schet>=100){Slave_DB->a.schet=100;}
	if(Slave_DB->a.TX_count){USART_port->a.CR1 |= 0x80;}

}
