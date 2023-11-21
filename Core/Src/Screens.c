/*
 * Screens.c
 *
 *  Created on: 14 нояб. 2023 г.
 *      Author: SHIT_OF_SIEMENS
 */


#include "stm32f4xx.h"
#include "fonts.h"
#include "Font_Processor.h"
#include "data_types.h"


extern uint32_t Page[29];//набор страниц для отображения на экране

extern uint32_t Page_write_addr;
extern __IO uint32_t RedColor;
extern __IO uint32_t YellowColor;
extern __IO uint32_t GreenColor;
extern __IO uint32_t BackgroundColor;
extern __IO uint32_t GrayColor;

extern uint32_t BasicSymbolColor;
extern uint32_t SelectionColor;
extern uint32_t RasrPointerColor;

extern int16_t Val3;
extern int32_t motoclock;

extern LTDC_HandleTypeDef hltdc;

extern Settings Settings_DB;
extern InterfaceControlDB Control_DB;

extern uint8_t screen;
extern uint8_t screen_mirror;
extern uint8_t screen_event;

extern PassWords PassW_block;

uint32_t FonColor[20];







void Screens_init(void)
{

	for(int i = 0; i < 20;i++)
	{
		FonColor[i] = BackgroundColor;
	}


	// Экран 0 (черный экран)
	HAL_LTDC_SetAddress(&hltdc, Page[0], 0);
	Zaliv(0x000000, Page[0], 800, 480);

	// Экран_1
	Zaliv(BackgroundColor, Page[1], 800, 480);
	Draw_Rectangle(0x000000,   0, 220, 800,   3, Page[1], 800, 480); // первая горизонталь

	for(int i = 0; i < 3; i++)
	{

		uint16_t shift_X = i * 260 + 7;

		if(i < 2)
		{
			Draw_Rectangle(0x000000, 260 + shift_X,   0,   3, 220, Page[1], 800, 480);
		}

		switch(i)
		{
			case 0:
				Short_Left_Colored_RU_DrawString_32("1",  			      1,  70 + shift_X,  23, BackgroundColor, BasicSymbolColor, Page[1]);
			break;

			case 1:
				Short_Left_Colored_RU_DrawString_32("2",  			      1,  70 + shift_X,  23, BackgroundColor, BasicSymbolColor, Page[1]);
			break;

			case 2:
				Short_Left_Colored_RU_DrawString_32("3",  			      1,  70 + shift_X,  23, BackgroundColor, BasicSymbolColor, Page[1]);
			break;
		}

		Short_Left_Colored_RU_DrawString_32("АНН",  			  3,   5 + shift_X,  20, BackgroundColor, BasicSymbolColor, Page[1]);
		Short_Left_Colored_RU_DrawString_32("Д.напор", 	 	  	  7,   5 + shift_X,  50, BackgroundColor, BasicSymbolColor, Page[1]);
		Short_Left_Colored_RU_DrawString_32("МПа", 	 	  		  3, 200 + shift_X,  50, BackgroundColor, BasicSymbolColor, Page[1]);
		Short_Left_Colored_RU_DrawString_32("Д.масла", 	 		  7,   5 + shift_X,  80, BackgroundColor, BasicSymbolColor, Page[1]);
		Short_Left_Colored_RU_DrawString_32("МПа", 	 	  		  3, 200 + shift_X,  80, BackgroundColor, BasicSymbolColor, Page[1]);
		Short_Left_Colored_RU_DrawString_32("Т.масла", 	 	  	  7,   5 + shift_X, 110, BackgroundColor, BasicSymbolColor, Page[1]);
		Short_Left_Colored_RU_DrawString_32("*С", 	 	  		  2, 200 + shift_X, 110, BackgroundColor, BasicSymbolColor, Page[1]);
		Short_Left_Colored_RU_DrawString_32("МотЧасы", 	 	  	  7,   5 + shift_X, 200, BackgroundColor, BasicSymbolColor, Page[1]);

		Short_Left_Colored_RU_DrawString_32("   Вкл   ", 		  9,  95 + shift_X,  20,      GreenColor, BasicSymbolColor, Page[1]);
		Short_Left_Colored_RU_DrawString_32("  РАЗГРУЗКА   ", 	 14,   5 + shift_X, 140, 		RedColor, BasicSymbolColor, Page[1]);
		Short_Left_Colored_RU_DrawString_32("тепл. защита  ", 	 14,   5 + shift_X, 170, 		RedColor, BasicSymbolColor, Page[1]);


	}

	Draw_Rectangle(0x000000, 665, 220, 3, 360, Page[1], 800, 480);
	Short_Left_Colored_RU_DrawString_32("УСТАВКА", 	 	  	 			 7, 670, 240, BackgroundColor, BasicSymbolColor, Page[1]);
	Short_Left_Colored_RU_DrawString_32("МПа", 	 	  	     			 3, 740, 267, BackgroundColor, BasicSymbolColor, Page[1]);
	Short_Left_Colored_RU_DrawString_32("Ур.Бак ", 	 	  	 			 7, 670, 300, BackgroundColor, BasicSymbolColor, Page[1]);
	Short_Left_Colored_RU_DrawString_32("мм", 	 	  	     			 2, 740, 327, BackgroundColor, BasicSymbolColor, Page[1]);
	Short_Left_Colored_RU_DrawString_32("Тем.Бак", 	 	  	 			 7, 670, 360, BackgroundColor, BasicSymbolColor, Page[1]);
	Short_Left_Colored_RU_DrawString_32("*С", 	 	  	     			 2, 740, 387, BackgroundColor, BasicSymbolColor, Page[1]);
	Short_Left_Colored_RU_DrawString_32("УЗЕЛ ФИЛЬТРОВ", 	 			13,  13, 240,       GrayColor, BasicSymbolColor, Page[1]);
	Short_Left_Colored_RU_DrawString_32("Д.в магистр:",		 			12, 300, 240, BackgroundColor, BasicSymbolColor, Page[1]);
	Short_Left_Colored_RU_DrawString_32("МПа", 	 	  		 			 3, 580, 240, BackgroundColor, BasicSymbolColor, Page[1]);
	Short_Left_Colored_RU_DrawString_32("Д.перед сл. напорн фильтром:", 28,  13, 270, BackgroundColor, BasicSymbolColor, Page[1]);
	Short_Left_Colored_RU_DrawString_32("МПа", 	 	  		 			 3, 580, 270, BackgroundColor, BasicSymbolColor, Page[1]);
	Short_Left_Colored_RU_DrawString_32("Д.перед сл.ф.:",			 	14,  13, 300, BackgroundColor, BasicSymbolColor, Page[1]);
	Short_Left_Colored_RU_DrawString_32("МПа", 							 3, 360, 300, BackgroundColor, BasicSymbolColor, Page[1]);
	Short_Left_Colored_RU_DrawString_32("за", 							 2, 450, 300, BackgroundColor, BasicSymbolColor, Page[1]);
	Short_Left_Colored_RU_DrawString_32("МПа", 							 3, 580, 300, BackgroundColor, BasicSymbolColor, Page[1]);
	Short_Left_Colored_RU_DrawString_32("Расход. сл.ф.:", 				14,  13, 330, BackgroundColor, BasicSymbolColor, Page[1]);
	Short_Left_Colored_RU_DrawString_32("л/м", 						 	 3, 360, 330, BackgroundColor, BasicSymbolColor, Page[1]);
	Short_Left_Colored_RU_DrawString_32("эмул", 					 	 4, 420, 330,       GrayColor, BasicSymbolColor, Page[1]);
	Short_Left_Colored_RU_DrawString_32("л/м", 						 	 3, 580, 330, BackgroundColor, BasicSymbolColor, Page[1]);
	Short_Left_Colored_RU_DrawString_32("Прокач  объем:", 				14,  13, 360, BackgroundColor, BasicSymbolColor, Page[1]);
	Short_Left_Colored_RU_DrawString_32("(м3)", 					 	 4, 420, 360,       GrayColor, BasicSymbolColor, Page[1]);

	// Экран_2 (устройство эмульсии)
	Zaliv(BackgroundColor, Page[2], 800, 480);
	Short_Left_Colored_RU_DrawString_32("Устройство приготовления эмульсии", 	33,  10,  30,       GrayColor, BasicSymbolColor, Page[2]);

	Short_Left_Colored_RU_DrawString_32("Расход концентрата:", 	 				19,  10, 180, BackgroundColor, BasicSymbolColor, Page[2]);
	Short_Left_Colored_RU_DrawString_32("Рефрактометр поточный", 	 			21,  10, 210, BackgroundColor, BasicSymbolColor, Page[2]);
	Short_Left_Colored_RU_DrawString_32("Датчик проводимости", 	 				19,  10, 240, BackgroundColor, BasicSymbolColor, Page[2]);
	Short_Left_Colored_RU_DrawString_32("Датчик рН          ", 	 				19,  10, 270, BackgroundColor, BasicSymbolColor, Page[2]);
	Short_Left_Colored_RU_DrawString_32("Давление перед фильтрами воды", 		29,  10, 300, BackgroundColor, BasicSymbolColor, Page[2]);
	Short_Left_Colored_RU_DrawString_32("Давление после фильтров  воды", 		29,  10, 330, BackgroundColor, BasicSymbolColor, Page[2]);
	Short_Left_Colored_RU_DrawString_32("Расходомер воды", 						15,  10, 360, BackgroundColor, BasicSymbolColor, Page[2]);
	Short_Left_Colored_RU_DrawString_32("л/м", 						 	 		 3, 520, 180, BackgroundColor, BasicSymbolColor, Page[2]);
	Short_Left_Colored_RU_DrawString_32("м3", 						 	 		 2, 720, 180, BackgroundColor, BasicSymbolColor, Page[2]);
	Short_Left_Colored_RU_DrawString_32("л/м", 						 	 		 3, 520, 360, BackgroundColor, BasicSymbolColor, Page[2]);
	Short_Left_Colored_RU_DrawString_32("м3", 						 	 		 2, 720, 360, BackgroundColor, BasicSymbolColor, Page[2]);
	Short_Left_Colored_RU_DrawString_32("МПа", 	 	  		 			 		 3, 720, 300, BackgroundColor, BasicSymbolColor, Page[2]);
	Short_Left_Colored_RU_DrawString_32("МПа", 	 	  		 			 		 3, 720, 330, BackgroundColor, BasicSymbolColor, Page[2]);

	Short_Left_Colored_RU_DrawString_32("МтЧас:", 						 		 6, 560,  90, BackgroundColor, BasicSymbolColor, Page[2]);
	Short_Left_Colored_RU_DrawString_32("МтЧас:", 						 		 6, 560, 120, BackgroundColor, BasicSymbolColor, Page[2]);
	Short_Left_Colored_RU_DrawString_32("МтЧас:", 						 		 6, 560, 150, BackgroundColor, BasicSymbolColor, Page[2]);

	// Экран_3 (пароль)
	Zaliv(BackgroundColor, Page[3], 800, 480);
	if(Control_DB.RazrPointer > 4){Control_DB.RazrPointer = 4;}


	// Экран 4
	Zaliv(BackgroundColor, Page[4], 800, 480);
	Short_Centred_RU_DrawString_32("Настройки станции насосной", 26, 400, 15, BackgroundColor, BasicSymbolColor, Page[4]);
	Draw_Rectangle(0x000000,   0, 30, 800,   3, Page[4], 800, 480);




	// Экран 20 (Авария)
	Zaliv(RedColor, Page[20], 800, 480);
	Short_Centred_RU_DrawString_32("Активные аварийные сообщения", 28, 400, 15, RedColor, BasicSymbolColor, Page[20]);
	Draw_Rectangle(0x000000,   0, 30, 800,   3, Page[20], 800, 480);


	// Экран_21 (сетевуха)
	Zaliv(BackgroundColor, Page[21], 800, 480);
	Short_Centred_RU_DrawString_32("настройки пульта", 16, 400, 15, BackgroundColor, BasicSymbolColor, Page[21]);
	Draw_Rectangle(0x000000,   0, 30, 800,   3, Page[21], 800, 480);


}

int16_t pass = 0;
int16_t pass_false = 0;



void Set_Screen(uint8_t screen)
{

	for(int i = 0; i < 20;i++)
	{
		if(i == Control_DB.MenuPointer) {FonColor[i] = SelectionColor;}
		else {FonColor[i] = BackgroundColor;}
	}

	switch(screen)
	{

		case 1:

			for(int i = 0; i < 3; i++)
			{
				uint16_t shift_X = i * 260 + 7;

				Short_Left_Colored_RU_DrawString_32("   Вкл   ", 		  9,  95 + shift_X,  20,      GreenColor, BasicSymbolColor, Page[1]);
				Short_Centred_DrawNumber_16(Val3, 1, 4, 0, 					 170 + shift_X,  52, 									Page[1]);
				Short_Centred_DrawNumber_16(Val3, 2, 4, 0, 					 170 + shift_X,  82, 									Page[1]);
				Short_Centred_DrawNumber_16(Val3, 0, 4, 0, 					 170 + shift_X, 112, 									Page[1]);
				Short_Left_Colored_RU_DrawString_32("  РАЗГРУЗКА   ", 	 14,   5 + shift_X, 140, 		RedColor, BasicSymbolColor, Page[1]);
				Short_Left_Colored_RU_DrawString_32("тепл. защита  ", 	 14,   5 + shift_X, 170, 		RedColor, BasicSymbolColor, Page[1]);
				Centred_DrawNumber_16_32bit(motoclock, 0, 10, 0, 			 200 + shift_X, 205, 800,480,Page[1],  BackgroundColor, BasicSymbolColor, Arial_11x18_Table, 11, 18);
			}

			Centred_DrawNumber_16(Val3, 0, 3, 0, 700, 270, 800, 480, Page[1], BackgroundColor, BasicSymbolColor, Arial_16x25_Table, 16, 25); // Уставка
			Centred_DrawNumber_16(Val3, 0, 3, 0, 700, 330, 800, 480, Page[1], BackgroundColor, BasicSymbolColor, Arial_16x25_Table, 16, 25); // уровень бак
			Centred_DrawNumber_16(Val3, 0, 3, 0, 700, 390, 800, 480, Page[1], BackgroundColor, BasicSymbolColor, Arial_16x25_Table, 16, 25); // температура бак

			Short_Centred_DrawNumber_16(Val3, 1, 4, 0, 					 			550, 242, 									 Page[1]); // давл в магистрали
			Short_Centred_DrawNumber_16(Val3, 1, 4, 0, 					 			550, 272, 									 Page[1]); // перед сливным напорным фильтром
			Short_Centred_DrawNumber_16(Val3, 1, 4, 0, 					 			330, 302, 									 Page[1]); // перед сливным фильтром
			Short_Centred_DrawNumber_16(Val3, 1, 4, 0, 					 			550, 302, 									 Page[1]); //    за сливным фильтром
			Short_Centred_DrawNumber_16(Val3, 1, 6, 0, 					 			310, 334, 									 Page[1]); // расход на сливном фильтре
			Short_Centred_DrawNumber_16(Val3, 1, 6, 0, 					 	 		530, 334, 									 Page[1]); // расход эмульсии
			Centred_DrawNumber_16_32bit(motoclock, 0, 10, 0, 			 			340, 364, 800,480,Page[1],  BackgroundColor, BasicSymbolColor, Arial_11x18_Table, 11, 18); // прокачаный объём на сливном фильтре
			Centred_DrawNumber_16_32bit(motoclock, 0, 10, 0, 			 			560, 364, 800,480,Page[1],  BackgroundColor, BasicSymbolColor, Arial_11x18_Table, 11, 18); // прокачаный объём эмульсии
			Short_Left_Colored_RU_DrawString_32("кл.промыв.1", 	 11,   				 90, 400, 		 RedColor, BasicSymbolColor, Page[1]);
			Short_Left_Colored_RU_DrawString_32("кл.промыв.2", 	 11,   				340, 400, 		 RedColor, BasicSymbolColor, Page[1]);

			Control_DB.RazrPointer 	= 0;

		break;

		case 2:

			Centred_DrawNumber_16_32bit(motoclock, 0, 10, 0, 			 					730,  94, 800,480,Page[2],  BackgroundColor, BasicSymbolColor, Arial_11x18_Table, 11, 18);
			Centred_DrawNumber_16_32bit(motoclock, 0, 10, 0, 			 					730, 124, 800,480,Page[2],  BackgroundColor, BasicSymbolColor, Arial_11x18_Table, 11, 18);
			Centred_DrawNumber_16_32bit(motoclock, 0, 10, 0, 			 					730, 154, 800,480,Page[2],  BackgroundColor, BasicSymbolColor, Arial_11x18_Table, 11, 18);

			Short_Left_Colored_RU_DrawString_32("Насос циркуляционный ", 				21,  10,  90,        RedColor, BasicSymbolColor, Page[2]);
			Short_Left_Colored_RU_DrawString_32("Насос концентрата    ", 				21,  10, 120,        RedColor, BasicSymbolColor, Page[2]);
			Short_Left_Colored_RU_DrawString_32("Насос закач.концентр.", 				21,  10, 150,        RedColor, BasicSymbolColor, Page[2]);
			Short_Left_Colored_RU_DrawString_32("тепл.защ", 							 8, 400,  90,        RedColor, BasicSymbolColor, Page[2]);
			Short_Left_Colored_RU_DrawString_32("тепл.защ", 							 8, 400, 120,        RedColor, BasicSymbolColor, Page[2]);
			Short_Left_Colored_RU_DrawString_32("тепл.защ", 							 8, 400, 150,        RedColor, BasicSymbolColor, Page[2]);

			Short_Centred_DrawNumber_16(Val3, 1, 6, 0, 					 					470, 184, 									 Page[2]);
			Centred_DrawNumber_16_32bit(motoclock, 0, 10, 0, 			 					650, 184, 800,480,Page[2],  BackgroundColor, BasicSymbolColor, Arial_11x18_Table, 11, 18);

			Short_Centred_DrawNumber_16(Val3, 1, 6, 0, 					 					470, 364, 									 Page[2]);
			Centred_DrawNumber_16_32bit(motoclock, 0, 10, 0, 			 					650, 364, 800,480,Page[2],  BackgroundColor, BasicSymbolColor, Arial_11x18_Table, 11, 18);

			Short_Centred_DrawNumber_16(Val3, 1, 6, 0, 					 					673, 304, 									 Page[2]);
			Short_Centred_DrawNumber_16(Val3, 1, 6, 0, 					 					673, 334, 									 Page[2]);

			Short_Left_Colored_RU_DrawString_32("кл.фил.1", 							 8,  20, 390,        RedColor, BasicSymbolColor, Page[2]);
			Short_Left_Colored_RU_DrawString_32("кл.фил.2", 							 8, 170, 390,        RedColor, BasicSymbolColor, Page[2]);
			Short_Left_Colored_RU_DrawString_32("кл.фил.3", 							 8, 320, 390,        RedColor, BasicSymbolColor, Page[2]);
			Short_Left_Colored_RU_DrawString_32("кл.воды ", 							 8, 470, 390,        RedColor, BasicSymbolColor, Page[2]);
			Short_Left_Colored_RU_DrawString_32("кл.конц ", 							 8, 620, 390,        RedColor, BasicSymbolColor, Page[2]);

			Control_DB.RazrPointer 	= 0;

		break;

		case 3:

			Short_Centred_RU_DrawString_32("Введите пароль", 14, 	  		400, 190, BackgroundColor, BasicSymbolColor, Page[3]);
			Centred_DrawNumber_16_32bit_controled(&PassW_block.PassWord, 		  		  0,   4, Control_DB.RazrPointer, 9999,      0, 400,  240, 800,480, Page[3], GrayColor, BasicSymbolColor, Arial_11x18_Table, 11, 18);
			if(PassW_block.PassFalseTimer)
			{
				Short_Centred_RU_DrawString_32("Пароль неверный", 15, 		400, 290,        RedColor, BasicSymbolColor, Page[3]);
			}
			else
			{
				Short_Centred_RU_DrawString_32("               ", 15, 		400, 290, BackgroundColor, BasicSymbolColor, Page[3]);
			}

			Control_DB.RazrPointerMAX = 4;

		break;

		case 4:
			Short_Left_Colored_RU_DrawString_32("Режим работы    ", 16,	30,  50, FonColor[0], BasicSymbolColor, Page[4]);

			if(Settings_DB.pump_mode == 1)
			{
				Short_Left_Colored_RU_DrawString_32("Авто", 4,600,  50, BackgroundColor, BasicSymbolColor, Page[4]);
				Centred_DrawNumber_16_32bit_controled(&Settings_DB.pump_mode,0, 1, Control_DB.RazrPointer, 1,   0, 470, 50, 800,480, Page[4], FonColor[0], BasicSymbolColor, Arial_11x18_Table, 11, 18);
				Draw_Rectangle(BackgroundColor, 30,   70,  750, 600, Page[4], 800, 480);
			}
			else
			{
				Centred_DrawNumber_16_32bit_controled(&Settings_DB.pump_mode,0, 1, Control_DB.RazrPointer, 1,   0, 470, 50, 800,480, Page[4], FonColor[0], BasicSymbolColor, Arial_11x18_Table, 11, 18);
				Short_Left_Colored_RU_DrawString_32("Ручн", 4,600,  50, BackgroundColor, BasicSymbolColor, Page[4]);
				Short_Left_Colored_RU_DrawString_32("Конц эмульсии    ", 17,30,  80, FonColor[1], BasicSymbolColor, Page[4]);
				Short_Left_Colored_RU_DrawString_32("Настр промыв фильт", 18, 30, 110, FonColor[2], BasicSymbolColor, Page[4]);
				Short_Left_Colored_RU_DrawString_32("Время промыв", 	12,	30, 140, FonColor[3], BasicSymbolColor, Page[4]);
				Short_Left_Colored_RU_DrawString_32("Настр мин уровн конц", 20, 30, 170, FonColor[4], BasicSymbolColor, Page[4]);
				Short_Left_Colored_RU_DrawString_32("Настр уровн авт разгр", 21, 30, 200, FonColor[5], BasicSymbolColor, Page[4]);
				Short_Left_Colored_RU_DrawString_32("Сброс настр по умол", 19, 	30, 230, FonColor[6], BasicSymbolColor, Page[4]);
				Centred_DrawNumber_16_32bit_controled(1,0, 1, Control_DB.RazrPointer, 1,   0, 470, 50, 800,480, Page[4], GrayColor, BasicSymbolColor, Arial_11x18_Table, 11, 18);
				Centred_DrawNumber_16_32bit_controled(1,0, 1, Control_DB.RazrPointer, 1,   0, 470, 170, 800,480, Page[4], GrayColor, BasicSymbolColor, Arial_11x18_Table, 11, 18);
				Centred_DrawNumber_16_32bit_controled(1,0, 1, Control_DB.RazrPointer, 1,   0, 470, 200, 800,480, Page[4], GrayColor, BasicSymbolColor, Arial_11x18_Table, 11, 18);
				Centred_DrawNumber_16_32bit_controled(1,0, 1, Control_DB.RazrPointer, 1,   0, 470, 80, 800,480, Page[4], GrayColor, BasicSymbolColor, Arial_11x18_Table, 11, 18);
//				Short_Left_Colored_RU_DrawString_32("По переп дав", 12,585,  110, BackgroundColor, BasicSymbolColor, Page[4]);
				Short_Left_Colored_RU_DrawString_32("По врем", 7,600,  90, BackgroundColor, BasicSymbolColor, Page[4]);
//				Short_Left_Colored_RU_DrawString_32("механ", 5,600,  200, BackgroundColor, BasicSymbolColor, Page[4]);
				Short_Left_Colored_RU_DrawString_32("моль/л", 6,600,  170, BackgroundColor, BasicSymbolColor, Page[4]);
				Short_Left_Colored_RU_DrawString_32("эл.магн", 7,600,  180, BackgroundColor, BasicSymbolColor, Page[4]);
			}
			//
//			Centred_DrawNumber_16_32bit_controled(1,0, 1, Control_DB.RazrPointer, 1,   0, 470, 50, 800,480, Page[4], GrayColor, BasicSymbolColor, Arial_11x18_Table, 11, 18);
//			Centred_DrawNumber_16_32bit_controled(1,0, 1, Control_DB.RazrPointer, 1,   0, 470, 170, 800,480, Page[4], GrayColor, BasicSymbolColor, Arial_11x18_Table, 11, 18);
//			Centred_DrawNumber_16_32bit_controled(1,0, 1, Control_DB.RazrPointer, 1,   0, 470, 200, 800,480, Page[4], GrayColor, BasicSymbolColor, Arial_11x18_Table, 11, 18);
//			Centred_DrawNumber_16_32bit_controled(1,0, 1, Control_DB.RazrPointer, 1,   0, 470, 80, 800,480, Page[4], GrayColor, BasicSymbolColor, Arial_11x18_Table, 11, 18);
//			Short_Left_Colored_RU_DrawString_32("По переп дав", 12,585,  110, BackgroundColor, BasicSymbolColor, Page[4]);
////			Short_Left_Colored_RU_DrawString_32("По врем", 7,600,  90, BackgroundColor, BasicSymbolColor, Page[4]);
//			Short_Left_Colored_RU_DrawString_32("механ", 5,600,  200, BackgroundColor, BasicSymbolColor, Page[4]);
//			Short_Left_Colored_RU_DrawString_32("моль/л", 6,600,  170, BackgroundColor, BasicSymbolColor, Page[4]);
////			Short_Left_Colored_RU_DrawString_32("эл.магн", 7,600,  180, BackgroundColor, BasicSymbolColor, Page[4]);
			Control_DB.MenuPointerMAX = 6;

		break;

		case 21:

			Short_Left_Colored_RU_DrawString_32("Адрес            ", 17,	100,  70, FonColor[0], BasicSymbolColor, Page[21]);
			Short_Left_Colored_RU_DrawString_32("Скорость         ", 17, 	100, 110, FonColor[1], BasicSymbolColor, Page[21]);
			Short_Left_Colored_RU_DrawString_32("Стоп биты        ", 17, 	100, 150, FonColor[2], BasicSymbolColor, Page[21]);
			Short_Left_Colored_RU_DrawString_32("Яркость дисплея  ", 17, 	100, 190, FonColor[3], BasicSymbolColor, Page[21]);
			Short_Left_Colored_RU_DrawString_32("Яркость клав-ры  ", 17, 	100, 230, FonColor[4], BasicSymbolColor, Page[21]);
			Short_Left_Colored_RU_DrawString_32("Сохранить во флеш", 17, 	100, 270, FonColor[5], BasicSymbolColor, Page[21]);

			Centred_DrawNumber_16_32bit_controled(&Settings_DB.RS485_ADDR, 			0, 3, Control_DB.RazrPointer,    255,      0, 470,  70, 800,480, Page[21], FonColor[0], BasicSymbolColor, Arial_11x18_Table, 11, 18);
			Centred_DrawNumber_16_32bit_controled(&Settings_DB.RS485_Speed, 		0, 6, Control_DB.RazrPointer, 115200,   9600, 470, 110, 800,480, Page[21], FonColor[1], BasicSymbolColor, Arial_11x18_Table, 11, 18);
			Centred_DrawNumber_16_32bit_controled(&Settings_DB.RS485_Stops, 		0, 1, Control_DB.RazrPointer,      2,      1, 470, 150, 800,480, Page[21], FonColor[2], BasicSymbolColor, Arial_11x18_Table, 11, 18);
			Centred_DrawNumber_16_32bit_controled(&Settings_DB.brightness_disp, 	0, 3, Control_DB.RazrPointer,    100,     10, 470, 190, 800,480, Page[21], FonColor[3], BasicSymbolColor, Arial_11x18_Table, 11, 18);
			Centred_DrawNumber_16_32bit_controled(&Settings_DB.brightness_clav, 	0, 3, Control_DB.RazrPointer,    100,     10, 470, 230, 800,480, Page[21], FonColor[4], BasicSymbolColor, Arial_11x18_Table, 11, 18);

			Control_DB.MenuPointerMAX = 5;

			Short_Left_Colored_RU_DrawString_32("бод/с", 5,					585,  110, BackgroundColor, BasicSymbolColor, Page[21]);

		break;

	}

	if(screen_event)
	{

		Control_DB.RazrPointer 	= 0;
		PassW_block.PassWord   	= 0;
		screen_event 			= 0;



	}

	HAL_LTDC_SetAddress(&hltdc, Page[screen], 0);
}




