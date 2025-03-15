/*
 * etr_screens.c
 *
 *  Created on: Feb 19, 2025
 *      Author: Carmen Unió Cruz
 */
#include "stm32l4xx_hal.h"
#include "DASH/etr_screens.h"
#include "LCD/ili9488.h"
#include "LCD/lcd_io_spi.h"
#include "LCD/lcd.h"
#include "LCD/stm32_adafruit_lcd.h"
#include "LCD/bmp.h"


uint8_t i = 0;
/*
 * 		@brief
 * 		@param
 * 		@retval
 */

void ETR_Screen_Init(void){
	BSP_LCD_Clear(LCD_COLOR(31,237,20));
	//Todo: insertar logo nuevo del equipo
	BSP_LCD_Clear(LCD_COLOR(31,237,20));
}



void ETR_Screen_Shutdown(void){

}

void ETR_Screen_InitPrecharge(void){

}

void ETR_Screen_PrechargeDone(void){

}

/*void ETR_Screen_PrechargeDone(void){

}

void ETR_Screen_Errors(void){

}

/*
BSP_LCD_SetFont(&Font50);
     sprintf(msg0, "%u", numero);
	  BSP_LCD_DisplayStringAt(0, 120, (uint8_t*)msg0, CENTER_MODE);
	  numero ++;

	  HAL_Delay(500);



  BSP_LCD_SetFont(&Font24);

  uint16_t y = 0;
  uint16_t x = 0;
  uint16_t msgy[20];
  uint16_t msgx[20];
  BSP_LCD_Clear(LCD_COLOR_BLACK);
  y = BSP_LCD_GetYSize();
  x = BSP_LCD_GetXSize();

  sprintf(msgy,"Y = %u", y);
  sprintf(msgx,"X = %u", x);

  BSP_LCD_DisplayStringAt(0, 120, (uint16_t*)msgy, CENTER_MODE);
  BSP_LCD_DisplayStringAt(0, 180, (uint16_t*)msgx, CENTER_MODE);
	  */
