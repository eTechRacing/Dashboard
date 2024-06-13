/*
 * init.h
 *
 *  Created on: Jun 7, 2024
 *      Author: usuari
 */

#ifndef INC_INIT_H_
#define INC_INIT_H_

#include <stdint.h>


#define NORMATIVE_TIME_LED		250

/**
  * @brief  Initialization of the Systems, such as LEDs and Buzzer, set by FS Rules.
  * @param  None
  * @retval None
  */
void NORMATIVE_INIT(void);

/**
  * @brief  Initialization of the CAN Peripheral and Interruptions.
  * @param  filtercan CAN_FilterTypeDef structure that contains
  *         the configuration information for the filter CAN.
  * @param  hcan1 CAN_HandleTypeDef structure that contains
  *         the configuration information for the specified CAN.
  * @param  hcan2 CAN_HandleTypeDef structure that contains
  *         the configuration information for the specified CAN.
  * @retval None
  */
void CAN1_CONFIG_INIT(CAN_FilterTypeDef canfil1, CAN_HandleTypeDef hcan1);

/**
  * @brief  Initialization of the CAN Peripheral and Interruptions.
  * @param  filtercan CAN_FilterTypeDef structure that contains
  *         the configuration information for the filter CAN.
  * @param  hcan1 CAN_HandleTypeDef structure that contains
  *         the configuration information for the specified CAN.
  * @param  hcan2 CAN_HandleTypeDef structure that contains
  *         the configuration information for the specified CAN.
  * @retval None
  */
void CAN2_CONFIG_INIT(CAN_FilterTypeDef canfil2, CAN_HandleTypeDef hcan2);


void VARIABLE_RESET(uint8_t *EnableDrive, uint8_t *RacingMode, uint8_t *PrechargeRequest, uint8_t *KeepAliveDash, uint8_t *Refri_Inverters, uint8_t *Refri_Accu, char *msgcan1, char *msgcan2, uint8_t *CarState_, char *PrechargeReqControl);



#endif /* INC_INIT_H_ */
