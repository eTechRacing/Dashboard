/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
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
#include "stm32h7xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define UP_BUTTON_Pin GPIO_PIN_3
#define UP_BUTTON_GPIO_Port GPIOE
#define OK_BUTTON_Pin GPIO_PIN_6
#define OK_BUTTON_GPIO_Port GPIOE
#define LEFT_BUTTON_Pin GPIO_PIN_15
#define LEFT_BUTTON_GPIO_Port GPIOC
#define DOWN_BUTTON_Pin GPIO_PIN_6
#define DOWN_BUTTON_GPIO_Port GPIOA
#define RIGHT_BUTTON_Pin GPIO_PIN_7
#define RIGHT_BUTTON_GPIO_Port GPIOA
#define LED_RED_1_Pin GPIO_PIN_8
#define LED_RED_1_GPIO_Port GPIOE
#define LED_RED_2_Pin GPIO_PIN_9
#define LED_RED_2_GPIO_Port GPIOE
#define LED_RED_3_Pin GPIO_PIN_10
#define LED_RED_3_GPIO_Port GPIOE
#define LED_YELLOW_1_Pin GPIO_PIN_11
#define LED_YELLOW_1_GPIO_Port GPIOE
#define LED_YELLOW_2_Pin GPIO_PIN_12
#define LED_YELLOW_2_GPIO_Port GPIOE
#define LED_YELLOW_3_Pin GPIO_PIN_13
#define LED_YELLOW_3_GPIO_Port GPIOE
#define LED_GREEN_1_Pin GPIO_PIN_14
#define LED_GREEN_1_GPIO_Port GPIOE
#define LED_GREEN_2_Pin GPIO_PIN_15
#define LED_GREEN_2_GPIO_Port GPIOE
#define LED_GREEN_3_Pin GPIO_PIN_10
#define LED_GREEN_3_GPIO_Port GPIOB
#define BUZZER_Pin GPIO_PIN_14
#define BUZZER_GPIO_Port GPIOB
#define IMD_LED_Pin GPIO_PIN_15
#define IMD_LED_GPIO_Port GPIOB
#define AMS_LED_Pin GPIO_PIN_9
#define AMS_LED_GPIO_Port GPIOA
#define RST_LCD_Pin GPIO_PIN_6
#define RST_LCD_GPIO_Port GPIOB
#define CS_LCD_Pin GPIO_PIN_7
#define CS_LCD_GPIO_Port GPIOB
#define AD_LCD_Pin GPIO_PIN_8
#define AD_LCD_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
