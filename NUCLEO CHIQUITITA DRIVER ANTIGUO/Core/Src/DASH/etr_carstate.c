/*
 * etr_carstate.c
 *
 *  Created on: Feb 25, 2025
 *      Author: cunio
 */

#include "DASH/etr_carstate.h"
#include "DASH/buttons.h"
#include "stdint.h"

const int NUM_SCREENS_PER_STATE[] = {
    3,  // DASH_0_ETR
    3,  // DASH_3_PRECHARGE
    1,  // DASH_6_PRECHARGE_STATUS
    1,  // DASH_9_PRECHARGE_FINISHED
    11, // DASH_12_RACING_MENU
    1,  // DASH_14_INVERTERS
    4,  // DASH_15_RACING_MODE
    1   // DASH_21_ERROR
};

DASH_State Screen = {DASH_0_ETR, SCREEN_1};

// haces la pantalla estatica, y los datos se ponen en la otra funcion
void refreshScreen(uint8_t event) {
    int numScreens = NUM_SCREENS_PER_STATE[Screen.ActualState];

    switch(Screen.ActualState) {

        case DASH_0_ETR:
        	Screen.ActualScreen = SCREEN_1;

            if (event == EVENT_BUTTON_DOWN && Screen.ActualScreen < numScreens - 1) {
                Screen.ActualScreen--;
            }
            if (event == EVENT_BUTTON_UP && Screen.ActualScreen > 0) {
                Screen.ActualScreen++;
            }
            if (event == EVENT_BUTTON_RIGHT) {
                Screen.ActualState++;
            }

            break;

        case DASH_3_PRECHARGE:
        	Screen.ActualScreen = SCREEN_1;
            if (event == EVENT_BUTTON_OK) {
            	// enviar estado de precharge por CAN
            }
            if (event == EVENT_BUTTON_RIGHT) {
                Screen.ActualState++;
            }
            break;

        case DASH_6_PRECHARGE_STATUS:
        	Screen.ActualScreen = SCREEN_1;
            if (event == EVENT_BUTTON_OK) {
                // Cambiar al siguiente estado tras completar la precarga
                Screen.ActualState = DASH_9_PRECHARGE_FINISHED;
                Screen.ActualScreen = SCREEN_1;
            }
            if (event == EVENT_BUTTON_RIGHT) {
                Screen.ActualState++;
            }
            break;

        case DASH_9_PRECHARGE_FINISHED:
        	Screen.ActualScreen = SCREEN_1;
        		// funcion de pantalla de preecharge finished
        		// esperar que se envie el cambio de estado
            if (event == EVENT_BUTTON_RIGHT) {
                Screen.ActualState++;
            }
            break;

        case DASH_12_RACING_MENU:
        	Screen.ActualScreen = SCREEN_1;
        		// menú complicado esperar a aprobar el state machine
            if (event == EVENT_BUTTON_RIGHT) {
                Screen.ActualState++;
            }
            break;

        case DASH_14_INVERTERS:
        	Screen.ActualScreen = SCREEN_1;
        		// funcion de pantalla de preecharge finished
        	    // esperar que se envie el cambio de estado
            if (event == EVENT_BUTTON_RIGHT) {
                Screen.ActualState++;
            }
            break;

        case DASH_15_RACING_MODE:
        	Screen.ActualScreen = SCREEN_1;
    			// menú complicado esperar a aprobar el state machine
            if (event == EVENT_BUTTON_RIGHT) {
                Screen.ActualState++;
            }
            break;

        case DASH_21_ERROR:
            	// funcion de pantalla error "ups... something went wrong"
            if (event == EVENT_BUTTON_RIGHT) {
                Screen.ActualState = DASH_0_ETR;
            }
            break;

    }
}

#include "DASH/etr_carstate.h"
#include <stdio.h>

// Declaramos la función que dibuja la pantalla
void drawScreen(void) {
    switch (Screen.ActualState) {
        case DASH_0_ETR:
            switch (Screen.ActualScreen) {
                case SCREEN_1:
                    // funcion de pantalla
                	break;
            }
            break;

        case DASH_3_PRECHARGE:
            switch (Screen.ActualScreen) {
                case SCREEN_1:
                    // funcion de pantalla
                    break;
            }
            break;

        case DASH_6_PRECHARGE_STATUS:
            		// funcion de pantalla
            break;

        case DASH_9_PRECHARGE_FINISHED:
            		// funcion de pantalla
            break;

        case DASH_12_RACING_MENU:
            switch (Screen.ActualScreen) {
                case SCREEN_1:
                    	// funcion de pantalla
                    break;
            }
            break;

        case DASH_14_INVERTERS:
            		// funcion de pantalla
            break;

        case DASH_15_RACING_MODE:
            switch (Screen.ActualScreen) {
                case SCREEN_1:
                    // funcion de pantalla
                    break;
            }
            break;

        case DASH_21_ERROR:
            		// funcion de pantalla
            break;

        default:
        		// funcion de pantalla
            break;
    }
}
