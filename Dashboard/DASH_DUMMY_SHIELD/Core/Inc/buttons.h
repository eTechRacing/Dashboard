/*
 * buttons.h
 *
 *  Created on: May 16, 2024
 *      Author: Carmen Unió Cruz
 */

#ifndef INC_BUTTONS_H_
#define INC_BUTTONS_H_

#include <stdint.h>

/**
  * @brief  Waits until User Presses the OK Button to send the
  * 		Precharge Request
  * @param  pointer to PrechargeRequest variable that holds the
  * 		state of the Request and sends it via CAN when the
  * 		Synchronism Signal is received
  * @retval None
  */
void buttonsPrecharge(uint8_t *PrechargeRequest);

/**
  * @brief  Waits until User Presses the OK Button to send the
  * 		RacingMode.
  * @param  pointer to RacingMode variable that holds the
  * 		state of the Mode and sends it via CAN when the
  * 		Synchronism Signal is received
  * @retval None
  */
void buttonsModeMenu(uint8_t *RacingMode);

/**
  * @brief  Waits until User Presses the OK Button to send the
  * 		RacingMode. Sub-Function that chooses The Competition
  * 		selected.
  * @param  pointer to RacingMode variable that holds the
  * 		state of the Mode and sends it via CAN when the
  * 		Synchronism Signal is received
  * @retval None
  */
void buttonsCompetitionMenu(uint8_t *RacingMode);

/**
  * @brief  Waits until User Presses the OK Button to send the
  * 		Ready To Drive
  * @param  pointer to EnableDrive variable that holds the
  * 		state of the RTD (Ready-To-Drive) and sends it
  * 		via CAN when the Synchronism Signal is received
  * @retval None
  */
void buttonsReadyToDrive(uint8_t *EnableDrive);




#endif /* INC_BUTTONS_H_ */

