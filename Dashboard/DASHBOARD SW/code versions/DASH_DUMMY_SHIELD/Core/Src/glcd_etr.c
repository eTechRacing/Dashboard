/*
 * glcd_etr.c
 *
 *  Created on: May 25, 2024
 *      Author: Pol & Carmen
 */

unsigned char glcd_flipped = 1;


#include "glcd_etr.h"
#include "main.h"

unsigned char glcd_buffer[SCREEN_WIDTH * SCREEN_HEIGHT / 8];



	void glcd_etr_command(SPI_HandleTypeDef hspi_channel, char command){

		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_8, GPIO_PIN_RESET); //a0
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_7, GPIO_PIN_RESET); //CS

		HAL_SPI_Transmit(&hspi_channel, (uint8_t *) &command, 1, 100);

		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_7, GPIO_PIN_SET); //CS

	}

	void glcd_etr_init(SPI_HandleTypeDef hspi_channel){

		HAL_GPIO_WritePin(RST_LCD_GPIO_Port, RST_LCD_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(CS_LCD_GPIO_Port, CS_LCD_Pin, GPIO_PIN_SET);

		glcd_etr_command(hspi_channel, 0x40);
		glcd_etr_command(hspi_channel, 0xA1);
		glcd_etr_command(hspi_channel, 0xC0);
		glcd_etr_command(hspi_channel, 0xA6);
		glcd_etr_command(hspi_channel, 0xA2);
		glcd_etr_command(hspi_channel, 0x2F);
		glcd_etr_command(hspi_channel, 0xF8);
		glcd_etr_command(hspi_channel, 0x00);
		glcd_etr_command(hspi_channel, 0x27);
		glcd_etr_command(hspi_channel, 0x81);
		glcd_etr_command(hspi_channel, 0x10);
		glcd_etr_command(hspi_channel, 0xAC);
		glcd_etr_command(hspi_channel, 0x00);
		glcd_etr_command(hspi_channel, 0xAF);

	}

	void glcd_etr_data(SPI_HandleTypeDef hspi_channel, unsigned char data) {

	    // A0 is high for display data
		HAL_GPIO_WritePin(GLCD_A0_PORT, GLCD_A0, GPIO_PIN_SET); //output_high(GLCD_A0);

	    // Select the chip
		HAL_GPIO_WritePin(GLCD_CS1_PORT, GLCD_CS1, GPIO_PIN_RESET); //output_low(GLCD_CS1);

		HAL_SPI_Transmit(&hspi_channel, (uint8_t *) &data, 1, 100);

	    // Unselect the chip
	    HAL_GPIO_WritePin(GLCD_CS1_PORT, GLCD_CS1, GPIO_PIN_SET); //output_high(GLCD_CS1);
	}

	void glcd_etr_refresh(SPI_HandleTypeDef hspi_channel) {
		glcd_etr_command(hspi_channel, GLCD_CMD_SET_PAGE | 0);

		 glcd_etr_command(hspi_channel, GLCD_CMD_COLUMN_LOWER);
		glcd_etr_command(hspi_channel, GLCD_CMD_COLUMN_UPPER);
	    for (int y = 0; y < 8; y++) {
	        glcd_etr_command(hspi_channel, GLCD_CMD_SET_PAGE | y);
	        glcd_etr_command(hspi_channel, GLCD_CMD_COLUMN_LOWER);
	       	glcd_etr_command(hspi_channel, GLCD_CMD_COLUMN_UPPER);

	        // Reset column to the left side.  The internal memory of the
	        // screen is 132*64, we need to account for this if the display
	        // is flipped.
	        //
	        // Some screens seem to map the internal memory to the screen
	        // pixels differently, the ST7565_REVERSE define allows this to
	        // be controlled if necessary.
	#ifdef ST7565_REVERSE
	        if (!glcd_flipped) {
	#else
	        if (glcd_flipped) {
	#endif
	            glcd_etr_command(hspi_channel, GLCD_CMD_COLUMN_LOWER | 4);
	        } else {
	            glcd_etr_command(hspi_channel, GLCD_CMD_COLUMN_LOWER);
	        }
	        glcd_etr_command(hspi_channel, GLCD_CMD_COLUMN_UPPER);
	        int16_t x;
	        for (x = 0; x < 128; x++) {
	            glcd_etr_data(hspi_channel, glcd_buffer[y * 128 + x]);
	        }
	    }
	 }


	    void glcd_pixel(uint8_t x, uint8_t y, uint8_t colour)
	    {
	       uint16_t array_pos; // *** Put declaration here
	       if (x > SCREEN_WIDTH || y > SCREEN_HEIGHT) return;
	       if ((x == 0) || (y == 0)) return;
	       // Real screen coordinates are 0-63, not 1-64.
	       x -= 1;
	       y -= 1;
	       array_pos = (int16_t)x +(((int16_t)y / 8)* 128);

	    #ifdef ST7565_DIRTY_PAGES
	    #warning ** ST7565_DIRTY_PAGES enabled, only changed pages will be written to the GLCD **
	        glcd_dirty_pages |= 1 << (array_pos / 128);
	    #endif

	        if (colour) {
	            glcd_buffer[array_pos] |= 1 << (y % 8);
	        } else {
	            glcd_buffer[array_pos] &= 0xFF ^ 1 << (y % 8);
	        }
	    }

	    void glcd_etr_blank(SPI_HandleTypeDef hspi_channel)
	    {
	    	uint16_t n;
	    	 		    // Reset the internal buffer
	    	 		    for (n = 1; n <= (SCREEN_WIDTH * SCREEN_HEIGHT / 8) - 1; n++) {
	    	 		        glcd_buffer[n] = 0;
	    	 		    }

	    }

	    void glcd_etr_blank_region(SPI_HandleTypeDef hspi_channel)
	    {
	    	int16_t n;
	    	int8_t x,y;
	    	// Reset the internal buffer
	    	for (n = 15; n <= (30 * 20 / 8) - 1; ++n) {
	    		glcd_buffer[n] = 0; //per fer q funcioni s'ha de fer amb dos FOR!
	    	}
	    	// Clear the actual screen
	    	for (y = 4; y < 8; y++) {
	    		glcd_etr_command(hspi_channel, GLCD_CMD_SET_PAGE | y);
	    		// Reset column to 0 (the left side)
	    	    glcd_etr_command(hspi_channel, GLCD_CMD_COLUMN_LOWER);
	    	    glcd_etr_command(hspi_channel, GLCD_CMD_COLUMN_UPPER);
	    	    // We iterate to 132 as the internal buffer is 65*132, not
	    	    // 64*124.
	    	    for (x=30 ; x < 60; x++) {
	    	    	glcd_etr_data(hspi_channel, 0x00);
	    	    }
	    	}
	    }

	    void glcd_flip_screen(SPI_HandleTypeDef hspi_channel, unsigned char flip)
	    {
	        if (flip) {
	            glcd_etr_command(hspi_channel, GLCD_CMD_HORIZONTAL_NORMAL);
	            glcd_etr_command(hspi_channel, GLCD_CMD_VERTICAL_REVERSE);
	            glcd_flipped = 0;
	        } else {
	            glcd_etr_command(hspi_channel, GLCD_CMD_HORIZONTAL_REVERSE);
	            glcd_etr_command(hspi_channel, GLCD_CMD_VERTICAL_NORMAL);
	            glcd_flipped = 1;
	        }
	    }

	    void glcd_inverse_screen(SPI_HandleTypeDef hspi_channel, unsigned char inverse)
	    {
	        if (inverse) {
	            glcd_etr_command(hspi_channel, GLCD_CMD_DISPLAY_REVERSE);
	        } else {
	            glcd_etr_command(hspi_channel, GLCD_CMD_DISPLAY_NORMAL);
	        }
	    }

	    void glcd_test_card(SPI_HandleTypeDef hspi_channel)
	    {
	        unsigned char p = 0xF0;
	        int16_t n;
	        for (n = 1; n <= (SCREEN_WIDTH * SCREEN_HEIGHT / 8); n++) {
	            glcd_buffer[n - 1] = p;

	            if (n % 4 == 0) {
	                unsigned char q = p;
	                p = p << 4;
	                p |= q >> 4;
	            }
	        }
	        glcd_etr_refresh(hspi_channel);
	    }

	    void glcd_contrast(SPI_HandleTypeDef hspi_channel, char resistor_ratio, char contrast) {
	        if (resistor_ratio > 7 || contrast > 63) return;

	        glcd_etr_command(hspi_channel, GLCD_CMD_RESISTOR | resistor_ratio);
	        glcd_etr_command(hspi_channel, GLCD_CMD_VOLUME_MODE);
	        glcd_etr_command(hspi_channel, contrast);

	        //HAL_GPIO_TogglePin(LED_RED_1_GPIO_Port, LED_RED_1_Pin);
	        //HAL_GPIO_TogglePin(LED_RED_1_GPIO_Port, LED_RED_1_Pin);
	        //???
	    }

