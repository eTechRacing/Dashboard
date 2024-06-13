 /*
 * statemachine.c
 *
 *  Created on: May 15, 2024
 *      Author: Carmen Unió Cruz
 */

//#include "statemachine.h"
//#include "can.h"
//#include "buttons.h"
//#include "graphics.h"
//#include "glcd.h"
//
//
//	void CarStateMachine_Handler(uint8_t *StateCar_, uint8_t *Current_CarState){
//
//		  switch (Current_CarState[0]) {
//
//
//		        case 0:
//
//		            if (StateCar_[0] == 3) {
//		              Current_CarState[0] = 3;
//		            }
//
//		            if (StateCar_[0] == 21){
//			          Current_CarState[0] = 21;
//		            }
//
//		            break;
//
//
//		        case 3:
//
//		            if (StateCar_[0] == 6) {
//		              Current_CarState[0] = 6;
//		            } if (StateCar_[0] == 21){
//			          Current_CarState[0] = 21;
//		            } break;
//
//
//		        case 6:
//
//		            if (StateCar_[0] == 9) {
//		              Current_CarState[0] = 6;
//		            } if (StateCar_[0] == 21){
//			          Current_CarState[0] = 21;
//		            } break;
//
//
//		        case 9:
//
//		            if (StateCar_[0] == 12) {
//		              Current_CarState[0] = 12;
//		            } if (StateCar_[0] == 21){
//			          Current_CarState[0] = 21;
//		            } break;
//
//
//		        case 12:
//
//		            if (StateCar_[0] == 14) {
//		              Current_CarState[0] = 14;
//		            } if (StateCar_[0] == 21){
//			          Current_CarState[0] = 15;
//		            } break;
//
//
//		        case 14:
//
//		            if (StateCar_[0] == 15) {
//		              Current_CarState[0] = 15;
//		            } if (StateCar_[0] == 21){
//			          Current_CarState[0] = 21;
//		            } break;
//
//
//		        case 15:
//
//		            if (StateCar_[0] == 21){
//			          Current_CarState[0] = 21;
//		            } break;
//
//
//		        case 21:
//
//		            break;
//
//
//		        default:
//
//		            break;
//		    }
//	}
//
//
