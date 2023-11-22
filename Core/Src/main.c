/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
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

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "MB_Slave_Lib.h"
#include "data_types.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
DMA2D_HandleTypeDef hdma2d;

LTDC_HandleTypeDef hltdc;

SPI_HandleTypeDef hspi1;

TIM_HandleTypeDef htim4;
TIM_HandleTypeDef htim5;

UART_HandleTypeDef huart7;

SDRAM_HandleTypeDef hsdram1;

/* USER CODE BEGIN PV */

extern keyboard KeysRetain;
extern keyboard KeysFlash;
extern keyboard KeysMirror;

uint32_t brightness_disp = 0;
uint32_t brightness_clav = 0;

__IO UART_Slave_DB Slave_1;
FMC_SDRAM_CommandTypeDef command;

uint32_t TEXT_PageADDR;

uint32_t timer 				= 0;
uint8_t  iterator 			= 0;
uint8_t  iterator_mirror 	= 0;

uint8_t Page_number 		= 0;
uint8_t Page_write  		= 0;
uint8_t Flash_erase 		= 0;


uint8_t Page_loag			= 0;
uint8_t Page_zaliv			= 0;

int flash_i = 0;

SPI_IO SPI_TX;
SPI_IO SPI_RX;

uint32_t Page[29];//набор страниц для отображения на экране

	 uint32_t Page_write_addr  	= 0x080E6C00;
__IO uint32_t RedColor 			= 0xFF4500;
__IO uint32_t YellowColor 		= 0xFFFF00;
__IO uint32_t GreenColor 		= 0x00FF00;
__IO uint32_t BackgroundColor 	= 0x7092BE;
__IO uint32_t GrayColor 		= 0x858585;

uint32_t BasicSymbolColor 		= 0x000000;
uint32_t SelectionColor 		= 0x00B400;
uint32_t RasrPointerColor 		= 0xFF0000;



int16_t Val3 = 12345;

uint8_t screen			= 1;
uint8_t screen_mirror	= 1;
uint8_t screen_event	= 0;



uint8_t PWM_launch = 0;

PassWords PassW_block = {0};

Algorithm_variables ALG_DB = {0};

Settings_Station BUV_settings_global = {0};

BUV_realtime_vars BUV_RT_VALS = {0};

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_DMA2D_Init(void);
static void MX_FMC_Init(void);
static void MX_LTDC_Init(void);
static void MX_SPI1_Init(void);
static void MX_UART7_Init(void);
static void MX_TIM4_Init(void);
static void MX_TIM5_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
Settings_panel 		Settings_DB;
InterfaceControlDB 	Control_DB;
Settings_Station	BUV_settings;
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

	PassW_block.PassWord 		=    0;
	PassW_block.PassWord_true 	= 1234;
	PassW_block.PassWord_DATA   = 3850;
  BUV_settings.time_of_work_pump = 5;
  BUV_settings.flushing_filter = 1;
  BUV_settings.conc_emul = 15;
  BUV_settings.pump_mode = 1;
  BUV_settings.time_flushing = 2;
  BUV_settings.work_pump1 = 1;
  BUV_settings.work_pump2 = 1;
  BUV_settings.work_pump3 = 1;
  BUV_settings.count_work_pump = 1;
  BUV_settings.work_auto_unload = 1;
  BUV_settings.min_level_emul = 50;
  BUV_settings.min_level_conc = 10;
  BUV_settings.min_level_emul_UP = 50;
  BUV_settings.max_level_emul_UP = 50;
  BUV_settings.flushing_mode_pressure_filter = 1;
  BUV_settings.period_flushing_pressure_filter = 10;
  BUV_settings.time_flushing_pressure_filter = 2;
  BUV_settings.difference_pressure_filter = 02;
  BUV_settings.time_control_pressure_filter = 3;
  BUV_settings.flushing_mode_water_filter = 1;
  BUV_settings.period_flushing_water_filter = 10;
  BUV_settings.time_flushing_water_filter = 2;
  BUV_settings.difference_water_filter = 02;
  BUV_settings.time_control_water_filter = 3;


	memcpy(&Settings_DB, 0x08060000, sizeof(Settings_DB)); // чтение настроек с флеш
	Settings_DB.FlashWriteFlag	 = 0;
	Settings_DB.RS485_Parity	 = 0;

	if(Settings_DB.RS485_ADDR == -1)
	{
		Settings_DB.RS485_ADDR  = 1;
		Settings_DB.RS485_Speed = 115200;
		Settings_DB.RS485_Stops = 1;
		Settings_DB.brightness_disp = 100;
		Settings_DB.brightness_clav = 100;
	}

	Slave_1.PORT    		= UART7_BASE;
	Slave_1.MB_Addr 		= Settings_DB.RS485_ADDR;
	Slave_1.Roll_max 		= 0;
	Slave_1.Transmit_delay 	= 2;
  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_DMA2D_Init();
  MX_FMC_Init();
  MX_LTDC_Init();
  MX_SPI1_Init();
  MX_UART7_Init();
  MX_TIM4_Init();
  MX_TIM5_Init();
  /* USER CODE BEGIN 2 */





	TIM4->CCR3 = 0;
	TIM4->CCR4 = 0;

	HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_3);
	HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_4);


	BSP_SDRAM_Initialization_Sequence(&hsdram1, &command);

	HAL_DMA2D_ConfigDeadTime(&hdma2d, 100);
	HAL_DMA2D_EnableDeadTime(&hdma2d);

	Page[0] = SDRAM_BANK_ADDR;
	for(int i = 1; i < 29; i++)
	{
		Page[i] = Page[i-1] + (800*480*3);
	}

	Screens_init();
	HAL_GPIO_WritePin(LTDC_DISP_GPIO_Port, LTDC_DISP_Pin, GPIO_PIN_SET);
	PWM_launch = 1;


	screen = 1;


	HAL_TIM_Base_Start_IT(&htim5);






	ALG_DB.clearing_pressure_filter_1.default_timer = 1000;
	ALG_DB.clearing_pressure_filter_2.default_timer = 1000;
	ALG_DB.clearing_water_filter_1.default_timer	= 1000;
	ALG_DB.clearing_water_filter_2.default_timer	= 1000;
	ALG_DB.clearing_water_filter_3.default_timer	= 1000;


  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {

	if(PWM_launch)
	{
		float temp  = brightness_disp;
		float temp2 = Settings_DB.brightness_disp;
		temp2 /= 100;
		temp *= temp2;
		TIM4->CCR3 = temp;

		temp  = brightness_clav;
		temp2 = Settings_DB.brightness_clav;
		temp2 /= 100;
		temp *= temp2;
		TIM4->CCR4 = temp;
	} // работа с подсветкой

	if(Settings_DB.FlashWriteFlag)
	{

		__disable_irq (); // запретить прерывания

		HAL_FLASH_Unlock();

		FLASH_Erase_Sector(FLASH_SECTOR_7, FLASH_VOLTAGE_RANGE_1); // стирание сектора 7 (0x08060000)

		while(FLASH->SR & 0x01){;} // Ждем пока снимется флаг BSY=

		uint8_t massive[sizeof(Settings_DB)];
		memcpy(&massive, &Settings_DB, sizeof(Settings_DB));

		for(flash_i = 0; flash_i < sizeof(Settings_DB); flash_i++)
		{
			HAL_FLASH_Program(FLASH_TYPEPROGRAM_BYTE, 0x08060000 + flash_i, massive[flash_i]);
		}

		HAL_FLASH_Lock();
		__enable_irq ();  // разрешить прерывания

		MX_UART7_Init();

		screen 						= 1;
		Control_DB.MenuPointer 		= 0;
		Settings_DB.FlashWriteFlag 	= 0;
		Control_DB.RazrPointer      = 0;
		Slave_1.MB_Addr 			= Settings_DB.RS485_ADDR;

	} // перепись настроек flash

	Set_Screen(screen);










	/*
	if(Flash_erase)
	{
		Flash_Erase();
		Flash_erase = 0;
		memcpy(Page[0], Page_write_addr, 800*480*3);
	}



	if(Page_write)
	{
		for(uint32_t i = 0; i < 800 * 480 * 3;)
		{
			SPI_TX.Addres = i;
			memcpy(&SPI_TX.buff, Page[0] + i, 256);
			SPI_transmit_256(&SPI_TX);
			i += 256;
		}

		Page_write = 0;

		for(uint32_t i = 0; i < 800 * 480 * 3;)
		{
			SPI_RX.Addres = i;
			SPI_recieve_256(&SPI_RX);
			memcpy(Page[0] + i, &SPI_RX.buff, 256);
			i += 256;
		}
	}


	if(Page_loag)
	{

		for(uint32_t i = 0; i < 800 * 480 * 3;)
		{
			SPI_RX.Addres = i;
			SPI_recieve_256(&SPI_RX);
			memcpy(Page[0] + i, &SPI_RX.buff, 256);
			i += 256;
		}

		Page_loag = 0;
	}

	if(Page_zaliv)
	{
		Zaliv(0x000000, Page[0], 800, 480);

		Page_zaliv = 0;
	}
	*/

    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 4;
  RCC_OscInitStruct.PLL.PLLN = 180;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 4;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Activate the Over-Drive mode
  */
  if (HAL_PWREx_EnableOverDrive() != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief DMA2D Initialization Function
  * @param None
  * @retval None
  */
static void MX_DMA2D_Init(void)
{

  /* USER CODE BEGIN DMA2D_Init 0 */

  /* USER CODE END DMA2D_Init 0 */

  /* USER CODE BEGIN DMA2D_Init 1 */

  /* USER CODE END DMA2D_Init 1 */
  hdma2d.Instance = DMA2D;
  hdma2d.Init.Mode = DMA2D_M2M;
  hdma2d.Init.ColorMode = DMA2D_OUTPUT_RGB888;
  hdma2d.Init.OutputOffset = 0;
  hdma2d.LayerCfg[1].InputOffset = 0;
  hdma2d.LayerCfg[1].InputColorMode = DMA2D_INPUT_RGB888;
  hdma2d.LayerCfg[1].AlphaMode = DMA2D_NO_MODIF_ALPHA;
  hdma2d.LayerCfg[1].InputAlpha = 0;
  if (HAL_DMA2D_Init(&hdma2d) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_DMA2D_ConfigLayer(&hdma2d, 1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN DMA2D_Init 2 */

  /* USER CODE END DMA2D_Init 2 */

}

/**
  * @brief LTDC Initialization Function
  * @param None
  * @retval None
  */
static void MX_LTDC_Init(void)
{

  /* USER CODE BEGIN LTDC_Init 0 */

  /* USER CODE END LTDC_Init 0 */

  LTDC_LayerCfgTypeDef pLayerCfg = {0};

  /* USER CODE BEGIN LTDC_Init 1 */

  /* USER CODE END LTDC_Init 1 */
  hltdc.Instance = LTDC;
  hltdc.Init.HSPolarity = LTDC_HSPOLARITY_AL;
  hltdc.Init.VSPolarity = LTDC_VSPOLARITY_AL;
  hltdc.Init.DEPolarity = LTDC_DEPOLARITY_AL;
  hltdc.Init.PCPolarity = LTDC_PCPOLARITY_IPC;
  hltdc.Init.HorizontalSync = 47;
  hltdc.Init.VerticalSync = 0;
  hltdc.Init.AccumulatedHBP = 87;
  hltdc.Init.AccumulatedVBP = 31;
  hltdc.Init.AccumulatedActiveW = 887;
  hltdc.Init.AccumulatedActiveH = 511;
  hltdc.Init.TotalWidth = 927;
  hltdc.Init.TotalHeigh = 524;
  hltdc.Init.Backcolor.Blue = 0;
  hltdc.Init.Backcolor.Green = 0;
  hltdc.Init.Backcolor.Red = 0;
  if (HAL_LTDC_Init(&hltdc) != HAL_OK)
  {
    Error_Handler();
  }
  pLayerCfg.WindowX0 = 0;
  pLayerCfg.WindowX1 = 800;
  pLayerCfg.WindowY0 = 0;
  pLayerCfg.WindowY1 = 480;
  pLayerCfg.PixelFormat = LTDC_PIXEL_FORMAT_RGB888;
  pLayerCfg.Alpha = 255;
  pLayerCfg.Alpha0 = 0;
  pLayerCfg.BlendingFactor1 = LTDC_BLENDING_FACTOR1_PAxCA;
  pLayerCfg.BlendingFactor2 = LTDC_BLENDING_FACTOR2_PAxCA;
  pLayerCfg.FBStartAdress = 0xC0000000;
  pLayerCfg.ImageWidth = 800;
  pLayerCfg.ImageHeight = 480;
  pLayerCfg.Backcolor.Blue = 0;
  pLayerCfg.Backcolor.Green = 0;
  pLayerCfg.Backcolor.Red = 0;
  if (HAL_LTDC_ConfigLayer(&hltdc, &pLayerCfg, 0) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN LTDC_Init 2 */

  /* USER CODE END LTDC_Init 2 */

}

/**
  * @brief SPI1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_SPI1_Init(void)
{

  /* USER CODE BEGIN SPI1_Init 0 */

  /* USER CODE END SPI1_Init 0 */

  /* USER CODE BEGIN SPI1_Init 1 */

  /* USER CODE END SPI1_Init 1 */
  /* SPI1 parameter configuration*/
  hspi1.Instance = SPI1;
  hspi1.Init.Mode = SPI_MODE_MASTER;
  hspi1.Init.Direction = SPI_DIRECTION_2LINES;
  hspi1.Init.DataSize = SPI_DATASIZE_8BIT;
  hspi1.Init.CLKPolarity = SPI_POLARITY_LOW;
  hspi1.Init.CLKPhase = SPI_PHASE_1EDGE;
  hspi1.Init.NSS = SPI_NSS_SOFT;
  hspi1.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_16;
  hspi1.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi1.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi1.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi1.Init.CRCPolynomial = 10;
  if (HAL_SPI_Init(&hspi1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN SPI1_Init 2 */

  /* USER CODE END SPI1_Init 2 */

}

/**
  * @brief TIM4 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM4_Init(void)
{

  /* USER CODE BEGIN TIM4_Init 0 */

  /* USER CODE END TIM4_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};
  TIM_OC_InitTypeDef sConfigOC = {0};

  /* USER CODE BEGIN TIM4_Init 1 */

  /* USER CODE END TIM4_Init 1 */
  htim4.Instance = TIM4;
  htim4.Init.Prescaler = 0;
  htim4.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim4.Init.Period = 10000;
  htim4.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim4.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim4) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim4, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_PWM_Init(&htim4) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim4, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigOC.OCMode = TIM_OCMODE_PWM1;
  sConfigOC.Pulse = 0;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
  if (HAL_TIM_PWM_ConfigChannel(&htim4, &sConfigOC, TIM_CHANNEL_3) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_PWM_ConfigChannel(&htim4, &sConfigOC, TIM_CHANNEL_4) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM4_Init 2 */

  /* USER CODE END TIM4_Init 2 */
  HAL_TIM_MspPostInit(&htim4);

}

/**
  * @brief TIM5 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM5_Init(void)
{

  /* USER CODE BEGIN TIM5_Init 0 */

  /* USER CODE END TIM5_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM5_Init 1 */

  /* USER CODE END TIM5_Init 1 */
  htim5.Instance = TIM5;
  htim5.Init.Prescaler = 0;
  htim5.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim5.Init.Period = 90000;
  htim5.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim5.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;
  if (HAL_TIM_Base_Init(&htim5) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim5, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim5, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM5_Init 2 */

  /* USER CODE END TIM5_Init 2 */

}

/**
  * @brief UART7 Initialization Function
  * @param None
  * @retval None
  */
static void MX_UART7_Init(void)
{

  /* USER CODE BEGIN UART7_Init 0 */

	/*
	 *
  huart7.Instance = UART7;

  huart7.Init.BaudRate = Settings_DB.RS485_Speed;

  if(Settings_DB.RS485_Parity)
  {
	  huart7.Init.WordLength = UART_WORDLENGTH_9B;
  }
  else
  {
	  huart7.Init.WordLength = UART_WORDLENGTH_8B;
  }

  if(Settings_DB.RS485_Stops == 1)
  {
	  huart7.Init.StopBits = UART_STOPBITS_1;
  }
  else
  {
	  huart7.Init.StopBits = UART_STOPBITS_2;
  }

  switch(Settings_DB.RS485_Parity)
  {
  	  case 0:
  		  huart7.Init.Parity = UART_PARITY_NONE;
      break;
  	  case 1:
  		  huart7.Init.Parity = UART_PARITY_EVEN;
      break;
  	  case 2:
  		  huart7.Init.Parity = UART_PARITY_ODD;
      break;
  }

  huart7.Init.Mode = UART_MODE_TX_RX;
  huart7.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart7.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart7) != HAL_OK)
  {
    Error_Handler();
  }
	 *
	 */

  /* USER CODE END UART7_Init 0 */

  /* USER CODE BEGIN UART7_Init 1 */

  /* USER CODE END UART7_Init 1 */

	  huart7.Instance = UART7;

	  huart7.Init.BaudRate = Settings_DB.RS485_Speed;

	  if(Settings_DB.RS485_Parity)
	  {
		  huart7.Init.WordLength = UART_WORDLENGTH_9B;
	  }
	  else
	  {
		  huart7.Init.WordLength = UART_WORDLENGTH_8B;
	  }

	  if(Settings_DB.RS485_Stops == 1)
	  {
		  huart7.Init.StopBits = UART_STOPBITS_1;
	  }
	  else
	  {
		  huart7.Init.StopBits = UART_STOPBITS_2;
	  }

	  switch(Settings_DB.RS485_Parity)
	  {
	  	  case 0:
	  		  huart7.Init.Parity = UART_PARITY_NONE;
	      break;
	  	  case 1:
	  		  huart7.Init.Parity = UART_PARITY_EVEN;
	      break;
	  	  case 2:
	  		  huart7.Init.Parity = UART_PARITY_ODD;
	      break;
	  }

	  huart7.Init.Mode = UART_MODE_TX_RX;
	  huart7.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	  huart7.Init.OverSampling = UART_OVERSAMPLING_16;
	  if (HAL_UART_Init(&huart7) != HAL_OK)
	  {
	    Error_Handler();
	  }

  /* USER CODE BEGIN UART7_Init 2 */
  UART7->CR1 |= 0x20;
  /* USER CODE END UART7_Init 2 */

}

/* FMC initialization function */
static void MX_FMC_Init(void)
{

  /* USER CODE BEGIN FMC_Init 0 */

  /* USER CODE END FMC_Init 0 */

  FMC_SDRAM_TimingTypeDef SdramTiming = {0};

  /* USER CODE BEGIN FMC_Init 1 */

  /* USER CODE END FMC_Init 1 */

  /** Perform the SDRAM1 memory initialization sequence
  */
  hsdram1.Instance = FMC_SDRAM_DEVICE;
  /* hsdram1.Init */
  hsdram1.Init.SDBank = FMC_SDRAM_BANK1;
  hsdram1.Init.ColumnBitsNumber = FMC_SDRAM_COLUMN_BITS_NUM_9;
  hsdram1.Init.RowBitsNumber = FMC_SDRAM_ROW_BITS_NUM_13;
  hsdram1.Init.MemoryDataWidth = FMC_SDRAM_MEM_BUS_WIDTH_16;
  hsdram1.Init.InternalBankNumber = FMC_SDRAM_INTERN_BANKS_NUM_4;
  hsdram1.Init.CASLatency = FMC_SDRAM_CAS_LATENCY_2;
  hsdram1.Init.WriteProtection = FMC_SDRAM_WRITE_PROTECTION_DISABLE;
  hsdram1.Init.SDClockPeriod = FMC_SDRAM_CLOCK_PERIOD_2;
  hsdram1.Init.ReadBurst = FMC_SDRAM_RBURST_ENABLE;
  hsdram1.Init.ReadPipeDelay = FMC_SDRAM_RPIPE_DELAY_2;
  /* SdramTiming */
  SdramTiming.LoadToActiveDelay = 2;
  SdramTiming.ExitSelfRefreshDelay = 8;
  SdramTiming.SelfRefreshTime = 5;
  SdramTiming.RowCycleDelay = 8;
  SdramTiming.WriteRecoveryTime = 4;
  SdramTiming.RPDelay = 2;
  SdramTiming.RCDDelay = 2;

  if (HAL_SDRAM_Init(&hsdram1, &SdramTiming) != HAL_OK)
  {
    Error_Handler( );
  }

  /* USER CODE BEGIN FMC_Init 2 */

  /* USER CODE END FMC_Init 2 */
}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
/* USER CODE BEGIN MX_GPIO_Init_1 */
/* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOE_CLK_ENABLE();
  __HAL_RCC_GPIOI_CLK_ENABLE();
  __HAL_RCC_GPIOF_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOJ_CLK_ENABLE();
  __HAL_RCC_GPIOG_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOK_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(LTDC_DISP_GPIO_Port, LTDC_DISP_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(RS485DE_GPIO_Port, RS485DE_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(SPI1_CS_GPIO_Port, SPI1_CS_Pin, GPIO_PIN_SET);

  /*Configure GPIO pin : LTDC_DISP_Pin */
  GPIO_InitStruct.Pin = LTDC_DISP_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(LTDC_DISP_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : RS485DE_Pin */
  GPIO_InitStruct.Pin = RS485DE_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  HAL_GPIO_Init(RS485DE_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : SPI1_CS_Pin */
  GPIO_InitStruct.Pin = SPI1_CS_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  HAL_GPIO_Init(SPI1_CS_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : BUTTON_1_Pin */
  GPIO_InitStruct.Pin = BUTTON_1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(BUTTON_1_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : BUTTON_2_Pin BUTTON_3_Pin BUTTON_4_Pin BUTTON_5_Pin
                           BUTTON_6_Pin BUTTON_7_Pin BUTTON_8_Pin BUTTON_16_Pin
                           BUTTON_15_Pin BUTTON_14_Pin */
  GPIO_InitStruct.Pin = BUTTON_2_Pin|BUTTON_3_Pin|BUTTON_4_Pin|BUTTON_5_Pin
                          |BUTTON_6_Pin|BUTTON_7_Pin|BUTTON_8_Pin|BUTTON_16_Pin
                          |BUTTON_15_Pin|BUTTON_14_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(GPIOH, &GPIO_InitStruct);

  /*Configure GPIO pins : BUTTON_12_Pin BUTTON_11_Pin BUTTON_10_Pin BUTTON_9_Pin */
  GPIO_InitStruct.Pin = BUTTON_12_Pin|BUTTON_11_Pin|BUTTON_10_Pin|BUTTON_9_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pin : BUTTON_13_Pin */
  GPIO_InitStruct.Pin = BUTTON_13_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(BUTTON_13_GPIO_Port, &GPIO_InitStruct);

/* USER CODE BEGIN MX_GPIO_Init_2 */
/* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */

void BSP_SDRAM_Initialization_Sequence(SDRAM_HandleTypeDef *hsdram, FMC_SDRAM_CommandTypeDef *Command){
  __IO uint32_t tmpmrd =0;
  /* Step 3:  Configure a clock configuration enable command */
  Command->CommandMode = FMC_SDRAM_CMD_CLK_ENABLE;
  Command->CommandTarget = FMC_SDRAM_CMD_TARGET_BANK1;
  Command->AutoRefreshNumber = 1;
  Command->ModeRegisterDefinition = 0;
  /* Send the command */
  HAL_SDRAM_SendCommand(hsdram, Command, SDRAM_TIMEOUT);

  /* Step 4: Insert 100 us minimum delay */
  /* Inserted delay is equal to 1 ms due to systick time base unit (ms) */
  HAL_Delay(1);

  /* Step 5: Configure a PALL (precharge all) command */
  Command->CommandMode = FMC_SDRAM_CMD_PALL;
  Command->CommandTarget = FMC_SDRAM_CMD_TARGET_BANK1;
  Command->AutoRefreshNumber = 1;
  Command->ModeRegisterDefinition = 0;
  /* Send the command */
  HAL_SDRAM_SendCommand(hsdram, Command, SDRAM_TIMEOUT);

  /* Step 6 : Configure a Auto-Refresh command */
  Command->CommandMode = FMC_SDRAM_CMD_AUTOREFRESH_MODE;
  Command->CommandTarget = FMC_SDRAM_CMD_TARGET_BANK1;
  Command->AutoRefreshNumber = 8;
  Command->ModeRegisterDefinition = 0;
  /* Send the command */
  HAL_SDRAM_SendCommand(hsdram, Command, SDRAM_TIMEOUT);

  /* Step 7: Program the external memory mode register */
  tmpmrd = (uint32_t)SDRAM_MODEREG_BURST_LENGTH_1          |
                     SDRAM_MODEREG_BURST_TYPE_SEQUENTIAL   |
                     SDRAM_MODEREG_CAS_LATENCY_2           |
                     SDRAM_MODEREG_OPERATING_MODE_STANDARD |
                     SDRAM_MODEREG_WRITEBURST_MODE_SINGLE;

  Command->CommandMode = FMC_SDRAM_CMD_LOAD_MODE;
  Command->CommandTarget = FMC_SDRAM_CMD_TARGET_BANK1;
  Command->AutoRefreshNumber = 1;
  Command->ModeRegisterDefinition = tmpmrd;
  /* Send the command */
  HAL_SDRAM_SendCommand(hsdram, Command, SDRAM_TIMEOUT);

  /* Step 8: Set the refresh rate counter */
  /* (15.62 us x Freq) - 20 */
  /* Set the device refresh counter */
  //hsdram->Instance->SDRTR |= ((uint32_t)((1292)<< 1));
  hsdram->Instance->SDRTR = ((uint32_t)(64000*65/4096-20) << 1);
};

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
