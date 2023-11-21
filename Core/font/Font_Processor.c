#include "Font_Processor.h"
#include "data_types.h"

extern uint32_t BackgroundColor;
extern uint32_t BasicSymbolColor;
extern uint32_t VideoBuffer;
extern uint32_t RasrPointerColor;

//extern Settings Settings_DB;
extern InterfaceControlDB Control_DB;


void DrawChar_16(uint8_t Char, uint16_t Coord_X, uint16_t Coord_Y, uint16_t Resolution_X, uint16_t Resolution_Y, uint32_t Video_buffer_pointer, uint32_t Font_Color, uint32_t Symbol_Color, uint16_t Table[], uint16_t width_char, uint16_t height_char)
{
	uint32_t Color_RGB;
	uint16_t Horizontal_line;
	struct {uint8_t b,g,r;} *vbuf=Video_buffer_pointer;

	for(int j=0;j<height_char;j++)
	{
		Horizontal_line = Table[(Char * height_char) + j];
		Horizontal_line = Horizontal_line >> (16 - width_char);

		for(int i=width_char;i>0;i--)
		{

			if(Horizontal_line & 0x1)
			{
				Color_RGB = Symbol_Color;
			}
			else
			{
				Color_RGB = Font_Color;
			}

			memcpy(&vbuf[Coord_X + ((Coord_Y+j) * Resolution_X) + i].b, &Color_RGB, 3);
			Horizontal_line = Horizontal_line >> 1;
		}

	}

}


void DrawChar_32(uint8_t Char, uint16_t Coord_X, uint16_t Coord_Y, uint16_t Resolution_X, uint16_t Resolution_Y, uint32_t Video_buffer_pointer, uint32_t Font_Color, uint32_t Symbol_Color, uint32_t Table[], uint16_t width_char, uint16_t height_char)
{
	uint32_t Color_RGB;
	uint32_t Horizontal_line;
	struct {uint8_t b,g,r;} *vbuf=Video_buffer_pointer;
	Char = Char - 32;

	for(int j=0;j<height_char;j++)
	{
		Horizontal_line = Table[(Char * height_char) + j];
		Horizontal_line = Horizontal_line >> (32 - width_char);

		for(int i=width_char;i>0;i--)
		{

			if(Horizontal_line & 0x1)
			{
				Color_RGB = Symbol_Color;
			}
			else
			{
				Color_RGB = Font_Color;
			}

			memcpy(&vbuf[Coord_X + ((Coord_Y+j) * Resolution_X) + i].b, &Color_RGB, 3);
			Horizontal_line = Horizontal_line >> 1;
		}
	}
}


void DrawString_16(char String[], uint16_t Len, uint16_t Coord_X, uint16_t Coord_Y, uint16_t Resolution_X, uint16_t Resolution_Y, uint32_t Video_buffer_pointer, uint32_t Font_Color, uint32_t Symbol_Color, uint32_t Table[], uint16_t width_char, uint16_t height_char)
{
	char String2[50];
	for(int i=0;i<Len;i++)
	{
	String2[i] = String[i] - 32;
	DrawChar_16(String2[i], (Coord_X + (width_char * i)), Coord_Y, Resolution_X, Resolution_Y, Video_buffer_pointer, Font_Color, Symbol_Color, Table, width_char, height_char);
	}
}

void Centred_DrawString_16(char String[], uint16_t Len, uint16_t Coord_X, uint16_t Coord_Y, uint16_t Resolution_X, uint16_t Resolution_Y, uint32_t Video_buffer_pointer, uint32_t Font_Color, uint32_t Symbol_Color, uint32_t Table[], uint16_t width_char, uint16_t height_char)
{
	Coord_Y = Coord_Y - (height_char / 2);
	Coord_X = Coord_X - ((width_char * Len) / 2);
	DrawString_16(String, Len, Coord_X, Coord_Y, Resolution_X, Resolution_Y, Video_buffer_pointer, Font_Color, Symbol_Color, Table, width_char, height_char);
}

void Short_Left_RU_DrawString_32(char String[], uint16_t Len, uint16_t Coord_X, uint16_t Coord_Y, uint32_t PageNumber)
{
	Coord_Y = Coord_Y - (27 / 2);
	RU_DrawString_32(String, Len, Coord_X, Coord_Y, 800, 480, PageNumber, BackgroundColor, BasicSymbolColor, RU_18x27_Table, 18, 27);
}

void Short_Left_Colored_RU_DrawString_32(char String[], uint16_t Len, uint16_t Coord_X, uint16_t Coord_Y, uint32_t Font_Color, uint32_t Symbol_Color, uint32_t PageNumber)
{
	Coord_Y = Coord_Y - (27 / 2);
	RU_DrawString_32(String, Len, Coord_X, Coord_Y, 800, 480, PageNumber, Font_Color, Symbol_Color, RU_18x27_Table, 18, 27);
}

void Short_Left_RU_DrawString_16(char String[], uint16_t Len, uint16_t Coord_X, uint16_t Coord_Y, uint32_t PageNumber)
{
	Coord_Y = Coord_Y - (27 / 2);
	RU_DrawString_32(String, Len, Coord_X, Coord_Y, 800, 480, PageNumber, BackgroundColor, BasicSymbolColor, RU_18x27_Table, 18, 27);
}

void Short_Centred_DrawString_16(char String[], uint16_t Len, uint16_t Coord_X,
		uint16_t Coord_Y, uint32_t PageNumber)
{
	Centred_DrawString_16(String, Len, Coord_X, Coord_Y, 800, 480, PageNumber, BackgroundColor, BasicSymbolColor, Arial_11x18_Table, 11, 18);
}

void Short_Centred_DrawString_16x25(char String[], uint16_t Len, uint16_t Coord_X,
		uint16_t Coord_Y, uint32_t PageNumber)
{
	Centred_DrawString_16(String, Len, Coord_X, Coord_Y, 800, 480, PageNumber, BackgroundColor, BasicSymbolColor, Arial_16x25_Table, 16, 25);
}

void Short_Centred_RU_DrawString_16(char String[], uint16_t Len, uint16_t Coord_X, uint16_t Coord_Y, uint32_t PageNumber)
{
	RU_DrawString_32(String, Len, Coord_X, Coord_Y, 800, 480, PageNumber, BackgroundColor, BasicSymbolColor, RU_18x27_Table, 18, 27);
}

void Short_Left_DrawString_16(char String[], uint16_t Len, uint16_t Coord_X, uint16_t Coord_Y, uint32_t Page)
{
	Coord_Y = Coord_Y - (27 / 2);
	DrawString_16(String, Len, Coord_X, Coord_Y, 800, 480, Page, BackgroundColor, BasicSymbolColor, Arial_16x25_Table, 16, 25);
}

void DrawString_32(char String[], uint16_t Len, uint16_t Coord_X, uint16_t Coord_Y, uint16_t Resolution_X, uint16_t Resolution_Y, uint32_t Video_buffer_pointer, uint32_t Font_Color, uint32_t Symbol_Color, uint32_t Table[], uint16_t width_char, uint16_t height_char)
{
	for(int i=0;i<Len;i++)
	{
	DrawChar_32(String[i], (Coord_X + (width_char * i)), Coord_Y, Resolution_X, Resolution_Y, Video_buffer_pointer, Font_Color, Symbol_Color, Table, width_char, height_char);
	}
}

void RU_DrawString_32(char String[], uint16_t Len, uint16_t Coord_X, uint16_t Coord_Y, uint16_t Resolution_X, uint16_t Resolution_Y, uint32_t Video_buffer_pointer, uint32_t Font_Color, uint32_t Symbol_Color, uint32_t Table[], uint16_t width_char, uint16_t height_char)
{

	uint8_t String_OUT[100];
	uint16_t num = 0;
	uint16_t limit = Len*2;
	for(int i=0;i<limit;i++)
	{
		if(String[i]>=208)
		{
			if(String[i]==208){String_OUT[num] = (String[i+1] - 79);}
			else{String_OUT[num] = (String[i+1] - 15);}
			i++;
		}
		else
		{
			String_OUT[num] = (String[i]);
			limit--;
		}
		num++;
	}

	for(int i=num;i<(Len*2);i++){String_OUT[i]=0;}


	for(int i=0;i<Len;i++)
	{
		DrawChar_32(String_OUT[i], (Coord_X + (width_char * i)), Coord_Y, Resolution_X, Resolution_Y, Video_buffer_pointer, Font_Color, Symbol_Color,
				Table, width_char, height_char);
	}
}

void Centred_RU_DrawString_32(char String[], uint16_t Len, uint16_t Coord_X, uint16_t Coord_Y, uint16_t Resolution_X, uint16_t Resolution_Y, uint32_t Video_buffer_pointer, uint32_t Font_Color, uint32_t Symbol_Color, uint32_t Table[], uint16_t width_char, uint16_t height_char)
{
	Coord_Y = Coord_Y - (height_char / 2);
	Coord_X = Coord_X - ((width_char * Len) / 2);
	RU_DrawString_32(String, Len, Coord_X, Coord_Y, Resolution_X, Resolution_Y, Video_buffer_pointer, Font_Color, Symbol_Color, Table, width_char, height_char);
}

void Short_Centred_RU_DrawString_32(char String[], uint16_t Len, uint16_t Coord_X,
		uint16_t Coord_Y, uint32_t Font_Color, uint32_t Symbol_Color, uint32_t PageNumber)
{
	Centred_RU_DrawString_32(String, Len, Coord_X, Coord_Y, 800, 480, PageNumber, Font_Color, Symbol_Color, RU_18x27_Table, 18, 27);
}

void Short_RU_DrawString_32(char String[], uint16_t Len, uint16_t Coord_X, uint16_t Coord_Y, uint32_t Font_Color, uint32_t Symbol_Color)
{
	RU_DrawString_32(String, Len, Coord_X, Coord_Y, 800, 480, VideoBuffer, Font_Color, Symbol_Color, RU_18x27_Table, 18, 27);
}

void Centred_DrawNumber_16(int16_t Register, uint16_t Comma, uint16_t Numbers, int16_t Pointer_Razr, uint16_t Coord_X, uint16_t Coord_Y, uint16_t Resolution_X, uint16_t Resolution_Y, uint32_t Video_buffer_pointer, uint32_t Font_Color, uint32_t Symbol_Color, uint32_t Table[], uint16_t width_char, uint16_t height_char)
{
	  char 		String[10];

	  uint8_t 	RazrPointerArray[10];
	  for(int i=0;i<10;i++)	{RazrPointerArray[i] = 0;}

	  uint8_t	TemporaryLenPointer;

	  uint16_t Cycle_Pointer;
	  uint16_t Final_Len = 0;
	  uint16_t Number_Len;
	  uint8_t BelowZero = 0;

	  if(Register < 0)
	  {
		  BelowZero = 1;
		  Register = 0 - Register;
	  }

	  if(Comma>5){Comma=5;}
	  if(Comma<0){Comma=0;}

	  itoa(Register, String, 10);

	  Cycle_Pointer = 0;

	  while(String[Cycle_Pointer] > 0) //подсчёт длинны числа
	  {
		  Cycle_Pointer++;
	  }

	  TemporaryLenPointer = Numbers;
	  for(int i=TemporaryLenPointer;i;i--)
	  {
		  RazrPointerArray[i-1] = TemporaryLenPointer;
		  TemporaryLenPointer--;
	  }


	  if(Comma>0)
	  {
		  if(Comma>=Cycle_Pointer)
		  {
			  Final_Len = Comma + 2;

			  int8_t temp = Cycle_Pointer;
			  for(int i=(Final_Len-1);i>=0;i--)
			  {
				  if(temp)
				  {
					  temp--;
					  String[i] = String[temp];
				  }
				  else
				  {
					  String[i] = '0';
				  }
			  }
			  String[1] = ',';
			  Cycle_Pointer--;
		  }
		  else
		  {
			  Final_Len = Cycle_Pointer + 1;

			  for(int i=(Final_Len-1);i>=0;i--)
			  {
				  if( i > (Final_Len - Comma - 1))
				  {
					  String[i] = String[i-1];
				  }
			  }
			  String[Final_Len - Comma - 1] = ',';
		  }
	  }
	  else{Final_Len = Cycle_Pointer;}


	  if(BelowZero)
	  {
		  for(int i=Final_Len;i>=0;i--)
		  {
			  String[i] = String[i - 1];
		  }
		  String[0] = '-';
		  Final_Len++;
	  }

		uint8_t StandartLen = Numbers;
		uint8_t IschLen = Final_Len - 1;
		if(Final_Len < StandartLen)
		{
			for(int i=(StandartLen - 1); i>=0;i--)
			{
				if(IschLen)
				{
					String[i] = String[IschLen];
					IschLen--;
				}
				else
				{
					if(i==(StandartLen - Final_Len))
					{
						String[i] = String[0];
					}
					else
					{
						String[i] = ' ';
					}
				}
			}
		}

		uint16_t StartX;
		uint16_t StartY;

		StartY = Coord_Y + (height_char / 2);
		StartX = Coord_X + ((width_char * StandartLen) / 2);

		if(Pointer_Razr<0){Pointer_Razr = 0;}

		for(int i=0;i<Numbers;i++)
		{
			if(Pointer_Razr == RazrPointerArray[i])
			{
				if(Pointer_Razr)
				{
					Draw_Rectangle( RasrPointerColor, (StartX - ((i+1) * width_char)), StartY + 1				 , width_char, 4, Video_buffer_pointer, 800, 480);
					Draw_Rectangle( RasrPointerColor, (StartX - ((i+1) * width_char)), (StartY - height_char - 4), width_char, 4, Video_buffer_pointer, 800, 480);
				}
			}
			else
			{
				Draw_Rectangle( BackgroundColor, (StartX - ((i+1) * width_char)), StartY + 1				 , width_char, 4, Video_buffer_pointer, 800, 480);
				Draw_Rectangle( BackgroundColor, (StartX - ((i+1) * width_char)), (StartY - height_char - 4), width_char, 4, Video_buffer_pointer, 800, 480);
			}
		}

		Centred_DrawString_16(String, StandartLen, Coord_X, Coord_Y, Resolution_X, Resolution_Y, Video_buffer_pointer, Font_Color, Symbol_Color, Table, width_char, height_char);
}

void Centred_DrawNumber_16_32bit(int32_t Register, uint16_t Comma, uint16_t Numbers, int16_t Pointer_Razr, uint16_t Coord_X, uint16_t Coord_Y, uint16_t Resolution_X, uint16_t Resolution_Y, uint32_t Video_buffer_pointer, uint32_t Font_Color, uint32_t Symbol_Color, uint32_t Table[], uint16_t width_char, uint16_t height_char)
{

	  char 		String[10];

	  uint8_t 	RazrPointerArray[10];
	  for(int i=0;i<10;i++)	{RazrPointerArray[i] = 0;}

	  uint8_t	TemporaryLenPointer;

	  uint16_t Cycle_Pointer;
	  uint16_t Final_Len = 0;
	  uint16_t Number_Len;
	  uint8_t BelowZero = 0;




	  if(Register < 0)
	  {
		  BelowZero = 1;
		  Register = 0 - Register;
	  }

	  if(Comma>5){Comma=5;}
	  if(Comma<0){Comma=0;}

	  itoa(Register, String, 10);

	  Cycle_Pointer = 0;

	  while(String[Cycle_Pointer] > 0) //подсчёт длинны числа
	  {
		  Cycle_Pointer++;
	  }

	  TemporaryLenPointer = Numbers;
	  for(int i=TemporaryLenPointer;i;i--)
	  {
		  RazrPointerArray[i-1] = TemporaryLenPointer;
		  TemporaryLenPointer--;
	  }


	  if(Comma>0)
	  {
		  if(Comma>=Cycle_Pointer)
		  {
			  Final_Len = Comma + 2;

			  int8_t temp = Cycle_Pointer;
			  for(int i=(Final_Len-1);i>=0;i--)
			  {
				  if(temp)
				  {
					  temp--;
					  String[i] = String[temp];
				  }
				  else
				  {
					  String[i] = '0';
				  }
			  }
			  String[1] = ',';
			  Cycle_Pointer--;
		  }
		  else
		  {
			  Final_Len = Cycle_Pointer + 1;

			  for(int i=(Final_Len-1);i>=0;i--)
			  {
				  if( i > (Final_Len - Comma - 1))
				  {
					  String[i] = String[i-1];
				  }
			  }
			  String[Final_Len - Comma - 1] = ',';
		  }
	  }
	  else{Final_Len = Cycle_Pointer;}


	  if(BelowZero)
	  {
		  for(int i=Final_Len;i>=0;i--)
		  {
			  String[i] = String[i - 1];
		  }
		  String[0] = '-';
		  Final_Len++;
	  }

		uint8_t StandartLen = Numbers;
		uint8_t IschLen = Final_Len - 1;
		if(Final_Len < StandartLen)
		{
			for(int i=(StandartLen - 1); i>=0;i--)
			{
				if(IschLen)
				{
					String[i] = String[IschLen];
					IschLen--;
				}
				else
				{
					if(i==(StandartLen - Final_Len))
					{
						String[i] = String[0];
					}
					else
					{
						String[i] = ' ';
					}
				}
			}
		}

		uint16_t StartX;
		uint16_t StartY;

		StartY = Coord_Y + (height_char / 2);
		StartX = Coord_X + ((width_char * StandartLen) / 2);

		if(Pointer_Razr<0){Pointer_Razr = 0;}

		for(int i=0;i<Numbers;i++)
		{
			if((Pointer_Razr == RazrPointerArray[i]) & (Font_Color != BackgroundColor))
			{
				if(Pointer_Razr)
				{
					Draw_Rectangle( RasrPointerColor, (StartX - ((i+1) * width_char)), StartY + 1				 , width_char, 4, Video_buffer_pointer, 800, 480);
					Draw_Rectangle( RasrPointerColor, (StartX - ((i+1) * width_char)), (StartY - height_char - 4), width_char, 4, Video_buffer_pointer, 800, 480);
				}
			}
			else
			{
				Draw_Rectangle( BackgroundColor, (StartX - ((i+1) * width_char)), StartY + 1				 , width_char, 4, Video_buffer_pointer, 800, 480);
				Draw_Rectangle( BackgroundColor, (StartX - ((i+1) * width_char)), (StartY - height_char - 4), width_char, 4, Video_buffer_pointer, 800, 480);
			}
		}

		Centred_DrawString_16(String, StandartLen, Coord_X, Coord_Y, Resolution_X, Resolution_Y, Video_buffer_pointer, Font_Color, Symbol_Color, Table, width_char, height_char);
}


void Centred_DrawNumber_16_32bit_controled(uint32_t ValPointer, uint16_t Comma, uint16_t Numbers, int16_t Pointer_Razr, int32_t Max, int32_t Min, uint16_t Coord_X, uint16_t Coord_Y, uint16_t Resolution_X, uint16_t Resolution_Y, uint32_t Video_buffer_pointer, uint32_t Font_Color, uint32_t Symbol_Color, uint32_t Table[], uint16_t width_char, uint16_t height_char)
{


	  int32_t Register;
	  memcpy(&Register, ValPointer, 4);

	  if((Pointer_Razr > 0) & (Font_Color != BackgroundColor))
	  {
		  Control_DB.VauePointer    = ValPointer;
		  Control_DB.RazrPointerMAX = Numbers;
		  Control_DB.ValueMax		= Max;
		  Control_DB.ValueMin		= Min;

		  uint8_t BackWriteFlag = 0;
		  if(Register > Control_DB.ValueMax)
		  {
			  BackWriteFlag = 1;
			  Register = Control_DB.ValueMax;
		  }
		  if(Register < Control_DB.ValueMin)
		  {
			  BackWriteFlag = 1;
			  Register = Control_DB.ValueMin;
		  }
		  if(BackWriteFlag)
		  {
			  memcpy(ValPointer, &Register, 4);
		  }
	  }


	  char 		String[10];

	  uint8_t 	RazrPointerArray[10];
	  for(int i=0;i<10;i++)	{RazrPointerArray[i] = 0;}

	  uint8_t	TemporaryLenPointer;

	  uint16_t Cycle_Pointer;
	  uint16_t Final_Len = 0;
	  uint16_t Number_Len;
	  uint8_t BelowZero = 0;



	  if(Register < 0)
	  {
		  BelowZero = 1;
		  Register = 0 - Register;
	  }

	  if(Comma>5){Comma=5;}
	  if(Comma<0){Comma=0;}

	  itoa(Register, String, 10);

	  Cycle_Pointer = 0;

	  while(String[Cycle_Pointer] > 0) //подсчёт длинны числа
	  {
		  Cycle_Pointer++;
	  }

	  TemporaryLenPointer = Numbers;
	  for(int i=TemporaryLenPointer;i;i--)
	  {
		  RazrPointerArray[i-1] = TemporaryLenPointer;
		  TemporaryLenPointer--;
	  }


	  if(Comma>0)
	  {
		  if(Comma>=Cycle_Pointer)
		  {
			  Final_Len = Comma + 2;

			  int8_t temp = Cycle_Pointer;
			  for(int i=(Final_Len-1);i>=0;i--)
			  {
				  if(temp)
				  {
					  temp--;
					  String[i] = String[temp];
				  }
				  else
				  {
					  String[i] = '0';
				  }
			  }
			  String[1] = ',';
			  Cycle_Pointer--;
		  }
		  else
		  {
			  Final_Len = Cycle_Pointer + 1;

			  for(int i=(Final_Len-1);i>=0;i--)
			  {
				  if( i > (Final_Len - Comma - 1))
				  {
					  String[i] = String[i-1];
				  }
			  }
			  String[Final_Len - Comma - 1] = ',';
		  }
	  }
	  else{Final_Len = Cycle_Pointer;}


	  if(BelowZero)
	  {
		  for(int i=Final_Len;i>=0;i--)
		  {
			  String[i] = String[i - 1];
		  }
		  String[0] = '-';
		  Final_Len++;
	  }

		uint8_t StandartLen = Numbers;
		uint8_t IschLen = Final_Len - 1;
		if(Final_Len < StandartLen)
		{
			for(int i=(StandartLen - 1); i>=0;i--)
			{
				if(IschLen)
				{
					String[i] = String[IschLen];
					IschLen--;
				}
				else
				{
					if(i==(StandartLen - Final_Len))
					{
						String[i] = String[0];
					}
					else
					{
						String[i] = ' ';
					}
				}
			}
		}

		uint16_t StartX;
		uint16_t StartY;

		StartY = Coord_Y + (height_char / 2);
		StartX = Coord_X + ((width_char * StandartLen) / 2);

		if(Pointer_Razr<0){Pointer_Razr = 0;}

		for(int i=0;i<Numbers;i++)
		{
			if((Pointer_Razr == RazrPointerArray[i]) & (Font_Color != BackgroundColor))
			{
				if(Pointer_Razr)
				{
					Draw_Rectangle( RasrPointerColor, (StartX - ((i+1) * width_char)), StartY + 1				 , width_char, 4, Video_buffer_pointer, 800, 480);
					Draw_Rectangle( RasrPointerColor, (StartX - ((i+1) * width_char)), (StartY - height_char - 4), width_char, 4, Video_buffer_pointer, 800, 480);
				}
			}
			else
			{
				Draw_Rectangle( BackgroundColor, (StartX - ((i+1) * width_char)), StartY + 1				 , width_char, 4, Video_buffer_pointer, 800, 480);
				Draw_Rectangle( BackgroundColor, (StartX - ((i+1) * width_char)), (StartY - height_char - 4), width_char, 4, Video_buffer_pointer, 800, 480);
			}
		}

		Centred_DrawString_16(String, StandartLen, Coord_X, Coord_Y, Resolution_X, Resolution_Y, Video_buffer_pointer, Font_Color, Symbol_Color, Table, width_char, height_char);
}


void Short_Centred_DrawNumber_16(int16_t Register, uint16_t Comma, uint16_t Numbers, int16_t Pointer_Razr,
		uint16_t Coord_X, uint16_t Coord_Y,  uint32_t PageNumber)
{
	Centred_DrawNumber_16(Register, Comma, Numbers, Pointer_Razr, Coord_X, Coord_Y, 800, 480, PageNumber, BackgroundColor, BasicSymbolColor, Arial_11x18_Table, 11, 18);
}

void Short_Centred_DrawNumber_Big(int16_t Register, uint16_t Comma, uint16_t Numbers, int16_t Pointer_Razr,
		uint16_t Coord_X, uint16_t Coord_Y,  uint32_t PageNumber)
{
	Centred_DrawNumber_16(Register, Comma, Numbers, Pointer_Razr, Coord_X, Coord_Y, 800, 480, PageNumber, BackgroundColor, BasicSymbolColor, Arial_16x25_Table, 16, 25);
}

void Short_Color_Centred_DrawNumber_16x25(int16_t Register, uint16_t Comma, uint16_t Numbers, int16_t Pointer_Razr, uint16_t Coord_X, uint16_t Coord_Y, uint32_t Font_Color, uint32_t Symbol_Color, uint32_t PageNumber)
{
	if(Font_Color == BackgroundColor) {Pointer_Razr = 0;}
	Centred_DrawNumber_16(Register, Comma, Numbers, Pointer_Razr, Coord_X, Coord_Y, 800, 480, PageNumber, Font_Color, Symbol_Color, Arial_16x25_Table, 16, 25);
}

void DrawTime(int16_t second, int16_t minute, int16_t hour, uint16_t Coord_X, uint16_t Coord_Y, uint16_t Resolution_X, uint16_t Resolution_Y, uint32_t Video_buffer_pointer, uint32_t Font_Color, uint32_t Symbol_Color, uint32_t Table[], uint16_t width_char, uint16_t height_char)
{
	char String[10];
	char StringOut[10];

	uint8_t Cycle_Pointer;

	itoa(second, String, 10);

	Cycle_Pointer = 0;
	while(String[Cycle_Pointer] > 0) //подсчёт длинны числа
	{Cycle_Pointer++;}
	if(Cycle_Pointer<2){String[1] = String[0]; String[0] = '0';}

	StringOut[0] = String[0];
	StringOut[1] = String[1];
	StringOut[2] = ':';

	itoa(minute, String, 10);

	Cycle_Pointer = 0;
	while(String[Cycle_Pointer] > 0) //подсчёт длинны числа
	{Cycle_Pointer++;}
	if(Cycle_Pointer<2){String[1] = String[0]; String[0] = '0';}

	StringOut[3] = String[0];
	StringOut[4] = String[1];
	StringOut[5] = ':';

	itoa(hour, String, 10);

	Cycle_Pointer = 0;
	while(String[Cycle_Pointer] > 0) //подсчёт длинны числа
	{Cycle_Pointer++;}
	if(Cycle_Pointer<2){String[1] = String[0]; String[0] = '0';}

	StringOut[6] = String[0];
	StringOut[7] = String[1];

	Centred_DrawString_16(StringOut, 8, Coord_X, Coord_Y, Resolution_X, Resolution_Y, Video_buffer_pointer, Font_Color, Symbol_Color, Table, width_char, height_char);
}

void DrawData(int16_t day, int16_t month, int16_t year, uint16_t Coord_X, uint16_t Coord_Y, uint16_t Resolution_X, uint16_t Resolution_Y, uint32_t Video_buffer_pointer, uint32_t Font_Color, uint32_t Symbol_Color, uint32_t Table[], uint16_t width_char, uint16_t height_char)
{
	char String[10];
	char StringOut[10];

	uint8_t Cycle_Pointer;

	itoa(day, String, 10);

	Cycle_Pointer = 0;
	while(String[Cycle_Pointer] > 0) //подсчёт длинны числа
	{Cycle_Pointer++;}
	if(Cycle_Pointer<2){String[1] = String[0]; String[0] = '0';}

	StringOut[0] = String[0];
	StringOut[1] = String[1];
	StringOut[2] = '/';

	itoa(month, String, 10);

	Cycle_Pointer = 0;
	while(String[Cycle_Pointer] > 0) //подсчёт длинны числа
	{Cycle_Pointer++;}
	if(Cycle_Pointer<2){String[1] = String[0]; String[0] = '0';}

	StringOut[3] = String[0];
	StringOut[4] = String[1];
	StringOut[5] = '/';

	itoa(year, String, 10);

	Cycle_Pointer = 0;
	while(String[Cycle_Pointer] > 0) //подсчёт длинны числа
	{Cycle_Pointer++;}
	if(Cycle_Pointer<2){String[1] = String[0]; String[0] = '0';}

	StringOut[6] = String[0];
	StringOut[7] = String[1];
	StringOut[8] = String[2];
	StringOut[9] = String[3];

	Centred_DrawString_16(StringOut, 10, Coord_X, Coord_Y, Resolution_X, Resolution_Y, Video_buffer_pointer, Font_Color, Symbol_Color, Table, width_char, height_char);
}

void PrintHeaderOfScreen(char String[], uint16_t Len, uint32_t Pointer_TimeAndDate, uint32_t Font_Color, uint32_t Symbol_Color, uint32_t Page)
{
	struct {uint8_t minute, second, day, hour, year, month;} *TimeDataPack=Pointer_TimeAndDate;
	DrawTime(TimeDataPack[0].second, TimeDataPack[0].minute, TimeDataPack[0].hour, 50, 18, 800, 480, Page, Font_Color, Symbol_Color, Arial_11x18_Table, 11, 18);
	DrawData(TimeDataPack[0].day, TimeDataPack[0].month, (TimeDataPack[0].year + 2000), 735, 18, 800, 480, Page, Font_Color, Symbol_Color, Arial_11x18_Table, 11, 18);
	Centred_RU_DrawString_32(String, Len, 350, 13, 800, 480, Page, Font_Color, Symbol_Color, RU_18x27_Table, 18, 27);
	Draw_Rectangle(0xFFFFFF, 0, 34, 800, 2, Page, 800, 480);
	//Centred_RU_DrawString_32("-------------------------------------------", 43, 400, 40, 800, 480, VideoBuffer, Font_Color, Symbol_Color, RU_18x27_Table, 18, 27);
}





void NumberChange(uint32_t pointer, uint8_t razr, uint8_t len, uint8_t Up, uint8_t Down)
{
	struct {int32_t a;} *Number = pointer;

	int32_t temp2;
	int16_t Tpoint = razr - 1;

	int16_t Symbols[10];

	for(int i= (len-1);i>=0;i--)
	{
		temp2 = pow(10,i);
		if(Number->a >= temp2)
		{
			Symbols[i] = Number->a / temp2;
			Number->a = Number->a - (temp2 * Symbols[i]);
		}
		else
		{
			Symbols[i] = 0;
		}
	}	// Разделение числа на разряды



	if(Up)
	{
		Symbols[Tpoint]++;
		if(Symbols[Tpoint] > 9){Symbols[Tpoint] = 0;}
	}

	if(Down)
	{
		Symbols[Tpoint]--;
		if(Symbols[Tpoint] < 0){Symbols[Tpoint] = 9;}
	}



	Number->a = 0;
	for(int i=(len-1);i>=0;i--)
	{
		Number->a = Number->a + Symbols[i] * pow(10,i);
	}	// Сборка числа обратно
}
















