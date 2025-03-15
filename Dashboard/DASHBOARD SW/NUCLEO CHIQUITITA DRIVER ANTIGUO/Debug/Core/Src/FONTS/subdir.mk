################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/FONTS/font12.c \
../Core/Src/FONTS/font16.c \
../Core/Src/FONTS/font20.c \
../Core/Src/FONTS/font24.c \
../Core/Src/FONTS/font50.c \
../Core/Src/FONTS/font8.c 

OBJS += \
./Core/Src/FONTS/font12.o \
./Core/Src/FONTS/font16.o \
./Core/Src/FONTS/font20.o \
./Core/Src/FONTS/font24.o \
./Core/Src/FONTS/font50.o \
./Core/Src/FONTS/font8.o 

C_DEPS += \
./Core/Src/FONTS/font12.d \
./Core/Src/FONTS/font16.d \
./Core/Src/FONTS/font20.d \
./Core/Src/FONTS/font24.d \
./Core/Src/FONTS/font50.d \
./Core/Src/FONTS/font8.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/FONTS/%.o Core/Src/FONTS/%.su Core/Src/FONTS/%.cyclo: ../Core/Src/FONTS/%.c Core/Src/FONTS/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L476xx -c -I../Core/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Src-2f-FONTS

clean-Core-2f-Src-2f-FONTS:
	-$(RM) ./Core/Src/FONTS/font12.cyclo ./Core/Src/FONTS/font12.d ./Core/Src/FONTS/font12.o ./Core/Src/FONTS/font12.su ./Core/Src/FONTS/font16.cyclo ./Core/Src/FONTS/font16.d ./Core/Src/FONTS/font16.o ./Core/Src/FONTS/font16.su ./Core/Src/FONTS/font20.cyclo ./Core/Src/FONTS/font20.d ./Core/Src/FONTS/font20.o ./Core/Src/FONTS/font20.su ./Core/Src/FONTS/font24.cyclo ./Core/Src/FONTS/font24.d ./Core/Src/FONTS/font24.o ./Core/Src/FONTS/font24.su ./Core/Src/FONTS/font50.cyclo ./Core/Src/FONTS/font50.d ./Core/Src/FONTS/font50.o ./Core/Src/FONTS/font50.su ./Core/Src/FONTS/font8.cyclo ./Core/Src/FONTS/font8.d ./Core/Src/FONTS/font8.o ./Core/Src/FONTS/font8.su

.PHONY: clean-Core-2f-Src-2f-FONTS

