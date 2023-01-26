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
all: UtilitariasGPIO2SinTrabaMaqTimers.axf

# Tool invocations
UtilitariasGPIO2SinTrabaMaqTimers.axf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: MCU Linker'
	arm-none-eabi-gcc -nostdlib -Xlinker -Map="UtilitariasGPIO2SinTrabaMaqTimers.map" -Xlinker --cref -Xlinker --gc-sections -Xlinker -print-memory-usage -mcpu=cortex-m0 -mthumb -T "UtilitariasGPIO2SinTrabaMaqTimers_Debug.ld" -o "UtilitariasGPIO2SinTrabaMaqTimers.axf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '
	$(MAKE) --no-print-directory post-build

# Other Targets
clean:
	-$(RM) $(EXECUTABLES)$(OBJS)$(C_DEPS) UtilitariasGPIO2SinTrabaMaqTimers.axf
	-@echo ' '

post-build:
	-@echo 'Performing post-build steps'
	-arm-none-eabi-size "UtilitariasGPIO2SinTrabaMaqTimers.axf"; # arm-none-eabi-objcopy -v -O binary "UtilitariasGPIO2SinTrabaMaqTimers.axf" "UtilitariasGPIO2SinTrabaMaqTimers.bin" ; # checksum -p LPC845 -d "UtilitariasGPIO2SinTrabaMaqTimers.bin";
	-@echo ' '

.PHONY: all clean dependents post-build

-include ../makefile.targets
