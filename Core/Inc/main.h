/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "fonts.h"
#include "Font_Processor.h"
#include "SPI_flash.h"

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */




/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */
#define WIDTH 800
#define HEIGHT 480


#define SDRAM_BANK_ADDR                          ((uint32_t)0xC0000000)
#define BUFFER_SIZE                              ((uint32_t)0x1000)
#define WRITE_READ_ADDR                          ((uint32_t)0x0800)

#define SDRAM_TIMEOUT                            ((uint32_t)0xFFFF)
#define SDRAM_MODEREG_BURST_LENGTH_1             ((uint16_t)0x0000)
#define SDRAM_MODEREG_BURST_LENGTH_2             ((uint16_t)0x0001)
#define SDRAM_MODEREG_BURST_LENGTH_4             ((uint16_t)0x0002)
#define SDRAM_MODEREG_BURST_LENGTH_8             ((uint16_t)0x0004)
#define SDRAM_MODEREG_BURST_TYPE_SEQUENTIAL      ((uint16_t)0x0000)
#define SDRAM_MODEREG_BURST_TYPE_INTERLEAVED     ((uint16_t)0x0008)
#define SDRAM_MODEREG_CAS_LATENCY_2              ((uint16_t)0x0020)
#define SDRAM_MODEREG_CAS_LATENCY_3              ((uint16_t)0x0030)
#define SDRAM_MODEREG_OPERATING_MODE_STANDARD    ((uint16_t)0x0000)
#define SDRAM_MODEREG_WRITEBURST_MODE_PROGRAMMED ((uint16_t)0x0000)
#define SDRAM_MODEREG_WRITEBURST_MODE_SINGLE     ((uint16_t)0x0200)
/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

void HAL_TIM_MspPostInit(TIM_HandleTypeDef *htim);

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define LTDC_DISP_Pin GPIO_PIN_3
#define LTDC_DISP_GPIO_Port GPIOE
#define RS485DE_Pin GPIO_PIN_8
#define RS485DE_GPIO_Port GPIOF
#define SPI1_CS_Pin GPIO_PIN_4
#define SPI1_CS_GPIO_Port GPIOA
#define BUTTON_1_Pin GPIO_PIN_5
#define BUTTON_1_GPIO_Port GPIOJ
#define BUTTON_2_Pin GPIO_PIN_6
#define BUTTON_2_GPIO_Port GPIOH
#define BUTTON_3_Pin GPIO_PIN_7
#define BUTTON_3_GPIO_Port GPIOH
#define BUTTON_4_Pin GPIO_PIN_8
#define BUTTON_4_GPIO_Port GPIOH
#define BUTTON_5_Pin GPIO_PIN_9
#define BUTTON_5_GPIO_Port GPIOH
#define BUTTON_6_Pin GPIO_PIN_10
#define BUTTON_6_GPIO_Port GPIOH
#define BUTTON_7_Pin GPIO_PIN_11
#define BUTTON_7_GPIO_Port GPIOH
#define BUTTON_8_Pin GPIO_PIN_12
#define BUTTON_8_GPIO_Port GPIOH
#define BUTTON_12_Pin GPIO_PIN_6
#define BUTTON_12_GPIO_Port GPIOC
#define BUTTON_11_Pin GPIO_PIN_7
#define BUTTON_11_GPIO_Port GPIOC
#define BUTTON_10_Pin GPIO_PIN_8
#define BUTTON_10_GPIO_Port GPIOC
#define BUTTON_9_Pin GPIO_PIN_9
#define BUTTON_9_GPIO_Port GPIOC
#define BUTTON_16_Pin GPIO_PIN_13
#define BUTTON_16_GPIO_Port GPIOH
#define BUTTON_15_Pin GPIO_PIN_14
#define BUTTON_15_GPIO_Port GPIOH
#define BUTTON_14_Pin GPIO_PIN_15
#define BUTTON_14_GPIO_Port GPIOH
#define BUTTON_13_Pin GPIO_PIN_0
#define BUTTON_13_GPIO_Port GPIOI

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
