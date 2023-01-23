################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
S_SRCS += \
../src/aeabi_romdiv_patch.s 

C_SRCS += \
../src/cr_startup_lpc84x.c \
../src/crp.c \
../src/gpio.c \
../src/inializacion.c \
../src/main.c \
../src/mtb.c \
../src/timer.c 

OBJS += \
./src/aeabi_romdiv_patch.o \
./src/cr_startup_lpc84x.o \
./src/crp.o \
./src/gpio.o \
./src/inializacion.o \
./src/main.o \
./src/mtb.o \
./src/timer.o 

C_DEPS += \
./src/cr_startup_lpc84x.d \
./src/crp.d \
./src/gpio.d \
./src/inializacion.d \
./src/main.d \
./src/mtb.d \
./src/timer.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.s
	@echo 'Building file: $<'
	@echo 'Invoking: MCU Assembler'
	arm-none-eabi-gcc -c -x assembler-with-cpp -DDEBUG -D__CODE_RED -DCORE_M0PLUS -D__USE_ROMDIVIDE -D__LPC84X__ -D__REDLIB__ -I"C:\Users\socco\Documents\MCUXpressoIDE_11.4.0_6237\workspace\UtilitariasGPIOSysTick2NoTrabado\inc" -g3 -mcpu=cortex-m0 -mthumb -specs=redlib.specs -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DDEBUG -D__CODE_RED -DCORE_M0PLUS -D__MTB_BUFFER_SIZE=256 -D__USE_ROMDIVIDE -D__LPC84X__ -D__REDLIB__ -I"C:\Users\socco\Documents\MCUXpressoIDE_11.4.0_6237\workspace\UtilitariasGPIOSysTick2NoTrabado\inc" -O0 -fno-common -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -fmerge-constants -fmacro-prefix-map="../$(@D)/"=. -mcpu=cortex-m0 -mthumb -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


