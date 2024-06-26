/*
 * car_state.c
 *
 *  Created on: Jun 15, 2024
 *      Author: Bernat Carnota
 */
#include "graphics.h"
#include "statemachine.h"
//#include "buttons.h"
#include "can.h"
#include "glcd_etr.h"
#include "init.h"
#include "font_tahoma.h"
#include "main.h"
#include "car_state.h"
#include <stdio.h>



void car_state_0(SPI_HandleTypeDef hspi_channel, uint8_t END_SD, uint8_t BMS_SD, uint8_t IMD_SD,
		uint8_t Shutdown_Setas, uint8_t Shutdown_BSPD_Inertia, uint8_t Shutdown_SC_BOTS, uint8_t Shutdown_TSMS_TSMP,
		uint8_t Shutdown_RightTS, uint8_t Shutdown_LeftTS, uint8_t Shutdown_HVBox, uint8_t Shutdown_HVD, uint8_t *Refri_Accumulator, uint8_t *Refri_Inverters, uint8_t *Refri_Motors, uint8_t BMS_Disconnect, uint8_t Dash_Disconect, uint8_t Front_Disconenct,
		uint8_t Ellipse_Disconect, uint8_t Rear_Disconnect, uint8_t APPS1_Disconect, uint8_t APPS2_Disconnect, uint8_t BrakePedal_Disconnect, uint8_t SteeringSensor_Disconnect,
		uint8_t SuspRR_Disconnect, uint8_t SuspRL_Disconnect, uint8_t SuspFR_Disconnect, uint8_t SuspFL_Disconnect, uint8_t Pitot_Disconnect){

	static uint8_t flag = 0;
	uint16_t DELAY = 150;
	glcd_etr_init(hspi_channel);
	glcd_etr_blank(hspi_channel);
	switch(flag){
	case 0:
		shutdown_chain(END_SD, BMS_SD, IMD_SD, Shutdown_Setas, Shutdown_BSPD_Inertia, Shutdown_SC_BOTS, Shutdown_TSMS_TSMP,
				Shutdown_RightTS, Shutdown_LeftTS, Shutdown_HVBox, Shutdown_HVD,  BMS_Disconnect,  Dash_Disconect,  Front_Disconenct,
				 Ellipse_Disconect,  Rear_Disconnect,  APPS1_Disconect,  APPS2_Disconnect,  BrakePedal_Disconnect,  SteeringSensor_Disconnect,
				 SuspRR_Disconnect,  SuspRL_Disconnect,  SuspFR_Disconnect,  SuspFL_Disconnect,  Pitot_Disconnect);
		draw_text("->", 110, 53, Tahoma7, 2);
		if(flag_right() == 1){
			flag = 1;
			HAL_Delay(DELAY);
		}
		break;
	case 1:
		cooling_mode_selection(Refri_Accumulator, Refri_Inverters, Refri_Motors);
		draw_text("<-", 110, 53, Tahoma7, 2);
		if(flag_left() == 1){
			flag = 0;
			HAL_Delay(DELAY);
		}
		break;
	}
	glcd_etr_refresh(hspi_channel);
}

void car_state_3(SPI_HandleTypeDef hspi_channel, uint8_t *Refri_Accumulator, uint8_t *Refri_Inverters, uint8_t *Refri_Motors){//afegir les variables carstate3screen i slected com a *
	uint8_t leftButtonState = Read_Button_Edge(LEFT_BUTTON_GPIO_Port, LEFT_BUTTON_Pin);
    uint8_t rightButtonState = Read_Button_Edge(RIGHT_BUTTON_GPIO_Port, RIGHT_BUTTON_Pin);
    uint8_t DELAY = 150;
	static uint8_t carstate3_screen= 0;

	glcd_etr_init(hspi_channel);
	blank_rectangle(1,1, 129, 129, 0);
	glcd_etr_blank(hspi_channel);
	switch(carstate3_screen){
	case(0):
		draw_text("PRESS THE CENTRAL", 6, 5, Tahoma7, 2);
		draw_text("BUTTON TO START", 8, 25, Tahoma10, 2);
		draw_text("THE PRECHARGE", 15, 45, Tahoma10, 2);
		if(leftButtonState == 1 || rightButtonState == 1){
			HAL_Delay(DELAY);
			carstate3_screen = 1;
		}
	break;
	case(1):
		cooling_mode_selection(Refri_Accumulator, Refri_Inverters, Refri_Motors);
	if(leftButtonState == 1 || rightButtonState == 1){
		HAL_Delay(DELAY);
		carstate3_screen = 0;
	}
	break;
	}
	glcd_etr_refresh(hspi_channel);
}

void car_state_6(SPI_HandleTypeDef hspi_channel, uint8_t PrechargePercentage, uint8_t *precharge_request_control){
	*precharge_request_control = 0;
	glcd_etr_init(hspi_channel);
	glcd_etr_blank(hspi_channel);
	blank_rectangle(1,1,130,64,0);
	draw_text("PRE-CHARGE SEQUENCE", 10, 3, Tahoma7, 1);
	draw_line(1, 14, 128, 14, 1);
	draw_text("Dame", 20, 20, Tahoma7, 1);
	draw_text("cosas guapas", 14, 30, Tahoma7, 1);
	draw_box (14, 48, 114, 63, 1);
	blank_rectangle(14, 49, (PrechargePercentage+14), 62, 1); //Pintem la part de la barra indicadora del proces que toqui en funcio del percentatge
	glcd_etr_refresh(hspi_channel);
}

void car_state_9(SPI_HandleTypeDef hspi_channel){
	glcd_etr_init(hspi_channel);
	glcd_etr_blank(hspi_channel);
	blank_rectangle(1,1,130,64,0);
	draw_text("PRECHARGE", 6, 10, Tahoma16, 2);
	draw_text("DONE", 30, 35, Tahoma16, 2);
	glcd_etr_refresh(hspi_channel);
}

void car_state_12(SPI_HandleTypeDef hspi_channel, uint8_t Racing_Mode, uint8_t rtd){
	glcd_etr_init(hspi_channel);
	glcd_etr_blank(hspi_channel);
	blank_rectangle(1,1,130,64,0);
	if(rtd==0)
		scrollDrawing(Racing_Mode, Tahoma7);
	else{
		draw_text("PRESS THE CENTRAL", 6, 5, Tahoma10, 2);
		draw_text("BUTTON AND", 25, 25, Tahoma10, 2);
		draw_text("BRAKE", 40, 45, Tahoma10, 2);
	}
	glcd_etr_refresh(hspi_channel);
}

void car_state_14(SPI_HandleTypeDef hspi_channel, uint8_t Enable_Drive){
	glcd_etr_init(hspi_channel);
	glcd_etr_blank(hspi_channel);
	blank_rectangle(1,1,130,64,0);
	draw_text("INVERTERS", 15, 10, Tahoma12, 1);
	draw_text("GETTING  READY", 4, 35, Tahoma12, 1);
	glcd_etr_refresh(hspi_channel);
}

void car_state_15(SPI_HandleTypeDef hspi_channel, uint8_t SoC_Average, uint16_t Lowest_CellVolt, uint16_t Highest_CellTemperature, uint16_t Average_CellTemperature, uint8_t *Refri_Accumulator, uint8_t *Refri_Inverters, uint8_t *Refri_Motors, uint8_t Car_Speed, uint8_t APPS1){
	char StrBuffer[40];
	static uint8_t flag = 0;
	uint8_t DELAY = 150;
	glcd_etr_init(hspi_channel);
	blank_rectangle(1,1, 129, 129, 0); //Borrem tota la pantalla
	glcd_etr_blank(hspi_channel);
  	setLEDs(APPS1);
	switch(flag){
	case 0:
		sprintf(StrBuffer,"Vmin %.2f  Tmax %d  Tavg %d",Lowest_CellVolt*0.0001,Highest_CellTemperature/10,Average_CellTemperature/10);
		drawXparameter(SoC_Average, 100);
		writeXparameterValue(Car_Speed);

		draw_text(StrBuffer, 4, 1, Tahoma7, 1);
		draw_text("Km/h", 80, 17, Tahoma7, 1);
		draw_text("->", 110, 53, Tahoma7, 2);
		if(flag_right() == 1){
			flag = 1;
			HAL_Delay(DELAY);
		}
		break;
	case 1:
		cooling_mode_selection(Refri_Accumulator, Refri_Inverters, Refri_Motors);
		draw_text("<-", 110, 53, Tahoma7, 2);
		if(flag_left() == 1){
			flag = 0;
			HAL_Delay(DELAY);
		}
		break;
	}

	glcd_etr_refresh(hspi_channel);
}

void car_state_21(SPI_HandleTypeDef hspi_channel){
	glcd_etr_init(hspi_channel);
	glcd_etr_blank(hspi_channel);
	blank_rectangle(1,1,130,64,0);
	blank_rectangle(14, 7, 114, 57, 0);//Descubrir porque esta esto!!!!
	draw_rectangle(14, 7, 114, 58, 1);//Dibuja un rectangulo
	draw_rectangle(15, 8, 115, 59, 1);//Dibuja el mismo rectangulo anterior pero desplazado para hacer la linea mas gorda
	draw_text("ERROR", 20, 20, Tahoma22, 2);
	glcd_etr_refresh(hspi_channel);
}

void CAR_STATE_FUNCTION(SPI_HandleTypeDef hspi_channel, uint8_t Car__State, uint8_t PrechargePercentage, uint8_t *precharge_request_control,
		uint8_t Racing_Mode, uint8_t rtd, uint8_t Enable_Drive, uint8_t SoC_Average, uint8_t Car_Speed, uint16_t Lowest_CellVolt,
		uint16_t Highest_CellTemperature, uint16_t Average_CellTemperature, uint8_t *Refri_Accumulator,
		uint8_t *Refri_Inverters, uint8_t *Refri_Motors, uint8_t END_SD, uint8_t BMS_SD, uint8_t IMD_SD,
		uint8_t Shutdown_Setas, uint8_t Shutdown_BSPD_Inertia, uint8_t Shutdown_SC_BOTS, uint8_t Shutdown_TSMS_TSMP,
		uint8_t Shutdown_RightTS, uint8_t Shutdown_LeftTS, uint8_t Shutdown_HVBox, uint8_t Shutdown_HVD, 	uint8_t BMS_Disconnect, uint8_t Dash_Disconect, uint8_t Front_Disconenct,
		uint8_t Ellipse_Disconect, uint8_t Rear_Disconnect, uint8_t APPS1_Disconect, uint8_t APPS2_Disconnect, uint8_t BrakePedal_Disconnect, uint8_t SteeringSensor_Disconnect,
		uint8_t SuspRR_Disconnect, uint8_t SuspRL_Disconnect, uint8_t SuspFR_Disconnect, uint8_t SuspFL_Disconnect, uint8_t Pitot_Disconnect, uint8_t APPS1){
	switch(Car__State){
		case(0):
		car_state_0(hspi_channel, END_SD, BMS_SD, IMD_SD, Shutdown_Setas, Shutdown_BSPD_Inertia, Shutdown_SC_BOTS, Shutdown_TSMS_TSMP,
				Shutdown_RightTS, Shutdown_LeftTS, Shutdown_HVBox, Shutdown_HVD, Refri_Accumulator, Refri_Inverters, Refri_Motors,  BMS_Disconnect,  Dash_Disconect,  Front_Disconenct,
				 Ellipse_Disconect,  Rear_Disconnect,  APPS1_Disconect,  APPS2_Disconnect,  BrakePedal_Disconnect,  SteeringSensor_Disconnect,
				 SuspRR_Disconnect,  SuspRL_Disconnect,  SuspFR_Disconnect,  SuspFL_Disconnect,  Pitot_Disconnect);
		break;
		case(3):
		car_state_3(hspi_channel, Refri_Accumulator, Refri_Inverters, Refri_Motors);
		break;
		case(6):
		car_state_6(hspi_channel, PrechargePercentage, precharge_request_control);
		break;
		case(9):
		car_state_9(hspi_channel);
		break;
		case(12):
		car_state_12(hspi_channel, Racing_Mode, rtd);
		break;
		case(14):
		car_state_14(hspi_channel, Enable_Drive);
		break;
		case(15):
		car_state_15(hspi_channel, SoC_Average, Lowest_CellVolt, Highest_CellTemperature, Average_CellTemperature, Refri_Accumulator, Refri_Inverters, Refri_Motors, Car_Speed, APPS1);
		break;
		case(21):
		car_state_21(hspi_channel);
		break;
		}
}
uint8_t flag_left(){
	static uint32_t cool_flag = 0;
	uint8_t leftButtonState = Read_Button_Edge(LEFT_BUTTON_GPIO_Port, LEFT_BUTTON_Pin);
	if(leftButtonState == 0){
		cool_flag = HAL_GetTick();
	}else{
		if(HAL_GetTick() - cool_flag > 1500){
			return 1;
		}
	}
	return 0;
}

uint8_t flag_right(){
	static uint32_t cool_flag = 0;
	uint8_t rightButtonState = Read_Button_Edge(RIGHT_BUTTON_GPIO_Port, RIGHT_BUTTON_Pin);
	if(rightButtonState == 0){
		cool_flag = HAL_GetTick();
	}else{
		if(HAL_GetTick() - cool_flag > 1500){
			return 1;
		}
	}
	return 0;
}

uint8_t flag_down(){
	static uint32_t cool_flag = 0;
	uint8_t downButtonState = Read_Button_Edge(DOWN_BUTTON_GPIO_Port, DOWN_BUTTON_Pin);
	if(downButtonState == 0){
		cool_flag = HAL_GetTick();
	}else{
		if(HAL_GetTick() - cool_flag > 1500){
			return 1;
		}
	}
	return 0;
}

uint8_t flag_up(){
	static uint32_t cool_flag = 0;
	uint8_t upButtonState = Read_Button_Edge(UP_BUTTON_GPIO_Port,UP_BUTTON_Pin);
	if(upButtonState == 0){
		cool_flag = HAL_GetTick();
	}else{
		if(HAL_GetTick() - cool_flag > 1500){
			return 1;
		}
	}
	return 0;
}

void shutdown_chain(uint8_t END_SD, uint8_t BMS_SD, uint8_t IMD_SD, uint8_t Shutdown_Setas, uint8_t Shutdown_BSPD_Inertia, uint8_t Shutdown_SC_BOTS, uint8_t Shutdown_TSMS_TSMP,
		uint8_t Shutdown_RightTS, uint8_t Shutdown_LeftTS, uint8_t Shutdown_HVBox, uint8_t Shutdown_HVD, 	uint8_t BMS_Disconnect, uint8_t Dash_Disconect, uint8_t Front_Disconenct,
uint8_t Ellipse_Disconect, uint8_t Rear_Disconnect, uint8_t APPS1_Disconect, uint8_t APPS2_Disconnect, uint8_t BrakePedal_Disconnect, uint8_t SteeringSensor_Disconnect,
uint8_t SuspRR_Disconnect, uint8_t SuspRL_Disconnect, uint8_t SuspFR_Disconnect, uint8_t SuspFL_Disconnect, uint8_t Pitot_Disconnect){
    uint8_t downButtonState = Read_Button_Edge(DOWN_BUTTON_GPIO_Port, DOWN_BUTTON_Pin);
    uint8_t upButtonState = Read_Button_Edge(UP_BUTTON_GPIO_Port, UP_BUTTON_Pin);
	static uint8_t selected = 0;
    uint8_t DELAY = 150;


	switch(selected){
	case 0:
		draw_text("SHUTDOWN CHAIN", 15, 5, Tahoma7, 2);
		switch(Shutdown_Setas){
		case 1:
			draw_text("Setas_SD OK", 6, 17, Tahoma7, 2);
			break;
		case 0:
			draw_text("Setas_SD FAIL", 6, 17, Tahoma7, 2);
			break;
		}
		switch(Shutdown_BSPD_Inertia){
		case 1:
			draw_text("BSPD_Inertia_SD OK", 6, 29, Tahoma7, 2);
			break;
		case 0:
			draw_text("BSPD_Inertia_SD FAIL", 6, 29, Tahoma7, 2);
			break;
		}
		switch(Shutdown_SC_BOTS){
		case 1:
			draw_text("SC_BOTS_SD OK", 6, 41, Tahoma7, 2);
			break;
		case 0:
			draw_text("SC_BOTS_SD FAIL", 6, 41, Tahoma7, 2);
			break;
		}
		switch(BMS_SD){
		case 1:
			draw_text("BMS_SD OK", 6, 53, Tahoma7, 2);
			break;
		case 0:
			draw_text("BMS_SD FAIL", 6, 53, Tahoma7, 2);
			break;
		}

		if(downButtonState == 1){
			HAL_Delay(DELAY);
			selected = 1;
		}
		if(upButtonState == 1){
			HAL_Delay(DELAY);
			selected = 5;
		}
	break;


	case 1:
		switch(IMD_SD){
		case 1:
			draw_text("IMD_SD OK", 6, 5, Tahoma7, 2);
			break;
		case 0:
			draw_text("IMD_SD FAIL", 6, 5, Tahoma7, 2);
			break;
		}
		switch(Shutdown_TSMS_TSMP){
		case 1:
			draw_text("TSMS_TSMP_SD OK", 6, 17, Tahoma7, 2);
			break;
		case 0:
			draw_text("TSMS_TSMP_SD FAIL", 6, 17, Tahoma7, 2);
			break;
		}
		switch(Shutdown_RightTS){
		case 1:
			draw_text("RightTS_SD OK", 6, 29, Tahoma7, 2);
			break;
		case 0:
			draw_text("RightTS_SD FAIL", 6, 29, Tahoma7, 2);
			break;
		}
		switch(Shutdown_LeftTS){
		case 1:
			draw_text("LeftTS_SD OK", 6, 41, Tahoma7, 2);
			break;
		case 0:
			draw_text("LeftTS_SD FAIL", 6, 41, Tahoma7, 2);
			break;
		}
		switch(Shutdown_HVBox){
		case 1:
			draw_text("HVBox_SD OK", 6, 53, Tahoma7, 2);
			break;
		case 0:
			draw_text("HVBox_SD FAIL", 6, 53, Tahoma7, 2);
			break;
		}
		if(downButtonState == 1){
			HAL_Delay(DELAY);
			selected = 2;
		}
		if(upButtonState == 1){
			HAL_Delay(DELAY);
			selected = 0;
		}
	break;
	case 2:
		switch(Shutdown_HVD){
		case 1:
			draw_text("HVD_SD OK", 6, 5, Tahoma7, 2);
			break;
		case 0:
			draw_text("HVD_SD FAIL", 6, 5, Tahoma7, 2);
			break;
		}
		switch(END_SD){
		case 1:
			draw_text("END_SD OK", 6, 17, Tahoma7, 2);
			break;
		case 0:
			draw_text("END_SD FAIL", 6, 17, Tahoma7, 2);
			break;
		}
		if(downButtonState == 1){
			HAL_Delay(DELAY);
			selected = 3;
		}
		if(upButtonState == 1){
			HAL_Delay(DELAY);
			selected = 1;
		}
	break;
		case 3:
				draw_text("DISCONNECTIONS", 13, 5, Tahoma7, 2);

			switch(BMS_Disconnect){
			case 0:
				draw_text("BMS OK", 6, 17, Tahoma7, 2);
				break;
			case 1:
				draw_text("BMS FAIL", 6, 17, Tahoma7, 2);
				break;
			}
			switch(Dash_Disconect){
			case 0:
				draw_text("Dash OK", 6, 29, Tahoma7, 2);
				break;
			case 1:
				draw_text("Dash FAIL", 6, 29, Tahoma7, 2);
				break;
			}
			switch(Front_Disconenct){
			case 0:
				draw_text("Front OK", 6, 41, Tahoma7, 2);
				break;
			case 1:
				draw_text("Front FAIL", 6, 41, Tahoma7, 2);
				break;
			}
			switch(Ellipse_Disconect){
			case 0:
				draw_text("Elipse OK", 6, 53, Tahoma7, 2);
				break;
			case 1:
				draw_text("Elipse FAIL", 6, 53, Tahoma7, 2);
				break;
			}
			if(downButtonState == 1){
				HAL_Delay(DELAY);
				selected = 4;
			}
			if(upButtonState == 1){
				HAL_Delay(DELAY);
				selected = 2;
			}
		break;
		case 4:
			switch(Rear_Disconnect){
			case 0:
				draw_text("Rear OK", 6, 5, Tahoma7, 2);
				break;
			case 1:
				draw_text("Rear FAIL", 6, 5, Tahoma7, 2);
				break;
			}
			switch(APPS1_Disconect){
			case 0:
				draw_text("APPS1 OK", 6, 17, Tahoma7, 2);
				break;
			case 1:
				draw_text("APPS1 FAIL", 6, 17, Tahoma7, 2);
				break;
			}
			switch(APPS2_Disconnect){
			case 0:
				draw_text("APPS2 OK", 6, 29, Tahoma7, 2);
				break;
			case 1:
				draw_text("APPS2 FAIL", 6, 29, Tahoma7, 2);
				break;
			}
			switch(BrakePedal_Disconnect){
			case 0:
				draw_text("Brake OK", 6, 41, Tahoma7, 2);
				break;
			case 1:
				draw_text("Brake FAIL", 6, 41, Tahoma7, 2);
				break;
			}
			switch(SteeringSensor_Disconnect){
			case 0:
				draw_text("Steering OK", 6, 53, Tahoma7, 2);
				break;
			case 1:
				draw_text("Steering FAIL", 6, 53, Tahoma7, 2);
				break;
			}
			if(downButtonState == 1){
				HAL_Delay(DELAY);
				selected = 5;
			}
			if(upButtonState == 1){
				HAL_Delay(DELAY);
				selected = 3;
			}
		break;
		case 5:
			switch(SuspRR_Disconnect){
			case 0:
				draw_text("SuspRR OK", 6, 5, Tahoma7, 2);
				break;
			case 1:
				draw_text("SuspRR FAIL", 6, 5, Tahoma7, 2);
				break;
			}
			switch(SuspRL_Disconnect){
			case 0:
				draw_text("SuspRL OK", 6, 17, Tahoma7, 2);
				break;
			case 1:
				draw_text("SuspRL FAIL", 6, 17, Tahoma7, 2);
				break;
			}
			switch(SuspFR_Disconnect){
			case 0:
				draw_text("SuspFR OK", 6, 29, Tahoma7, 2);
				break;
			case 1:
				draw_text("SuspFR FAIL", 6, 29, Tahoma7, 2);
				break;
			}
			switch(SuspFL_Disconnect){
			case 0:
				draw_text("SuspFL OK", 6, 41, Tahoma7, 2);
				break;
			case 1:
				draw_text("SuspFL FAIL", 6, 41, Tahoma7, 2);
				break;
			}
			switch(Pitot_Disconnect){
			case 0:
				draw_text("Pitot OK", 6, 53, Tahoma7, 2);
				break;
			case 1:
				draw_text("Pitot FAIL", 6, 53, Tahoma7, 2);
				break;
			}
			if(downButtonState == 1){
				HAL_Delay(DELAY);
				selected = 0;
			}
			if(upButtonState == 1){
				HAL_Delay(DELAY);
				selected = 4;
			}
		break;
	}
}


uint8_t Read_Button_Edge(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin) {
   GPIO_PinState currentState = HAL_GPIO_ReadPin(GPIOx, GPIO_Pin);
    if(currentState == GPIO_PIN_SET){
    	return 1;
    }
    return 0;
}

void cooling_mode_selection(uint8_t *Refri_Accumulator, uint8_t *Refri_Inverters, uint8_t *Refri_Motors){
    uint8_t downButtonState = Read_Button_Edge(DOWN_BUTTON_GPIO_Port, DOWN_BUTTON_Pin);
    uint8_t upButtonState = Read_Button_Edge(UP_BUTTON_GPIO_Port, UP_BUTTON_Pin);
    uint8_t centralButtonState = Read_Button_Edge(OK_BUTTON_GPIO_Port, OK_BUTTON_Pin);

    uint8_t DELAY = 150;
	static uint8_t selected = 0;
	static uint8_t Refri_Accu = 1;
	static uint8_t Refri_Inv = 1;
	static uint8_t Refri_Mot = 1;
	switch(selected){ //requadre per indicar la selecció
			case(0):
				draw_box (7, 2, 114, 18, 1);
				switch(Refri_Accu){
				case(0):
					draw_text("ACCU         ON", 12, 5, Tahoma7, 2);
					*Refri_Accumulator = 0;
					if(centralButtonState == 1){
						HAL_Delay(DELAY);
						Refri_Accu = 1;
					}
				break;
				case(1):
					draw_text("ACCU         OFF", 12, 5, Tahoma7, 2);
					*Refri_Accumulator = 1;
					if(centralButtonState == 1){
						HAL_Delay(DELAY);
						Refri_Accu = 2;
					}
				break;
				case(2):
					draw_text("ACCU         FULL", 12, 5, Tahoma7, 2);
					*Refri_Accumulator = 2;
					if(centralButtonState == 1){
						HAL_Delay(DELAY);
						Refri_Accu = 0;
					}
				break;
				}
				if(upButtonState == 1){
					HAL_Delay(DELAY);
					selected = 2;
				}
				if(downButtonState == 1){
					HAL_Delay(DELAY);
					selected = 1;
				}
			break;
			case(1):
				draw_box (7, 17, 114, 32, 1);
				switch(Refri_Inv){
				case(0):
					draw_text("INVERTERS  ON", 12, 20, Tahoma7, 2);
					*Refri_Inverters = 0;
					if(centralButtonState == 1){
						HAL_Delay(DELAY);
						Refri_Inv = 1;
					}
				break;
				case(1):
					draw_text("INVERTERS OFF", 12, 20, Tahoma7, 2);
					*Refri_Inverters = 1;
					if(centralButtonState == 1){
						HAL_Delay(DELAY);
						Refri_Inv = 2;
					}
				break;
				case(2):
					draw_text("INVERTERS FULL", 12, 20, Tahoma7, 2);
					*Refri_Inverters = 2;
					if(centralButtonState == 1){
						HAL_Delay(DELAY);
						Refri_Inv = 0;
					}
				break;
				}
				if(upButtonState == 1){
					HAL_Delay(DELAY);
					selected = 0;
				}
				if(downButtonState == 1){
					HAL_Delay(DELAY);
					selected = 2;
				}
			break;
			case(2):
				draw_box (7, 32, 114, 47, 1);
				switch(Refri_Mot){
				case(0):
					draw_text("MOTORS       ON", 12, 35, Tahoma7, 2);
					*Refri_Motors = 0;
					if(centralButtonState == 1){
						HAL_Delay(DELAY);
						Refri_Mot = 1;
					}
				break;
				case(1):
					draw_text("MOTORS      OFF", 12, 35, Tahoma7, 2);
					*Refri_Motors = 1;
					if(centralButtonState == 1){
						HAL_Delay(DELAY);
						Refri_Mot = 2;
					}
				break;
				case(2):
					draw_text("MOTORS      FULL", 12, 35, Tahoma7, 2);
					*Refri_Motors = 2;
					if(centralButtonState == 1){
						HAL_Delay(DELAY);
						Refri_Mot = 0;
					}
				break;
				}
				if(upButtonState == 1){
					HAL_Delay(DELAY);
					selected = 1;
				}
				if(downButtonState == 1){
					HAL_Delay(DELAY);
					selected = 0;
				}
			break;
			}
		switch(Refri_Accu){
		case(0):
			draw_text("ACCU         ON", 12, 5, Tahoma7, 2);
		break;
		case(1):
			draw_text("ACCU         OFF", 12, 5, Tahoma7, 2);
		break;
		case(2):
			draw_text("ACCU         FULL", 12, 5, Tahoma7, 2);
		break;
		}
		switch(Refri_Inv){
		case(0):
			draw_text("INVERTERS  ON", 12, 20, Tahoma7, 2);
		break;
		case(1):
			draw_text("INVERTERS OFF", 12, 20, Tahoma7, 2);
		break;
		case(2):
			draw_text("INVERTERS FULL", 12, 20, Tahoma7, 2);
		break;
		}
		switch(Refri_Mot){
		case(0):
			draw_text("MOTORS       ON", 12, 35, Tahoma7, 2);
		break;
		case(1):
			draw_text("MOTORS      OFF", 12, 35, Tahoma7, 2);
		break;
		case(2):
			draw_text("MOTORS      FULL", 12, 35, Tahoma7, 2);
		break;
		}
}

void racing_mode_selection(uint8_t *Racing_Mode, uint8_t *RTD) {
    uint8_t downButtonState = Read_Button_Edge(DOWN_BUTTON_GPIO_Port, DOWN_BUTTON_Pin);
    uint8_t upButtonState = Read_Button_Edge(UP_BUTTON_GPIO_Port, UP_BUTTON_Pin);
    uint8_t leftButtonState = Read_Button_Edge(LEFT_BUTTON_GPIO_Port, LEFT_BUTTON_Pin);
    uint8_t rightButtonState = Read_Button_Edge(RIGHT_BUTTON_GPIO_Port, RIGHT_BUTTON_Pin);
    uint8_t DELAY = 150;

    switch (Racing_Mode[0]) {
        case 1:
            if (downButtonState == 1) {
                HAL_Delay(DELAY);
                Racing_Mode[0] = 2;  // Cambiar a 2 después de presionar el botón
            }
            if (upButtonState == 1) {
                HAL_Delay(DELAY);
                Racing_Mode[0] = 5;
            }
            if (leftButtonState == 1 || rightButtonState == 1) {
                HAL_Delay(DELAY);
                *RTD = 1;

            }
            break;

        case 2:
            if (downButtonState == 1) {
                HAL_Delay(DELAY);
                Racing_Mode[0] = 3;
            }
            if (upButtonState == 1) {
                HAL_Delay(DELAY);
                Racing_Mode[0] = 1;
            }
            if (leftButtonState == 1 || rightButtonState == 1) {
                HAL_Delay(DELAY);
                *RTD = 1;
            }
            break;

        case 3:
            if (downButtonState == 1) {
                HAL_Delay(DELAY);
                Racing_Mode[0] = 4;
            }
            if (upButtonState == 1) {
                HAL_Delay(DELAY);
                Racing_Mode[0] = 2;
            }
            if (leftButtonState == 1 || rightButtonState == 1) {
                HAL_Delay(DELAY);
                *RTD = 1;
            }
            break;

        case 4:
            if (downButtonState == 1) {
                HAL_Delay(DELAY);
                Racing_Mode[0] = 5;
            }
            if (upButtonState == 1) {
            	HAL_Delay(DELAY);
                Racing_Mode[0] = 3;
            }
            if (leftButtonState == 1 || rightButtonState == 1) {
            	HAL_Delay(DELAY);
                *RTD = 1;
            }
            break;

        case 5:
            if (downButtonState == 1) {
            	HAL_Delay(DELAY);
                Racing_Mode[0] = 1;
            }
            if (upButtonState == 1) {
            	HAL_Delay(DELAY);
                Racing_Mode[0] = 4;
            }
            if (leftButtonState == 1 || rightButtonState == 1) {
            	HAL_Delay(DELAY);
                *RTD = 1;
            }
            break;
    }
}

void BMS_IMD_ERROR(uint8_t BMS_SD, uint8_t IMD_SD){
	if(BMS_SD==0){
		HAL_GPIO_WritePin(AMS_LED_GPIO_Port, AMS_LED_Pin, 1);
	}
	if(IMD_SD==0){
		HAL_GPIO_WritePin(IMD_LED_GPIO_Port, IMD_LED_Pin, 1);
	}
}


uint8_t enable_driving(uint8_t *Enable_Drive, uint8_t *rtd){
    uint8_t leftButtonState = Read_Button_Edge(LEFT_BUTTON_GPIO_Port, LEFT_BUTTON_Pin);
    uint8_t rightButtonState = Read_Button_Edge(RIGHT_BUTTON_GPIO_Port, RIGHT_BUTTON_Pin);
    uint8_t DELAY = 150;
	Enable_Drive[0] = HAL_GPIO_ReadPin(OK_BUTTON_GPIO_Port, OK_BUTTON_Pin);
	if(leftButtonState == 1){
		HAL_Delay(DELAY);
		*rtd=0;
	}
	if(rightButtonState == 1){
		HAL_Delay(DELAY);
		*rtd=0;
	}
	return *rtd;
}

uint8_t car_state_12_control(uint8_t *Racing_Mode, uint8_t *rtd, uint8_t *Enable_Drive){
	if(*rtd==0){
		racing_mode_selection(Racing_Mode, rtd);
	}
	else
	{
		enable_driving(Enable_Drive, rtd);
	}
	return *rtd;
}

void setLEDs(uint8_t percentage) {
    // Turn off all LEDs first
    HAL_GPIO_WritePin(LED_RED_3_GPIO_Port, LED_RED_3_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(LED_RED_2_GPIO_Port, LED_RED_2_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(LED_RED_1_GPIO_Port, LED_RED_1_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(LED_YELLOW_3_GPIO_Port, LED_YELLOW_3_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(LED_YELLOW_2_GPIO_Port, LED_YELLOW_2_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(LED_YELLOW_1_GPIO_Port, LED_YELLOW_1_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(LED_GREEN_3_GPIO_Port, LED_GREEN_3_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(LED_GREEN_2_GPIO_Port, LED_GREEN_2_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(LED_GREEN_1_GPIO_Port, LED_GREEN_1_Pin, GPIO_PIN_RESET);

    // Determine the number of LEDs to light up
    uint8_t numLEDs = (percentage * 9) / 100;

    // Light up LEDs based on the percentage and turn off the others
    switch (numLEDs) {
        case 9:
            HAL_GPIO_WritePin(LED_RED_3_GPIO_Port, LED_RED_3_Pin, GPIO_PIN_SET);
            HAL_GPIO_WritePin(LED_RED_2_GPIO_Port, LED_RED_2_Pin, GPIO_PIN_SET);
            HAL_GPIO_WritePin(LED_RED_1_GPIO_Port, LED_RED_1_Pin, GPIO_PIN_SET);
            HAL_GPIO_WritePin(LED_YELLOW_3_GPIO_Port, LED_YELLOW_3_Pin, GPIO_PIN_SET);
            HAL_GPIO_WritePin(LED_YELLOW_2_GPIO_Port, LED_YELLOW_2_Pin, GPIO_PIN_SET);
            HAL_GPIO_WritePin(LED_YELLOW_1_GPIO_Port, LED_YELLOW_1_Pin, GPIO_PIN_SET);
            HAL_GPIO_WritePin(LED_GREEN_3_GPIO_Port, LED_GREEN_3_Pin, GPIO_PIN_SET);
            HAL_GPIO_WritePin(LED_GREEN_2_GPIO_Port, LED_GREEN_2_Pin, GPIO_PIN_SET);
            HAL_GPIO_WritePin(LED_GREEN_1_GPIO_Port, LED_GREEN_1_Pin, GPIO_PIN_SET);
            break;
        case 8:
            HAL_GPIO_WritePin(LED_RED_3_GPIO_Port, LED_RED_3_Pin, GPIO_PIN_SET);
            HAL_GPIO_WritePin(LED_RED_2_GPIO_Port, LED_RED_2_Pin, GPIO_PIN_SET);
            HAL_GPIO_WritePin(LED_RED_1_GPIO_Port, LED_RED_1_Pin, GPIO_PIN_SET);
            HAL_GPIO_WritePin(LED_YELLOW_3_GPIO_Port, LED_YELLOW_3_Pin, GPIO_PIN_SET);
            HAL_GPIO_WritePin(LED_YELLOW_2_GPIO_Port, LED_YELLOW_2_Pin, GPIO_PIN_SET);
            HAL_GPIO_WritePin(LED_YELLOW_1_GPIO_Port, LED_YELLOW_1_Pin, GPIO_PIN_SET);
            HAL_GPIO_WritePin(LED_GREEN_1_GPIO_Port, LED_GREEN_1_Pin, GPIO_PIN_SET);
            HAL_GPIO_WritePin(LED_GREEN_2_GPIO_Port, LED_GREEN_2_Pin, GPIO_PIN_SET);
            break;
        case 7:
            HAL_GPIO_WritePin(LED_RED_3_GPIO_Port, LED_RED_3_Pin, GPIO_PIN_SET);
            HAL_GPIO_WritePin(LED_RED_2_GPIO_Port, LED_RED_2_Pin, GPIO_PIN_SET);
            HAL_GPIO_WritePin(LED_RED_1_GPIO_Port, LED_RED_1_Pin, GPIO_PIN_SET);
            HAL_GPIO_WritePin(LED_YELLOW_3_GPIO_Port, LED_YELLOW_3_Pin, GPIO_PIN_SET);
            HAL_GPIO_WritePin(LED_YELLOW_2_GPIO_Port, LED_YELLOW_2_Pin, GPIO_PIN_SET);
            HAL_GPIO_WritePin(LED_YELLOW_1_GPIO_Port, LED_YELLOW_1_Pin, GPIO_PIN_SET);
            HAL_GPIO_WritePin(LED_GREEN_1_GPIO_Port, LED_GREEN_1_Pin, GPIO_PIN_SET);
            break;
        case 6:
            HAL_GPIO_WritePin(LED_RED_3_GPIO_Port, LED_RED_3_Pin, GPIO_PIN_SET);
            HAL_GPIO_WritePin(LED_RED_2_GPIO_Port, LED_RED_2_Pin, GPIO_PIN_SET);
            HAL_GPIO_WritePin(LED_RED_1_GPIO_Port, LED_RED_1_Pin, GPIO_PIN_SET);
            HAL_GPIO_WritePin(LED_YELLOW_3_GPIO_Port, LED_YELLOW_3_Pin, GPIO_PIN_SET);
            HAL_GPIO_WritePin(LED_YELLOW_2_GPIO_Port, LED_YELLOW_2_Pin, GPIO_PIN_SET);
            HAL_GPIO_WritePin(LED_YELLOW_1_GPIO_Port, LED_YELLOW_1_Pin, GPIO_PIN_SET);
            break;
        case 5:
            HAL_GPIO_WritePin(LED_RED_3_GPIO_Port, LED_RED_3_Pin, GPIO_PIN_SET);
            HAL_GPIO_WritePin(LED_RED_2_GPIO_Port, LED_RED_2_Pin, GPIO_PIN_SET);
            HAL_GPIO_WritePin(LED_RED_1_GPIO_Port, LED_RED_1_Pin, GPIO_PIN_SET);
            HAL_GPIO_WritePin(LED_YELLOW_2_GPIO_Port, LED_YELLOW_2_Pin, GPIO_PIN_SET);
            HAL_GPIO_WritePin(LED_YELLOW_1_GPIO_Port, LED_YELLOW_1_Pin, GPIO_PIN_SET);
            break;
        case 4:
//            HAL_GPIO_WritePin(LED_RED_3_GPIO_Port, LED_RED_3_Pin, GPIO_PIN_SET);
//            HAL_GPIO_WritePin(LED_RED_2_GPIO_Port, LED_RED_2_Pin, GPIO_PIN_SET);
//            HAL_GPIO_WritePin(LED_RED_1_GPIO_Port, LED_RED_1_Pin, GPIO_PIN_SET);
            HAL_GPIO_WritePin(LED_YELLOW_1_GPIO_Port, LED_YELLOW_1_Pin, GPIO_PIN_SET);
            break;
        case 3:
            HAL_GPIO_WritePin(LED_RED_3_GPIO_Port, LED_RED_3_Pin, GPIO_PIN_SET);
            HAL_GPIO_WritePin(LED_RED_2_GPIO_Port, LED_RED_2_Pin, GPIO_PIN_SET);
            HAL_GPIO_WritePin(LED_RED_1_GPIO_Port, LED_RED_1_Pin, GPIO_PIN_SET);
            break;
        case 2:
            HAL_GPIO_WritePin(LED_RED_1_GPIO_Port, LED_RED_1_Pin, GPIO_PIN_SET);
            HAL_GPIO_WritePin(LED_RED_2_GPIO_Port, LED_RED_2_Pin, GPIO_PIN_SET);
            break;
        case 1:
            HAL_GPIO_WritePin(LED_RED_1_GPIO_Port, LED_RED_1_Pin, GPIO_PIN_SET);
            break;
        case 0:
            // All LEDs are already off at the beginning of the function
          break;
    }
}

