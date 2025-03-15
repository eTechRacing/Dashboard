/*
 * buttons.c
 *
 *  Created on: Mar 6, 2025
 *      Author: cunio
 */

#include <stdint.h>
#include "DASH/buttons.h"

extern uint8_t currentButtonState_Up;
extern uint8_t currentButtonState_Down;
extern uint8_t currentButtonState_Left;
extern uint8_t currentButtonState_Right;
extern uint8_t currentButtonState_OK;

extern uint8_t lastButtonState_Up;
extern uint8_t lastButtonState_Down;
extern uint8_t lastButtonState_Left;
extern uint8_t lastButtonState_Right;
extern uint8_t lastButtonState_OK;

extern uint8_t pendingButtonEvent;

	//FALTA POR DEFINIR LOS PUNTOS

void refreshButton (void){
	 currentButtonState_Up = buttonUpPressed();
	 currentButtonState_Down = buttonDownPressed();
	 currentButtonState_Left = buttonLeftPressed();
	 currentButtonState_Right = buttonRightPressed();
	 currentButtonState_OK = buttonOKPressed();

	          if (currentButtonState_Up != lastButtonState_Up) {
	              pendingButtonEvent = EVENT_BUTTON_UP;
	          }

	          if (currentButtonState_Down != lastButtonState_Down) {
	        	  pendingButtonEvent = EVENT_BUTTON_DOWN;
	          }

	          if (currentButtonState_Left != lastButtonState_Left) {
	        	  pendingButtonEvent = EVENT_BUTTON_LEFT;
	          }

	          if (currentButtonState_Right != lastButtonState_Right) {
	        	  pendingButtonEvent = EVENT_BUTTON_RIGHT;
	          }

	          if (currentButtonState_OK != lastButtonState_OK) {
	        	  pendingButtonEvent = EVENT_BUTTON_OK;
	          }

	          lastButtonState_Up = currentButtonState_Up;
	          lastButtonState_Down = currentButtonState_Down;
	          lastButtonState_Left = currentButtonState_Left;
	          lastButtonState_Right = currentButtonState_Right;
	          lastButtonState_OK = currentButtonState_OK;
}

// mini maquina de estados de

int buttonUpPressed() {
    return (HAL_GPIO_ReadPin(GPIO_PORT, GPIO_PIN_UP) == GPIO_PIN_SET);
}

int buttonDownPressed() {
    return (HAL_GPIO_ReadPin(GPIO_PORT, GPIO_PIN_DOWN) == GPIO_PIN_SET);
}

int buttonLeftPressed() {
    return (HAL_GPIO_ReadPin(GPIO_PORT, GPIO_PIN_LEFT) == GPIO_PIN_SET);
}

int buttonRightPressed() {
    return (HAL_GPIO_ReadPin(GPIO_PORT, GPIO_PIN_RIGHT) == GPIO_PIN_SET);
}

int buttonOKPressed() {
    return (HAL_GPIO_ReadPin(GPIO_PORT, GPIO_PIN_OK) == GPIO_PIN_SET);
}
