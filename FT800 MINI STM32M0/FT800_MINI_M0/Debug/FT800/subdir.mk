################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../FT800/FT800_Audio.c \
../FT800/FT800_Driver.c \
../FT800/FT800_Graphics.c \
../FT800/FT800_Port.c \
../FT800/FT800_SD.c 

OBJS += \
./FT800/FT800_Audio.o \
./FT800/FT800_Driver.o \
./FT800/FT800_Graphics.o \
./FT800/FT800_Port.o \
./FT800/FT800_SD.o 

C_DEPS += \
./FT800/FT800_Audio.d \
./FT800/FT800_Driver.d \
./FT800/FT800_Graphics.d \
./FT800/FT800_Port.d \
./FT800/FT800_SD.d 


# Each subdirectory must supply rules for building sources it contributes
FT800/FT800_Audio.o: ../FT800/FT800_Audio.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F051x8 -DDEBUG -c -I../Inc -I../FT800 -I../Drivers/STM32F0xx_HAL_Driver/Inc -I../Drivers/CMSIS/Include -I../Drivers/STM32F0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F0xx/Include -I../SD -I../Middlewares/Third_Party/FatFs/src -O0 -ffunction-sections -Wall -fstack-usage -MMD -MP -MF"FT800/FT800_Audio.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
FT800/FT800_Driver.o: ../FT800/FT800_Driver.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F051x8 -DDEBUG -c -I../Inc -I../FT800 -I../Drivers/STM32F0xx_HAL_Driver/Inc -I../Drivers/CMSIS/Include -I../Drivers/STM32F0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F0xx/Include -I../SD -I../Middlewares/Third_Party/FatFs/src -O0 -ffunction-sections -Wall -fstack-usage -MMD -MP -MF"FT800/FT800_Driver.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
FT800/FT800_Graphics.o: ../FT800/FT800_Graphics.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F051x8 -DDEBUG -c -I../Inc -I../FT800 -I../Drivers/STM32F0xx_HAL_Driver/Inc -I../Drivers/CMSIS/Include -I../Drivers/STM32F0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F0xx/Include -I../SD -I../Middlewares/Third_Party/FatFs/src -O0 -ffunction-sections -Wall -fstack-usage -MMD -MP -MF"FT800/FT800_Graphics.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
FT800/FT800_Port.o: ../FT800/FT800_Port.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F051x8 -DDEBUG -c -I../Inc -I../FT800 -I../Drivers/STM32F0xx_HAL_Driver/Inc -I../Drivers/CMSIS/Include -I../Drivers/STM32F0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F0xx/Include -I../SD -I../Middlewares/Third_Party/FatFs/src -O0 -ffunction-sections -Wall -fstack-usage -MMD -MP -MF"FT800/FT800_Port.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
FT800/FT800_SD.o: ../FT800/FT800_SD.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F051x8 -DDEBUG -c -I../Inc -I../FT800 -I../Drivers/STM32F0xx_HAL_Driver/Inc -I../Drivers/CMSIS/Include -I../Drivers/STM32F0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F0xx/Include -I../SD -I../Middlewares/Third_Party/FatFs/src -O0 -ffunction-sections -Wall -fstack-usage -MMD -MP -MF"FT800/FT800_SD.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

