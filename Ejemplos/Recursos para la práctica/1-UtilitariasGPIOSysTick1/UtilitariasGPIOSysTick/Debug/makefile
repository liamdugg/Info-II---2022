################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include src/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: UtilitariasGPIOSysTick.axf

# Tool invocations
UtilitariasGPIOSysTick.axf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: MCU Linker'
	arm-none-eabi-gcc -nostdlib -Xlinker -Map="UtilitariasGPIOSysTick.map" -Xlinker --cref -Xlinker --gc-sections -Xlinker -print-memory-usage -mcpu=cortex-m0 -mthumb -T "UtilitariasGPIOSysTick_Debug.ld" -o "UtilitariasGPIOSysTick.axf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '
	$(MAKE) --no-print-directory post-build

# Other Targets
clean:
	-$(RM) $(EXECUTABLES)$(OBJS)$(C_DEPS) UtilitariasGPIOSysTick.axf
	-@echo ' '

post-build:
	-@echo 'Performing post-build steps'
	-arm-none-eabi-size "UtilitariasGPIOSysTick.axf"; # arm-none-eabi-objcopy -v -O binary "UtilitariasGPIOSysTick.axf" "UtilitariasGPIOSysTick.bin" ; # checksum -p LPC845 -d "UtilitariasGPIOSysTick.bin";
	-@echo ' '

.PHONY: all clean dependents post-build

-include ../makefile.targets
