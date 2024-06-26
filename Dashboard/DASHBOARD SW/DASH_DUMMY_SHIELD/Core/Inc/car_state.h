/*
 * car_state.h
 *
 *  Created on: Jun 15, 2024
 *      Author: Guillem Ropero
 */

#ifndef INC_CAR_STATE_H_
#define INC_CAR_STATE_H_

#include "main.h"

void BMS_IMD_ERROR(uint8_t BMS_SD, uint8_t IMD_SD);
void setLEDs(uint8_t percentage);
void car_state_0(SPI_HandleTypeDef hspi_channel, uint8_t END_SD, uint8_t BMS_SD, uint8_t IMD_SD,
		uint8_t Shutdown_Setas, uint8_t Shutdown_BSPD_Inertia, uint8_t Shutdown_SC_BOTS, uint8_t Shutdown_TSMS_TSMP,
		uint8_t Shutdown_RightTS, uint8_t Shutdown_LeftTS, uint8_t Shutdown_HVBox, uint8_t Shutdown_HVD, uint8_t *Refri_Accumulator, uint8_t *Refri_Inverters, uint8_t *Refri_Motors, uint8_t BMS_Disconnect, uint8_t Dash_Disconect, uint8_t Front_Disconenct,
		uint8_t Ellipse_Disconect, uint8_t Rear_Disconnect, uint8_t APPS1_Disconect, uint8_t APPS2_Disconnect, uint8_t BrakePedal_Disconnect, uint8_t SteeringSensor_Disconnect,
		uint8_t SuspRR_Disconnect, uint8_t SuspRL_Disconnect, uint8_t SuspFR_Disconnect, uint8_t SuspFL_Disconnect, uint8_t Pitot_Disconnect);

void car_state_3(SPI_HandleTypeDef hspi_channel, uint8_t *Refri_Accumulator, uint8_t *Refri_Inverters, uint8_t *Refri_Motors);
void car_state_6(SPI_HandleTypeDef hspi_channel, uint8_t PrechargePercentage, uint8_t *precharge_request_control);
void car_state_9(SPI_HandleTypeDef hspi_channel);
void car_state_12(SPI_HandleTypeDef hspi_channel, uint8_t Racing_Mode, uint8_t rtd);
void car_state_14(SPI_HandleTypeDef hspi_channel, uint8_t Enable_Drive);
void car_state_15(SPI_HandleTypeDef hspi_channel, uint8_t CarSpeed, uint16_t Lowest_CellVolt, uint16_t Highest_CellTemperature, uint16_t Average_CellTemperature, uint8_t *Refri_Accumulator, uint8_t *Refri_Inverters, uint8_t *Refri_Motors, uint8_t Car_Speed, uint8_t APPS1);
void car_state_21(SPI_HandleTypeDef hspi_channel);
void CAR_STATE_FUNCTION(SPI_HandleTypeDef hspi_channel, uint8_t Car__State, uint8_t PrechargePercentage, uint8_t *precharge_request_control,
		uint8_t Racing_Mode, uint8_t rtd, uint8_t Enable_Drive, uint8_t SoC_Average, uint8_t Car_Speed, uint16_t Lowest_CellVolt,
		uint16_t Highest_CellTemperature, uint16_t Average_CellTemperature, uint8_t *Refri_Accumulator,
		uint8_t *Refri_Inverters, uint8_t *Refri_Motors, uint8_t END_SD, uint8_t BMS_SD, uint8_t IMD_SD,
		uint8_t Shutdown_Setas, uint8_t Shutdown_BSPD_Inertia, uint8_t Shutdown_SC_BOTS, uint8_t Shutdown_TSMS_TSMP,
		uint8_t Shutdown_RightTS, uint8_t Shutdown_LeftTS, uint8_t Shutdown_HVBox, uint8_t Shutdown_HVD, 	uint8_t BMS_Disconnect, uint8_t Dash_Disconect, uint8_t Front_Disconenct,
		uint8_t Ellipse_Disconect, uint8_t Rear_Disconnect, uint8_t APPS1_Disconect, uint8_t APPS2_Disconnect, uint8_t BrakePedal_Disconnect, uint8_t SteeringSensor_Disconnect,
		uint8_t SuspRR_Disconnect, uint8_t SuspRL_Disconnect, uint8_t SuspFR_Disconnect, uint8_t SuspFL_Disconnect, uint8_t Pitot_Disconnect, uint8_t APPS1);
void cooling_mode_selection(uint8_t *Refri_Accumulator, uint8_t *Refri_Inverters, uint8_t *Refri_Motors);
uint8_t flag_right();
uint8_t flag_left();
uint8_t flag_up();
uint8_t flag_down();
void shutdown_chain(uint8_t END_SD, uint8_t BMS_SD, uint8_t IMD_SD, uint8_t Shutdown_Setas, uint8_t Shutdown_BSPD_Inertia, uint8_t Shutdown_SC_BOTS, uint8_t Shutdown_TSMS_TSMP,
		uint8_t Shutdown_RightTS, uint8_t Shutdown_LeftTS, uint8_t Shutdown_HVBox, uint8_t Shutdown_HVD, 	uint8_t BMS_Disconnect, uint8_t Dash_Disconect, uint8_t Front_Disconenct,
uint8_t Ellipse_Disconect, uint8_t Rear_Disconnect, uint8_t APPS1_Disconect, uint8_t APPS2_Disconnect, uint8_t BrakePedal_Disconnect, uint8_t SteeringSensor_Disconnect,
uint8_t SuspRR_Disconnect, uint8_t SuspRL_Disconnect, uint8_t SuspFR_Disconnect, uint8_t SuspFL_Disconnect, uint8_t Pitot_Disconnect);
void racing_mode_selection(uint8_t *Racing_Mode, uint8_t *RTD);
uint8_t enable_driving(uint8_t *Enable_Drive, uint8_t *rtd);
uint8_t Read_Button_Edge(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);
uint8_t car_state_12_control(uint8_t *Racing_Mode, uint8_t *rtd, uint8_t *Enable_Drive);
#endif /* INC_CAR_STATE_H_ */
