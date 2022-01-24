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
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F415xx -c -I../Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Middlewares/Third_Party/FatFs/src -I../Drivers/CMSIS/Include -I../FT800 -I../SD -Og -ffunction-sections -Wall -fstack-usage -MMD -MP -MF"SD/my_diskio.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

