/*
 * algorithm_handler.c
 *
 *  Created on: 20 нояб. 2023 г.
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

extern Settings_panel Settings_DB;
extern InterfaceControlDB Control_DB;

extern uint8_t screen;
extern uint8_t screen_mirror;
extern uint8_t screen_event;

extern PassWords PassW_block;
extern Algorithm_variables ALG_DB;

extern Settings_Station BUV_settings_global;







void TimedBitValue_handler(TimedBitValue *Var)
{
	if(Var->state & !Var->state_mirror)
	{
		Var->timer = Var->default_timer; // Запуск таймера при переходе 0 -> 1
	}
	Var->state_mirror = Var->state;

	if(!Var->state)
	{
		Var->timer = 0; // Обнуление таймера при принудительном сбросе
	}
	else
	{
		if(!Var->timer)
		{
			Var->state = 0;
		}
		Var->timer--;
	}
}









































