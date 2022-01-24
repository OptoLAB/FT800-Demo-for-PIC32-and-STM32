################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include Startup/subdir.mk
-include Src/subdir.mk
-include SD/subdir.mk
-include Middlewares/Third_Party/FatFs/src/option/subdir.mk
-include Middlewares/Third_Party/FatFs/src/subdir.mk
-include FT800/subdir.mk
-include Drivers/STM32F0xx_HAL_Driver/Src/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
FT800_MINI_M0.elf \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
FT800_MINI_M0.list \

OBJCOPY_HEX += \
FT800_MINI_M0.hex \


# All Target
all: FT800_MINI_M0.elf secondary-outputs

# Tool invocations
FT800_MINI_M0.elf: $(OBJS) $(USER_OBJS) C:\Users\Jovan\Desktop\FT800\ MINI\ STM32M0\FT800_MINI_M0\STM32F051R8TX_FLASH.ld
	arm-none-eabi-gcc -o "FT800_MINI_M0.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m0 -T"C:\Users\Jovan\Desktop\FT800 MINI STM32M0\FT800_MINI_M0\STM32F051R8TX_FLASH.ld" --specs=nosys.specs -Wl,-Map="FT800_MINI_M0.map" -Wl,--gc-sections -static --specs=nano.specs -mfloat-abi=soft -mthumb -Wl,--start-group -lc -lm -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

FT800_MINI_M0.list: $(EXECUTABLES)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "FT800_MINI_M0.list"
	@echo 'Finished building: $@'
	@echo ' '

FT800_MINI_M0.hex: $(EXECUTABLES)
	arm-none-eabi-objcopy  -O ihex $(EXECUTABLES) "FT800_MINI_M0.hex"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) *
	-@echo ' '

secondary-outputs: $(SIZE_OUTPUT) $(OBJDUMP_LIST) $(OBJCOPY_HEX)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
