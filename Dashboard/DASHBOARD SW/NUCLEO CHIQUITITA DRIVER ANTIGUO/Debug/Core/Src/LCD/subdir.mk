################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/LCD/ili9488.c \
../Core/Src/LCD/lcd_io_spi.c \
../Core/Src/LCD/stm32_adafruit_lcd.c 

OBJS += \
./Core/Src/LCD/ili9488.o \
./Core/Src/LCD/lcd_io_spi.o \
./Core/Src/LCD/stm32_adafruit_lcd.o 

C_DEPS += \
./Core/Src/LCD/ili9488.d \
./Core/Src/LCD/lcd_io_spi.d \
./Core/Src/LCD/stm32_adafruit_lcd.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/LCD/%.o Core/Src/LCD/%.su Core/Src/LCD/%.cyclo: ../Core/Src/LCD/%.c Core/Src/LCD/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L476xx -c -I../Core/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Src-2f-LCD

clean-Core-2f-Src-2f-LCD:
	-$(RM) ./Core/Src/LCD/ili9488.cyclo ./Core/Src/LCD/ili9488.d ./Core/Src/LCD/ili9488.o ./Core/Src/LCD/ili9488.su ./Core/Src/LCD/lcd_io_spi.cyclo ./Core/Src/LCD/lcd_io_spi.d ./Core/Src/LCD/lcd_io_spi.o ./Core/Src/LCD/lcd_io_spi.su ./Core/Src/LCD/stm32_adafruit_lcd.cyclo ./Core/Src/LCD/stm32_adafruit_lcd.d ./Core/Src/LCD/stm32_adafruit_lcd.o ./Core/Src/LCD/stm32_adafruit_lcd.su

.PHONY: clean-Core-2f-Src-2f-LCD

