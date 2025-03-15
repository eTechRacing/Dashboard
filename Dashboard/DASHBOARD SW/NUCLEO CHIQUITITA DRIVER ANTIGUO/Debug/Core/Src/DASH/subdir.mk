################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/DASH/buttons.c \
../Core/Src/DASH/etr_carstate.c \
../Core/Src/DASH/etr_screens.c 

OBJS += \
./Core/Src/DASH/buttons.o \
./Core/Src/DASH/etr_carstate.o \
./Core/Src/DASH/etr_screens.o 

C_DEPS += \
./Core/Src/DASH/buttons.d \
./Core/Src/DASH/etr_carstate.d \
./Core/Src/DASH/etr_screens.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/DASH/%.o Core/Src/DASH/%.su Core/Src/DASH/%.cyclo: ../Core/Src/DASH/%.c Core/Src/DASH/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L476xx -c -I../Core/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Src-2f-DASH

clean-Core-2f-Src-2f-DASH:
	-$(RM) ./Core/Src/DASH/buttons.cyclo ./Core/Src/DASH/buttons.d ./Core/Src/DASH/buttons.o ./Core/Src/DASH/buttons.su ./Core/Src/DASH/etr_carstate.cyclo ./Core/Src/DASH/etr_carstate.d ./Core/Src/DASH/etr_carstate.o ./Core/Src/DASH/etr_carstate.su ./Core/Src/DASH/etr_screens.cyclo ./Core/Src/DASH/etr_screens.d ./Core/Src/DASH/etr_screens.o ./Core/Src/DASH/etr_screens.su

.PHONY: clean-Core-2f-Src-2f-DASH

