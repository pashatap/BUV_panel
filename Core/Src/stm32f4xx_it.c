/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    stm32f4xx_it.c
  * @brief   Interrupt Service Routines.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stm32f4xx_it.h"
/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "MB_Slave_Lib.h"
#include "data_types.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN TD */

/* USER CODE END TD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */
keyboard KeysRetain;
keyboard KeysFlash;
keyboard KeysMirror;
/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN PV */
extern UART_Slave_DB Slave_1;
extern uint32_t timer;

extern uint8_t screen;
extern uint8_t screen_mirror;
extern uint8_t screen_event;



uint8_t screen_save = 1;

extern uint8_t PWM_launch;

extern Settings_panel Settings_DB;

extern InterfaceControlDB Control_DB;

extern PassWords PassW_block;

extern Algorithm_variables ALG_DB;

extern uint32_t brightness_disp;
extern uint32_t brightness_clav;

extern Settings_Station BUV_settings_global;

extern BUV_realtime_vars BUV_RT_VALS;


uint32_t timer_1;
uint32_t timer_2;

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/* External variables --------------------------------------------------------*/
extern TIM_HandleTypeDef htim5;
extern UART_HandleTypeDef huart7;
/* USER CODE BEGIN EV */

/* USER CODE END EV */

/******************************************************************************/
/*           Cortex-M4 Processor Interruption and Exception Handlers          */
/******************************************************************************/
/**
  * @brief This function handles Non maskable interrupt.
  */
void NMI_Handler(void)
{
  /* USER CODE BEGIN NonMaskableInt_IRQn 0 */

  /* USER CODE END NonMaskableInt_IRQn 0 */
  /* USER CODE BEGIN NonMaskableInt_IRQn 1 */
  while (1)
  {
  }
  /* USER CODE END NonMaskableInt_IRQn 1 */
}

/**
  * @brief This function handles Hard fault interrupt.
  */
void HardFault_Handler(void)
{
  /* USER CODE BEGIN HardFault_IRQn 0 */

  /* USER CODE END HardFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_HardFault_IRQn 0 */
    /* USER CODE END W1_HardFault_IRQn 0 */
  }
}

/**
  * @brief This function handles Memory management fault.
  */
void MemManage_Handler(void)
{
  /* USER CODE BEGIN MemoryManagement_IRQn 0 */

  /* USER CODE END MemoryManagement_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_MemoryManagement_IRQn 0 */
    /* USER CODE END W1_MemoryManagement_IRQn 0 */
  }
}

/**
  * @brief This function handles Pre-fetch fault, memory access fault.
  */
void BusFault_Handler(void)
{
  /* USER CODE BEGIN BusFault_IRQn 0 */

  /* USER CODE END BusFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_BusFault_IRQn 0 */
    /* USER CODE END W1_BusFault_IRQn 0 */
  }
}

/**
  * @brief This function handles Undefined instruction or illegal state.
  */
void UsageFault_Handler(void)
{
  /* USER CODE BEGIN UsageFault_IRQn 0 */

  /* USER CODE END UsageFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_UsageFault_IRQn 0 */
    /* USER CODE END W1_UsageFault_IRQn 0 */
  }
}

/**
  * @brief This function handles System service call via SWI instruction.
  */
void SVC_Handler(void)
{
  /* USER CODE BEGIN SVCall_IRQn 0 */

  /* USER CODE END SVCall_IRQn 0 */
  /* USER CODE BEGIN SVCall_IRQn 1 */

  /* USER CODE END SVCall_IRQn 1 */
}

/**
  * @brief This function handles Debug monitor.
  */
void DebugMon_Handler(void)
{
  /* USER CODE BEGIN DebugMonitor_IRQn 0 */

  /* USER CODE END DebugMonitor_IRQn 0 */
  /* USER CODE BEGIN DebugMonitor_IRQn 1 */

  /* USER CODE END DebugMonitor_IRQn 1 */
}

/**
  * @brief This function handles Pendable request for system service.
  */
void PendSV_Handler(void)
{
  /* USER CODE BEGIN PendSV_IRQn 0 */

  /* USER CODE END PendSV_IRQn 0 */
  /* USER CODE BEGIN PendSV_IRQn 1 */

  /* USER CODE END PendSV_IRQn 1 */
}

/**
  * @brief This function handles System tick timer.
  */
void SysTick_Handler(void)
{
  /* USER CODE BEGIN SysTick_IRQn 0 */

	timer_1++;

	if(PassW_block.PassFalseTimer){PassW_block.PassFalseTimer--;}

	if(PWM_launch)
	{
		if(brightness_disp < 10000){brightness_disp += 1;}
		if(brightness_clav < 10000){brightness_clav += 1;}
	}

	TimedBitValue_handler(&ALG_DB.clearing_pressure_filter_1);
	TimedBitValue_handler(&ALG_DB.clearing_pressure_filter_2);
	TimedBitValue_handler(&ALG_DB.clearing_water_filter_1);
	TimedBitValue_handler(&ALG_DB.clearing_water_filter_2);
	TimedBitValue_handler(&ALG_DB.clearing_water_filter_3);

	KeyboardCheck();

	KeyboardWork();

  /* USER CODE END SysTick_IRQn 0 */
  HAL_IncTick();
  /* USER CODE BEGIN SysTick_IRQn 1 */

  /* USER CODE END SysTick_IRQn 1 */
}

/******************************************************************************/
/* STM32F4xx Peripheral Interrupt Handlers                                    */
/* Add here the Interrupt Handlers for the used peripherals.                  */
/* For the available peripheral interrupt handler names,                      */
/* please refer to the startup file (startup_stm32f4xx.s).                    */
/******************************************************************************/

/**
  * @brief This function handles TIM5 global interrupt.
  */
void TIM5_IRQHandler(void)
{
  /* USER CODE BEGIN TIM5_IRQn 0 */

	timer_2++;
	Slave_Clock_1ms(&Slave_1);

  /* USER CODE END TIM5_IRQn 0 */
  HAL_TIM_IRQHandler(&htim5);
  /* USER CODE BEGIN TIM5_IRQn 1 */

  /* USER CODE END TIM5_IRQn 1 */
}

/**
  * @brief This function handles UART7 global interrupt.
  */
void UART7_IRQHandler(void)
{
  /* USER CODE BEGIN UART7_IRQn 0 */

	  Slave_PORT_Processor(&Slave_1);

	  Slave_Processor(&Slave_1);

  /* USER CODE END UART7_IRQn 0 */
  HAL_UART_IRQHandler(&huart7);
  /* USER CODE BEGIN UART7_IRQn 1 */

  /* USER CODE END UART7_IRQn 1 */
}

/* USER CODE BEGIN 1 */

void KeyboardWork(void)
{

	uint8_t scr_plus  = 0;
	uint8_t scr_minus = 0;


	if(KeysRetain.Up & KeysRetain.Down)
	{
		screen 					= 21;
		Control_DB.MenuPointer  = 0;
		Control_DB.RazrPointer 	= 0;
	}
	if(KeysFlash.ESC & (screen < 5))
	{
		screen_save 	= screen;
		screen 			= 20;
		KeysFlash.ESC 	= 0;
	}
	if(KeysFlash.ESC & (screen == 20))
	{
		screen = screen_save;
		KeysFlash.ESC 	= 0;
	}
	if (KeysFlash.ESC & (screen == 8))
	{
		screen = 6;
		KeysFlash.ESC 	= 0;
	}
	if (KeysFlash.ESC & (screen == 9))
		{
			screen = 6;
			KeysFlash.ESC 	= 0;
		}
	if (KeysFlash.ESC & (screen == 14))
		{
			screen = 6;
			KeysFlash.ESC 	= 0;
		}
	if(KeysFlash.ESC & (((screen >= 5) & (screen <= 7)) | (screen == 21)))
	{
		screen 			= 1;
		screen_save 	= 1;
		Control_DB.RazrPointer 	= 0;
	}

	if(KeysFlash.Right)
	{
		if(Control_DB.RazrPointer)
		{
			Control_DB.RazrPointer--;
			if(Control_DB.RazrPointer == 0)
			{
				Control_DB.RazrPointer = Control_DB.RazrPointerMAX;
			}
		}
		else
		{
			scr_plus = 1;
		}
	}
	if(KeysFlash.Left)
	{
		if(Control_DB.RazrPointer)
		{
			Control_DB.RazrPointer++;
			if(Control_DB.RazrPointer > Control_DB.RazrPointerMAX)
			{
				Control_DB.RazrPointer = 1;
			}
		}
		else
		{
			scr_minus = 1;
		}
	}

	if(KeysFlash.ENT)
	{



		if(screen == 3)
		{

			if(PassW_block.DataClearingUnlock)
			{
				switch(Control_DB.MenuPointer)
				{
					case 1:
						BUV_RT_VALS.ANN_1.Pump.MotoClock = 0;
					break;
					case 2:
						BUV_RT_VALS.ANN_2.Pump.MotoClock = 0;
					break;
					case 3:
						BUV_RT_VALS.ANN_3.Pump.MotoClock = 0;
					break;
					case 4:
						BUV_RT_VALS.EMULSION_NODE.Pump_circulation.MotoClock = 0;
					break;
					case 5:
						BUV_RT_VALS.EMULSION_NODE.Pump_concentrate.MotoClock = 0;
					break;
					case 6:
						BUV_RT_VALS.EMULSION_NODE.Pump_concentrate_injection.MotoClock = 0;
					break;
					case 7:
						BUV_RT_VALS.ANN_1.Unload_counter = 0;
					break;
					case 8:
						BUV_RT_VALS.ANN_2.Unload_counter = 0;
					break;
					case 9:
						BUV_RT_VALS.ANN_3.Unload_counter = 0;
					break;
					case 10:
						BUV_RT_VALS.FILT_NODE.Flush_valve_1_counter = 0;
					break;
					case 11:
						BUV_RT_VALS.FILT_NODE.Flush_valve_2_counter = 0;
					break;
					case 12:
						BUV_RT_VALS.EMULSION_NODE.Filter_flow_valve_1_counter = 0;
					break;
					case 13:
						BUV_RT_VALS.EMULSION_NODE.Filter_flow_valve_2_counter = 0;
					break;
					case 14:
						BUV_RT_VALS.EMULSION_NODE.Filter_flow_valve_3_counter = 0;
					break;
					case 15:
						BUV_RT_VALS.FILT_NODE.Drain_filter_flowmeter.Volume = 0;
					break;
					case 16:
						BUV_RT_VALS.FILT_NODE.Emulsion_flowmeter.Volume = 0;
					break;
					case 17:
						BUV_RT_VALS.EMULSION_NODE.Flowmeter_concent.Volume = 0;
					break;
					case 18:
						BUV_RT_VALS.EMULSION_NODE.Flowmeter_water.Volume = 0;
					break;
					case 19:
						BUV_RT_VALS.EMULSION_NODE.Node_work_counter = 0;
					break;
				}
			}

			if(PassW_block.PassWord != PassW_block.PassWord_DATA)
			{
				PassW_block.PassWord = 0;
			}
			else
			{
				PassW_block.PassWord = 0;
				PassW_block.DataClearingUnlock = 1;
			}
		}

		if(screen == 4)
		{
			switch(Control_DB.MenuPointer)
			{
				case 0:
					ALG_DB.clearing_pressure_filter_1.state = 1;
				break;
				case 1:
					ALG_DB.clearing_pressure_filter_2.state = 1;
				break;
				case 2:
					ALG_DB.clearing_water_filter_1.state = 1;
				break;
				case 3:
					ALG_DB.clearing_water_filter_2.state = 1;
				break;
				case 4:
					ALG_DB.clearing_water_filter_3.state = 1;
				break;
			}
		}

		if(screen == 5)
		{
			if(PassW_block.PassWord != PassW_block.PassWord_true)
			{
				if(Control_DB.RazrPointer)
				{
					PassW_block.PassFalseTimer = 1000;
					PassW_block.PassWord       =    0;
				}
			}
			else
			{
				screen = 6; // переход после ввода правильного пароля
			}
		}

		if ((screen==6) & (Control_DB.MenuPointer == 7))
		{
				screen = 8;
		}
		if((screen == 6) &(Control_DB.MenuPointer == 8))
			{
				screen = 9;
			}
		if((screen == 6) &(Control_DB.MenuPointer == 14))
		{
			screen = 14;
		}


		if((screen == 7) & (Control_DB.MenuPointer == 4))
		{
			BUV_settings_global.work_on_water_enable = !BUV_settings_global.work_on_water_enable;
		}

		if ((screen==14)&(Control_DB.MenuPointer == 1))
		{
			screen =7;
		}
		if(Control_DB.RazrPointerMAX)
		{
			if(Control_DB.RazrPointer)
			{
				Control_DB.RazrPointer = 0;
			}
			else
			{
				if((screen == 3) | (screen == 5))
				{
					Control_DB.RazrPointer = 4;
				}
				else
				{
					Control_DB.RazrPointer = 1;
				}
			}
		}

		if((screen == 21) & (Control_DB.MenuPointer == 5))
		{
			Settings_DB.FlashWriteFlag = 1;
		}



	}

	if(KeysFlash.Down)
	{
		if(Control_DB.RazrPointer == 0)
		{
			Control_DB.MenuPointer++;
			if(Control_DB.MenuPointer > Control_DB.MenuPointerMAX){Control_DB.MenuPointer = 0;}
		}
		else
		{
			NumberChange(Control_DB.VauePointer, Control_DB.RazrPointer, Control_DB.RazrPointerMAX, 0, 1);
		}
	}
	if(KeysFlash.Up)
	{
		if(Control_DB.RazrPointer == 0)
		{
			Control_DB.MenuPointer--;
			if(Control_DB.MenuPointer < 0){Control_DB.MenuPointer = Control_DB.MenuPointerMAX;}
		}
		else
		{
			NumberChange(Control_DB.VauePointer, Control_DB.RazrPointer, Control_DB.RazrPointerMAX, 1, 0);
		}
	}


	if(screen <= 5)
	{
		if(scr_plus) {screen++;}
		if(scr_minus){screen--;}

		if(KeysFlash.Right | KeysFlash.Left)
		{
			if(screen > 5){screen = 1;}
			if(screen < 1){screen = 5;}
		}
	}

	if(screen != screen_mirror)
	{
		screen_mirror = screen;
		screen_event  = 1;
	}

	KeyboardClear();
}

void KeyboardCheck(void)
{

	KeysRetain.ESC 			= !HAL_GPIO_ReadPin( BUTTON_1_GPIO_Port,  BUTTON_1_Pin);
	KeysRetain.ENT 			= !HAL_GPIO_ReadPin( BUTTON_2_GPIO_Port,  BUTTON_2_Pin);
	KeysRetain.Right 		= !HAL_GPIO_ReadPin( BUTTON_3_GPIO_Port,  BUTTON_3_Pin);
	KeysRetain.Left 		= !HAL_GPIO_ReadPin( BUTTON_4_GPIO_Port,  BUTTON_4_Pin);
	KeysRetain.Down 		= !HAL_GPIO_ReadPin( BUTTON_5_GPIO_Port,  BUTTON_5_Pin);
	KeysRetain.Up 			= !HAL_GPIO_ReadPin( BUTTON_6_GPIO_Port,  BUTTON_6_Pin);
	KeysRetain.PressDown 	= !HAL_GPIO_ReadPin( BUTTON_7_GPIO_Port,  BUTTON_7_Pin);
	KeysRetain.AHH3_Stop 	= !HAL_GPIO_ReadPin( BUTTON_8_GPIO_Port,  BUTTON_8_Pin);
	KeysRetain.AutoPusk 	= !HAL_GPIO_ReadPin( BUTTON_9_GPIO_Port,  BUTTON_9_Pin);
	KeysRetain.AutoStop 	= !HAL_GPIO_ReadPin(BUTTON_10_GPIO_Port, BUTTON_10_Pin);
	KeysRetain.AHH1_Stop 	= !HAL_GPIO_ReadPin(BUTTON_11_GPIO_Port, BUTTON_11_Pin);
	KeysRetain.AHH2_Stop 	= !HAL_GPIO_ReadPin(BUTTON_12_GPIO_Port, BUTTON_12_Pin);
	KeysRetain.PressUp 		= !HAL_GPIO_ReadPin(BUTTON_13_GPIO_Port, BUTTON_13_Pin);
	KeysRetain.AHH3_Pusk 	= !HAL_GPIO_ReadPin(BUTTON_14_GPIO_Port, BUTTON_14_Pin);
	KeysRetain.AHH2_Pusk 	= !HAL_GPIO_ReadPin(BUTTON_15_GPIO_Port, BUTTON_15_Pin);
	KeysRetain.AHH1_Pusk 	= !HAL_GPIO_ReadPin(BUTTON_16_GPIO_Port, BUTTON_16_Pin);

	if(KeysRetain.ESC 		& !KeysMirror.ESC)			{KeysFlash.ESC 			= 1;}
	if(KeysRetain.ENT 		& !KeysMirror.ENT)			{KeysFlash.ENT 			= 1;}
	if(KeysRetain.Right 	& !KeysMirror.Right)		{KeysFlash.Right 		= 1;}
	if(KeysRetain.Left 		& !KeysMirror.Left)			{KeysFlash.Left 		= 1;}
	if(KeysRetain.Down 		& !KeysMirror.Down)			{KeysFlash.Down 		= 1;}
	if(KeysRetain.Up 		& !KeysMirror.Up)			{KeysFlash.Up 			= 1;}
	if(KeysRetain.PressDown & !KeysMirror.PressDown)	{KeysFlash.PressDown 	= 1;}
	if(KeysRetain.AHH3_Stop & !KeysMirror.AHH3_Stop)	{KeysFlash.AHH3_Stop 	= 1;}
	if(KeysRetain.AutoPusk 	& !KeysMirror.AutoPusk)		{KeysFlash.AutoPusk 	= 1;}
	if(KeysRetain.AutoStop 	& !KeysMirror.AutoStop)		{KeysFlash.AutoStop 	= 1;}
	if(KeysRetain.AHH1_Stop & !KeysMirror.AHH1_Stop)	{KeysFlash.AHH1_Stop 	= 1;}
	if(KeysRetain.AHH2_Stop & !KeysMirror.AHH2_Stop)	{KeysFlash.AHH2_Stop 	= 1;}
	if(KeysRetain.PressUp 	& !KeysMirror.PressUp)		{KeysFlash.PressUp 		= 1;}
	if(KeysRetain.AHH3_Pusk & !KeysMirror.AHH3_Pusk)	{KeysFlash.AHH3_Pusk 	= 1;}
	if(KeysRetain.AHH2_Pusk & !KeysMirror.AHH2_Pusk)	{KeysFlash.AHH2_Pusk 	= 1;}
	if(KeysRetain.AHH1_Pusk & !KeysMirror.AHH1_Pusk)	{KeysFlash.AHH1_Pusk 	= 1;}

	KeysMirror.ESC 			= KeysRetain.ESC;
	KeysMirror.ENT 			= KeysRetain.ENT;
	KeysMirror.Right 		= KeysRetain.Right;
	KeysMirror.Left 		= KeysRetain.Left;
	KeysMirror.Down 		= KeysRetain.Down;
	KeysMirror.Up 			= KeysRetain.Up;
	KeysMirror.PressDown 	= KeysRetain.PressDown;
	KeysMirror.AHH3_Stop 	= KeysRetain.AHH3_Stop;
	KeysMirror.AutoPusk 	= KeysRetain.AutoPusk;
	KeysMirror.AutoStop 	= KeysRetain.AutoStop;
	KeysMirror.AHH1_Stop 	= KeysRetain.AHH1_Stop;
	KeysMirror.AHH2_Stop 	= KeysRetain.AHH2_Stop;
	KeysMirror.PressUp 		= KeysRetain.PressUp;
	KeysMirror.AHH3_Pusk 	= KeysRetain.AHH3_Pusk;
	KeysMirror.AHH2_Pusk 	= KeysRetain.AHH2_Pusk;
	KeysMirror.AHH1_Pusk 	= KeysRetain.AHH1_Pusk;

}

void KeyboardClear(void)
{
	KeysFlash.ESC 			= 0;
	KeysFlash.ENT 			= 0;
	KeysFlash.Right 		= 0;
	KeysFlash.Left 			= 0;
	KeysFlash.Down 			= 0;
	KeysFlash.Up 			= 0;
	KeysFlash.PressDown 	= 0;
	KeysFlash.AHH3_Stop 	= 0;
	KeysFlash.AutoPusk 		= 0;
	KeysFlash.AutoStop 		= 0;
	KeysFlash.AHH1_Stop 	= 0;
	KeysFlash.AHH2_Stop 	= 0;
	KeysFlash.PressUp 		= 0;
	KeysFlash.AHH3_Pusk 	= 0;
	KeysFlash.AHH2_Pusk 	= 0;
	KeysFlash.AHH1_Pusk 	= 0;
}

/* USER CODE END 1 */
