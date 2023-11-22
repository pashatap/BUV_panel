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

} Settings_panel; // настройки которые задаются и сохраняются только в этой панели

typedef struct data_types
{
	uint8_t trigger;
	uint8_t trigger_mirror;
	uint8_t execute;
} background_zaliv;


typedef struct
{
//настройки станции насосной
	int32_t time_of_work_pump;
	int32_t pump_mode;
	int32_t flushing_filter;
	int32_t conc_emul;
	int32_t time_flushing;
	int32_t work_pump1;
	int32_t work_pump2;
	int32_t work_pump3;
	int32_t count_work_pump;
	int32_t work_auto_unload;
	int32_t min_level_emul;
	int32_t min_level_conc;
	int32_t min_level_emul_UP;
	int32_t max_level_emul_UP;
	int32_t flushing_mode_pressure_filter;
	int32_t period_flushing_pressure_filter;
	int32_t time_flushing_pressure_filter;
	int32_t difference_pressure_filter;
	int32_t time_control_pressure_filter;
	int32_t flushing_mode_water_filter;
	int32_t period_flushing_water_filter;
	int32_t time_flushing_water_filter;
	int32_t difference_water_filter;
	int32_t time_control_water_filter;

								//

	// Заводские настройки
	int32_t	Max_ANN_operation; 					// Макс насосов работающих одновременно
	int32_t	Max_Pressure;						// Максимальное давление которое можно выставить
	int32_t	Major_repear_period;				// Срок капитального ремонта (часов)
	int32_t	emulsion_off_level;					// Уровень эмульсии при котором отключается станция
	uint8_t	work_on_water_enable;   			// Работа на воде разрешена
	int32_t	water_work_conconcentrate_level;	// Настройка уровня концентрата при котором предупреждение что работаем на воде

} Settings_Station; // настройки для платы управления


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

	uint8_t state;
	uint8_t state_mirror;
	uint16_t timer;
	uint16_t default_timer;

} TimedBitValue;




typedef struct
{

	TimedBitValue clearing_pressure_filter_1;
	TimedBitValue clearing_pressure_filter_2;
	TimedBitValue clearing_water_filter_1;
	TimedBitValue clearing_water_filter_2;
	TimedBitValue clearing_water_filter_3;

} Algorithm_variables;


typedef struct
{
	int16_t Flow;		// мгновенный расход (0.1 л/мин)
	int32_t Volume;		// мгновенный расход (0.001  м3)
} FlowMeter; // переменные расходомера

typedef struct
{

	uint8_t State;							// Состояние (включен / выключен)
	uint8_t Bimetal;						// состояние тепловой бимет защиты 	(1-сработка)
	int32_t MotoClock;						// Моточасы

} engine; // переменные мотора

typedef struct
{

	engine Pump;

	int16_t Out_Pressure;					// Давление на напоре	(0.1  МПа)
	int16_t Oil_Pressure;					// Давление масла		(0.01 МПа)
	int16_t Oil_Temperature;				// Температура масла	(0.1 *С)

	uint8_t Unload;							// состояние клапана разгрузки 					(вкл/выкл)

	uint32_t Unload_counter;				// счётчик сработок автомата разгрузки

} ANN; // переменные агрегата насосного

typedef struct
{

	int16_t Out_Pressure;					// Давление в магистрали						(0.1  МПа)
	int16_t Pressure_before_press_filter;	// Давление перед сливным напорным фильтром		(0.1  МПа)
	int16_t Pressure_before_filter;			// Давление перед сливным фильтром				(0.1  МПа)
	int16_t Pressure_behind_filter;			// Давление за    сливным фильтром				(0.1  МПа)

	FlowMeter Drain_filter_flowmeter;		// Расходомер на сливном фильтре
	FlowMeter Emulsion_flowmeter;			// Расходомер эмульсии

	uint8_t Flush_valve_1;					// Клапан промывки 1
	uint8_t Flush_valve_2;					// Клапан промывки 2

	uint32_t Flush_valve_1_counter;			// Счётчик сработок клапана промывки 1
	uint32_t Flush_valve_2_counter;			// Счётчик сработок клапана промывки 2

} Filters_Node; // переменные узла фильтров

typedef struct
{

	engine Pump_circulation;				// Насос циркуляционный
	engine Pump_concentrate;				// Насос концентрата
	engine Pump_concentrate_injection;		// Насос закачки концентрата

	FlowMeter Flowmeter_water;				// Расходомер воды
	FlowMeter Flowmeter_concent;			// Расходомер концентрата

	int16_t Pressure_before_water_filters;	// Давление перед фильтрами воды 				(0.1  МПа)
	int16_t Pressure_behind_water_filters;	// Давление после фильтров  воды 				(0.1  МПа)

	uint8_t Filter_flow_valve_1;			// Клапан промывки фильтра 1
	uint8_t Filter_flow_valve_2;			// Клапан промывки фильтра 2
	uint8_t Filter_flow_valve_3;			// Клапан промывки фильтра 3

	uint32_t Filter_flow_valve_1_counter;	// Счётчик сработок клапана промывки фильтра 1
	uint32_t Filter_flow_valve_2_counter;	// Счётчик сработок клапана промывки фильтра 2
	uint32_t Filter_flow_valve_3_counter;	// Счётчик сработок клапана промывки фильтра 3

	uint8_t Water_valve;					// Клапан воды
	uint8_t Concentrate_valve;				// Клапан концентрата

	uint32_t Node_work_counter;				// Количество сработок блока приготовления эмульсии

} Emulsion_mixer;

typedef struct
{

	int16_t Ustauka; 				// Уставка давления текущая
	int16_t TANK_level; 			// Уровень 		в баке эмульсии
	int16_t TANK_temperature;		// Температура 	в баке

	ANN ANN_1;						// Переменные Агрегата 1
	ANN ANN_2;						// Переменные Агрегата 2
	ANN ANN_3;						// Переменные Агрегата 3

	Filters_Node FILT_NODE;			// Узел фильтров

	Emulsion_mixer EMULSION_NODE; 	// Устройство приготовления эмульсии (УПЭ)

} BUV_realtime_vars; // Блок переменных всего бува




typedef struct
{

	int32_t PassWord;
	int32_t PassWord_true;
	int32_t PassFalseTimer;

	int32_t PassWord_DATA;
	uint8_t DataClearingUnlock;

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


