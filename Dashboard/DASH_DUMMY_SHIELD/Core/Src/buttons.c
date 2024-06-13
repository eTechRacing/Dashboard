/*
 * buttons.c
 *
 *  Created on: May 16, 2024
 *      Author: Carmen Unió Cruz
 */

	#include "buttons.h"
	#include "main.h"
	#include "can.h"

	void buttonsPrecharge(uint8_t *PrechargeRequest){

		while (HAL_GPIO_ReadPin(OK_BUTTON_GPIO_Port, OK_BUTTON_Pin) != GPIO_PIN_SET){
			//	Loop Until OK Button is pressed.
		}
			//PrechargeRequest Is Updated and ready to be sent when gets the Syncronism Signal.
		PrechargeRequest[0] = 1;
	}

	void buttonsCompetitionMenu(uint8_t *RacingMode){

				// 2 -> Endurance; 3 -> Acceleration; 4 -> Skippad; 5 -> Autocross
			uint8_t menu[] = {2,3,4,5};
			uint8_t current_mode = menu[0];

			while (HAL_GPIO_ReadPin(OK_BUTTON_GPIO_Port, OK_BUTTON_Pin) != GPIO_PIN_SET){

				if(current_mode == menu[0]){
					//IDLE SCREEN
					if (HAL_GPIO_ReadPin(RIGHT_BUTTON_GPIO_Port, RIGHT_BUTTON_Pin) == 1){
						current_mode = menu[1];

					} if (HAL_GPIO_ReadPin(LEFT_BUTTON_GPIO_Port, LEFT_BUTTON_Pin) == 1){
						current_mode = menu[3];
					}
				}

				if(current_mode == menu[1]){
					// IDLE SCREEN
					if (HAL_GPIO_ReadPin(RIGHT_BUTTON_GPIO_Port, RIGHT_BUTTON_Pin) == 1){
						current_mode = menu[2];

					} if (HAL_GPIO_ReadPin(LEFT_BUTTON_GPIO_Port, LEFT_BUTTON_Pin) == 1){
						current_mode = menu[0];
					}
				}
				if(current_mode == menu[2]){
					//IDLE SCREEN
					if (HAL_GPIO_ReadPin(RIGHT_BUTTON_GPIO_Port, RIGHT_BUTTON_Pin) == 1){
						current_mode = menu[3];

					} if (HAL_GPIO_ReadPin(LEFT_BUTTON_GPIO_Port, LEFT_BUTTON_Pin) == 1){
						current_mode = menu[1];
					}
				}

				if(current_mode == menu[3]){
					//IDLE SCREEN
					if (HAL_GPIO_ReadPin(RIGHT_BUTTON_GPIO_Port, RIGHT_BUTTON_Pin) == 1){
						current_mode = menu[2];

					} if (HAL_GPIO_ReadPin(LEFT_BUTTON_GPIO_Port, LEFT_BUTTON_Pin) == 1){
						current_mode = menu[0];
					}
				}
			}

				//RacingMode Is Updated and ready to be sent when gets the Syncronism Signal.
			RacingMode[0] = current_mode;

		}

	void buttonsModeMenu(uint8_t *RacingMode){

			// 1 represents WorkShop Mode, and 2 represents Competition Mode
		uint8_t menu[2] = {1,2};
		uint8_t current_mode = menu[0];

			// Loop until Mode is selected
		while (HAL_GPIO_ReadPin(OK_BUTTON_GPIO_Port, OK_BUTTON_Pin) != 1){

			if(current_mode == menu[0]){
				//IDLE SCREEN
				if (HAL_GPIO_ReadPin(RIGHT_BUTTON_GPIO_Port, RIGHT_BUTTON_Pin) == 1){
					current_mode = menu[1];

				} if (HAL_GPIO_ReadPin(LEFT_BUTTON_GPIO_Port, LEFT_BUTTON_Pin) == 1){
					current_mode = menu[3];
				}
			}

			if(current_mode == menu[1]){
				// IDLE SCREEN
				if (HAL_GPIO_ReadPin(RIGHT_BUTTON_GPIO_Port, RIGHT_BUTTON_Pin) == 1){
					current_mode = menu[2];

				} if (HAL_GPIO_ReadPin(LEFT_BUTTON_GPIO_Port, LEFT_BUTTON_Pin) == 1){
					current_mode = menu[0];
				}
			}
		}

			// if the RacingMode selected is not Workshop the function buttonsCompetitionMenu is called
		if (current_mode == menu [0]){

			RacingMode[0] = menu [0];

		} else {

				//Browses the different Competitions and RacingMode is Selected.
			buttonsCompetitionMenu(RacingMode);

		}
	}



	void buttonsReadyToDrive(uint8_t *EnableDrive){

		while (HAL_GPIO_ReadPin(OK_BUTTON_GPIO_Port, OK_BUTTON_Pin) != GPIO_PIN_SET){
				//	Loop Until OK Button is pressed.
			}

			//EnableDrive Is Updated and ready to be sent when gets the Syncronism Signal.
		EnableDrive[0] = 1;
	}



