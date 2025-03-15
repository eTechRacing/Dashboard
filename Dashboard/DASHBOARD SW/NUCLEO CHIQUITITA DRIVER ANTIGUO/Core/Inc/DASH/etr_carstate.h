/*
 * etr_carstate.h
 *
 *  Created on: Feb 25, 2025
 *      Author: cunio
 */

#ifndef INC_DASH_ETR_CARSTATE_H_
#define INC_DASH_ETR_CARSTATE_H_

#include "stdint.h"

	typedef enum {
		DASH_0_ETR,
		DASH_3_PRECHARGE,
		DASH_6_PRECHARGE_STATUS,
		DASH_9_PRECHARGE_FINISHED,
		DASH_12_RACING_MENU,
		DASH_14_INVERTERS,
		DASH_15_RACING_MODE,
		DASH_21_ERROR
	}	DASH_CarState;

	typedef enum {
		SCREEN_1,
		SCREEN_2,
		SCREEN_3,
		SCREEN_4,
		SCREEN_5,
		SCREEN_6,
		SCREEN_7,
		SCREEN_8,
		SCREEN_9,
		SCREEN_10,
		SCREEN_11,
	}	DASH_Screen;

	typedef struct {
		DASH_CarState ActualState;
		DASH_Screen ActualScreen;
	}	DASH_State;

	extern DASH_State Screen;

	extern const int NUM_SCREENS_PER_STATE[];
	void refreshScreen(uint8_t event);
	void drawScreen(void);

#endif /* INC_DASH_ETR_CARSTATE_H_ */
