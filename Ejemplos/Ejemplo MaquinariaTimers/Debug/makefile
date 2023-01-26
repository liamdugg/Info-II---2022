################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include src/primitivas/subdir.mk
-include src/drivers/subdir.mk
-include src/app/subdir.mk
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
all: SemaforoMaquinaria.axf

# Tool invocations
SemaforoMaquinaria.axf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: MCU Linker'
	arm-none-eabi-gcc -nostdlib -Xlinker -Map="SemaforoMaquinaria.map" -Xlinker --cref -Xlinker --gc-sections -Xlinker -print-memory-usage -mcpu=cortex-m0 -mthumb -T "UtilitariasGPIO2SinTrabaMaqTimers_Debug.ld" -o "SemaforoMaquinaria.axf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '
	$(MAKE) --no-print-directory post-build

# Other Targets
clean:
	-$(RM) $(EXECUTABLES)$(OBJS)$(C_DEPS) SemaforoMaquinaria.axf
	-@echo ' '

post-build:
	-@echo 'Performing post-build steps'
	-arm-none-eabi-size "SemaforoMaquinaria.axf"; # arm-none-eabi-objcopy -v -O binary "SemaforoMaquinaria.axf" "SemaforoMaquinaria.bin" ; # checksum -p LPC845 -d "SemaforoMaquinaria.bin";
	-@echo ' '

.PHONY: all clean dependents post-build

-include ../makefile.targets
