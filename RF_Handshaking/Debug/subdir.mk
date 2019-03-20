################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../LoRa.c \
../main.c \
../ssp.c 

OBJS += \
./LoRa.o \
./main.o \
./ssp.o 

C_DEPS += \
./LoRa.d \
./main.d \
./ssp.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DDEBUG -D__USE_CMSIS=CMSIS_CORE_LPC17xx -D__CODE_RED -D__REDLIB__ -I"C:\Users\tarun\Desktop\New folder\1\CMSIS_CORE_LPC17xx\inc" -I"C:\Users\tarun\Documents\MCUXpressoIDE_10.2.1_795\myworkspace2\RF_Handshaking\include" -I"C:\Users\tarun\Documents\MCUXpressoIDE_10.2.1_795\myworkspace2\FreeRTOS_Library\include" -I"C:\Users\tarun\Documents\MCUXpressoIDE_10.2.1_795\myworkspace2\FreeRTOS_Library\portable" -O0 -g3 -fsigned-char -c -fmessage-length=0 -fno-builtin -ffunction-sections -mcpu=cortex-m3 -mthumb -D__REDLIB__ -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


