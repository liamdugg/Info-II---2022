################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/Fun_GPIO.c \
../Drivers/adc.c \
../Drivers/swm.c \
../Drivers/uart.c 

C_DEPS += \
./Drivers/Fun_GPIO.d \
./Drivers/adc.d \
./Drivers/swm.d \
./Drivers/uart.d 

OBJS += \
./Drivers/Fun_GPIO.o \
./Drivers/adc.o \
./Drivers/swm.o \
./Drivers/uart.o 


# Each subdirectory must supply rules for building sources it contributes
Drivers/%.o: ../Drivers/%.c Drivers/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DDEBUG -D__CODE_RED -DCORE_M0PLUS -D__MTB_BUFFER_SIZE=256 -D__USE_ROMDIVIDE -D__LPC84X__ -D__REDLIB__ -I"C:\Users\Nahuel\OneDrive - UTN.BA\2022\finales\info2\Info-II---2022\Ejemplos\RESUELTOS integradores\LectorPasaporte\inc" -O0 -fno-common -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -fmerge-constants -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m0 -mthumb -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-Drivers

clean-Drivers:
	-$(RM) ./Drivers/Fun_GPIO.d ./Drivers/Fun_GPIO.o ./Drivers/adc.d ./Drivers/adc.o ./Drivers/swm.d ./Drivers/swm.o ./Drivers/uart.d ./Drivers/uart.o

.PHONY: clean-Drivers

