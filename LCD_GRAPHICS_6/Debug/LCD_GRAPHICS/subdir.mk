################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../LCD_GRAPHICS/LCD_GRAPHICS.c 

C_DEPS += \
./LCD_GRAPHICS/LCD_GRAPHICS.d 

OBJS += \
./LCD_GRAPHICS/LCD_GRAPHICS.o 


# Each subdirectory must supply rules for building sources it contributes
LCD_GRAPHICS/%.o: ../LCD_GRAPHICS/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM C Compiler 5'
	armcc --cpu=Cortex-A9.no_neon --apcs=/hardfp --arm -O0 -g --md --depend_format=unix_escaped --no_depend_system_headers --depend_dir="LCD_GRAPHICS" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


