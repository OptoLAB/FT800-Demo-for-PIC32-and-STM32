################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../SD/my_diskio.c 

OBJS += \
./SD/my_diskio.o 

C_DEPS += \
./SD/my_diskio.d 


# Each subdirectory must supply rules for building sources it contributes
SD/my_diskio.o: ../SD/my_diskio.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F051x8 -DDEBUG -c -I../Inc -I../FT800 -I../Drivers/STM32F0xx_HAL_Driver/Inc -I../Drivers/CMSIS/Include -I../Drivers/STM32F0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F0xx/Include -I../SD -I../Middlewares/Third_Party/FatFs/src -O0 -ffunction-sections -Wall -fstack-usage -MMD -MP -MF"SD/my_diskio.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

