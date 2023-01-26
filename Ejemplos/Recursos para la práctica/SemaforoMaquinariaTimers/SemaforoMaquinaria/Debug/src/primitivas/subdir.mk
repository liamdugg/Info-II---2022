################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/primitivas/AP_FuncionesMDE.c \
../src/primitivas/AP_Inicializacion.c \
../src/primitivas/AP_MDE.c \
../src/primitivas/botones.c 

OBJS += \
./src/primitivas/AP_FuncionesMDE.o \
./src/primitivas/AP_Inicializacion.o \
./src/primitivas/AP_MDE.o \
./src/primitivas/botones.o 

C_DEPS += \
./src/primitivas/AP_FuncionesMDE.d \
./src/primitivas/AP_Inicializacion.d \
./src/primitivas/AP_MDE.d \
./src/primitivas/botones.d 


# Each subdirectory must supply rules for building sources it contributes
src/primitivas/%.o: ../src/primitivas/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DDEBUG -D__CODE_RED -DCORE_M0PLUS -D__MTB_BUFFER_SIZE=256 -D__USE_ROMDIVIDE -D__LPC84X__ -D__REDLIB__ -I"C:\Users\Federico\Documents\MCUXpressoIDE_11.3.0_5222\workspace\SemaforoMaquinaria\inc" -O0 -fno-common -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -fmerge-constants -fmacro-prefix-map="../$(@D)/"=. -mcpu=cortex-m0 -mthumb -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


