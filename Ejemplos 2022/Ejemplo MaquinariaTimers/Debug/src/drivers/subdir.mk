################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
S_SRCS += \
../src/drivers/aeabi_romdiv_patch.s 

C_SRCS += \
../src/drivers/cr_startup_lpc84x.c \
../src/drivers/crp.c \
../src/drivers/gpio.c \
../src/drivers/inializacion.c \
../src/drivers/mtb.c \
../src/drivers/timer.c \
../src/drivers/timer_handlers.c 

OBJS += \
./src/drivers/aeabi_romdiv_patch.o \
./src/drivers/cr_startup_lpc84x.o \
./src/drivers/crp.o \
./src/drivers/gpio.o \
./src/drivers/inializacion.o \
./src/drivers/mtb.o \
./src/drivers/timer.o \
./src/drivers/timer_handlers.o 

C_DEPS += \
./src/drivers/cr_startup_lpc84x.d \
./src/drivers/crp.d \
./src/drivers/gpio.d \
./src/drivers/inializacion.d \
./src/drivers/mtb.d \
./src/drivers/timer.d \
./src/drivers/timer_handlers.d 


# Each subdirectory must supply rules for building sources it contributes
src/drivers/%.o: ../src/drivers/%.s
	@echo 'Building file: $<'
	@echo 'Invoking: MCU Assembler'
	arm-none-eabi-gcc -c -x assembler-with-cpp -DDEBUG -D__CODE_RED -DCORE_M0PLUS -D__USE_ROMDIVIDE -D__LPC84X__ -D__REDLIB__ -I"C:\Users\Federico\Documents\MCUXpressoIDE_11.3.0_5222\workspace\SemaforoMaquinaria\inc" -g3 -mcpu=cortex-m0 -mthumb -specs=redlib.specs -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/drivers/%.o: ../src/drivers/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DDEBUG -D__CODE_RED -DCORE_M0PLUS -D__MTB_BUFFER_SIZE=256 -D__USE_ROMDIVIDE -D__LPC84X__ -D__REDLIB__ -I"C:\Users\Federico\Documents\MCUXpressoIDE_11.3.0_5222\workspace\SemaforoMaquinaria\inc" -O0 -fno-common -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -fmerge-constants -fmacro-prefix-map="../$(@D)/"=. -mcpu=cortex-m0 -mthumb -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


