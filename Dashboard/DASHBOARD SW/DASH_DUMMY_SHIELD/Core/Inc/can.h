/*
 * can.h
 *
 *  Created on: May 2, 2024
 *      Author: Pol Crespiera Rododreda
 */

#ifndef INC_CAN_H_
#define INC_CAN_H_

#include "main.h"

/* TX ID --------------------------------------------------------------------*/
#define Id_Cooling 			0xA1
#define Id_CustomeMode 		0xA5
#define Id_EnableDrive 		0xA1
#define Id_Keep_Alive 		0xCB
#define Id_Mode 			0xA2
#define Id_PrechargeRequest 0xA0
#define Id_TorqueLockOn 	0xA3

/* RX ID --------------------------------------------------------------------*/

#define Id_CarState 		0x81
#define Id_DashData 		0x83
#define Id_Disconnections 	0xCD
#define Id_SDC_BMS 			0x90
#define Id_SDC_Front 		0xD0
#define Id_SDC_Rear 		0xD1
#define Id_Synchronism 		0x80
#define Id_Temperatures 	0x93
#define Id_VDCParams 		0x8F
#define Id_Voltages 		0x92
#define Id_VDC_Values		0xD5

void filtercanconfig_can1(CAN_FilterTypeDef *filtercan1);
void filtercanconfig_can2(CAN_FilterTypeDef *filtercan2);


/**
  * @brief  Takes the Global Variables and sends it via CAN.
  * @param  hcan CAN_HandleTypeDef structure that contains
  *         the configuration information for the specified CAN.
  * @param  TxMailbox CAN_HeaderTypeDef structure that contains
  *         the configuration information for the specified CAN.
  * @param  TxData pointer to a uint8_t variable  that contains
  *         the Data that will be sent via CAN.
  * @param  uint8_t variable that contains the data sent via CAN.
  * @retval None
  */
void message_cantx_Cooling (CAN_HandleTypeDef hcan2, CAN_TxHeaderTypeDef TxHeader, uint8_t *TxData, uint8_t Refri_Accu, uint8_t Refri_Inverters, uint8_t Refri_Motors);

/**
  * @brief  Takes the Global Variables and sends it via CAN.
  * @param  hcan CAN_HandleTypeDef structure that contains
  *         the configuration information for the specified CAN.
  * @param  TxMailbox CAN_HeaderTypeDef structure that contains
  *         the configuration information for the specified CAN.
  * @param  TxData pointer to a uint8_t variable  that contains
  *         the Data that will be sent via CAN.
  * @param  uint8_t variable that contains the data sent via CAN.
  * @retval None
  */
void message_cantx_EnableDrive (CAN_HandleTypeDef hcan1, CAN_TxHeaderTypeDef TxHeader, uint8_t *TxData, uint8_t EnableDrive_Order);

/**
  * @brief  Takes the Global Variables and sends it via CAN.
  * @param  hcan CAN_HandleTypeDef structure that contains
  *         the configuration information for the specified CAN.
  * @param  TxMailbox CAN_HeaderTypeDef structure that contains
  *         the configuration information for the specified CAN.
  * @param  TxData pointer to a uint8_t variable  that contains
  *         the Data that will be sent via CAN.
  * @param  uint8_t variable that contains the data sent via CAN.
  * @retval None
  */
void message_cantx_Keep_Alive (CAN_HandleTypeDef hcan1, CAN_TxHeaderTypeDef TxHeader, uint8_t *TxData, uint8_t Dash_Alive);

/**
  * @brief  Takes the Global Variables and sends it via CAN.
  * @param  hcan CAN_HandleTypeDef structure that contains
  *         the configuration information for the specified CAN.
  * @param  TxMailbox CAN_HeaderTypeDef structure that contains
  *         the configuration information for the specified CAN.
  * @param  TxData pointer to a uint8_t variable  that contains
  *         the Data that will be sent via CAN.
  * @param  uint8_t variable that contains the data sent via CAN.
  * @retval None
  */
void message_cantx_Mode (CAN_HandleTypeDef hcan1, CAN_TxHeaderTypeDef TxHeader, uint8_t *TxData, uint8_t RacingMode);

/**
  * @brief  Takes the Global Variables and sends it via CAN.
  * @param  hcan CAN_HandleTypeDef structure that contains
  *         the configuration information for the specified CAN.
  * @param  TxMailbox CAN_HeaderTypeDef structure that contains
  *         the configuration information for the specified CAN.
  * @param  TxData pointer to a uint8_t variable  that contains
  *         the Data that will be sent via CAN.
  * @param  uint8_t variable that contains the data sent via CAN.
  * @retval None
  */
void message_cantx_PrechargeRequest (CAN_HandleTypeDef hcan1, CAN_TxHeaderTypeDef TxHeader, uint8_t *TxData, uint8_t PrechargeRequest);
/*

void rx_sorter(CAN_HandleTypeDef hcan1, uint32_t TxMailbox, CAN_RxHeaderTypeDef RxHeader, uint8_t RxData, uint8_t *Disconnection_SteeringSensor,
		uint8_t *Disconnection_Susp_R_R, uint8_t *Disconnection_Susp_R_L, uint8_t *Disconnection_Susp_F_R, uint8_t *Disconnection_Susp_F_L, uint8_t *Disconnection_Pitot,
		uint8_t *Disconnection_BMS, uint8_t *Disconnection_DashBoard, uint8_t *Disconnection_Front, uint8_t *Disconnection_Ellipse, uint8_t *Disconnection_Rear,
		uint8_t *Disconnection_APPS1, uint8_t *Disconnection_APPS2, uint8_t *Disconnection_BrakePedal, uint8_t *Car_State, uint16_t *Precharge_Voltage, uint8_t *Precharge_Percentage,
		uint8_t *Speed, uint8_t *SoC_Avg, uint16_t *Disconections, uint8_t *SCD_BMS, uint8_t *SCD_Front, uint8_t *SCD_Rear, uint8_t *Sync_CAN1, uint16_t *Lowest_CellTemp,
		uint16_t *Highest_CellTemp, uint16_t *Average_CellTemp, uint8_t *VDC_Max_Tyre_Slip, uint16_t *Lowest_CellVoltage, uint16_t *Highest_CellVoltage, uint32_t *Accumulator_CellVoltage);
*/

/**
  * @brief  Takes the Data from the CAN1 Message and sorts it in
  * 		different variables depending of the ID and position
  * 		byte-wise.
  * @param  hcan CAN_HandleTypeDef structure that contains
  *         the configuration information for the specified CAN.
  * @param  RxMailbox uint32_t variable that contains the
  * 		RxData and RxHeader.
  * @param  RxHeader CAN_HeaderTypeDef structure that contains
  *         the configuration information for the specified CAN.
  * @param  RxData pointer to a uint8_t variable  that contains
  *         the Data that will be sent via CAN.
  * @param  pointer to uint8_t variable that contains the data
  * 		thats going to be updated when a message is received.
  * @retval None
  */
void rx_sorter_can1(CAN_HandleTypeDef hcan1, uint32_t RxMailbox, CAN_RxHeaderTypeDef RXHeader, uint8_t *RxData, uint8_t *msg_var,
		uint8_t *Car_State, uint16_t *Precharge_Voltage, uint8_t *Precharge_Percentage, uint8_t *Speed, uint8_t *SoC_Avg,uint8_t *SDC_END, uint8_t *SDC_BMS,uint8_t *SDC_IMD,
		uint8_t *Sync,  uint16_t *Lowest_CellTemp, uint16_t *Highest_CellTemp, uint16_t *Average_CellTemp, uint8_t *VDC_Max_Tyre_Slip,
		uint16_t *Lowest_CellVoltage, uint16_t *Highest_CellVoltage, uint32_t *Accumulator_Voltage);
/**
  * @brief  Takes the Data from the CAN2 Message and sorts it in
  * 		different variables depending of the ID and position
  * 		byte-wise.
  * @param  hcan CAN_HandleTypeDef structure that contains
  *         the configuration information for the specified CAN.
  * @param  RxMailbox uint32_t variable that contains the
  * 		RxData and RxHeader.
  * @param  RxHeader CAN_HeaderTypeDef structure that contains
  *         the configuration information for the specified CAN.
  * @param  RxData pointer to a uint8_t variable  that contains
  *         the Data that will be sent via CAN.
  * @param  pointer to uint8_t variable that contains the data
  * 		thats going to be updated when a message is received.
  * @retval None
  */
void rx_sorter_can2(CAN_HandleTypeDef hcan2, uint32_t RxMailbox, CAN_RxHeaderTypeDef RXHeader, uint8_t *RxData, uint8_t *msg_var,
		uint8_t *Disconnection_SteeringSensor, uint8_t *Disconnection_Susp_R_R, uint8_t *Disconnection_Susp_R_L, uint8_t *Disconnection_Susp_F_R,
		uint8_t *Disconnection_Susp_F_L, uint8_t *Disconnection_Pitot, uint8_t *Disconnection_BMS, uint8_t *Disconnection_DashBoard,
		uint8_t *Disconnection_Front, uint8_t *Disconnection_Ellipse, uint8_t *Disconnection_Rear, uint8_t *Disconnection_APPS1, uint8_t *Disconnection_APPS2,
		uint8_t *Disconnection_BrakePedal, uint8_t *Shutdown_Setas, uint8_t *Shutdown_BSPD_Inertia, uint8_t *Shutdown_SC_BOTS, uint8_t *Shutdown_TSMS_TSMP,
		uint8_t *Shutdown_RightTS, uint8_t *Shutdown_LeftTS, uint8_t *Shutdown_HVBox, uint8_t *Shutdown_HVD, uint8_t *Sync,
		uint8_t *APPS1, uint8_t *APPS2, uint8_t *Break_Value, uint8_t *Steering_sensor_value);



#endif /* INC_CAN_H_ */
