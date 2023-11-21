/*
 * ADC_functions.c
 *
 *  Created on: 4 февр. 2021 г.
 *      Author: Motor
 */
#include "stm32f4xx.h"
#include "data_types.h"

void ADC_preparation_simple(ADC_analog_preparation *ADC_Var);
void ADC_preparation(ADC_analog_preparation *ADC_Var);
void ADC_deafult(ADC_analog_preparation *ADC_Var);
void ADC_Float_USR(ADC_Float_massive *massive);
void Float_Approx(Approx *DB);
void Float_Approx_X6(Approx_X6 *DB);
void Channel_Reset(ADC_analog_preparation *ADC_Var);
void Channel_Conservate(ADC_analog_preparation *ADC_Var);
void Power_meter(ADC_analog_preparation *part_1, ADC_analog_preparation *part_2);
void phase_delta_meter(ADC_analog_preparation *part_1, ADC_analog_preparation *part_2);


void Z_filter(Z_filter_DB *filter);

void MAX(uint32_t pointer, uint32_t Val1, uint32_t Val2, uint32_t Val3);
