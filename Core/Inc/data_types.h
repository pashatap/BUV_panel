#include "stm32f4xx.h"


typedef struct
{
	uint8_t ESC;
	uint8_t ENT;
	uint8_t Right;
	uint8_t Left;
	uint8_t Down;
	uint8_t Up;
	uint8_t PressDown;
	uint8_t AHH3_Stop;
	uint8_t AutoPusk;
	uint8_t AutoStop;
	uint8_t AHH1_Stop;
	uint8_t AHH2_Stop;
	uint8_t PressUp;
	uint8_t AHH3_Pusk;
	uint8_t AHH2_Pusk;
	uint8_t AHH1_Pusk;
} keyboard;


typedef struct
{

	int32_t  RS485_ADDR;
	int32_t  RS485_Speed;
	int32_t  RS485_Stops;
	int32_t  RS485_Parity;

	uint8_t  FlashWriteFlag;

	int32_t  brightness_disp;
	int32_t  brightness_clav;
	int32_t  pump_mode;




} Settings;


typedef struct
{

	int16_t MenuPointer;
	int16_t RazrPointer;

	int16_t MenuPointerMAX;
	int16_t RazrPointerMAX;

	uint32_t VauePointer;

	int32_t  ValueMax;
	int32_t  ValueMin;

} InterfaceControlDB;

typedef struct
{

	int32_t Number_M;
	int16_t pointer;
	int16_t pointer_M;
	int16_t pointerMax;
	int16_t Symbols[10];
	int16_t Len;
	uint8_t x;
	uint8_t y;

	uint32_t Change_pointer;

	int32_t Max;
	int32_t Min;

	char Space_Symbol;

} ChahgeBlockDB;




typedef struct
{

	int32_t PassWord;
	int32_t PassWord_true;
	int32_t PassFalseTimer;

} PassWords;


























typedef struct
{

	uint8_t pointer;   		// указатель строки массива
	float massive[50];   	// массив предыдущих результатов
	float result;
	float InValue;
	float InValue_old;		// контроль изменения

	float allowance;		// допуск отклонения

} ADC_Float_massive;



typedef struct
{

	int32_t Inom;  			// Номинальный ток
	int32_t KZkrat;   		// Кратность тока КЗ

	int32_t Krut;  			// Крутизна хар-ки (*e^чётотам)

	int32_t Tpusk; 			// Время не чувствительности при пуске

	int32_t Perekos_active; // вкл/откл защиты по перекосу фаз
	int32_t Dop_perekos;	// допустимый перекос фаз
	int32_t Tperekos; 		// Время перекоса

	int32_t Relay_control;  // тип срабатывания выходных реле

} ProtectionCurrentDB;

typedef struct
{

	uint8_t ALARM;

	uint8_t Obriv;
	uint8_t KZ;

} OtherProtection;



typedef struct
{

	float InValue;
	float OutValue;

	double kX4;
	double kX3;
	double kX2;
	double kX1;
	double k;

} Approx;


typedef struct
{

	float InValue;
	float OutValue;

	double kX6;
	double kX5;
	double kX4;
	double kX3;
	double kX2;
	double kX1;
	double k;

} Approx_X6;


typedef struct
{
	float value_input;

	float value;

	float value_old;
	float value_input_old;

	float filter_coeff;

} Z_filter_DB;



typedef struct
{

	int16_t momentary_RAW; 	// Мгновенное   значение
	float  momentary;     	// Мгновенное   значение фильтрованное
	float  deafult;       	// Значение при нуле на входе
	float  high;
	float  low;
	float  high_;			// Максимальное значение
	float  low_;			// Минимальное  значение
	float  high_max;
	float  low_max;

	float  momentary_lock;

	float  Value_fast;
	float  Value_slow;
	float  Value;

	float input;
	float input_old;
	float momentary_old;

	int16_t ADC_max;
	int16_t ADC_min;

	float filter_coeff;




	// Для измерения частоты
	int16_t up_ticks;
	int16_t up_ticks_result;
	int16_t down_ticks;
	int16_t down_ticks_result;

	float frequency;
	float frequency_input;

	Z_filter_DB freq_filter;

	int16_t new_period_ticks;
	int16_t period_ticks;

	float phase_delta;
	Z_filter_DB phase_filter;

	float val_max;				// Выходное значение
	float val_max_temp;

	Z_filter_DB Default_Level;

	int16_t Phase_delay_ticks_photo;
	int16_t Phase_delay_ticks_photo_out;
	int8_t  Phase_number;

	float momentary_HalfReal;
	float momentary_power_integral;
	float Power_active_ADC;
	float Power_Full_ADC;

	int8_t up_halfperiod_ok;
	int8_t down_halfperiod_ok;

	uint8_t  Virtual_bit;

} ADC_analog_preparation;


typedef struct
{
	uint8_t Bit;
	uint8_t Active_flag;


	int32_t I_A_counter_up;
	int32_t I_A_counter_down;

	int32_t I_A_counter_up_save;
	int32_t I_A_counter_down_save;

	int32_t I_A_counter_up_save_mirror;
	int32_t I_A_counter_down_save_mirror;

	int32_t Period;

	float frequency;

	float ADC_speed;

	int32_t Voltage_ticks;

	float Rads;  // Угол в радианах
	float CosFi; // консинус угла

	Z_filter_DB RadsFilter;

} PhaseMeter_DB;


