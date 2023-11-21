/*
 * ADC_functions.c
 *
 *  Created on: 4 февр. 2021 г.
 *      Author: Motor
 */
#include "ADC_functions.h"

extern float ADC_Speed;

extern uint16_t Global_A_phase_ticks;
extern uint16_t Global_B_phase_ticks;
extern uint16_t Global_C_phase_ticks;



void ADC_preparation_simple(ADC_analog_preparation *ADC_Var)
{

	ADC_Var->input = ADC_Var->momentary_RAW;

	ADC_Var->momentary = (ADC_Var->filter_coeff * ADC_Var->input_old) + ((1-ADC_Var->filter_coeff) * ADC_Var->momentary_old);

	ADC_Var->input_old = ADC_Var->input;

	ADC_Var->momentary_old = ADC_Var->momentary;

	if(ADC_Var->momentary > ADC_Var->high)
	{
		ADC_Var->high = ADC_Var->momentary;
	}
	if(ADC_Var->momentary < ADC_Var->low)
	{
		ADC_Var->low = ADC_Var->momentary;
	}
}




void ADC_preparation(ADC_analog_preparation *ADC_Var)
{
	ADC_Var->input = ADC_Var->momentary_RAW;

	ADC_Var->Virtual_bit = ADC_Var->input > ADC_Var->Default_Level.value;

	ADC_Var->momentary = (ADC_Var->filter_coeff * ADC_Var->input_old) + ((1-ADC_Var->filter_coeff) * ADC_Var->momentary_old);

	ADC_Var->momentary_old = ADC_Var->momentary;
	ADC_Var->input_old = ADC_Var->input;

	if(ADC_Var->momentary > ADC_Var->high)
	{
		ADC_Var->high = ADC_Var->momentary;

		if(ADC_Var->Phase_number == 1)
		{ADC_Var->Phase_delay_ticks_photo = Global_A_phase_ticks;}
		if(ADC_Var->Phase_number == 2)
		{ADC_Var->Phase_delay_ticks_photo = Global_B_phase_ticks;}
		if(ADC_Var->Phase_number == 3)
		{ADC_Var->Phase_delay_ticks_photo = Global_C_phase_ticks;}
	}
	if(ADC_Var->momentary < ADC_Var->low)
	{
		ADC_Var->low = ADC_Var->momentary;
	}

	ADC_Var->momentary_HalfReal = ADC_Var->momentary - ADC_Var->Default_Level.value;

	ADC_Var->high_max = ADC_Var->high;
	if(ADC_Var->high_ > ADC_Var->high_max){ADC_Var->high_max = ADC_Var->high_;}

	ADC_Var->low_max = ADC_Var->low;
	if(ADC_Var->low_ < ADC_Var->low_max){ADC_Var->low_max = ADC_Var->low_;}

	ADC_Var->val_max = ADC_Var->high_max - ADC_Var->low_max;
}

void ADC_deafult(ADC_analog_preparation *ADC_Var)
{
	ADC_Var->Phase_delay_ticks_photo_out = ADC_Var->Phase_delay_ticks_photo;

	ADC_Var->deafult = (ADC_Var->high + ADC_Var->low) / 2;

	ADC_Var->Default_Level.value_input = ADC_Var->deafult;
	Z_filter(&ADC_Var->Default_Level);

	ADC_Var->high_ = ADC_Var->high;
	ADC_Var->low_  = ADC_Var->low;

	ADC_Var->high = ADC_Var->deafult;
	ADC_Var->low  = ADC_Var->deafult;

}

void ADC_Float_USR(ADC_Float_massive *massive)
{

	float TempVar = 0;
	uint8_t Count = 50;

	if((massive->InValue > massive->InValue_old + 0.01) | (massive->InValue < massive->InValue_old - 0.01))
	{
		massive->InValue_old = massive->InValue;

		if(massive->InValue > 30)
		{
			if((massive->InValue > massive->result * (1 + massive->allowance)) | (massive->InValue < massive->result * (1 - massive->allowance)))
			{
				for(uint8_t i = 0;i<Count;i++)
				{
					massive->massive[i] = massive->InValue;
				}
			}
		}

		massive->pointer++;

		if(massive->pointer >= Count){massive->pointer = 0;}
		massive->massive[massive->pointer] = massive->InValue;

		for(int i=0;i<Count;i++)
		{
			TempVar = TempVar + massive->massive[i];
		}
		TempVar = TempVar / Count;

		massive->result = TempVar;

	}

}

void Float_Approx(Approx *DB)
{

	double InValue = DB->InValue;

	double K = DB->k;
	double X  = InValue;
	double X2 = X  * InValue;
	double X3 = X2 * InValue;
	double X4 = X3 * InValue;

	X  = X  * DB->kX1;
	X2 = X2 * DB->kX2;
	X3 = X3 * DB->kX3;
	X4 = X4 * DB->kX4;

	InValue = K + X + X2 + X3 + X4;

	DB->OutValue = InValue;

	//DB->OutValue = DB->InValue;

}

void Float_Approx_X6(Approx_X6 *DB)
{

	double InValue = DB->InValue;

	double K	= DB->k;
	double X	= InValue;
	double X2 	= X  * InValue;
	double X3 	= X2 * InValue;
	double X4 	= X3 * InValue;
	double X5 	= X4 * InValue;
	double X6 	= X5 * InValue;

	X	*= DB->kX1;
	X2	*= DB->kX2;
	X3	*= DB->kX3;
	X4	*= DB->kX4;
	X5	*= DB->kX5;
	X6	*= DB->kX6;

	InValue = K + X + X2 + X3 + X4 + X5 + X6;

	DB->OutValue = InValue;

	//DB->OutValue = DB->InValue;

}

void Channel_Reset(ADC_analog_preparation *ADC_Var)
{
	//if(ADC_Var->low == 0)
	//{
		ADC_Var->deafult = ADC_Var->momentary_RAW;

		ADC_Var->Default_Level.value 			= ADC_Var->deafult;
		ADC_Var->Default_Level.value_input 		= ADC_Var->deafult;
		ADC_Var->Default_Level.value_input_old 	= ADC_Var->deafult;
		ADC_Var->Default_Level.value_old 		= ADC_Var->deafult;

		ADC_Var->high    = ADC_Var->deafult;
		ADC_Var->low     = ADC_Var->deafult;

		ADC_Var->ADC_max = ADC_Var->deafult;
		ADC_Var->ADC_min = ADC_Var->deafult;

		ADC_Var->momentary     = ADC_Var->deafult;
		ADC_Var->momentary_old = ADC_Var->deafult;

		ADC_Var->input         = ADC_Var->deafult;
		ADC_Var->input_old     = ADC_Var->deafult;

		ADC_Var->Value_fast   = 0;
		ADC_Var->Value_slow   = 0;
		ADC_Var->Value		  = 0;

		ADC_Var->val_max	  = 0;
		ADC_Var->val_max_temp = 0;
	/*}
	else
	{

		ADC_Var->deafult = (ADC_Var->high + ADC_Var->low) / 2;

		ADC_Var->Default_Level.value 			= ADC_Var->deafult;
		ADC_Var->Default_Level.value_input 		= ADC_Var->deafult;
		ADC_Var->Default_Level.value_input_old 	= ADC_Var->deafult;
		ADC_Var->Default_Level.value_old 		= ADC_Var->deafult;

		ADC_Var->ADC_max = ADC_Var->deafult;
		ADC_Var->ADC_min = ADC_Var->deafult;

		ADC_Var->momentary     = ADC_Var->deafult;
		ADC_Var->momentary_old = ADC_Var->deafult;

		ADC_Var->input         = ADC_Var->deafult;
		ADC_Var->input_old     = ADC_Var->deafult;

		ADC_Var->Value_fast   = 0;
		ADC_Var->Value_slow   = 0;
		ADC_Var->Value		  = 0;

		ADC_Var->val_max	  = 0;
		ADC_Var->val_max_temp = 0;

	}*/
}

void Channel_Soft_Switch(ADC_analog_preparation *ADC_Var)
{

	ADC_Var->momentary     					= ADC_Var->deafult;
	ADC_Var->momentary_old 					= ADC_Var->deafult;

	ADC_Var->input         					= ADC_Var->deafult;
	ADC_Var->input_old     					= ADC_Var->deafult;

	ADC_Var->high    						= ADC_Var->deafult;
	ADC_Var->low     						= ADC_Var->deafult;

	ADC_Var->ADC_max 						= ADC_Var->deafult;
	ADC_Var->ADC_min 						= ADC_Var->deafult;

	ADC_Var->Default_Level.value 			= ADC_Var->deafult;
	ADC_Var->Default_Level.value_input 		= ADC_Var->deafult;
	ADC_Var->Default_Level.value_input_old 	= ADC_Var->deafult;
	ADC_Var->Default_Level.value_old 		= ADC_Var->deafult;

	ADC_Var->Value_fast   					= 0;
	ADC_Var->Value_slow   					= 0;
	ADC_Var->Value		  					= 0;

	ADC_Var->val_max	  					= 0;
	ADC_Var->val_max_temp 					= 0;

}



void Z_filter(Z_filter_DB *filter)
{
	filter->value = (filter->filter_coeff * filter->value_input_old) + ((1 - filter->filter_coeff) * filter->value_old);

	filter->value_input_old = filter->value_input;
	filter->value_old = filter->value;

	if((filter->value > 1000000) | (filter->value < -1000000))	// Вывод из мёртвой точки
	{
		filter->value 			= filter->value_input;
		filter->value_old 		= filter->value_input;
		filter->value_input_old = filter->value_input;
	}
}


void frequency_meter(ADC_analog_preparation *ADC_Var)
{
	// Определение частоты
	ADC_Var->new_period_ticks++;

	if((!ADC_Var->up_halfperiod_ok) & (!ADC_Var->down_halfperiod_ok))
	{ADC_Var->up_halfperiod_ok = 1;}

	if(ADC_Var->up_halfperiod_ok)
	{ADC_Var->up_ticks++;}

	if(ADC_Var->down_halfperiod_ok)
	{ADC_Var->down_ticks++;}

	if(ADC_Var->momentary > (ADC_Var->Default_Level.value + 0))
	{
		if(ADC_Var->down_ticks > 50)
		{
			ADC_Var->down_ticks_result 	= ADC_Var->down_ticks;
			ADC_Var->down_ticks 		= 0;

			ADC_Var->up_halfperiod_ok 	= 1;
			ADC_Var->down_halfperiod_ok	= 0;

			ADC_Var->period_ticks = ADC_Var->new_period_ticks;
			ADC_Var->new_period_ticks = 0;

		}
	}

	if(ADC_Var->momentary < (ADC_Var->Default_Level.value - 50))
	{
		if(ADC_Var->up_ticks > 50)
		{
			ADC_Var->up_ticks_result = ADC_Var->up_ticks;
			ADC_Var->up_ticks = 0;

			ADC_Var->up_halfperiod_ok 	= 0;
			ADC_Var->down_halfperiod_ok	= 1;
		}
	}

}


void phase_delta_meter(ADC_analog_preparation *part_1, ADC_analog_preparation *part_2)
{

	float temp;

	if(!part_1->new_period_ticks)
	{

		if(part_1->val_max > 1000)
		{
			part_1->frequency_input = part_1->period_ticks;			// Число тиков за период
			part_1->frequency_input /= 10000;						// частота выборки АЦП
			part_1->frequency_input = 1 / part_1->frequency_input;	// частота в Герцах

			part_1->freq_filter.value_input = part_1->frequency_input;
			Z_filter(&part_1->freq_filter);
		}
		else
		{part_1->frequency_input = 0;}

		if((part_1->val_max > 200) & (part_2->val_max > 10))
		{

			temp = part_2->Phase_delay_ticks_photo_out - part_1->Phase_delay_ticks_photo_out;
			if(temp > (part_1->period_ticks / 2)){temp = temp - part_1->period_ticks;}
			temp *= (36 / (1000 / part_1->freq_filter.value));

			temp = (temp * 0.7) + 62.1;
			if((temp < 10) |(temp >  80)){temp = 80;}

			part_1->phase_filter.value_input = temp;
			Z_filter(&part_1->phase_filter);

		}
		else
		{

			part_1->phase_filter.value_input = 0;
			Z_filter(&part_1->phase_filter);

		}

	}

	part_1->phase_delta = part_1->phase_filter.value;

}

void MAX(uint32_t pointer, uint32_t Val1_p, uint32_t Val2_p, uint32_t Val3_p)
{
	float Val1;
	memcpy(&Val1, Val1_p, 4);
	float Val2;
	memcpy(&Val2, Val2_p, 4);
	float Val3;
	memcpy(&Val3, Val3_p, 4);

	float tempvar = Val1;
	if(Val2 > tempvar){tempvar = Val2;}
	if(Val3 > tempvar){tempvar = Val3;}
	memcpy(pointer, &tempvar, 4);
}

void MIN(uint32_t pointer, uint32_t Val1_p, uint32_t Val2_p, uint32_t Val3_p)
{
	float Val1;
	memcpy(&Val1, Val1_p, 4);
	float Val2;
	memcpy(&Val2, Val2_p, 4);
	float Val3;
	memcpy(&Val3, Val3_p, 4);

	float tempvar = Val1;
	if(Val2 < tempvar){tempvar = Val2;}
	if(Val3 < tempvar){tempvar = Val3;}
	memcpy(pointer, &tempvar, 4);
}

void Power_meter(ADC_analog_preparation *part_1, ADC_analog_preparation *part_2)
{
	part_1->momentary_power_integral += part_1->momentary_HalfReal * part_2->momentary_HalfReal;	// приращение интеграла
	part_1->Power_Full_ADC = ((part_1->val_max / 2) * (part_2->val_max / 2)) / 1.414213562373095;	// среднеквадратичная мощность
}
