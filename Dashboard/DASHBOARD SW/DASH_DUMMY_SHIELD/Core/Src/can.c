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
uint32_t TxMailbox;



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

void message_cantx_Cooling (CAN_HandleTypeDef hcan2, CAN_TxHeaderTypeDef TxHeader, uint8_t *TxData, uint8_t Refri_Accu, uint8_t Refri_Inverters, uint8_t Refri_Motors){
	TxHeader.DLC = 1;                                        //Number of bites to be transmitted max->8.
	TxHeader.IDE = CAN_ID_STD;                               //IDE: Identifier Extension. ID_STD: Standard Identifier. Dominant(0) = 11 bit ID, Recessive(1) = 29 bit ID
	TxHeader.RTR = CAN_RTR_DATA;                             //RTR: Remote Transmission Request, Dominant(0) = Data frame, Recessive (1) = Remote Frame. Type of trace
	TxHeader.StdId = Id_Cooling;                             //Standard identifier ID
	TxHeader.TransmitGlobalTime = DISABLE;                   //A temporal mark in the CAN message is not added
    TxData[0] = (Refri_Accu) | (Refri_Inverters <<2) | (Refri_Motors <<4);       //Sent data. The TxData is the buffer where the data is saved
    if (HAL_CAN_AddTxMessage(&hcan2, &TxHeader, TxData, &TxMailbox) != HAL_OK);
}


void message_cantx_EnableDrive (CAN_HandleTypeDef hcan1, CAN_TxHeaderTypeDef TxHeader, uint8_t *TxData, uint8_t EnableDrive_Order){
	TxHeader.DLC = 1;
	TxHeader.IDE = CAN_ID_STD;
	TxHeader.RTR = CAN_RTR_DATA;
	TxHeader.StdId = Id_EnableDrive;
	TxHeader.TransmitGlobalTime = DISABLE;
    TxData[0] = EnableDrive_Order;
    if (HAL_CAN_AddTxMessage(&hcan1, &TxHeader, TxData, &TxMailbox) != HAL_OK);
}

void message_cantx_Keep_Alive (CAN_HandleTypeDef hcan1, CAN_TxHeaderTypeDef TxHeader, uint8_t *TxData, uint8_t Dash_Alive){
	TxHeader.DLC = 1;
	TxHeader.IDE = 0;
	TxHeader.RTR = 0;
	TxHeader.StdId = 0xCB;
	TxHeader.TransmitGlobalTime = DISABLE;
    TxData[0] = Dash_Alive;
    if (HAL_CAN_AddTxMessage(&hcan1, &TxHeader, TxData, &TxMailbox) != HAL_OK);
}

void message_cantx_Mode (CAN_HandleTypeDef hcan1, CAN_TxHeaderTypeDef TxHeader, uint8_t *TxData, uint8_t RacingMode){
	TxHeader.DLC = 1;
	TxHeader.IDE = CAN_ID_STD;
	TxHeader.RTR = CAN_RTR_DATA;
	TxHeader.StdId = Id_Mode;
	TxHeader.TransmitGlobalTime = DISABLE;
    TxData[0] = RacingMode;
    if (HAL_CAN_AddTxMessage(&hcan1, &TxHeader, TxData, &TxMailbox) != HAL_OK);
}

void message_cantx_PrechargeRequest (CAN_HandleTypeDef hcan1, CAN_TxHeaderTypeDef TxHeader, uint8_t *TxData, uint8_t PrechargeRequest){
	TxHeader.DLC = 1;
	TxHeader.IDE = CAN_ID_STD;
	TxHeader.RTR = CAN_RTR_DATA;
	TxHeader.StdId = Id_PrechargeRequest;
	TxHeader.TransmitGlobalTime = DISABLE;
    TxData[0] = PrechargeRequest;
    if (HAL_CAN_AddTxMessage(&hcan1, &TxHeader, TxData, &TxMailbox) != HAL_OK);
}


void rx_sorter_can1(CAN_HandleTypeDef hcan1, uint32_t RxMailbox, CAN_RxHeaderTypeDef RXHeader, uint8_t *RxData, uint8_t *msg_var,
		uint8_t *Car_State, uint16_t *Precharge_Voltage, uint8_t *Precharge_Percentage, uint8_t *Speed, uint8_t *SoC_Avg,uint8_t *SDC_END, uint8_t *SDC_BMS,uint8_t *SDC_IMD,uint8_t *AMS_LED,uint8_t *IMD_LED,
		uint8_t *Sync,  uint16_t *Lowest_CellTemp, uint16_t *Highest_CellTemp, uint16_t *Average_CellTemp, uint8_t *VDC_Max_Tyre_Slip,
		uint16_t *Lowest_CellVoltage, uint16_t *Highest_CellVoltage, uint32_t *Accumulator_Voltage, uint8_t *TV_MODE){

	if (HAL_CAN_GetRxMessage(&hcan1, CAN_RX_FIFO0, &RXHeader, RxData)!= HAL_OK){
		Error_Handler();
	}


	switch(RXHeader.StdId){

	case Id_CarState:

		*Car_State = RxData[0];

		break;

	case Id_DashData:

		*Precharge_Voltage = (RxData[1]) + (RxData[0] << 8);
		*Precharge_Percentage = RxData[2];
		*Speed = RxData[3];
		*SoC_Avg = RxData[4];

		break;


	case Id_SDC_BMS:

		*SDC_END = 0x01&RxData[0];
		*SDC_BMS = 0x01&(RxData[0]>>1);
		*SDC_IMD = 0x01&(RxData[0]>>2);
		*AMS_LED = 0x01&(RxData[0]>>3);
		*IMD_LED = 0x01&(RxData[0]>>4);

		break;


	case Id_Synchronism:

		*Sync = RxData[0];				//hacer otra variable para CAN1 Y CAN2

		*msg_var = 1;

		break;

	case Id_ETAS_Interal_Values:

		*TV_MODE = 0b00000111&RxData[1];


		break;

	case Id_Temperatures:

		*Lowest_CellTemp = (uint16_t)(RxData[0]) << 8 | (uint16_t)(RxData[1]);
		*Highest_CellTemp = (uint16_t)(RxData[2]) << 8 | (uint16_t)(RxData[3]);
		*Average_CellTemp = (uint16_t)(RxData[4]) << 8 | (uint16_t)(RxData[5]);

		break;


	case Id_VDCParams:

		*VDC_Max_Tyre_Slip = RxData[0];

		break;


	case Id_Voltages:


		*Lowest_CellVoltage= (uint16_t)(RxData[0])  << 8 | (uint16_t)(RxData[1]);
		*Highest_CellVoltage = (uint16_t)(RxData[2])  << 8 | (uint16_t)(RxData[3]);
		*Accumulator_Voltage = (uint32_t)(RxData[4])  << 16 | (uint32_t)(RxData[5] << 8) | (uint32_t)(RxData[6]);


		break;

	}
}



void rx_sorter_can2(CAN_HandleTypeDef hcan2, uint32_t RxMailbox, CAN_RxHeaderTypeDef RXHeader, uint8_t *RxData, uint8_t *msg_var,
		uint8_t *Disconnection_SteeringSensor, uint8_t *Disconnection_Susp_R_R, uint8_t *Disconnection_Susp_R_L, uint8_t *Disconnection_Susp_F_R,
		uint8_t *Disconnection_Susp_F_L, uint8_t *Disconnection_Pitot, uint8_t *Disconnection_BMS, uint8_t *Disconnection_DashBoard,
		uint8_t *Disconnection_Front, uint8_t *Disconnection_Ellipse, uint8_t *Disconnection_Rear, uint8_t *Disconnection_APPS1, uint8_t *Disconnection_APPS2,
		uint8_t *Disconnection_BrakePedal, uint8_t *Shutdown_Setas, uint8_t *Shutdown_BSPD_Inertia, uint8_t *Shutdown_SC_BOTS, uint8_t *Shutdown_TSMS_TSMP,
		uint8_t *Shutdown_RightTS, uint8_t *Shutdown_LeftTS, uint8_t *Shutdown_HVBox, uint8_t *Shutdown_HVD, uint8_t *Sync,
		uint8_t *APPS1, uint8_t *APPS2, uint8_t *Break_Value, uint8_t *Steering_sensor_value){

	if (HAL_CAN_GetRxMessage(&hcan2, CAN_RX_FIFO1, &RXHeader, RxData)!= HAL_OK);

	switch(RXHeader.StdId){

	case Id_Disconnections:

		*Disconnection_BMS = RxData[0] & 1;
		*Disconnection_DashBoard = (RxData[0] >> 1) & 0x01;
		*Disconnection_Front = (RxData[0] >> 2) & 0x01;
		*Disconnection_Ellipse = (RxData[0] >> 3) & 0x01;
		*Disconnection_Rear = (RxData[0] >> 4) & 0x01;
		*Disconnection_APPS1 = (RxData[0] >> 5) & 0x01;
		*Disconnection_APPS2 = (RxData[0] >> 6) & 0x01;
		*Disconnection_BrakePedal = (RxData[0] >> 7) & 0x01;
		*Disconnection_SteeringSensor = RxData[1] & 0x01;
		*Disconnection_Susp_R_R = (RxData[1] >> 1) & 0x01;
		*Disconnection_Susp_R_L = (RxData[1] >> 2) & 0x01;
		*Disconnection_Susp_F_R = (RxData[1] >> 3) & 0x01;
		*Disconnection_Susp_F_L = (RxData[1] >> 4) & 0x01;
		*Disconnection_Pitot = (RxData[1] >> 5) & 0x01;
		break;

	case Id_VDC_Values:
		*APPS1 = RxData[0];
		*APPS2 = RxData[1];
		*Break_Value = RxData[2];
		*Steering_sensor_value = RxData[3];
		break;

	case Id_SDC_Front:
		*Shutdown_Setas = 0x01&RxData[0];
		*Shutdown_BSPD_Inertia = 0x01&(RxData[0]>>1);
		*Shutdown_SC_BOTS = 0x01&(RxData[0]>>2);

		break;

	case Id_SDC_Rear:
		*Shutdown_TSMS_TSMP = 0x01&RxData[0];
		*Shutdown_RightTS = 0x01&(RxData[0]>>1);
		*Shutdown_LeftTS = 0x01&(RxData[0]>>2);
		*Shutdown_HVBox = 0x01&(RxData[0]>>3);
		*Shutdown_HVD = 0x01&(RxData[0]>>4);

		break;


	case Id_Synchronism:

		*Sync = RxData[0];

		*msg_var = 1;

		break;

	}
}


