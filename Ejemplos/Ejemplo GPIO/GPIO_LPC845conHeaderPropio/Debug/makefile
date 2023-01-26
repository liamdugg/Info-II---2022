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
all: GPIO_LPC845conHeaderPropio.axf

# Tool invocations
GPIO_LPC845conHeaderPropio.axf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: MCU Linker'
	arm-none-eabi-gcc -nostdlib -Xlinker -Map="GPIO_LPC845conHeaderPropio.map" -Xlinker --cref -Xlinker --gc-sections -Xlinker -print-memory-usage -mcpu=cortex-m0 -mthumb -T "pruebaLPC845TotalmentePelado_Debug.ld" -o "GPIO_LPC845conHeaderPropio.axf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '
	$(MAKE) --no-print-directory post-build

# Other Targets
clean:
	-$(RM) $(EXECUTABLES)$(OBJS)$(C_DEPS) GPIO_LPC845conHeaderPropio.axf
	-@echo ' '

post-build:
	-@echo 'Performing post-build steps'
	-arm-none-eabi-size "GPIO_LPC845conHeaderPropio.axf"; # arm-none-eabi-objcopy -v -O binary "GPIO_LPC845conHeaderPropio.axf" "GPIO_LPC845conHeaderPropio.bin" ; # checksum -p LPC845 -d "GPIO_LPC845conHeaderPropio.bin";
	-@echo ' '

.PHONY: all clean dependents post-build

-include ../makefile.targets
