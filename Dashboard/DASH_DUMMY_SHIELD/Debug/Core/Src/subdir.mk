################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/buttons.c \
../Core/Src/can.c \
../Core/Src/etr_screen.c \
../Core/Src/glcd.c \
../Core/Src/glcd_etr.c \
../Core/Src/graphics.c \
../Core/Src/init.c \
../Core/Src/main.c \
../Core/Src/statemachine.c \
../Core/Src/stm32f7xx_hal_msp.c \
../Core/Src/stm32f7xx_it.c \
../Core/Src/syscalls.c \
../Core/Src/sysmem.c \
../Core/Src/system_stm32f7xx.c 

OBJS += \
./Core/Src/buttons.o \
./Core/Src/can.o \
./Core/Src/etr_screen.o \
./Core/Src/glcd.o \
./Core/Src/glcd_etr.o \
./Core/Src/graphics.o \
./Core/Src/init.o \
./Core/Src/main.o \
./Core/Src/statemachine.o \
./Core/Src/stm32f7xx_hal_msp.o \
./Core/Src/stm32f7xx_it.o \
./Core/Src/syscalls.o \
./Core/Src/sysmem.o \
./Core/Src/system_stm32f7xx.o 

C_DEPS += \
./Core/Src/buttons.d \
./Core/Src/can.d \
./Core/Src/etr_screen.d \
./Core/Src/glcd.d \
./Core/Src/glcd_etr.d \
./Core/Src/graphics.d \
./Core/Src/init.d \
./Core/Src/main.d \
./Core/Src/statemachine.d \
./Core/Src/stm32f7xx_hal_msp.d \
./Core/Src/stm32f7xx_it.d \
./Core/Src/syscalls.d \
./Core/Src/sysmem.d \
./Core/Src/system_stm32f7xx.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/%.o Core/Src/%.su Core/Src/%.cyclo: ../Core/Src/%.c Core/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F777xx -c -I../Core/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F7xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Src

clean-Core-2f-Src:
	-$(RM) ./Core/Src/buttons.cyclo ./Core/Src/buttons.d ./Core/Src/buttons.o ./Core/Src/buttons.su ./Core/Src/can.cyclo ./Core/Src/can.d ./Core/Src/can.o ./Core/Src/can.su ./Core/Src/etr_screen.cyclo ./Core/Src/etr_screen.d ./Core/Src/etr_screen.o ./Core/Src/etr_screen.su ./Core/Src/glcd.cyclo ./Core/Src/glcd.d ./Core/Src/glcd.o ./Core/Src/glcd.su ./Core/Src/glcd_etr.cyclo ./Core/Src/glcd_etr.d ./Core/Src/glcd_etr.o ./Core/Src/glcd_etr.su ./Core/Src/graphics.cyclo ./Core/Src/graphics.d ./Core/Src/graphics.o ./Core/Src/graphics.su ./Core/Src/init.cyclo ./Core/Src/init.d ./Core/Src/init.o ./Core/Src/init.su ./Core/Src/main.cyclo ./Core/Src/main.d ./Core/Src/main.o ./Core/Src/main.su ./Core/Src/statemachine.cyclo ./Core/Src/statemachine.d ./Core/Src/statemachine.o ./Core/Src/statemachine.su ./Core/Src/stm32f7xx_hal_msp.cyclo ./Core/Src/stm32f7xx_hal_msp.d ./Core/Src/stm32f7xx_hal_msp.o ./Core/Src/stm32f7xx_hal_msp.su ./Core/Src/stm32f7xx_it.cyclo ./Core/Src/stm32f7xx_it.d ./Core/Src/stm32f7xx_it.o ./Core/Src/stm32f7xx_it.su ./Core/Src/syscalls.cyclo ./Core/Src/syscalls.d ./Core/Src/syscalls.o ./Core/Src/syscalls.su ./Core/Src/sysmem.cyclo ./Core/Src/sysmem.d ./Core/Src/sysmem.o ./Core/Src/sysmem.su ./Core/Src/system_stm32f7xx.cyclo ./Core/Src/system_stm32f7xx.d ./Core/Src/system_stm32f7xx.o ./Core/Src/system_stm32f7xx.su

.PHONY: clean-Core-2f-Src

