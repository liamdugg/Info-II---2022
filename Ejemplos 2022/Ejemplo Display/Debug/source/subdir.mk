################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../source/LPC845_Display.c \
../source/dr_7seg.c \
../source/dr_gpio.c \
../source/mtb.c \
../source/timer.c 

OBJS += \
./source/LPC845_Display.o \
./source/dr_7seg.o \
./source/dr_gpio.o \
./source/mtb.o \
./source/timer.o 

C_DEPS += \
./source/LPC845_Display.d \
./source/dr_7seg.d \
./source/dr_gpio.d \
./source/mtb.d \
./source/timer.d 


# Each subdirectory must supply rules for building sources it contributes
source/%.o: ../source/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__REDLIB__ -DCPU_LPC845M301JBD48 -DCPU_LPC845M301JBD48_cm0plus -DSDK_OS_BAREMETAL -DSDK_DEBUGCONSOLE=1 -DCR_INTEGER_PRINTF -DPRINTF_FLOAT_ENABLE=0 -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -I"C:\Users\lsuge\Documents\MCUXpressoIDE_11.4.0_6237\workspace\LPC845_Display\board" -I"C:\Users\lsuge\Documents\MCUXpressoIDE_11.4.0_6237\workspace\LPC845_Display\source" -I"C:\Users\lsuge\Documents\MCUXpressoIDE_11.4.0_6237\workspace\LPC845_Display\drivers" -I"C:\Users\lsuge\Documents\MCUXpressoIDE_11.4.0_6237\workspace\LPC845_Display\component\uart" -I"C:\Users\lsuge\Documents\MCUXpressoIDE_11.4.0_6237\workspace\LPC845_Display\utilities" -I"C:\Users\lsuge\Documents\MCUXpressoIDE_11.4.0_6237\workspace\LPC845_Display\CMSIS" -I"C:\Users\lsuge\Documents\MCUXpressoIDE_11.4.0_6237\workspace\LPC845_Display\device" -O0 -fno-common -g3 -Wall -c -ffunction-sections -fdata-sections -ffreestanding -fno-builtin -fmerge-constants -fmacro-prefix-map="../$(@D)/"=. -mcpu=cortex-m0plus -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


