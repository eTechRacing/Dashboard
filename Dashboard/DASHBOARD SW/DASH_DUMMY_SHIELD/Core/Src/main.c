/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ****************************  * @attention
  ** C
**************************************************
  opyright (c) 2024 STMicroelectronics.
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
#include "graphics.h"
#include "statemachine.h"
#include "can.h"
#include "glcd_etr.h"
#include "init.h"
#include "car_state.h"

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
CAN_HandleTypeDef hcan1;
CAN_HandleTypeDef hcan2;

SPI_HandleTypeDef hspi3;

TIM_HandleTypeDef htim11;
TIM_HandleTypeDef htim13;
TIM_HandleTypeDef htim14;

/* USER CODE BEGIN PV */


	/* CAN  -----------------------------------------------------------------*/

	CAN_TxHeaderTypeDef TxHeader;
	CAN_RxHeaderTypeDef RxHeader;
	CAN_FilterTypeDef can1filter;
	CAN_FilterTypeDef can2filter;

	uint32_t RxMailbox = 0;
	uint8_t TxData[30];
	uint8_t RxData[30];

	/* CAR STATE -------------------------------------------------------------*/

	uint8_t Car__State;	//0 -> Init; 3 -> PrechargeRequest; 6 -> Precharge In Process; 9 -> Precharge Done; 12 -> Racing Menu; 14 -> Inverters Ready; 15 -> Racing Mode; 21 -> Errors
	uint8_t Racing_Mode;
	uint8_t Precharge_Request;

	/* DASH DATA -------------------------------------------------------------*/

	uint16_t PrechargeVoltage;
	uint8_t PrechargePercentage;
	uint8_t CarSpeed;
	uint8_t SoC_Average;

	/* DEBUG -------------------------------------------------------------*/

	uint16_t counter = 0;

	/* DISCONNECTIONS  -------------------------------------------------------*/

	uint8_t BMS_Disconnect;
	uint8_t Dash_Disconect;
	uint8_t Front_Disconenct;
	uint8_t Ellipse_Disconect;
	uint8_t Rear_Disconnect;
	uint8_t APPS1_Disconect;
	uint8_t APPS2_Disconnect;
	uint8_t BrakePedal_Disconnect;
	uint8_t SteeringSensor_Disconnect;
	uint8_t SuspRR_Disconnect;
	uint8_t SuspRL_Disconnect;
	uint8_t SuspFR_Disconnect;
	uint8_t SuspFL_Disconnect;
	uint8_t Pitot_Disconnect;

	/* SHUTDOWN  -------------------------------------------------------------*/

	uint8_t END_SD;
	uint8_t BMS_SD = 1;
	uint8_t IMD_SD = 1;
	uint8_t Shutdown_Setas;
	uint8_t Shutdown_BSPD_Inertia;
	uint8_t Shutdown_SC_BOTS;
	uint8_t Shutdown_TSMS_TSMP;
	uint8_t Shutdown_RightTS;
	uint8_t Shutdown_LeftTS;
	uint8_t Shutdown_HVBox;
	uint8_t Shutdown_HVD;

	/* SYNCRONISM  -----------------------------------------------------------*/

	uint8_t syncronism1;
	uint8_t syncronism2;
	uint8_t KeepAlive;

	/* TEMPERATURAS  ---------------------------------------------------------*/

	uint16_t Lowest_CellTemperature;
	uint16_t Highest_CellTemperature;
	uint16_t Average_CellTemperature;

	/* VDC  ------------------------------------------------------------------*/

	uint8_t VDC_Params;

	/* VOLTAGES  -------------------------------------------------------------*/

	uint16_t Lowest_CellVolt;
	uint16_t Highest_CellVolt;
	uint32_t Accu_Volt;

	/* COOLING  --------------------------------------------------------------*/

	uint8_t Refri_Accumulator; // 0-> ON - 1-> OFF - 2->FULL
	uint8_t Refri_Inverters;
	uint8_t Refri_Motors;


	/* ENABLE TO DRIVE   -----------------------------------------------------*/

	uint8_t Enable_Drive;
	uint8_t RTD;

	/* CONTROL  --------------------------------------------------------------*/

	uint8_t msg_can1;
	uint8_t msg_can2;
	uint8_t msg;

	/* SCREENS  --------------------------------------------------------------*/

	uint8_t CS3_Screen = 0; //0 for Default 1 for refri
	uint8_t RefriSelected=0;// 0 accu 1 inverters 2 motors

	/* SCREENS  --------------------------------------------------------------*/
	uint8_t APPS1;
	uint8_t APPS2;
	uint8_t Break_Value;
	uint8_t Steering_sensor_value;
	uint8_t TV_MODE;


/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MPU_Config(void);
static void MX_GPIO_Init(void);
static void MX_CAN1_Init(void);
static void MX_CAN2_Init(void);
static void MX_SPI3_Init(void);
static void MX_TIM14_Init(void);
static void MX_TIM13_Init(void);
static void MX_TIM11_Init(void);
/* USER CODE BEGIN PFP */
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */


/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{

  /* USER CODE BEGIN 1 */


  /* USER CODE END 1 */

  /* MPU Configuration--------------------------------------------------------*/
  MPU_Config();

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
  MX_CAN1_Init();
  MX_CAN2_Init();
  MX_SPI3_Init();
  MX_TIM14_Init();
  MX_TIM13_Init();
  MX_TIM11_Init();
  /* USER CODE BEGIN 2 */

  filtercanconfig_can1(&can1filter);
  filtercanconfig_can2(&can2filter);
  CAN1_CONFIG_INIT(can1filter, hcan1);
  CAN2_CONFIG_INIT(can2filter, hcan2);

  glcd_etr_init(hspi3);
  glcd_etr_blank(hspi3);
  logo_ETR();
  glcd_etr_refresh(hspi3);

  NORMATIVE_INIT();
  VARIABLE_RESET(&Enable_Drive, &Racing_Mode, &Precharge_Request, &KeepAlive, &Refri_Inverters, &Refri_Accumulator, &Refri_Motors, &msg_can1, &msg_can2, &Car__State, &Precharge_Request);

  if(HAL_TIM_Base_Start_IT(&htim13) != HAL_OK) Error_Handler();
  if(HAL_TIM_Base_Start_IT(&htim14) != HAL_OK) Error_Handler();
  if(HAL_TIM_Base_Start_IT(&htim11) != HAL_OK) Error_Handler();


  glcd_etr_blank(hspi3);
  glcd_etr_refresh(hspi3);


  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
	  while (1){
			CAR_STATE_FUNCTION(hspi3, Car__State, PrechargePercentage, &Precharge_Request, &Racing_Mode, &RTD, &Enable_Drive,
					SoC_Average, CarSpeed, Lowest_CellVolt,Highest_CellTemperature,Average_CellTemperature, &Refri_Accumulator, &Refri_Inverters,
					&Refri_Motors, END_SD, BMS_SD, IMD_SD, Shutdown_Setas, Shutdown_BSPD_Inertia, Shutdown_SC_BOTS, Shutdown_TSMS_TSMP,
					Shutdown_RightTS, Shutdown_LeftTS, Shutdown_HVBox, Shutdown_HVD,  BMS_Disconnect,  Dash_Disconect,  Front_Disconenct,
					 Ellipse_Disconect,  Rear_Disconnect,  APPS1_Disconect,  APPS2_Disconnect,  BrakePedal_Disconnect,  SteeringSensor_Disconnect,
					 SuspRR_Disconnect,  SuspRL_Disconnect,  SuspFR_Disconnect,  SuspFL_Disconnect,  Pitot_Disconnect, APPS1, TV_MODE);
	  }
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */

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
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE3);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 8;
  RCC_OscInitStruct.PLL.PLLN = 108;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 2;
  RCC_OscInitStruct.PLL.PLLR = 2;
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
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_3) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief CAN1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_CAN1_Init(void)
{

  /* USER CODE BEGIN CAN1_Init 0 */

  /* USER CODE END CAN1_Init 0 */

  /* USER CODE BEGIN CAN1_Init 1 */

  /* USER CODE END CAN1_Init 1 */
  hcan1.Instance = CAN1;
  hcan1.Init.Prescaler = 12;
  hcan1.Init.Mode = CAN_MODE_NORMAL;
  hcan1.Init.SyncJumpWidth = CAN_SJW_1TQ;
  hcan1.Init.TimeSeg1 = CAN_BS1_6TQ;
  hcan1.Init.TimeSeg2 = CAN_BS2_2TQ;
  hcan1.Init.TimeTriggeredMode = DISABLE;
  hcan1.Init.AutoBusOff = DISABLE;
  hcan1.Init.AutoWakeUp = DISABLE;
  hcan1.Init.AutoRetransmission = DISABLE;
  hcan1.Init.ReceiveFifoLocked = DISABLE;
  hcan1.Init.TransmitFifoPriority = DISABLE;
  if (HAL_CAN_Init(&hcan1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN CAN1_Init 2 */

  /* USER CODE END CAN1_Init 2 */

}

/**
  * @brief CAN2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_CAN2_Init(void)
{

  /* USER CODE BEGIN CAN2_Init 0 */

  /* USER CODE END CAN2_Init 0 */

  /* USER CODE BEGIN CAN2_Init 1 */

  /* USER CODE END CAN2_Init 1 */
  hcan2.Instance = CAN2;
  hcan2.Init.Prescaler = 12;
  hcan2.Init.Mode = CAN_MODE_NORMAL;
  hcan2.Init.SyncJumpWidth = CAN_SJW_1TQ;
  hcan2.Init.TimeSeg1 = CAN_BS1_6TQ;
  hcan2.Init.TimeSeg2 = CAN_BS2_2TQ;
  hcan2.Init.TimeTriggeredMode = DISABLE;
  hcan2.Init.AutoBusOff = DISABLE;
  hcan2.Init.AutoWakeUp = DISABLE;
  hcan2.Init.AutoRetransmission = DISABLE;
  hcan2.Init.ReceiveFifoLocked = DISABLE;
  hcan2.Init.TransmitFifoPriority = DISABLE;
  if (HAL_CAN_Init(&hcan2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN CAN2_Init 2 */

  /* USER CODE END CAN2_Init 2 */

}

/**
  * @brief SPI3 Initialization Function
  * @param None
  * @retval None
  */
static void MX_SPI3_Init(void)
{

  /* USER CODE BEGIN SPI3_Init 0 */

  /* USER CODE END SPI3_Init 0 */

  /* USER CODE BEGIN SPI3_Init 1 */

  /* USER CODE END SPI3_Init 1 */
  /* SPI3 parameter configuration*/
  hspi3.Instance = SPI3;
  hspi3.Init.Mode = SPI_MODE_MASTER;
  hspi3.Init.Direction = SPI_DIRECTION_1LINE;
  hspi3.Init.DataSize = SPI_DATASIZE_8BIT;
  hspi3.Init.CLKPolarity = SPI_POLARITY_LOW;
  hspi3.Init.CLKPhase = SPI_PHASE_1EDGE;
  hspi3.Init.NSS = SPI_NSS_SOFT;
  hspi3.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_256;
  hspi3.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi3.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi3.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi3.Init.CRCPolynomial = 7;
  hspi3.Init.CRCLength = SPI_CRC_LENGTH_DATASIZE;
  hspi3.Init.NSSPMode = SPI_NSS_PULSE_ENABLE;
  if (HAL_SPI_Init(&hspi3) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN SPI3_Init 2 */

  /* USER CODE END SPI3_Init 2 */

}

/**
  * @brief TIM11 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM11_Init(void)
{

  /* USER CODE BEGIN TIM11_Init 0 */

  /* USER CODE END TIM11_Init 0 */

  /* USER CODE BEGIN TIM11_Init 1 */

  /* USER CODE END TIM11_Init 1 */
  htim11.Instance = TIM11;
  htim11.Init.Prescaler = 108;
  htim11.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim11.Init.Period = 1000;
  htim11.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim11.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim11) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM11_Init 2 */

  /* USER CODE END TIM11_Init 2 */

}

/**
  * @brief TIM13 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM13_Init(void)
{

  /* USER CODE BEGIN TIM13_Init 0 */

  /* USER CODE END TIM13_Init 0 */

  /* USER CODE BEGIN TIM13_Init 1 */

  /* USER CODE END TIM13_Init 1 */
  htim13.Instance = TIM13;
  htim13.Init.Prescaler = 108-1;
  htim13.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim13.Init.Period = 10000;
  htim13.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim13.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim13) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM13_Init 2 */

  /* USER CODE END TIM13_Init 2 */

}

/**
  * @brief TIM14 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM14_Init(void)
{

  /* USER CODE BEGIN TIM14_Init 0 */

  /* USER CODE END TIM14_Init 0 */

  /* USER CODE BEGIN TIM14_Init 1 */

  /* USER CODE END TIM14_Init 1 */
  htim14.Instance = TIM14;
  htim14.Init.Prescaler = 108-1;
  htim14.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim14.Init.Period = 4000;
  htim14.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim14.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim14) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM14_Init 2 */

  /* USER CODE END TIM14_Init 2 */

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
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOE, LED_RED_1_Pin|LED_RED_2_Pin|LED_RED_3_Pin|LED_YELLOW_1_Pin
                          |LED_YELLOW_2_Pin|LED_YELLOW_3_Pin|LED_GREEN_1_Pin|LED_GREEN_2_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, LED_GREEN_3_Pin|BUZZER_Pin|IMD_LED_Pin|RST_LCD_Pin
                          |CS_LCD_Pin|A0_LCD_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(AMS_LED_GPIO_Port, AMS_LED_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : UP_BUTTON_Pin OK_BUTTON_Pin */
  GPIO_InitStruct.Pin = UP_BUTTON_Pin|OK_BUTTON_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

  /*Configure GPIO pin : LEFT_BUTTON_Pin */
  GPIO_InitStruct.Pin = LEFT_BUTTON_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(LEFT_BUTTON_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : DOWN_BUTTON_Pin RIGHT_BUTTON_Pin */
  GPIO_InitStruct.Pin = DOWN_BUTTON_Pin|RIGHT_BUTTON_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : LED_RED_1_Pin LED_RED_2_Pin LED_RED_3_Pin LED_YELLOW_1_Pin
                           LED_YELLOW_2_Pin LED_YELLOW_3_Pin LED_GREEN_1_Pin LED_GREEN_2_Pin */
  GPIO_InitStruct.Pin = LED_RED_1_Pin|LED_RED_2_Pin|LED_RED_3_Pin|LED_YELLOW_1_Pin
                          |LED_YELLOW_2_Pin|LED_YELLOW_3_Pin|LED_GREEN_1_Pin|LED_GREEN_2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

  /*Configure GPIO pins : LED_GREEN_3_Pin BUZZER_Pin IMD_LED_Pin */
  GPIO_InitStruct.Pin = LED_GREEN_3_Pin|BUZZER_Pin|IMD_LED_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pin : AMS_LED_Pin */
  GPIO_InitStruct.Pin = AMS_LED_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(AMS_LED_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : RST_LCD_Pin CS_LCD_Pin A0_LCD_Pin */
  GPIO_InitStruct.Pin = RST_LCD_Pin|CS_LCD_Pin|A0_LCD_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

/* USER CODE BEGIN MX_GPIO_Init_2 */
/* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */

void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan1) {

	rx_sorter_can1(*hcan1, RxMailbox, RxHeader, RxData, &msg_can1, &Car__State, &PrechargeVoltage, &PrechargePercentage,
			&CarSpeed, &SoC_Average, &END_SD, &BMS_SD, &IMD_SD, &syncronism1, &Lowest_CellTemperature, &Highest_CellTemperature,
			&Average_CellTemperature, &VDC_Params, &Lowest_CellVolt, &Highest_CellVolt, &Accu_Volt, &TV_MODE);
	if(msg == 0)msg = 1;
}

void HAL_CAN_RxFifo1MsgPendingCallback(CAN_HandleTypeDef *hcan2) {

	rx_sorter_can2(*hcan2, RxMailbox, RxHeader, RxData, &msg_can2, &SteeringSensor_Disconnect, &SuspRR_Disconnect, &SuspRL_Disconnect,
			&SuspFR_Disconnect, &SuspFL_Disconnect, &Pitot_Disconnect, &BMS_Disconnect, &Dash_Disconect, &Front_Disconenct,
			&Ellipse_Disconect, &Rear_Disconnect, &APPS1_Disconect, &APPS2_Disconnect, &BrakePedal_Disconnect, &Shutdown_Setas,
			&Shutdown_BSPD_Inertia, &Shutdown_SC_BOTS, &Shutdown_TSMS_TSMP, &Shutdown_RightTS, &Shutdown_LeftTS, &Shutdown_HVBox,
			&Shutdown_HVD, &syncronism2, &APPS1, &APPS2, &Break_Value, &Steering_sensor_value);
}


void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {

	if (htim->Instance == TIM14)
	{
		switch(msg){
			case 1:
				message_cantx_Keep_Alive(hcan1, TxHeader, TxData, KeepAlive);
				KeepAlive++;
				msg = 2;
			break;
			case 2:
				message_cantx_EnableDrive(hcan1,  TxHeader, TxData, Enable_Drive);
				Enable_Drive = 0;
				msg = 3;
			break;
			case 3:
				message_cantx_PrechargeRequest(hcan1, TxHeader, TxData, Precharge_Request);
				msg = 4;
			break;
			case 4:
				message_cantx_Mode(hcan1, TxHeader, TxData, Racing_Mode);
				msg = 5;
			break;
			case 5:
				message_cantx_Cooling(hcan2, TxHeader, TxData, Refri_Accumulator, Refri_Inverters, Refri_Motors);
				msg = 0;
			break;
		}
		if(HAL_GetTick() >=5000){
			BMS_IMD_ERROR(BMS_SD, IMD_SD);
		}
		}
	}
/* USER CODE END 4 */

 /* MPU Configuration */

void MPU_Config(void)
{
  MPU_Region_InitTypeDef MPU_InitStruct = {0};

  /* Disables the MPU */
  HAL_MPU_Disable();

  /** Initializes and configures the Region and the memory to be protected
  */
  MPU_InitStruct.Enable = MPU_REGION_ENABLE;
  MPU_InitStruct.Number = MPU_REGION_NUMBER0;
  MPU_InitStruct.BaseAddress = 0x0;
  MPU_InitStruct.Size = MPU_REGION_SIZE_4GB;
  MPU_InitStruct.SubRegionDisable = 0x87;
  MPU_InitStruct.TypeExtField = MPU_TEX_LEVEL0;
  MPU_InitStruct.AccessPermission = MPU_REGION_NO_ACCESS;
  MPU_InitStruct.DisableExec = MPU_INSTRUCTION_ACCESS_DISABLE;
  MPU_InitStruct.IsShareable = MPU_ACCESS_SHAREABLE;
  MPU_InitStruct.IsCacheable = MPU_ACCESS_NOT_CACHEABLE;
  MPU_InitStruct.IsBufferable = MPU_ACCESS_NOT_BUFFERABLE;

  HAL_MPU_ConfigRegion(&MPU_InitStruct);
  /* Enables the MPU */
  HAL_MPU_Enable(MPU_PRIVILEGED_DEFAULT);

}

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
