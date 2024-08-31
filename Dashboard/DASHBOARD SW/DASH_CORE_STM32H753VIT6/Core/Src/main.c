/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
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

FDCAN_HandleTypeDef hfdcan1;
FDCAN_HandleTypeDef hfdcan2;

SPI_HandleTypeDef hspi3;

TIM_HandleTypeDef htim14;

/* USER CODE BEGIN PV */

/* CAN  -----------------------------------------------------------------*/

FDCAN_TxHeaderTypeDef TxHeader;
FDCAN_RxHeaderTypeDef RxHeader;
FDCAN_FilterTypeDef can1filter;
FDCAN_FilterTypeDef can2filter;

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
uint8_t BMS_OK = 1;
uint32_t BMS_SD_SC;
uint32_t IMD_SD_SC;
uint32_t BMS_DISC_SC;
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
uint8_t APPS1prova;
uint8_t APPS2;
uint8_t Break_Value;
uint8_t Steering_sensor_value;
uint8_t TV_MODE;
uint8_t LV_CURRENT;

uint8_t cunter;

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MPU_Config(void);
static void MX_GPIO_Init(void);
static void MX_FDCAN1_Init(void);
static void MX_FDCAN2_Init(void);
static void MX_SPI3_Init(void);
static void MX_TIM14_Init(void);
/* USER CODE BEGIN PFP */
static void FDCAN_Config(void);
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
  MX_FDCAN1_Init();
  MX_FDCAN2_Init();
  MX_SPI3_Init();
  MX_TIM14_Init();
  /* USER CODE BEGIN 2 */
  FDCAN_Config();

  glcd_etr_init(hspi3);
  glcd_etr_blank(hspi3);
  logo_ETR();
  glcd_etr_refresh(hspi3);

  NORMATIVE_INIT();
  VARIABLE_RESET(&Enable_Drive, &Racing_Mode, &Precharge_Request, &KeepAlive, &Refri_Inverters, &Refri_Accumulator, &Refri_Motors, &msg_can1, &msg_can2, &Car__State, &Precharge_Request);

  if(HAL_TIM_Base_Start_IT(&htim14) != HAL_OK) Error_Handler();

  glcd_etr_blank(hspi3);
  glcd_etr_refresh(hspi3);

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
		CAR_STATE_FUNCTION(hspi3, Car__State, PrechargePercentage, &Precharge_Request, &Racing_Mode, &RTD, &Enable_Drive,
				SoC_Average, CarSpeed, Lowest_CellVolt,Highest_CellTemperature,Average_CellTemperature, &Refri_Accumulator, &Refri_Inverters,
				&Refri_Motors, END_SD, BMS_SD, IMD_SD, Shutdown_Setas, Shutdown_BSPD_Inertia, Shutdown_SC_BOTS, Shutdown_TSMS_TSMP,
				Shutdown_RightTS, Shutdown_LeftTS, Shutdown_HVBox, Shutdown_HVD,  BMS_Disconnect,  Dash_Disconect,  Front_Disconenct,
				 Ellipse_Disconect,  Rear_Disconnect,  APPS1_Disconect,  APPS2_Disconnect,  BrakePedal_Disconnect,  SteeringSensor_Disconnect,
				 SuspRR_Disconnect,  SuspRL_Disconnect,  SuspFR_Disconnect,  SuspFL_Disconnect,  Pitot_Disconnect, APPS1, APPS2, Break_Value,
				 Steering_sensor_value, TV_MODE, syncronism1, syncronism2, LV_CURRENT);
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

  /** Supply configuration update enable
  */
  HAL_PWREx_ConfigSupply(PWR_LDO_SUPPLY);

  /** Configure the main internal regulator output voltage
  */
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE3);

  while(!__HAL_PWR_GET_FLAG(PWR_FLAG_VOSRDY)) {}

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_DIV1;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 4;
  RCC_OscInitStruct.PLL.PLLN = 9;
  RCC_OscInitStruct.PLL.PLLP = 2;
  RCC_OscInitStruct.PLL.PLLQ = 3;
  RCC_OscInitStruct.PLL.PLLR = 2;
  RCC_OscInitStruct.PLL.PLLRGE = RCC_PLL1VCIRANGE_3;
  RCC_OscInitStruct.PLL.PLLVCOSEL = RCC_PLL1VCOMEDIUM;
  RCC_OscInitStruct.PLL.PLLFRACN = 3072;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2
                              |RCC_CLOCKTYPE_D3PCLK1|RCC_CLOCKTYPE_D1PCLK1;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.SYSCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB3CLKDivider = RCC_APB3_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_APB1_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_APB2_DIV1;
  RCC_ClkInitStruct.APB4CLKDivider = RCC_APB4_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief FDCAN1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_FDCAN1_Init(void)
{

  /* USER CODE BEGIN FDCAN1_Init 0 */

  /* USER CODE END FDCAN1_Init 0 */

  /* USER CODE BEGIN FDCAN1_Init 1 */

  /* USER CODE END FDCAN1_Init 1 */
  hfdcan1.Instance = FDCAN1;
  hfdcan1.Init.FrameFormat = FDCAN_FRAME_FD_NO_BRS;
  hfdcan1.Init.Mode = FDCAN_MODE_NORMAL;
  hfdcan1.Init.AutoRetransmission = ENABLE;
  hfdcan1.Init.TransmitPause = DISABLE;
  hfdcan1.Init.ProtocolException = DISABLE;
  hfdcan1.Init.NominalPrescaler = 1;
  hfdcan1.Init.NominalSyncJumpWidth = 13;
  hfdcan1.Init.NominalTimeSeg1 = 86;
  hfdcan1.Init.NominalTimeSeg2 = 13;
  hfdcan1.Init.DataPrescaler = 25;
  hfdcan1.Init.DataSyncJumpWidth = 1;
  hfdcan1.Init.DataTimeSeg1 = 2;
  hfdcan1.Init.DataTimeSeg2 = 1;
  hfdcan1.Init.MessageRAMOffset = 0;
  hfdcan1.Init.StdFiltersNbr = 1;
  hfdcan1.Init.ExtFiltersNbr = 0;
  hfdcan1.Init.RxFifo0ElmtsNbr = 1;
  hfdcan1.Init.RxFifo0ElmtSize = FDCAN_DATA_BYTES_8;
  hfdcan1.Init.RxFifo1ElmtsNbr = 0;
  hfdcan1.Init.RxFifo1ElmtSize = FDCAN_DATA_BYTES_8;
  hfdcan1.Init.RxBuffersNbr = 0;
  hfdcan1.Init.RxBufferSize = FDCAN_DATA_BYTES_8;
  hfdcan1.Init.TxEventsNbr = 0;
  hfdcan1.Init.TxBuffersNbr = 0;
  hfdcan1.Init.TxFifoQueueElmtsNbr = 1;
  hfdcan1.Init.TxFifoQueueMode = FDCAN_TX_FIFO_OPERATION;
  hfdcan1.Init.TxElmtSize = FDCAN_DATA_BYTES_8;
  if (HAL_FDCAN_Init(&hfdcan1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN FDCAN1_Init 2 */

  /* USER CODE END FDCAN1_Init 2 */

}

/**
  * @brief FDCAN2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_FDCAN2_Init(void)
{

  /* USER CODE BEGIN FDCAN2_Init 0 */

  /* USER CODE END FDCAN2_Init 0 */

  /* USER CODE BEGIN FDCAN2_Init 1 */

  /* USER CODE END FDCAN2_Init 1 */
  hfdcan2.Instance = FDCAN2;
  hfdcan2.Init.FrameFormat = FDCAN_FRAME_FD_NO_BRS;
  hfdcan2.Init.Mode = FDCAN_MODE_NORMAL;
  hfdcan2.Init.AutoRetransmission = ENABLE;
  hfdcan2.Init.TransmitPause = DISABLE;
  hfdcan2.Init.ProtocolException = DISABLE;
  hfdcan2.Init.NominalPrescaler = 1;
  hfdcan2.Init.NominalSyncJumpWidth = 13;
  hfdcan2.Init.NominalTimeSeg1 = 86;
  hfdcan2.Init.NominalTimeSeg2 = 13;
  hfdcan2.Init.DataPrescaler = 25;
  hfdcan2.Init.DataSyncJumpWidth = 1;
  hfdcan2.Init.DataTimeSeg1 = 2;
  hfdcan2.Init.DataTimeSeg2 = 1;
  hfdcan2.Init.MessageRAMOffset = 9;
  hfdcan2.Init.StdFiltersNbr = 0;
  hfdcan2.Init.ExtFiltersNbr = 0;
  hfdcan2.Init.RxFifo0ElmtsNbr = 1;
  hfdcan2.Init.RxFifo0ElmtSize = FDCAN_DATA_BYTES_8;
  hfdcan2.Init.RxFifo1ElmtsNbr = 0;
  hfdcan2.Init.RxFifo1ElmtSize = FDCAN_DATA_BYTES_8;
  hfdcan2.Init.RxBuffersNbr = 3;
  hfdcan2.Init.RxBufferSize = FDCAN_DATA_BYTES_8;
  hfdcan2.Init.TxEventsNbr = 4;
  hfdcan2.Init.TxBuffersNbr = 4;
  hfdcan2.Init.TxFifoQueueElmtsNbr = 4;
  hfdcan2.Init.TxFifoQueueMode = FDCAN_TX_FIFO_OPERATION;
  hfdcan2.Init.TxElmtSize = FDCAN_DATA_BYTES_8;
  if (HAL_FDCAN_Init(&hfdcan2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN FDCAN2_Init 2 */

  /* USER CODE END FDCAN2_Init 2 */

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
  hspi3.Init.CRCPolynomial = 0x0;
  hspi3.Init.NSSPMode = SPI_NSS_PULSE_ENABLE;
  hspi3.Init.NSSPolarity = SPI_NSS_POLARITY_LOW;
  hspi3.Init.FifoThreshold = SPI_FIFO_THRESHOLD_01DATA;
  hspi3.Init.TxCRCInitializationPattern = SPI_CRC_INITIALIZATION_ALL_ZERO_PATTERN;
  hspi3.Init.RxCRCInitializationPattern = SPI_CRC_INITIALIZATION_ALL_ZERO_PATTERN;
  hspi3.Init.MasterSSIdleness = SPI_MASTER_SS_IDLENESS_00CYCLE;
  hspi3.Init.MasterInterDataIdleness = SPI_MASTER_INTERDATA_IDLENESS_00CYCLE;
  hspi3.Init.MasterReceiverAutoSusp = SPI_MASTER_RX_AUTOSUSP_DISABLE;
  hspi3.Init.MasterKeepIOState = SPI_MASTER_KEEP_IO_STATE_DISABLE;
  hspi3.Init.IOSwap = SPI_IO_SWAP_DISABLE;
  if (HAL_SPI_Init(&hspi3) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN SPI3_Init 2 */

  /* USER CODE END SPI3_Init 2 */

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
  htim14.Init.Prescaler = 75-1;
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
                          |CS_LCD_Pin|AD_LCD_Pin, GPIO_PIN_RESET);

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

  /*Configure GPIO pins : LED_GREEN_3_Pin BUZZER_Pin IMD_LED_Pin RST_LCD_Pin
                           CS_LCD_Pin AD_LCD_Pin */
  GPIO_InitStruct.Pin = LED_GREEN_3_Pin|BUZZER_Pin|IMD_LED_Pin|RST_LCD_Pin
                          |CS_LCD_Pin|AD_LCD_Pin;
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

/* USER CODE BEGIN MX_GPIO_Init_2 */
/* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */
static void FDCAN_Config(void)
{
  FDCAN_FilterTypeDef sFilterConfig;

  /* Configure Rx filter */
  sFilterConfig.IdType = FDCAN_STANDARD_ID;
  sFilterConfig.FilterIndex = 0;
  sFilterConfig.FilterType = FDCAN_FILTER_RANGE;
  sFilterConfig.FilterConfig = FDCAN_FILTER_TO_RXFIFO0;
  sFilterConfig.FilterID1 = 0x00;
  sFilterConfig.FilterID2 = 0x00;
  sFilterConfig.RxBufferIndex = 0;

  if (HAL_FDCAN_ConfigFilter(&hfdcan1, &sFilterConfig) != HAL_OK)
  {
    Error_Handler();
  }

  FDCAN_FilterTypeDef sFilterConfig2;

  sFilterConfig2.IdType = FDCAN_STANDARD_ID;
  sFilterConfig2.FilterIndex = 0;
  sFilterConfig2.FilterType = FDCAN_FILTER_RANGE;
  sFilterConfig2.FilterConfig = FDCAN_FILTER_TO_RXFIFO0;
  sFilterConfig2.FilterID1 = 0x00;
  sFilterConfig2.FilterID2 = 0x00;
  sFilterConfig2.RxBufferIndex = 0;
  if (HAL_FDCAN_ConfigFilter(&hfdcan2, &sFilterConfig2) != HAL_OK)
  {
    /* Filter configuration Error */
    Error_Handler();
  }
  // STart FDCAN1
  if(HAL_FDCAN_Start(&hfdcan1)!= HAL_OK)
  {
   Error_Handler();
  }

  // STart FDCAN2
  if(HAL_FDCAN_Start(&hfdcan2)!= HAL_OK)
  {
   Error_Handler();
  }

  // Activate the notification for new data in FIFO0 for FDCAN1
  if (HAL_FDCAN_ActivateNotification(&hfdcan1, FDCAN_IT_RX_FIFO0_NEW_MESSAGE, 0) != HAL_OK)
  {
    /* Notification Error */
    Error_Handler();
  }

  // Activate the notification for new data in FIFO1 for FDCAN2
  if (HAL_FDCAN_ActivateNotification(&hfdcan2, FDCAN_IT_RX_FIFO0_NEW_MESSAGE, 0) != HAL_OK)
  {
    /* Notification Error */
    Error_Handler();
  }
}
void HAL_FDCAN_RxFifo0Callback(FDCAN_HandleTypeDef *hfdcan, uint32_t RxFifo0ITs)
{
	  if((RxFifo0ITs & FDCAN_IT_RX_FIFO0_NEW_MESSAGE) != RESET)
	  {
		  if(hfdcan->Instance==FDCAN1)
		  {

	rx_sorter_can1(*hfdcan, RxMailbox, RxHeader, RxData, &msg, &Car__State, &PrechargeVoltage, &PrechargePercentage,
			&CarSpeed, &SoC_Average, &END_SD, &BMS_SD, &IMD_SD, &syncronism1, &Lowest_CellTemperature, &Highest_CellTemperature,
			&Average_CellTemperature, &VDC_Params, &Lowest_CellVolt, &Highest_CellVolt, &Accu_Volt, &TV_MODE, &LV_CURRENT);
	  }
		  if(hfdcan->Instance==FDCAN2)
		  {

	rx_sorter_can2(*hfdcan, RxMailbox, RxHeader, RxData, &msg_can2, &SteeringSensor_Disconnect, &SuspRR_Disconnect, &SuspRL_Disconnect,
			&SuspFR_Disconnect, &SuspFL_Disconnect, &Pitot_Disconnect, &BMS_Disconnect, &Dash_Disconect, &Front_Disconenct,
			&Ellipse_Disconect, &Rear_Disconnect, &APPS1_Disconect, &APPS2_Disconnect, &BrakePedal_Disconnect, &Shutdown_Setas,
			&Shutdown_BSPD_Inertia, &Shutdown_SC_BOTS, &Shutdown_TSMS_TSMP, &Shutdown_RightTS, &Shutdown_LeftTS, &Shutdown_HVBox,
			&Shutdown_HVD, &syncronism2, &APPS1, &APPS2, &Break_Value, &Steering_sensor_value, &BMS_OK);
		  }
	  }
}

//void HAL_FDCAN_RxFifo1Callback(FDCAN_HandleTypeDef *hfdcan, uint32_t RxFifo1ITs)
//{
//	cunter++;
//	  if((RxFifo1ITs & FDCAN_IT_RX_FIFO1_NEW_MESSAGE) != RESET)
//	  {
//
//	rx_sorter_can2(*hfdcan, RxMailbox, RxHeader, RxData, &msg_can2, &SteeringSensor_Disconnect, &SuspRR_Disconnect, &SuspRL_Disconnect,
//			&SuspFR_Disconnect, &SuspFL_Disconnect, &Pitot_Disconnect, &BMS_Disconnect, &Dash_Disconect, &Front_Disconenct,
//			&Ellipse_Disconect, &Rear_Disconnect, &APPS1_Disconect, &APPS2_Disconnect, &BrakePedal_Disconnect, &Shutdown_Setas,
//			&Shutdown_BSPD_Inertia, &Shutdown_SC_BOTS, &Shutdown_TSMS_TSMP, &Shutdown_RightTS, &Shutdown_LeftTS, &Shutdown_HVBox,
//			&Shutdown_HVD, &syncronism2, &APPS1, &APPS2, &Break_Value, &Steering_sensor_value);
//	  }
//}


void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {

	if (htim->Instance == TIM14)
	{

		switch(msg){
			case 1:
				message_cantx_Keep_Alive(hfdcan1, TxHeader, TxData, KeepAlive);
				KeepAlive++;
				msg = 2;
			break;
			case 2:
				message_cantx_EnableDrive(hfdcan1,  TxHeader, TxData, Enable_Drive);
				Enable_Drive = 0;
				msg = 3;
			break;
			case 3:
				message_cantx_PrechargeRequest(hfdcan1, TxHeader, TxData, Precharge_Request);
				msg = 4;
			break;
			case 4:
				message_cantx_Mode(hfdcan1, TxHeader, TxData, Racing_Mode);
				msg = 5;
			break;
			case 5:
				message_cantx_Cooling(hfdcan2, TxHeader, TxData, Refri_Accumulator, Refri_Inverters, Refri_Motors);
				msg = 0;
			break;
		}
		if(HAL_GetTick() >=5000){
			BMS_IMD_ERROR(BMS_Disconnect, BMS_OK, BMS_SD, IMD_SD, &BMS_SD_SC, &IMD_SD_SC, &BMS_DISC_SC);
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
