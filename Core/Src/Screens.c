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
#include"Function_for_screen.h"


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

//extern int16_t Val3;
//extern int32_t motoclock;

extern LTDC_HandleTypeDef hltdc;

extern Settings_panel Settings_DB;
extern InterfaceControlDB Control_DB;

extern uint8_t screen;
extern uint8_t screen_mirror;
extern uint8_t screen_event;

extern PassWords PassW_block;
extern Algorithm_variables ALG_DB;

extern Settings_Station BUV_settings_global;

extern BUV_realtime_vars BUV_RT_VALS;

extern Settings_Station	BUV_settings;

uint32_t FonColor[20];



int16_t pass = 0;
int16_t pass_false = 0;


uint8_t engine_state;

uint8_t unload;
uint8_t bimetal;

int16_t Press_napor;
int16_t Press_maslo;
int16_t Temp_maslo;
int32_t motoclock;

background_zaliv Work_regim_zaliv_1 = {0};



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

	// Экран 3
	Zaliv(BackgroundColor, Page[3], 800, 480);
	Short_Centred_RU_DrawString_32("ОКНО ДАННЫЕ", 11, 400, 15, BackgroundColor, BasicSymbolColor, Page[3]);
	Draw_Rectangle(0x000000,     0, 30, 800,   3, Page[3], 800, 480);
	Draw_Rectangle(0x000000,   500, 70,   3, 410, Page[3], 800, 480);


	// Экран 4
	Zaliv(BackgroundColor, Page[4], 800, 480);
	Short_Centred_RU_DrawString_32("ОКНО РУЧНОГО УПРАВЛЕНИЯ", 23, 400, 15, BackgroundColor, BasicSymbolColor, Page[4]);
	Draw_Rectangle(0x000000,   0, 30, 800,   3, Page[4], 800, 480);

	// Экран_5 (пароль)
	Zaliv(BackgroundColor, Page[5], 800, 480);
	if(Control_DB.RazrPointer > 4){Control_DB.RazrPointer = 4;}


	// Экран 6
	Zaliv(BackgroundColor, Page[6], 800, 480);
	Short_Centred_RU_DrawString_32("Настройки станции насосной", 26, 400, 15, BackgroundColor, BasicSymbolColor, Page[6]);
	Draw_Rectangle(0x000000,   0, 30, 800,   3, Page[6], 800, 480);


	// Экран 7
	Zaliv(BackgroundColor, Page[7], 800, 480);
	Short_Centred_RU_DrawString_32("Заводские параметры", 19, 400, 15, BackgroundColor, BasicSymbolColor, Page[7]);
	Draw_Rectangle(0x000000,   0, 30, 800,   3, Page[7], 800, 480);


	//Экран 8
	Zaliv(BackgroundColor, Page[8], 800, 480);
	Short_Centred_RU_DrawString_32("Настройки промывки напорного фильтра", 36, 400, 15, BackgroundColor, BasicSymbolColor, Page[8]);
	Draw_Rectangle(0x000000,   0, 30, 800,   3, Page[8], 800, 480);
	//Экран 9
	Zaliv(BackgroundColor, Page[9], 800, 480);
	Short_Centred_RU_DrawString_32("Настройки промывки фильтра воды", 31, 400, 15, BackgroundColor, BasicSymbolColor, Page[9]);
	Draw_Rectangle(0x000000,   0, 30, 800,   3, Page[9], 800, 480);

	//Экран 14
	Zaliv(BackgroundColor, Page[14], 800, 480);
	Short_Centred_RU_DrawString_32("Настройки станции насосной", 26, 400, 15, BackgroundColor, BasicSymbolColor, Page[14]);
	Draw_Rectangle(0x000000,   0, 30, 800,   3, Page[14], 800, 480);

	// Экран 20 (Авария)
	Zaliv(RedColor, Page[20], 800, 480);
	Short_Centred_RU_DrawString_32("Активные аварийные сообщения", 28, 400, 15, RedColor, BasicSymbolColor, Page[20]);
	Draw_Rectangle(0x000000,   0, 30, 800,   3, Page[20], 800, 480);


	// Экран_21 (сетевуха)
	Zaliv(BackgroundColor, Page[21], 800, 480);
	Short_Centred_RU_DrawString_32("настройки пульта", 16, 400, 15, BackgroundColor, BasicSymbolColor, Page[21]);
	Draw_Rectangle(0x000000,   0, 30, 800,   3, Page[21], 800, 480);


}




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
				switch(i)
				{
					case 0:
						engine_state = BUV_RT_VALS.ANN_1.Pump.State;
						unload		 = BUV_RT_VALS.ANN_1.Unload;
						bimetal      = BUV_RT_VALS.ANN_1.Pump.Bimetal;
						Press_napor  = BUV_RT_VALS.ANN_1.Out_Pressure;
						Press_maslo  = BUV_RT_VALS.ANN_1.Oil_Pressure;
						Temp_maslo   = BUV_RT_VALS.ANN_1.Oil_Temperature;
						motoclock    = BUV_RT_VALS.ANN_1.Pump.MotoClock;
					break;

					case 1:
						engine_state = BUV_RT_VALS.ANN_2.Pump.State;
						unload		 = BUV_RT_VALS.ANN_2.Unload;
						bimetal      = BUV_RT_VALS.ANN_2.Pump.Bimetal;
						Press_napor  = BUV_RT_VALS.ANN_2.Out_Pressure;
						Press_maslo  = BUV_RT_VALS.ANN_2.Oil_Pressure;
						Temp_maslo   = BUV_RT_VALS.ANN_2.Oil_Temperature;
						motoclock    = BUV_RT_VALS.ANN_2.Pump.MotoClock;
					break;

					case 2:
						engine_state = BUV_RT_VALS.ANN_3.Pump.State;
						unload		 = BUV_RT_VALS.ANN_3.Unload;
						bimetal      = BUV_RT_VALS.ANN_3.Pump.Bimetal;
						Press_napor  = BUV_RT_VALS.ANN_3.Out_Pressure;
						Press_maslo  = BUV_RT_VALS.ANN_3.Oil_Pressure;
						Temp_maslo   = BUV_RT_VALS.ANN_3.Oil_Temperature;
						motoclock    = BUV_RT_VALS.ANN_3.Pump.MotoClock;
					break;
				}

				uint16_t shift_X = i * 260 + 7;

				if(engine_state)
				{
					Short_Left_Colored_RU_DrawString_32("   Вкл   ", 		  9,  95 + shift_X,  20,      GreenColor, BasicSymbolColor, Page[1]);
				}
				else
				{
					Short_Left_Colored_RU_DrawString_32("   Выкл  ", 		  9,  95 + shift_X,  20,        RedColor, BasicSymbolColor, Page[1]);
				}
				Short_Centred_DrawNumber_16(Press_napor, 1, 4, 0, 					 170 + shift_X,  52, 									Page[1]);
				Short_Centred_DrawNumber_16(Press_maslo, 2, 4, 0, 					 170 + shift_X,  82, 									Page[1]);
				Short_Centred_DrawNumber_16(Temp_maslo , 0, 4, 0, 					 170 + shift_X, 112, 									Page[1]);
				if(unload)
				{
					Short_Left_Colored_RU_DrawString_32("  РАЗГРУЗКА   ", 	 14,   5 + shift_X, 140, 	  GreenColor, BasicSymbolColor, Page[1]);
				}
				else
				{
					Short_Left_Colored_RU_DrawString_32("  РАЗГРУЗКА   ", 	 14,   5 + shift_X, 140, 		RedColor, BasicSymbolColor, Page[1]);
				}
				if(bimetal)
				{
					Short_Left_Colored_RU_DrawString_32(" тепл. защита ", 	 14,   5 + shift_X, 170, 		RedColor, BasicSymbolColor, Page[1]);
				}
				else
				{
					Short_Left_Colored_RU_DrawString_32(" тепл. защита ", 	 14,   5 + shift_X, 170, 	  GreenColor, BasicSymbolColor, Page[1]);
				}

				Centred_DrawNumber_16_32bit(motoclock, 0, 10, 0, 			 200 + shift_X, 205, 800,480,Page[1],  BackgroundColor, BasicSymbolColor, Arial_11x18_Table, 11, 18);
			}

			Centred_DrawNumber_16(BUV_RT_VALS.Ustauka, 			0, 3, 0, 700, 270, 800, 480, Page[1], BackgroundColor, BasicSymbolColor, Arial_16x25_Table, 16, 25); // Уставка
			Centred_DrawNumber_16(BUV_RT_VALS.TANK_level, 		0, 3, 0, 700, 330, 800, 480, Page[1], BackgroundColor, BasicSymbolColor, Arial_16x25_Table, 16, 25); // уровень бак
			Centred_DrawNumber_16(BUV_RT_VALS.TANK_temperature, 0, 3, 0, 700, 390, 800, 480, Page[1], BackgroundColor, BasicSymbolColor, Arial_16x25_Table, 16, 25); // температура бак

			Short_Centred_DrawNumber_16(BUV_RT_VALS.FILT_NODE.Out_Pressure, 				1, 4, 0, 550, 242, 					 Page[1]); // давл в магистрали
			Short_Centred_DrawNumber_16(BUV_RT_VALS.FILT_NODE.Pressure_before_press_filter, 1, 4, 0, 550, 272, 					 Page[1]); // перед сливным напорным фильтром
			Short_Centred_DrawNumber_16(BUV_RT_VALS.FILT_NODE.Pressure_before_filter, 		1, 4, 0, 330, 302, 					 Page[1]); // перед сливным фильтром
			Short_Centred_DrawNumber_16(BUV_RT_VALS.FILT_NODE.Pressure_behind_filter, 		1, 4, 0, 550, 302, 					 Page[1]); // за сливным фильтром
			Short_Centred_DrawNumber_16(BUV_RT_VALS.FILT_NODE.Drain_filter_flowmeter.Flow,  1, 6, 0, 310, 334, 					 Page[1]); // расход на сливном фильтре
			Short_Centred_DrawNumber_16(BUV_RT_VALS.FILT_NODE.Emulsion_flowmeter.Flow, 		1, 6, 0, 530, 334, 					 Page[1]); // расход эмульсии

			Centred_DrawNumber_16_32bit(BUV_RT_VALS.FILT_NODE.Drain_filter_flowmeter.Volume, 0, 10, 0, 340, 364, 800,480,Page[1],  BackgroundColor, BasicSymbolColor, Arial_11x18_Table, 11, 18); // прокачаный объём на сливном фильтре
			Centred_DrawNumber_16_32bit(BUV_RT_VALS.FILT_NODE.Emulsion_flowmeter.Volume,     0, 10, 0, 560, 364, 800,480,Page[1],  BackgroundColor, BasicSymbolColor, Arial_11x18_Table, 11, 18); // прокачаный объём эмульсии

			if(BUV_RT_VALS.FILT_NODE.Flush_valve_1)
			{
				Short_Left_Colored_RU_DrawString_32("кл.промыв.1", 	 11,  90, 400, GreenColor, BasicSymbolColor, Page[1]);
			}
			else
			{
				Short_Left_Colored_RU_DrawString_32("кл.промыв.1", 	 11,  90, 400,   RedColor, BasicSymbolColor, Page[1]);
			}

			if(BUV_RT_VALS.FILT_NODE.Flush_valve_2)
			{
				Short_Left_Colored_RU_DrawString_32("кл.промыв.2", 	 11, 340, 400, GreenColor, BasicSymbolColor, Page[1]);
			}
			else
			{
				Short_Left_Colored_RU_DrawString_32("кл.промыв.2", 	 11, 340, 400,   RedColor, BasicSymbolColor, Page[1]);
			}

			Control_DB.RazrPointer 		= 0;

		break;

		case 2:

			Centred_DrawNumber_16_32bit(BUV_RT_VALS.EMULSION_NODE.Pump_circulation.MotoClock,			 0, 10, 0, 730,  94, 800,480,Page[2],  BackgroundColor, BasicSymbolColor, Arial_11x18_Table, 11, 18);
			Centred_DrawNumber_16_32bit(BUV_RT_VALS.EMULSION_NODE.Pump_concentrate.MotoClock,			 0, 10, 0, 730, 124, 800,480,Page[2],  BackgroundColor, BasicSymbolColor, Arial_11x18_Table, 11, 18);
			Centred_DrawNumber_16_32bit(BUV_RT_VALS.EMULSION_NODE.Pump_concentrate_injection.MotoClock,	 0, 10, 0, 730, 154, 800,480,Page[2],  BackgroundColor, BasicSymbolColor, Arial_11x18_Table, 11, 18);

			if(BUV_RT_VALS.EMULSION_NODE.Pump_circulation.State)
			{
				Short_Left_Colored_RU_DrawString_32("Насос циркуляционный ", 				21,  10,  90,      GreenColor, BasicSymbolColor, Page[2]);
			}
			else
			{
				Short_Left_Colored_RU_DrawString_32("Насос циркуляционный ", 				21,  10,  90,        RedColor, BasicSymbolColor, Page[2]);
			}

			if(BUV_RT_VALS.EMULSION_NODE.Pump_circulation.Bimetal)
			{
				Short_Left_Colored_RU_DrawString_32("тепл.защ", 							 8, 400,  90,      GreenColor, BasicSymbolColor, Page[2]);
			}
			else
			{
				Short_Left_Colored_RU_DrawString_32("тепл.защ", 							 8, 400,  90,        RedColor, BasicSymbolColor, Page[2]);
			}


			if(BUV_RT_VALS.EMULSION_NODE.Pump_concentrate.State)
			{
				Short_Left_Colored_RU_DrawString_32("Насос концентрата    ", 				21,  10, 120,      GreenColor, BasicSymbolColor, Page[2]);
			}
			else
			{
				Short_Left_Colored_RU_DrawString_32("Насос концентрата    ", 				21,  10, 120,        RedColor, BasicSymbolColor, Page[2]);
			}

			if(BUV_RT_VALS.EMULSION_NODE.Pump_concentrate.Bimetal)
			{
				Short_Left_Colored_RU_DrawString_32("тепл.защ", 							 8, 400, 120,      GreenColor, BasicSymbolColor, Page[2]);
			}
			else
			{
				Short_Left_Colored_RU_DrawString_32("тепл.защ", 							 8, 400, 120,        RedColor, BasicSymbolColor, Page[2]);
			}

			if(BUV_RT_VALS.EMULSION_NODE.Pump_concentrate_injection.State)
			{
				Short_Left_Colored_RU_DrawString_32("Насос закач.концентр.", 				21,  10, 150,      GreenColor, BasicSymbolColor, Page[2]);
			}
			else
			{
				Short_Left_Colored_RU_DrawString_32("Насос закач.концентр.", 				21,  10, 150,        RedColor, BasicSymbolColor, Page[2]);
			}

			if(BUV_RT_VALS.EMULSION_NODE.Pump_concentrate_injection.Bimetal)
			{
				Short_Left_Colored_RU_DrawString_32("тепл.защ", 							 8, 400, 150,      GreenColor, BasicSymbolColor, Page[2]);
			}
			else
			{
				Short_Left_Colored_RU_DrawString_32("тепл.защ", 							 8, 400, 150,        RedColor, BasicSymbolColor, Page[2]);
			}

			Short_Centred_DrawNumber_16(BUV_RT_VALS.EMULSION_NODE.Flowmeter_concent.Flow,   	 1,  6, 0, 470, 184, Page[2]);
			Centred_DrawNumber_16_32bit(BUV_RT_VALS.EMULSION_NODE.Flowmeter_concent.Volume, 	 0, 10, 0, 650, 184, 800,480,Page[2],  BackgroundColor, BasicSymbolColor, Arial_11x18_Table, 11, 18);

			Short_Centred_DrawNumber_16(BUV_RT_VALS.EMULSION_NODE.Flowmeter_water.Flow, 		 1, 6, 0,  470, 364, Page[2]);
			Centred_DrawNumber_16_32bit(BUV_RT_VALS.EMULSION_NODE.Flowmeter_water.Volume, 		 0, 10, 0, 650, 364, 800,480,Page[2],  BackgroundColor, BasicSymbolColor, Arial_11x18_Table, 11, 18);

			Short_Centred_DrawNumber_16(BUV_RT_VALS.EMULSION_NODE.Pressure_before_water_filters, 1, 6, 0,  673, 304, Page[2]);
			Short_Centred_DrawNumber_16(BUV_RT_VALS.EMULSION_NODE.Pressure_behind_water_filters, 1, 6, 0,  673, 334, Page[2]);

			if(BUV_RT_VALS.EMULSION_NODE.Filter_flow_valve_1)
			{
				Short_Left_Colored_RU_DrawString_32("кл.фил.1", 8,  20, 400,      GreenColor, BasicSymbolColor, Page[2]);
			}
			else
			{
				Short_Left_Colored_RU_DrawString_32("кл.фил.1", 8,  20, 400,        RedColor, BasicSymbolColor, Page[2]);
			}
			if(BUV_RT_VALS.EMULSION_NODE.Filter_flow_valve_2)
			{
				Short_Left_Colored_RU_DrawString_32("кл.фил.2", 8, 170, 400,      GreenColor, BasicSymbolColor, Page[2]);
			}
			else
			{
				Short_Left_Colored_RU_DrawString_32("кл.фил.2", 8, 170, 400,        RedColor, BasicSymbolColor, Page[2]);
			}
			if(BUV_RT_VALS.EMULSION_NODE.Filter_flow_valve_3)
			{
				Short_Left_Colored_RU_DrawString_32("кл.фил.3", 8, 320, 400,      GreenColor, BasicSymbolColor, Page[2]);
			}
			else
			{
				Short_Left_Colored_RU_DrawString_32("кл.фил.3", 8, 320, 400,        RedColor, BasicSymbolColor, Page[2]);
			}

			if(BUV_RT_VALS.EMULSION_NODE.Water_valve)
			{
				Short_Left_Colored_RU_DrawString_32("кл.воды ", 8, 470, 400,      GreenColor, BasicSymbolColor, Page[2]);
			}
			else
			{
				Short_Left_Colored_RU_DrawString_32("кл.воды ", 8, 470, 400,        RedColor, BasicSymbolColor, Page[2]);
			}

			if(BUV_RT_VALS.EMULSION_NODE.Concentrate_valve)
			{
				Short_Left_Colored_RU_DrawString_32("кл.конц ", 8, 620, 400,      GreenColor, BasicSymbolColor, Page[2]);
			}
			else
			{
				Short_Left_Colored_RU_DrawString_32("кл.конц ", 8, 620, 400,        RedColor, BasicSymbolColor, Page[2]);
			}

			Control_DB.RazrPointer 		= 0;

		break;

		case 3: // Окно данные

			if(!PassW_block.DataClearingUnlock)
			{
				Control_DB.MenuPointerMAX 	= 0;
				Short_Left_Colored_RU_DrawString_32("ввод пароля для возм.обнуления:", 	31,	10,  50, FonColor[0], BasicSymbolColor, Page[3]);
			}
			else
			{
				Control_DB.MenuPointerMAX 	= 19;
				Short_Left_Colored_RU_DrawString_32("пароль подтвержден             ", 	31,	10,  50, FonColor[0], BasicSymbolColor, Page[3]);
			}
			Short_Left_Colored_RU_DrawString_32("МтЧс Агр.насосного 1", 	20,	10,  80, FonColor[1], BasicSymbolColor, Page[3]);
			Short_Left_Colored_RU_DrawString_32("МтЧс Агр.насосного 2", 	20,	10, 110, FonColor[2], BasicSymbolColor, Page[3]);
			Short_Left_Colored_RU_DrawString_32("МтЧс Агр.насосного 3", 	20,	10, 140, FonColor[3], BasicSymbolColor, Page[3]);
			Short_Left_Colored_RU_DrawString_32("МтЧс циркуляц насоса", 	20,	10, 170, FonColor[4], BasicSymbolColor, Page[3]);
			Short_Left_Colored_RU_DrawString_32("МтЧс насоса концентр", 	20,	10, 200, FonColor[5], BasicSymbolColor, Page[3]);
			Short_Left_Colored_RU_DrawString_32("МтЧс нас.закач.конц ", 	20,	10, 230, FonColor[6], BasicSymbolColor, Page[3]);

			Centred_DrawNumber_16_32bit_controled(&PassW_block.PassWord, 0,  4, Control_DB.RazrPointer, 9999, 0, 620,  50, 800,480, Page[3], FonColor[0], BasicSymbolColor, Arial_11x18_Table, 11, 18);

			Centred_DrawNumber_16_32bit(BUV_RT_VALS.ANN_1.Pump.MotoClock, 								0, 10, 0,  440,  83, 800,480,Page[3],  BackgroundColor, BasicSymbolColor, Arial_11x18_Table, 11, 18);
			Centred_DrawNumber_16_32bit(BUV_RT_VALS.ANN_2.Pump.MotoClock, 								0, 10, 0,  440, 113, 800,480,Page[3],  BackgroundColor, BasicSymbolColor, Arial_11x18_Table, 11, 18);
			Centred_DrawNumber_16_32bit(BUV_RT_VALS.ANN_3.Pump.MotoClock, 								0, 10, 0,  440, 143, 800,480,Page[3],  BackgroundColor, BasicSymbolColor, Arial_11x18_Table, 11, 18);
			Centred_DrawNumber_16_32bit(BUV_RT_VALS.EMULSION_NODE.Pump_circulation.MotoClock, 			0, 10, 0,  440, 173, 800,480,Page[3],  BackgroundColor, BasicSymbolColor, Arial_11x18_Table, 11, 18);
			Centred_DrawNumber_16_32bit(BUV_RT_VALS.EMULSION_NODE.Pump_concentrate.MotoClock, 			0, 10, 0,  440, 203, 800,480,Page[3],  BackgroundColor, BasicSymbolColor, Arial_11x18_Table, 11, 18);
			Centred_DrawNumber_16_32bit(BUV_RT_VALS.EMULSION_NODE.Pump_concentrate_injection.MotoClock, 0, 10, 0,  440, 233, 800,480,Page[3],  BackgroundColor, BasicSymbolColor, Arial_11x18_Table, 11, 18);

			Short_Left_Colored_RU_DrawString_32("Ср-ки авт.разгр АНН1", 	20,	10, 260, FonColor[7], BasicSymbolColor, Page[3]);
			Short_Left_Colored_RU_DrawString_32("Ср-ки авт.разгр АНН2", 	20,	10, 290, FonColor[8], BasicSymbolColor, Page[3]);
			Short_Left_Colored_RU_DrawString_32("Ср-ки авт.разгр АНН3", 	20,	10, 320, FonColor[9], BasicSymbolColor, Page[3]);

			Centred_DrawNumber_16_32bit(BUV_RT_VALS.ANN_1.Unload_counter, 	 0, 10, 0,  440, 263, 800,480,Page[3],  BackgroundColor, BasicSymbolColor, Arial_11x18_Table, 11, 18);
			Centred_DrawNumber_16_32bit(BUV_RT_VALS.ANN_2.Unload_counter, 	 0, 10, 0,  440, 293, 800,480,Page[3],  BackgroundColor, BasicSymbolColor, Arial_11x18_Table, 11, 18);
			Centred_DrawNumber_16_32bit(BUV_RT_VALS.ANN_3.Unload_counter, 	 0, 10, 0,  440, 323, 800,480,Page[3],  BackgroundColor, BasicSymbolColor, Arial_11x18_Table, 11, 18);

			Short_Left_Colored_RU_DrawString_32("Пр-ки фильт.1.эмульс", 	20,	10, 350, FonColor[10], BasicSymbolColor, Page[3]);
			Short_Left_Colored_RU_DrawString_32("Пр-ки фильт.2.эмульс", 	20,	10, 380, FonColor[11], BasicSymbolColor, Page[3]);
			Short_Left_Colored_RU_DrawString_32("Пр-ки фильт.1.воды  ", 	20,	10, 410, FonColor[12], BasicSymbolColor, Page[3]);
			Short_Left_Colored_RU_DrawString_32("Пр-ки фильт.2.воды  ", 	20,	10, 440, FonColor[13], BasicSymbolColor, Page[3]);
			Short_Left_Colored_RU_DrawString_32("Пр-ки фильт.3.воды  ", 	20,	10, 470, FonColor[14], BasicSymbolColor, Page[3]);

			Centred_DrawNumber_16_32bit(BUV_RT_VALS.FILT_NODE.Flush_valve_1_counter, 			0, 10, 0,  440, 353, 800,480,Page[3],  BackgroundColor, BasicSymbolColor, Arial_11x18_Table, 11, 18);
			Centred_DrawNumber_16_32bit(BUV_RT_VALS.FILT_NODE.Flush_valve_2_counter, 			0, 10, 0,  440, 383, 800,480,Page[3],  BackgroundColor, BasicSymbolColor, Arial_11x18_Table, 11, 18);
			Centred_DrawNumber_16_32bit(BUV_RT_VALS.EMULSION_NODE.Filter_flow_valve_1_counter, 	0, 10, 0,  440, 413, 800,480,Page[3],  BackgroundColor, BasicSymbolColor, Arial_11x18_Table, 11, 18);
			Centred_DrawNumber_16_32bit(BUV_RT_VALS.EMULSION_NODE.Filter_flow_valve_2_counter, 	0, 10, 0,  440, 443, 800,480,Page[3],  BackgroundColor, BasicSymbolColor, Arial_11x18_Table, 11, 18);
			Centred_DrawNumber_16_32bit(BUV_RT_VALS.EMULSION_NODE.Filter_flow_valve_3_counter, 	0, 10, 0,  440, 473, 800,480,Page[3],  BackgroundColor, BasicSymbolColor, Arial_11x18_Table, 11, 18);

			Short_Left_Colored_RU_DrawString_32("Объем сл.фильт  ",     16,	505,  80, FonColor[15], BasicSymbolColor, Page[3]);
			Short_Left_Colored_RU_DrawString_32("Объем пр.эмульс ",     16,	505, 140, FonColor[16], BasicSymbolColor, Page[3]);
			Short_Left_Colored_RU_DrawString_32("Объем пр.концент",     16,	505, 200, FonColor[17], BasicSymbolColor, Page[3]);
			Short_Left_Colored_RU_DrawString_32("Объем пр.воды   ",     16,	505, 260, FonColor[18], BasicSymbolColor, Page[3]);
			Short_Left_Colored_RU_DrawString_32("Кол-во ср. УПЭ  ",     16,	505, 320, FonColor[19], BasicSymbolColor, Page[3]);

			Centred_DrawNumber_16_32bit(BUV_RT_VALS.FILT_NODE.Drain_filter_flowmeter.Volume, 	0, 10, 0,  650, 113, 800,480,Page[3],  BackgroundColor, BasicSymbolColor, Arial_11x18_Table, 11, 18);
			Centred_DrawNumber_16_32bit(BUV_RT_VALS.FILT_NODE.Emulsion_flowmeter.Volume, 		0, 10, 0,  650, 173, 800,480,Page[3],  BackgroundColor, BasicSymbolColor, Arial_11x18_Table, 11, 18);
			Centred_DrawNumber_16_32bit(BUV_RT_VALS.EMULSION_NODE.Flowmeter_concent.Volume, 	0, 10, 0,  650, 233, 800,480,Page[3],  BackgroundColor, BasicSymbolColor, Arial_11x18_Table, 11, 18);
			Centred_DrawNumber_16_32bit(BUV_RT_VALS.EMULSION_NODE.Flowmeter_water.Volume, 		0, 10, 0,  650, 293, 800,480,Page[3],  BackgroundColor, BasicSymbolColor, Arial_11x18_Table, 11, 18);
			Centred_DrawNumber_16_32bit(BUV_RT_VALS.EMULSION_NODE.Node_work_counter, 			0, 10, 0,  650, 353, 800,480,Page[3],  BackgroundColor, BasicSymbolColor, Arial_11x18_Table, 11, 18);

			if(Control_DB.MenuPointer == 0)
			{
				Control_DB.RazrPointerMAX   = 4;
			}
			else
			{
				Control_DB.RazrPointer 		= 0;
				Control_DB.RazrPointerMAX   = 0;
			}


		break;

		case 4: // Ручное управление

			if(!ALG_DB.clearing_pressure_filter_1.state)
			{
				Short_Left_Colored_RU_DrawString_32(" Промыть напорный фильтр 1 ", 27,	100,  70, FonColor[0], BasicSymbolColor, Page[4]);
			}
			else
			{
				Short_Left_Colored_RU_DrawString_32(" Промывка фильтра......  1 ", 27,	100,  70, FonColor[0], BasicSymbolColor, Page[4]);
			}

			if(!ALG_DB.clearing_pressure_filter_2.state)
			{
				Short_Left_Colored_RU_DrawString_32(" Промыть напорный фильтр 2 ", 27,	100, 110, FonColor[1], BasicSymbolColor, Page[4]);
			}
			else
			{
				Short_Left_Colored_RU_DrawString_32(" Промывка фильтра......  2 ", 27,	100, 110, FonColor[1], BasicSymbolColor, Page[4]);
			}

			if(!ALG_DB.clearing_water_filter_1.state)
			{
				Short_Left_Colored_RU_DrawString_32(" Промыть фильтр воды     1 ", 27,	100, 150, FonColor[2], BasicSymbolColor, Page[4]);
			}
			else
			{
				Short_Left_Colored_RU_DrawString_32(" Промывка фильтра......  1 ", 27,	100, 150, FonColor[2], BasicSymbolColor, Page[4]);
			}

			if(!ALG_DB.clearing_water_filter_2.state)
			{
				Short_Left_Colored_RU_DrawString_32(" Промыть фильтр воды     2 ", 27,	100, 190, FonColor[3], BasicSymbolColor, Page[4]);
			}
			else
			{
				Short_Left_Colored_RU_DrawString_32(" Промывка фильтра......  2 ", 27,	100, 190, FonColor[3], BasicSymbolColor, Page[4]);
			}

			if(!ALG_DB.clearing_water_filter_3.state)
			{
				Short_Left_Colored_RU_DrawString_32(" Промыть фильтр воды     3 ", 27,	100, 230, FonColor[4], BasicSymbolColor, Page[4]);
			}
			else
			{
				Short_Left_Colored_RU_DrawString_32(" Промывка фильтра......  3 ", 27,	100, 230, FonColor[4], BasicSymbolColor, Page[4]);
			}

			Control_DB.MenuPointerMAX 	= 4;
			Control_DB.RazrPointer 		= 0;

		break;




		case 5:

			Short_Centred_RU_DrawString_32("Введите пароль", 14, 	  		400, 190, BackgroundColor, BasicSymbolColor, Page[5]);
			Centred_DrawNumber_16_32bit_controled(&PassW_block.PassWord, 0,   4, Control_DB.RazrPointer, 9999, 0, 400,  240, 800,480, Page[5], GrayColor, BasicSymbolColor, Arial_11x18_Table, 11, 18);
			if(PassW_block.PassFalseTimer)
			{
				Short_Centred_RU_DrawString_32("Пароль неверный", 15, 		400, 290,        RedColor, BasicSymbolColor, Page[5]);
			}
			else
			{
				Short_Centred_RU_DrawString_32("               ", 15, 		400, 290, BackgroundColor, BasicSymbolColor, Page[5]);
			}

			Control_DB.RazrPointerMAX 	= 4;
			Control_DB.MenuPointerMAX 	= 0;

		break;

		case 6:
			Short_Left_Colored_RU_DrawString_32("Режим работы    ", 16,	30,  50, FonColor[0], BasicSymbolColor, Page[6]);
			Centred_DrawNumber_16_32bit_controled(&BUV_settings.pump_mode,0, 1, Control_DB.RazrPointer, 1,   0, 470, 50, 800,480, Page[6], FonColor[0], BasicSymbolColor, Arial_11x18_Table, 11, 18);

			if(BUV_settings.pump_mode)
			{

				Short_Left_Colored_RU_DrawString_32("Авто", 4,585,  50, BackgroundColor, BasicSymbolColor, Page[6]);
				
				Short_Left_Colored_RU_DrawString_32("Насос АНН1", 10,30,  80, FonColor[1], BasicSymbolColor, Page[6]);
				Centred_DrawNumber_16_32bit_controled(&BUV_settings.work_pump1,0, 1, Control_DB.RazrPointer, 3,   1, 470, 80, 800,480, Page[6], FonColor[1], BasicSymbolColor, Arial_11x18_Table, 11, 18);
				update_station_pump(BUV_settings.work_pump1,80);

				Short_Left_Colored_RU_DrawString_32("Насос АНН2", 10,30,  110,FonColor[2], BasicSymbolColor, Page[6]);
				Centred_DrawNumber_16_32bit_controled(&BUV_settings.work_pump2,0, 1, Control_DB.RazrPointer, 3,   1, 470, 110, 800,480, Page[6], FonColor[2], BasicSymbolColor, Arial_11x18_Table, 11, 18);
				update_station_pump(BUV_settings.work_pump2,110);
				Short_Left_Colored_RU_DrawString_32("Насос АНН3", 10,30,  140, FonColor[3], BasicSymbolColor, Page[6]);
				Centred_DrawNumber_16_32bit_controled(&BUV_settings.work_pump3,0, 1, Control_DB.RazrPointer, 3,   1, 470, 140, 800,480, Page[6], FonColor[3], BasicSymbolColor, Arial_11x18_Table, 11, 18);
				update_station_pump(BUV_settings.work_pump3,140);
				
				Short_Left_Colored_RU_DrawString_32("Время раб нас", 13,30,  170, FonColor[4], BasicSymbolColor, Page[6]);
				Short_Left_Colored_RU_DrawString_32("Ч", 1,585,  170, BackgroundColor, BasicSymbolColor, Page[6]);
				Centred_DrawNumber_16_32bit_controled(&BUV_settings.time_of_work_pump,0, 3, Control_DB.RazrPointer, 120,  5, 470, 170, 800,480, Page[6], FonColor[4], BasicSymbolColor, Arial_11x18_Table, 11, 18);

				Short_Left_Colored_RU_DrawString_32("Настр кол раб нас", 17, 30, 200, FonColor[5], BasicSymbolColor, Page[6]);
				Centred_DrawNumber_16_32bit_controled(&BUV_settings.count_work_pump,0, 1, Control_DB.RazrPointer, 3,   1, 470, 200, 800,480, Page[6], FonColor[5], BasicSymbolColor, Arial_11x18_Table, 11, 18);

				Short_Left_Colored_RU_DrawString_32("Конц эмульсии    ", 17,30,  230, FonColor[6], BasicSymbolColor, Page[6]);
				Centred_DrawNumber_16_32bit_controled(&BUV_settings.conc_emul,1, 3, Control_DB.RazrPointer, 50,   10, 470, 230, 800,480, Page[6], FonColor[6], BasicSymbolColor, Arial_11x18_Table, 11, 18);
				Short_Left_Colored_RU_DrawString_32("моль/л", 6,585,  230, BackgroundColor, BasicSymbolColor, Page[6]);

				Short_Left_Colored_RU_DrawString_32("Настр промыв нап фильт", 22, 30, 260, FonColor[7], BasicSymbolColor, Page[6]);

				Short_Left_Colored_RU_DrawString_32("Настр промыв фильт воды", 23, 30, 290, FonColor[8], BasicSymbolColor, Page[6]);

				Short_Left_Colored_RU_DrawString_32("Настр мин уровн конц", 20, 30, 320, FonColor[9], BasicSymbolColor, Page[6]);
				Centred_DrawNumber_16_32bit_controled(&BUV_settings.min_level_conc,0, 3, Control_DB.RazrPointer, 100,   0, 470, 320, 800,480, Page[6], FonColor[9], BasicSymbolColor, Arial_11x18_Table, 11, 18);
				Short_Left_Colored_RU_DrawString_32("Процент", 7,585,  320, BackgroundColor, BasicSymbolColor, Page[6]);

				Short_Left_Colored_RU_DrawString_32("Настр уровн авт разгр", 21, 30, 350, FonColor[10], BasicSymbolColor, Page[6]);
				Centred_DrawNumber_16_32bit_controled(&BUV_settings.work_auto_unload,0, 1, Control_DB.RazrPointer, 1,   0, 470, 350, 800,480, Page[6], FonColor[10], BasicSymbolColor, Arial_11x18_Table, 11, 18);
				setting_auto_unload(BUV_settings.work_auto_unload);

				Short_Left_Colored_RU_DrawString_32("Настр мин уровн эмул", 20, 30, 380, FonColor[11], BasicSymbolColor, Page[6]);
				Centred_DrawNumber_16_32bit_controled(&BUV_settings.min_level_emul,0, 3, Control_DB.RazrPointer, 100,   0, 470, 380, 800,480, Page[6], FonColor[11], BasicSymbolColor, Arial_11x18_Table, 11, 18);
				Short_Left_Colored_RU_DrawString_32("Процент", 7,585,  380, BackgroundColor, BasicSymbolColor, Page[6]);

				Short_Left_Colored_RU_DrawString_32("Мин уровн эмул УПЭ", 18, 30, 410, FonColor[12], BasicSymbolColor, Page[6]);
				Centred_DrawNumber_16_32bit_controled(&BUV_settings.min_level_emul_UP,0, 3, Control_DB.RazrPointer, 100,   0, 470, 410, 800,480, Page[6], FonColor[12], BasicSymbolColor, Arial_11x18_Table, 11, 18);
				Short_Left_Colored_RU_DrawString_32("Процент", 7,585,  410, BackgroundColor, BasicSymbolColor, Page[6]);


				Short_Left_Colored_RU_DrawString_32("Макс уровн эмул УПЭ", 19, 30, 440, FonColor[13], BasicSymbolColor, Page[6]);
				Centred_DrawNumber_16_32bit_controled(&BUV_settings.max_level_emul_UP,0, 3, Control_DB.RazrPointer, 100,   0, 470, 440, 800,480, Page[6], FonColor[13], BasicSymbolColor, Arial_11x18_Table, 11, 18);
				Short_Left_Colored_RU_DrawString_32("Процент", 7,585,  440, BackgroundColor, BasicSymbolColor, Page[6]);

				Short_Left_Colored_RU_DrawString_32("Далее", 5, 30, 470, FonColor[14], BasicSymbolColor, Page[6]);
				Control_DB.MenuPointerMAX = 14;
			}
			else
			{
				Short_Left_Colored_RU_DrawString_32("Ручн", 4,585,  50, BackgroundColor, BasicSymbolColor, Page[6]);



			}
	


		break;

		case 7: // Заводские настройки

			Short_Left_Colored_RU_DrawString_32("Макс кол-во одновр. раб. АНН :", 30,	20,  70, FonColor[0], BasicSymbolColor, Page[7]);
			Centred_DrawNumber_16_32bit_controled(&BUV_settings_global.Max_ANN_operation,   0, 1, Control_DB.RazrPointer,     3,      1, 700,  70, 800,480, Page[7], FonColor[0], BasicSymbolColor, Arial_11x18_Table, 11, 18);

			Short_Left_Colored_RU_DrawString_32("Макс выставляемое давление   :", 30,	20, 110, FonColor[1], BasicSymbolColor, Page[7]);
			Centred_DrawNumber_16_32bit_controled(&BUV_settings_global.Max_Pressure, 	    0, 2, Control_DB.RazrPointer,    60,     10, 700, 110, 800,480, Page[7], FonColor[1], BasicSymbolColor, Arial_11x18_Table, 11, 18);

			Short_Left_Colored_RU_DrawString_32("Срок кап ремонта АНН (ч)     :", 30,	20, 150, FonColor[2], BasicSymbolColor, Page[7]);
			Centred_DrawNumber_16_32bit_controled(&BUV_settings_global.Major_repear_period, 0, 5, Control_DB.RazrPointer, 50000,   5000, 700, 150, 800,480, Page[7], FonColor[2], BasicSymbolColor, Arial_11x18_Table, 11, 18);

			Short_Left_Colored_RU_DrawString_32("Ур.эмульсии при котором откл :", 30,	20, 190, FonColor[3], BasicSymbolColor, Page[7]);
			Centred_DrawNumber_16_32bit_controled(&BUV_settings_global.emulsion_off_level, 0, 3, Control_DB.RazrPointer,    900,    100, 700, 190, 800,480, Page[7], FonColor[3], BasicSymbolColor, Arial_11x18_Table, 11, 18);

			if(!BUV_settings_global.work_on_water_enable)
			{
				Short_Left_Colored_RU_DrawString_32("Работа на воде запрещена      ", 30,	20, 230, FonColor[4], BasicSymbolColor, Page[7]);
			}
			else
			{
				Short_Left_Colored_RU_DrawString_32("Работа на воде разрешена      ", 30,	20, 230, FonColor[4], BasicSymbolColor, Page[7]);
			}

			Short_Left_Colored_RU_DrawString_32("Ур.конц-та при котором предупр",    30,	20, 270, FonColor[5], BasicSymbolColor, Page[7]);
			Centred_DrawNumber_16_32bit_controled(&BUV_settings_global.water_work_conconcentrate_level, 0, 3, Control_DB.RazrPointer,    900,    100, 700, 270, 800,480, Page[7], FonColor[5], BasicSymbolColor, Arial_11x18_Table, 11, 18);


			Control_DB.MenuPointerMAX 	= 5;
			if(Control_DB.MenuPointer == 4)
			{
				Control_DB.RazrPointer = 0;
			}

		break;
		case 8:
				Short_Left_Colored_RU_DrawString_32("Режим промывки", 14,	30,  50, FonColor[0], BasicSymbolColor, Page[8]);
				Centred_DrawNumber_16_32bit_controled(&BUV_settings.flushing_mode_pressure_filter,0, 1, Control_DB.RazrPointer, 4,   1, 470, 50, 800,480, Page[8], FonColor[0], BasicSymbolColor, Arial_11x18_Table, 11, 18);
				update_mode_flushing(BUV_settings.flushing_mode_pressure_filter,Page[8]);


				Short_Left_Colored_RU_DrawString_32("Период промывки", 13,30,  80, FonColor[1], BasicSymbolColor, Page[8]);
				Short_Left_Colored_RU_DrawString_32("Ч", 1,585,  80, BackgroundColor, BasicSymbolColor, Page[8]);
				Centred_DrawNumber_16_32bit_controled(&BUV_settings.period_flushing_pressure_filter,0, 3, Control_DB.RazrPointer, 120,  5, 470, 80, 800,480, Page[8], FonColor[1], BasicSymbolColor, Arial_11x18_Table, 11, 18);
			
				Short_Left_Colored_RU_DrawString_32("Время промывки", 14,30,  110, FonColor[2], BasicSymbolColor, Page[8]);
				Short_Left_Colored_RU_DrawString_32("Сек", 3,585,  110, BackgroundColor, BasicSymbolColor, Page[8]);
				Centred_DrawNumber_16_32bit_controled(&BUV_settings.time_flushing_pressure_filter,0, 2, Control_DB.RazrPointer, 10,  1, 470, 110, 800,480, Page[8], FonColor[2], BasicSymbolColor, Arial_11x18_Table, 11, 18);

				Short_Left_Colored_RU_DrawString_32("Перепад Давления", 16,30,  140, FonColor[3], BasicSymbolColor, Page[8]);
				Short_Left_Colored_RU_DrawString_32("МПа", 3,585,  140, BackgroundColor, BasicSymbolColor, Page[8]);
				Centred_DrawNumber_16_32bit_controled(&BUV_settings.difference_pressure_filter,1, 3, Control_DB.RazrPointer, 10,  1, 470, 140, 800,480, Page[8], FonColor[3], BasicSymbolColor, Arial_11x18_Table, 11, 18);

				Short_Left_Colored_RU_DrawString_32("Вр кон знач при перепад", 23,30,  170, FonColor[4], BasicSymbolColor, Page[8]);
				Centred_DrawNumber_16_32bit_controled(&BUV_settings.time_control_pressure_filter,0, 2, Control_DB.RazrPointer, 10,  1, 470, 170, 800,480, Page[8], FonColor[4], BasicSymbolColor, Arial_11x18_Table, 11, 18);
				Short_Left_Colored_RU_DrawString_32("Сек", 3,585,  170, BackgroundColor, BasicSymbolColor, Page[8]);

				Control_DB.MenuPointerMAX 	= 5;
			break;
		case 9:

			Short_Left_Colored_RU_DrawString_32("Режим промывки", 14,	30,  50, FonColor[0], BasicSymbolColor, Page[9]);
			Centred_DrawNumber_16_32bit_controled(&BUV_settings.flushing_mode_water_filter,0, 1, Control_DB.RazrPointer, 4,   1, 470, 50, 800,480, Page[9], FonColor[0], BasicSymbolColor, Arial_11x18_Table, 11, 18);
			update_mode_flushing(BUV_settings.flushing_mode_water_filter,Page[9]);

			Short_Left_Colored_RU_DrawString_32("Период промывки", 13,30,  80, FonColor[1], BasicSymbolColor, Page[9]);
			Short_Left_Colored_RU_DrawString_32("Ч", 1,585,  80, BackgroundColor, BasicSymbolColor, Page[9]);
			Centred_DrawNumber_16_32bit_controled(&BUV_settings.period_flushing_water_filter,0, 3, Control_DB.RazrPointer, 120,  5, 470, 80, 800,480, Page[9], FonColor[1], BasicSymbolColor, Arial_11x18_Table, 11, 18);

			Short_Left_Colored_RU_DrawString_32("Время промывки", 14,30,  110, FonColor[2], BasicSymbolColor, Page[9]);
			Short_Left_Colored_RU_DrawString_32("Сек", 3,585,  110, BackgroundColor, BasicSymbolColor, Page[9]);
			Centred_DrawNumber_16_32bit_controled(&BUV_settings.time_flushing_water_filter,0, 2, Control_DB.RazrPointer, 10,  1, 470, 110, 800,480, Page[9], FonColor[2], BasicSymbolColor, Arial_11x18_Table, 11, 18);

			Short_Left_Colored_RU_DrawString_32("Перепад Давления", 16,30,  140, FonColor[3], BasicSymbolColor, Page[9]);
			Short_Left_Colored_RU_DrawString_32("МПа", 3,585,  140, BackgroundColor, BasicSymbolColor, Page[9]);
			Centred_DrawNumber_16_32bit_controled(&BUV_settings.difference_water_filter,1, 3, Control_DB.RazrPointer, 10,  1, 470, 140, 800,480, Page[9], FonColor[3], BasicSymbolColor, Arial_11x18_Table, 11, 18);

			Short_Left_Colored_RU_DrawString_32("Вр кон знач при перепад", 23,30,  170, FonColor[4], BasicSymbolColor, Page[9]);
			Centred_DrawNumber_16_32bit_controled(&BUV_settings.time_control_water_filter,0, 2, Control_DB.RazrPointer, 10,  1, 470, 170, 800,480, Page[9], FonColor[4], BasicSymbolColor, Arial_11x18_Table, 11, 18);
			Short_Left_Colored_RU_DrawString_32("Сек", 3,585,  170, BackgroundColor, BasicSymbolColor, Page[9]);

			Control_DB.MenuPointerMAX 	= 5;
			break;
		case 14:
				Short_Left_Colored_RU_DrawString_32("Сброс настроек по умол", 22,	30,  50, FonColor[0], BasicSymbolColor, Page[14]);
				Short_Left_Colored_RU_DrawString_32("Заводские настройки", 19,	30,  80, FonColor[1], BasicSymbolColor, Page[14]);
				Control_DB.MenuPointerMAX = 2;

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

			Short_Left_Colored_RU_DrawString_32("бод/с", 5,					585, 110, BackgroundColor, BasicSymbolColor, Page[21]);

		break;

	}


	if(screen_event)
	{

		Control_DB.MenuPointer  		= 0;
		Control_DB.RazrPointer 			= 0;
		PassW_block.PassWord   			= 0;
		PassW_block.DataClearingUnlock	= 0;
		screen_event 					= 0;

	}

	HAL_LTDC_SetAddress(&hltdc, Page[screen], 0);
}




