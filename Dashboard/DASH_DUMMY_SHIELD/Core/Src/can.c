/*
 *  can.c
 *
 *  Created on: May 2, 2024
 *      Author: Pol Crespiera Rododreda
 *
 *  This Source file contains functions used for the CAN Communication in the
 *  code for the Dashboard.
 *
 *  The functions that start with "message_cantx" are the ones in charge of taking the various
 *  signals and variables and preparing the whole message and header for the CAN communication.
 *
 *  The functions that start with "message_canrx" are the ones in charge of taking the data received
 *  and adapting it to the thing needed.
 */

#include "can.h"
#include "main.h"


/*
 * 	Function: filtercanconfig
 * 	Purpose: Define the configurations needed to recieve data.
 * 	Inputs: None.
 */


void filtercanconfig_can1(CAN_FilterTypeDef *filtercan1){
	filtercan1->FilterActivation = ENABLE;          // This activates the filter as it is enable
	filtercan1->FilterBank = 0;                                // This refers to which filter is being configured. On this case is the filter number 0
	filtercan1->FilterFIFOAssignment = CAN_FILTER_FIFO0;       // Defines at which FIFO is this filter being configured to.
	filtercan1->FilterIdHigh = 0x0000;                         // MSB: Most Significant Bit. When it's in 0, accepts all the messages
	filtercan1->FilterIdLow = 0x0000;                          // LSB: Least Significant Bit. When it's in 0, accepts all the messages
	filtercan1->FilterMaskIdHigh = 0x0000;                     // Most Significant Bit of the mask. When it's in 0, accepts all the messages
	filtercan1->FilterMaskIdLow = 0x0000;                      // Least Significant Bit of the mask. When it's in 0, accepts all the messages
	filtercan1->FilterMode = CAN_FILTERMODE_IDMASK;            // FilterMode: How are we filtering the incoming messages. Only the messages that coincide with the mask and the filter are accepted
	filtercan1->FilterScale = CAN_FILTERSCALE_32BIT;           // Defines the Filter Scale. (use the 32 bits)
	filtercan1->SlaveStartFilterBank = 14;                     // Indicates the first filter slave number. In this case it is the principal filter.

}

void filtercanconfig_can2(CAN_FilterTypeDef *filtercan2){
	filtercan2->FilterActivation = ENABLE;          // This activates the filter as it is enable
	filtercan2->FilterBank = 14;                                // This refers to which filter is being configured. On this case is the filter number 0
	filtercan2->FilterFIFOAssignment = CAN_FILTER_FIFO1;       // Defines at which FIFO is this filter being configured to.
	filtercan2->FilterIdHigh = 0x0000;                         // MSB: Most Significant Bit. When it's in 0, accepts all the messages
	filtercan2->FilterIdLow = 0x0000;                          // LSB: Least Significant Bit. When it's in 0, accepts all the messages
	filtercan2->FilterMaskIdHigh = 0x0000;                     // Most Significant Bit of the mask. When it's in 0, accepts all the messages
	filtercan2->FilterMaskIdLow = 0x0000;                      // Least Significant Bit of the mask. When it's in 0, accepts all the messages
	filtercan2->FilterMode = CAN_FILTERMODE_IDMASK;            // FilterMode: How are we filtering the incoming messages. Only the messages that coincide with the mask and the filter are accepted
	filtercan2->FilterScale = CAN_FILTERSCALE_32BIT;           // Defines the Filter Scale. (use the 32 bits)
	filtercan2->SlaveStartFilterBank = 14;                     // Indicates the first filter slave number. In this case it is the principal filter.

}

void message_cantx_Cooling (CAN_HandleTypeDef hcan2, uint32_t TxMailbox, CAN_TxHeaderTypeDef TxHeader, uint8_t *TxData, uint8_t *Refri_Accu, uint8_t *Refri_Inverters){
	TxHeader.DLC = 1;                                        //Number of bites to be transmitted max->8.
	TxHeader.IDE = CAN_ID_STD;                               //IDE: Identifier Extension. ID_STD: Standard Identifier. Dominant(0) = 11 bit ID, Recessive(1) = 29 bit ID
	TxHeader.RTR = CAN_RTR_DATA;                             //RTR: Remote Transmission Request, Dominant(0) = Data frame, Recessive (1) = Remote Frame. Type of trace
	TxHeader.StdId = Id_Cooling;                             //Standard identifier ID
	TxHeader.TransmitGlobalTime = DISABLE;                   //A temporal mark in the CAN message is not added
    TxData[0] = (uint8_t)(Refri_Accu[0]) | (uint8_t)(Refri_Inverters[0]) <<1;       //Sent data. The TxData is the buffer where the data is saved
    if (HAL_CAN_AddTxMessage(&hcan2, &TxHeader, TxData, &TxMailbox) != HAL_OK);
}


void message_cantx_EnableDrive (CAN_HandleTypeDef hcan1, uint32_t TxMailbox, CAN_TxHeaderTypeDef TxHeader, uint8_t *TxData, uint8_t *EnableDrive_Order){
	TxHeader.DLC = 1;
	TxHeader.IDE = CAN_ID_STD;
	TxHeader.RTR = CAN_RTR_DATA;
	TxHeader.StdId = Id_EnableDrive;
	TxHeader.TransmitGlobalTime = DISABLE;
    TxData[0] = EnableDrive_Order[0];
    if (HAL_CAN_AddTxMessage(&hcan1, &TxHeader, TxData, &TxMailbox) != HAL_OK);
}

void message_cantx_Keep_Alive (CAN_HandleTypeDef hcan1, uint32_t TxMailbox, CAN_TxHeaderTypeDef TxHeader, uint8_t *TxData, uint8_t *Dash_Alive){
	TxHeader.DLC = 1;
	TxHeader.IDE = CAN_ID_STD;
	TxHeader.RTR = CAN_RTR_DATA;
	TxHeader.StdId = Id_Keep_Alive;
	TxHeader.TransmitGlobalTime = DISABLE;
    TxData[0] = Dash_Alive[0];
    if (HAL_CAN_AddTxMessage(&hcan1, &TxHeader, TxData, &TxMailbox) != HAL_OK);
}

void message_cantx_Mode (CAN_HandleTypeDef hcan1, uint32_t TxMailbox, CAN_TxHeaderTypeDef TxHeader, uint8_t *TxData, uint8_t *RacingMode){
	TxHeader.DLC = 1;
	TxHeader.IDE = CAN_ID_STD;
	TxHeader.RTR = CAN_RTR_DATA;
	TxHeader.StdId = Id_Mode;
	TxHeader.TransmitGlobalTime = DISABLE;
    TxData[0] = RacingMode[0];
    if (HAL_CAN_AddTxMessage(&hcan1, &TxHeader, TxData, &TxMailbox) != HAL_OK);
}

void message_cantx_PrechargeRequest (CAN_HandleTypeDef hcan1, uint32_t TxMailbox, CAN_TxHeaderTypeDef TxHeader, uint8_t *TxData, uint8_t *PrechargeRequest){
	TxHeader.DLC = 1;
	TxHeader.IDE = CAN_ID_STD;
	TxHeader.RTR = CAN_RTR_DATA;
	TxHeader.StdId = Id_PrechargeRequest;
	TxHeader.TransmitGlobalTime = DISABLE;
    TxData[0] = PrechargeRequest[0];
    if (HAL_CAN_AddTxMessage(&hcan1, &TxHeader, TxData, &TxMailbox) != HAL_OK);
}


void rx_sorter_can1(CAN_HandleTypeDef hcan1, uint32_t RxMailbox, CAN_RxHeaderTypeDef RXHeader, uint8_t *RxData, char *msg_var,
		uint8_t *Car_State, uint16_t *Precharge_Voltage, uint8_t *Precharge_Percentage, uint8_t *Speed, uint8_t *SoC_Avg, uint8_t *SCD_BMS,
		uint8_t *Sync,  uint16_t *Lowest_CellTemp, uint16_t *Highest_CellTemp, uint16_t *Average_CellTemp, uint8_t *VDC_Max_Tyre_Slip,
		uint16_t *Lowest_CellVoltage, uint16_t *Highest_CellVoltage, uint32_t *Accumulator_CellVoltage){

	if (HAL_CAN_GetRxMessage(&hcan1, CAN_RX_FIFO0, &RXHeader, RxData)!= HAL_OK);

	*msg_var = 1;

	switch(RXHeader.StdId){


	case Id_CarState:

		HAL_GPIO_TogglePin(LED_GREEN_2_GPIO_Port, LED_GREEN_2_Pin);
		Car_State[0] = RxData[0];

		break;


	case Id_DashData:

		Precharge_Voltage[0] = (uint16_t)(RxData[1]) | (uint16_t)(RxData[0] << 8);
		Precharge_Percentage[0] = RxData[2];
		Speed[0] = RxData[3];
		SoC_Avg[0] = RxData[4];

		break;


	case Id_SDC_BMS:

		SCD_BMS[0] = RxData[0];

		break;


	case Id_Synchronism:

		Sync[0] = RxData[0];				//hacer otra variable para CAN1 Y CAN2

		msg_var[0] = 1;

		break;


	case Id_Temperatures:

		Lowest_CellTemp[0] = (uint16_t)(RxData[0]) << 8 | (uint16_t)(RxData[1]);
		Highest_CellTemp[0] = (uint16_t)(RxData[2]) << 8 | (uint16_t)(RxData[3]);
		Average_CellTemp[0] = (uint16_t)(RxData[4]) << 8 | (uint16_t)(RxData[5]);

		break;


	case Id_VDCParams:

		VDC_Max_Tyre_Slip[0] = RxData[0];

		break;


	case Id_Voltages:


		Lowest_CellVoltage[0] = (uint16_t)(RxData[0])  << 8 | (uint16_t)(RxData[1]);
		Highest_CellVoltage[0] = (uint16_t)(RxData[2])  << 8 | (uint16_t)(RxData[3]);
		Accumulator_CellVoltage[0] = (uint32_t)(RxData[4])  << 16 | (uint32_t)(RxData[5] << 8) | (uint32_t)(RxData[6]);


		break;

	}
}



void rx_sorter_can2(CAN_HandleTypeDef hcan2, uint32_t RxMailbox, CAN_RxHeaderTypeDef RXHeader, uint8_t *RxData, char *msg_var,
		uint8_t *Disconnection_SteeringSensor, uint8_t *Disconnection_Susp_R_R, uint8_t *Disconnection_Susp_R_L, uint8_t *Disconnection_Susp_F_R,
		uint8_t *Disconnection_Susp_F_L, uint8_t *Disconnection_Pitot, uint8_t *Disconnection_BMS, uint8_t *Disconnection_DashBoard,
		uint8_t *Disconnection_Front, uint8_t *Disconnection_Ellipse, uint8_t *Disconnection_Rear, uint8_t *Disconnection_APPS1, uint8_t *Disconnection_APPS2,
		uint8_t *Disconnection_BrakePedal, uint8_t *SCD_Front, uint8_t *SCD_Rear, uint8_t *Sync){

	if (HAL_CAN_GetRxMessage(&hcan2, CAN_RX_FIFO0, &RXHeader, RxData)!= HAL_OK);

	*msg_var = 1;

	switch(RXHeader.StdId){


	case Id_Disconnections:

		Disconnection_BMS[0] = RxData[0] & 1;
		Disconnection_DashBoard[0] = RxData[0] << 1 & 128;
		Disconnection_Front[0] = RxData[0] << 2 & 128;
		Disconnection_Ellipse[0] = RxData[0] << 3 & 128;
		Disconnection_Rear[0] = RxData[0] << 4 & 128;
		Disconnection_APPS1[0] = RxData[0] << 5 & 128;
		Disconnection_APPS2[0] = RxData[0] << 6 & 128;
		Disconnection_BrakePedal[0] = RxData[0] << 7 & 128;
		Disconnection_SteeringSensor[0] = RxData[1] & 128;
		Disconnection_Susp_R_R[0] = RxData[1] << 1 & 128;
		Disconnection_Susp_R_L[0] = RxData[1] << 2 & 128;
		Disconnection_Susp_F_R[0] = RxData[1] << 3 & 128;
		Disconnection_Susp_F_L[0] = RxData[1] << 4 & 128;
		Disconnection_Pitot[0] = RxData[1] << 5 & 128;

		break;


	case Id_SDC_Front:

		SCD_Front[0] = RxData[0];

		break;


	case Id_SDC_Rear:

		SCD_Rear[0] = RxData[0];

		break;


	case Id_Synchronism:

		Sync[0] = RxData[0];

		msg_var[0] = 1;

		break;

	}
}


