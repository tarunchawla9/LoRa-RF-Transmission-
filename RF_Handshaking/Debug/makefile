################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
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
all: SimpleDemo.axf

# Tool invocations
SimpleDemo.axf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: MCU Linker'
	arm-none-eabi-gcc -nostdlib -L"C:\Users\tarun\Documents\MCUXpressoIDE_10.2.1_795\myworkspace2\FreeRTOS_Library\Debug" -L"C:\Users\tarun\Desktop\New folder\1\CMSIS_CORE_LPC17xx\Debug" -Xlinker --gc-sections -Xlinker -Map=SimpleDemo.map -mcpu=cortex-m3 -mthumb -T "Example16_Debug.ld" -o "SimpleDemo.axf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '
	$(MAKE) --no-print-directory post-build

# Other Targets
clean:
	-$(RM) $(EXECUTABLES)$(OBJS)$(C_DEPS) SimpleDemo.axf
	-@echo ' '

post-build:
	-@echo 'Performing post-build steps'
	-arm-none-eabi-size SimpleDemo.axf ; arm-none-eabi-objcopy -O ihex SimpleDemo.axf SimpleDemo.hex
	-@echo ' '

.PHONY: all clean dependents post-build

-include ../makefile.targets
