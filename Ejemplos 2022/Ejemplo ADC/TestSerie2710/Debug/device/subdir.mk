################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../device/system_LPC845.c 

OBJS += \
./device/system_LPC845.o 

C_DEPS += \
./device/system_LPC845.d 


# Each subdirectory must supply rules for building sources it contributes
device/%.o: ../device/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__REDLIB__ -DCPU_LPC845M301JBD48 -DCPU_LPC845M301JBD48_cm0plus -DFSL_RTOS_BM -DSDK_OS_BAREMETAL -DSDK_DEBUGCONSOLE=1 -DCR_INTEGER_PRINTF -DPRINTF_FLOAT_ENABLE=0 -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -I"C:\DOCS\info2\nuevoWorkspace\TestSerie2710\drivers" -I"C:\DOCS\info2\nuevoWorkspace\TestSerie2710\component\uart" -I"C:\DOCS\info2\nuevoWorkspace\TestSerie2710\utilities" -I"C:\DOCS\info2\nuevoWorkspace\TestSerie2710\CMSIS" -I"C:\DOCS\info2\nuevoWorkspace\TestSerie2710\device" -I"C:\DOCS\info2\nuevoWorkspace\TestSerie2710\board" -I"C:\DOCS\info2\nuevoWorkspace\TestSerie2710\source" -I"C:\DOCS\info2\nuevoWorkspace\TestSerie2710\drivers" -I"C:\DOCS\info2\nuevoWorkspace\TestSerie2710\component\uart" -I"C:\DOCS\info2\nuevoWorkspace\TestSerie2710\utilities" -I"C:\DOCS\info2\nuevoWorkspace\TestSerie2710\CMSIS" -I"C:\DOCS\info2\nuevoWorkspace\TestSerie2710\device" -O0 -fno-common -g3 -Wall -c -ffunction-sections -fdata-sections -ffreestanding -fno-builtin -fmerge-constants -fmacro-prefix-map="../$(@D)/"=. -mcpu=cortex-m0plus -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


