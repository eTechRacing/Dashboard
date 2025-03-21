################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/CAN/CAN_X_2025.c 

OBJS += \
./Core/Src/CAN/CAN_X_2025.o 

C_DEPS += \
./Core/Src/CAN/CAN_X_2025.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/CAN/%.o Core/Src/CAN/%.su Core/Src/CAN/%.cyclo: ../Core/Src/CAN/%.c Core/Src/CAN/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L476xx -c -I../Core/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Src-2f-CAN

clean-Core-2f-Src-2f-CAN:
	-$(RM) ./Core/Src/CAN/CAN_X_2025.cyclo ./Core/Src/CAN/CAN_X_2025.d ./Core/Src/CAN/CAN_X_2025.o ./Core/Src/CAN/CAN_X_2025.su

.PHONY: clean-Core-2f-Src-2f-CAN

