################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/fatfs.c \
../Src/main.c \
../Src/my_delays.c \
../Src/stm32f0xx_hal_msp.c \
../Src/stm32f0xx_it.c \
../Src/system_stm32f0xx.c \
../Src/user_diskio.c 

OBJS += \
./Src/fatfs.o \
./Src/main.o \
./Src/my_delays.o \
./Src/stm32f0xx_hal_msp.o \
./Src/stm32f0xx_it.o \
./Src/system_stm32f0xx.o \
./Src/user_diskio.o 

C_DEPS += \
./Src/fatfs.d \
./Src/main.d \
./Src/my_delays.d \
./Src/stm32f0xx_hal_msp.d \
./Src/stm32f0xx_it.d \
./Src/system_stm32f0xx.d \
./Src/user_diskio.d 


# Each subdirectory must supply rules for building sources it contributes
Src/fatfs.o: ../Src/fatfs.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F051x8 -DDEBUG -c -I../Inc -I../FT800 -I../Drivers/STM32F0xx_HAL_Driver/Inc -I../Drivers/CMSIS/Include -I../Drivers/STM32F0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F0xx/Include -I../SD -I../Middlewares/Third_Party/FatFs/src -O0 -ffunction-sections -Wall -fstack-usage -MMD -MP -MF"Src/fatfs.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Src/main.o: ../Src/main.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F051x8 -DDEBUG -c -I../Inc -I../FT800 -I../Drivers/STM32F0xx_HAL_Driver/Inc -I../Drivers/CMSIS/Include -I../Drivers/STM32F0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F0xx/Include -I../SD -I../Middlewares/Third_Party/FatFs/src -O0 -ffunction-sections -Wall -fstack-usage -MMD -MP -MF"Src/main.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Src/my_delays.o: ../Src/my_delays.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F051x8 -DDEBUG -c -I../Inc -I../FT800 -I../Drivers/STM32F0xx_HAL_Driver/Inc -I../Drivers/CMSIS/Include -I../Drivers/STM32F0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F0xx/Include -I../SD -I../Middlewares/Third_Party/FatFs/src -O0 -ffunction-sections -Wall -fstack-usage -MMD -MP -MF"Src/my_delays.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Src/stm32f0xx_hal_msp.o: ../Src/stm32f0xx_hal_msp.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F051x8 -DDEBUG -c -I../Inc -I../FT800 -I../Drivers/STM32F0xx_HAL_Driver/Inc -I../Drivers/CMSIS/Include -I../Drivers/STM32F0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F0xx/Include -I../SD -I../Middlewares/Third_Party/FatFs/src -O0 -ffunction-sections -Wall -fstack-usage -MMD -MP -MF"Src/stm32f0xx_hal_msp.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Src/stm32f0xx_it.o: ../Src/stm32f0xx_it.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F051x8 -DDEBUG -c -I../Inc -I../FT800 -I../Drivers/STM32F0xx_HAL_Driver/Inc -I../Drivers/CMSIS/Include -I../Drivers/STM32F0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F0xx/Include -I../SD -I../Middlewares/Third_Party/FatFs/src -O0 -ffunction-sections -Wall -fstack-usage -MMD -MP -MF"Src/stm32f0xx_it.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Src/system_stm32f0xx.o: ../Src/system_stm32f0xx.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F051x8 -DDEBUG -c -I../Inc -I../FT800 -I../Drivers/STM32F0xx_HAL_Driver/Inc -I../Drivers/CMSIS/Include -I../Drivers/STM32F0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F0xx/Include -I../SD -I../Middlewares/Third_Party/FatFs/src -O0 -ffunction-sections -Wall -fstack-usage -MMD -MP -MF"Src/system_stm32f0xx.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Src/user_diskio.o: ../Src/user_diskio.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F051x8 -DDEBUG -c -I../Inc -I../FT800 -I../Drivers/STM32F0xx_HAL_Driver/Inc -I../Drivers/CMSIS/Include -I../Drivers/STM32F0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F0xx/Include -I../SD -I../Middlewares/Third_Party/FatFs/src -O0 -ffunction-sections -Wall -fstack-usage -MMD -MP -MF"Src/user_diskio.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

