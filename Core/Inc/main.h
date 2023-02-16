/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
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
extern volatile unsigned long ulHighFrequencyTimerTicks;

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
#define B1_Pin GPIO_PIN_13
#define B1_GPIO_Port GPIOC
#define LED1_Pin GPIO_PIN_3
#define LED1_GPIO_Port GPIOF
#define LED2_Pin GPIO_PIN_5
#define LED2_GPIO_Port GPIOF
#define LED3_Pin GPIO_PIN_10
#define LED3_GPIO_Port GPIOF
#define LD1_Pin GPIO_PIN_0
#define LD1_GPIO_Port GPIOB
#define STEP1_EN_Pin GPIO_PIN_13
#define STEP1_EN_GPIO_Port GPIOF
#define STEP1_Dir_Pin GPIO_PIN_14
#define STEP1_Dir_GPIO_Port GPIOF
#define STEP1_step_Pin GPIO_PIN_15
#define STEP1_step_GPIO_Port GPIOF
#define GPIO4_Pin GPIO_PIN_7
#define GPIO4_GPIO_Port GPIOE
#define GPIO5_Pin GPIO_PIN_8
#define GPIO5_GPIO_Port GPIOE
#define PWM3_Pin GPIO_PIN_9
#define PWM3_GPIO_Port GPIOE
#define GPIO3_Pin GPIO_PIN_10
#define GPIO3_GPIO_Port GPIOE
#define PWM4_Pin GPIO_PIN_11
#define PWM4_GPIO_Port GPIOE
#define GPIO2_Pin GPIO_PIN_12
#define GPIO2_GPIO_Port GPIOE
#define PWM5_Pin GPIO_PIN_13
#define PWM5_GPIO_Port GPIOE
#define STOP_Pin GPIO_PIN_14
#define STOP_GPIO_Port GPIOE
#define GPIO1_Pin GPIO_PIN_15
#define GPIO1_GPIO_Port GPIOE
#define PWM1_Pin GPIO_PIN_10
#define PWM1_GPIO_Port GPIOB
#define PWM2_Pin GPIO_PIN_11
#define PWM2_GPIO_Port GPIOB
#define STLINK_RX_Pin GPIO_PIN_8
#define STLINK_RX_GPIO_Port GPIOD
#define STLINK_TX_Pin GPIO_PIN_9
#define STLINK_TX_GPIO_Port GPIOD
#define USB_OTG_FS_PWR_EN_Pin GPIO_PIN_10
#define USB_OTG_FS_PWR_EN_GPIO_Port GPIOD
#define USB_OTG_FS_OVCR_Pin GPIO_PIN_7
#define USB_OTG_FS_OVCR_GPIO_Port GPIOG
#define FAULT_Pin GPIO_PIN_0
#define FAULT_GPIO_Port GPIOE
#define LD2_Pin GPIO_PIN_1
#define LD2_GPIO_Port GPIOE
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
