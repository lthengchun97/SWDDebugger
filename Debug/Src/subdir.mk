################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/AFIO.c \
../Src/Gpio.c \
../Src/Rcc.c \
../Src/abortreg.c \
../Src/debug.c \
../Src/main.c \
../Src/statandcontrol.c \
../Src/stm32f1xx_hal_msp.c \
../Src/stm32f1xx_it.c \
../Src/system_stm32f1xx.c 

OBJS += \
./Src/AFIO.o \
./Src/Gpio.o \
./Src/Rcc.o \
./Src/abortreg.o \
./Src/debug.o \
./Src/main.o \
./Src/statandcontrol.o \
./Src/stm32f1xx_hal_msp.o \
./Src/stm32f1xx_it.o \
./Src/system_stm32f1xx.o 

C_DEPS += \
./Src/AFIO.d \
./Src/Gpio.d \
./Src/Rcc.d \
./Src/abortreg.d \
./Src/debug.d \
./Src/main.d \
./Src/statandcontrol.d \
./Src/stm32f1xx_hal_msp.d \
./Src/stm32f1xx_it.d \
./Src/system_stm32f1xx.d 


# Each subdirectory must supply rules for building sources it contributes
Src/%.o: ../Src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -mfloat-abi=soft '-D__weak=__attribute__((weak))' '-D__packed=__attribute__((__packed__))' -DUSE_HAL_DRIVER -DSTM32F103xB -I"C:/Users/ME-D203-06/Desktop/ltc/SWDDebugger/Inc" -I"C:/Users/ME-D203-06/Desktop/ltc/SWDDebugger/Drivers/STM32F1xx_HAL_Driver/Inc" -I"C:/Users/ME-D203-06/Desktop/ltc/SWDDebugger/Drivers/STM32F1xx_HAL_Driver/Inc/Legacy" -I"C:/Users/ME-D203-06/Desktop/ltc/SWDDebugger/Drivers/CMSIS/Device/ST/STM32F1xx/Include" -I"C:/Users/ME-D203-06/Desktop/ltc/SWDDebugger/Drivers/CMSIS/Include"  -Og -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


