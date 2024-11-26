/*
 * init.c
 *
 *  Created on: Jun 7, 2024
 *      Author: Carmen Unió Cruz
 *
 */


#include "main.h"
#include "init.h"
#include "can.h"
#include "statemachine.h"


void NORMATIVE_INIT(void){

		//Turn On the Buzzer
//	HAL_GPIO_WritePin(BUZZER_GPIO_Port, BUZZER_Pin, 1);
//
//		//Delays the Sound a Time set by FS Rules 2,5 seconds
//	HAL_Delay(0);
//
//		//Turns Off the Buzzer
//	HAL_GPIO_WritePin(BUZZER_GPIO_Port, BUZZER_Pin, 0);

		// Turns On the IMD and AMS LEDs
	HAL_GPIO_WritePin(IMD_LED_GPIO_Port, IMD_LED_Pin,1);
	HAL_GPIO_WritePin(AMS_LED_GPIO_Port, AMS_LED_Pin,1);

		// Delays a Set Time found in FS Rules 2,5 seconds
	HAL_Delay(NORMATIVE_TIME_LED);

		//Turns Off the LEDs
	HAL_GPIO_WritePin(IMD_LED_GPIO_Port, IMD_LED_Pin,0);
	HAL_GPIO_WritePin(AMS_LED_GPIO_Port, AMS_LED_Pin,0);

}

//void CAN1_CONFIG_INIT(FDCAN_FilterTypeDef canfil1, FDCAN_HandleTypeDef hcan1){
//
//		//Config of the Filter
//    if(HAL_CAN_ConfigFilter(&hcan1, &canfil1) != HAL_OK) Error_Handler();
//
//    	//Starts the Peripheral
//    if(HAL_CAN_Start(&hcan1) != HAL_OK)Error_Handler();
//
//    	//Activates the notifications and the Interruption that uses. In this case a Message Pending in the FIFO 0.
//    if(HAL_CAN_ActivateNotification(&hcan1, CAN_IT_RX_FIFO0_MSG_PENDING) != HAL_OK)Error_Handler();
//}
//
//void CAN2_CONFIG_INIT(FDCAN_FilterTypeDef canfil2, FDCAN_HandleTypeDef hcan2){
//
//		//Config of the Filter
//    if(HAL_CAN_ConfigFilter(&hcan2, &canfil2) != HAL_OK) Error_Handler();
//
//		//Starts the Peripheral
//    if(HAL_CAN_Start(&hcan2) != HAL_OK)Error_Handler();
//
//		//Activates the notifications and the Interruption that uses. In this case a Message Pending in the FIFO 1.
//    if(HAL_CAN_ActivateNotification(&hcan2, CAN_IT_RX_FIFO1_MSG_PENDING) != HAL_OK)Error_Handler();
//}

void VARIABLE_RESET(uint8_t *EnableDrive, uint8_t *RacingMode, uint8_t *PrechargeRequest, uint8_t *KeepAliveDash, uint8_t *Refri_Inverters, uint8_t *Refri_Accu, uint8_t *Refri_Motors, uint8_t *msgcan1, uint8_t *msgcan2, uint8_t *CarState_, uint8_t *PrechargeReqControl){

		// Sets to 0 all the variables that require to be Reset
	*EnableDrive = 0;
	*RacingMode = 1;
	*PrechargeRequest = 0;
	*KeepAliveDash = 0;
	*msgcan1 = 0;
	*msgcan2 = 0;
	*Refri_Inverters = 1;
	*Refri_Accu = 1;
	*Refri_Motors = 1;
	*CarState_ = 0;
	*PrechargeReqControl = 0;


}
