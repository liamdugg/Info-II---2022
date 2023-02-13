################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/AP_FuncionesMDE.c \
../src/AP_Inicializacion.c \
../src/AP_MDE.c \
../src/LectorPasaporte.c \
../src/cr_startup_lpc84x.c \
../src/crp.c \
../src/mtb.c 

S_SRCS += \
../src/aeabi_romdiv_patch.s 

C_DEPS += \
./src/AP_FuncionesMDE.d \
./src/AP_Inicializacion.d \
./src/AP_MDE.d \
./src/LectorPasaporte.d \
./src/cr_startup_lpc84x.d \
./src/crp.d \
./src/mtb.d 

OBJS += \
./src/AP_FuncionesMDE.o \
./src/AP_Inicializacion.o \
./src/AP_MDE.o \
./src/LectorPasaporte.o \
./src/aeabi_romdiv_patch.o \
./src/cr_startup_lpc84x.o \
./src/crp.o \
./src/mtb.o 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c src/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DDEBUG -D__CODE_RED -DCORE_M0PLUS -D__MTB_BUFFER_SIZE=256 -D__USE_ROMDIVIDE -D__LPC84X__ -D__REDLIB__ -I"C:\Users\Nahuel\OneDrive - UTN.BA\2022\finales\info2\Info-II---2022\Ejemplos\RESUELTOS integradores\LectorPasaporte\inc" -O0 -fno-common -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -fmerge-constants -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m0 -mthumb -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/%.o: ../src/%.s src/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU Assembler'
	arm-none-eabi-gcc -c -x assembler-with-cpp -DDEBUG -D__CODE_RED -DCORE_M0PLUS -D__USE_ROMDIVIDE -D__LPC84X__ -D__REDLIB__ -g3 -mcpu=cortex-m0 -mthumb -specs=redlib.specs -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-src

clean-src:
	-$(RM) ./src/AP_FuncionesMDE.d ./src/AP_FuncionesMDE.o ./src/AP_Inicializacion.d ./src/AP_Inicializacion.o ./src/AP_MDE.d ./src/AP_MDE.o ./src/LectorPasaporte.d ./src/LectorPasaporte.o ./src/aeabi_romdiv_patch.o ./src/cr_startup_lpc84x.d ./src/cr_startup_lpc84x.o ./src/crp.d ./src/crp.o ./src/mtb.d ./src/mtb.o

.PHONY: clean-src

