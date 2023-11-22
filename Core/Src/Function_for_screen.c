/*
 * Function_for_screen.c
 *
 *  Created on: Nov 22, 2023
 *      Author: Admin
 */
#include "Function_for_screen.h"
#include "Font_Processor.h"

extern uint32_t BasicSymbolColor;
extern __IO uint32_t BackgroundColor;
extern uint32_t Page[29];//набор страниц для отображения на экране




void update_station_pump(int32_t value,int32_t pix)

{
	switch(value)
	{
	case 1:
		Short_Left_Colored_RU_DrawString_32("РАЗРЕШЕНО", 9,585,  pix, BackgroundColor, BasicSymbolColor, Page[6]);
		break;
	case 2:
		Short_Left_Colored_RU_DrawString_32("ЗАПРЕЩЕНО", 9,585,  pix, BackgroundColor, BasicSymbolColor, Page[6]);
		break;
	case 3:
		Short_Left_Colored_RU_DrawString_32("РЕМОНТ   ", 9,585,  pix, BackgroundColor, BasicSymbolColor, Page[6]);
		break;
	}
}
void setting_auto_unload(int32_t value)
{
	if(value)
	{
		Short_Left_Colored_RU_DrawString_32("механ  ", 7,600,  350, BackgroundColor, BasicSymbolColor, Page[6]);
	}
	else
	{
		Short_Left_Colored_RU_DrawString_32("эл.магн", 7,600,  350, BackgroundColor, BasicSymbolColor, Page[6]);
	}
}
void update_mode_flushing(int32_t value,uint32_t page)
{
	switch (value)
	{
	case 1:
		Short_Left_Colored_RU_DrawString_32(" ПО ВРЕМЕНИ    ", 15,550,  50, BackgroundColor, BasicSymbolColor, page);
		break;
	case 2:
		Short_Left_Colored_RU_DrawString_32("ПО ПЕРЕП ДАВ   ", 15,550,  50, BackgroundColor, BasicSymbolColor, page);

		break;

	case 3:
		Short_Left_Colored_RU_DrawString_32("ПО ПЕР ДАВ и ВР", 15,550,  50, BackgroundColor, BasicSymbolColor, page);
		break;
	case 4:
		Short_Left_Colored_RU_DrawString_32("В РУЧНУЮ       ", 15,550,  50, BackgroundColor, BasicSymbolColor, page);
		break;
	}
}
