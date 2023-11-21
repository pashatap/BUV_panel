#include "stm32f4xx.h"

extern uint32_t VideoBuffer;
extern __IO uint32_t BasicFon;
extern __IO uint8_t  temporary_line_buffer;

void Zaliv(uint32_t Color, uint32_t Bufer_Pointer, uint16_t Resolution_X, uint16_t Resolution_Y)
{
	struct {uint8_t b,g,r;} *TempBuf=Bufer_Pointer;
	for(int i=0;i<(Resolution_X*Resolution_Y);i++){memcpy(&TempBuf[i].b, &Color, 3);} //Заливка всего экрана
} // Заливка экрана

void ZalivARGB(uint32_t Color, uint32_t Bufer_Pointer, uint16_t Resolution_X, uint16_t Resolution_Y)
{
	struct {uint8_t a,b,g,r;} *TempBuf=Bufer_Pointer;
	for(int i=0;i<(Resolution_X*Resolution_Y);i++){memcpy(&TempBuf[i].b, &Color, 4);} //Заливка всего экрана
} // Заливка экрана

void Draw_Rectangle(uint32_t Color, uint16_t Start_X, uint16_t Start_Y, uint16_t Size_X, uint16_t Size_Y, uint32_t Bufer_Pointer, uint16_t Resolution_X, uint16_t Resolution_Y)
{
	struct {uint8_t b,g,r;} *TempBuf=Bufer_Pointer;
	for(int i=Start_Y;i<(Start_Y + Size_Y);i++)
	{
		for(int j=Start_X;j<(Start_X + Size_X);j++)
		{
			memcpy(&TempBuf[(i * Resolution_X) + j].b, &Color, 3);
		}
	}
}

void Picture(void)
{
	while(!(BasicFon == 0x436594))
	{

		QspiReadData(0, 10, VideoBuffer);
		memcpy(&BasicFon, VideoBuffer, 3);
		if(BasicFon == 0xFFFFFF)
		{
		  QspiReadData(0, 800 * 480 * 3, VideoBuffer);
		  memcpy(&BasicFon, VideoBuffer, 3);
		}

	}
}
