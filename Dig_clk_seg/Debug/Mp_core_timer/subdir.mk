################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Mp_core_timer/Mp_core_timer.c 

C_DEPS += \
./Mp_core_timer/Mp_core_timer.d 

OBJS += \
./Mp_core_timer/Mp_core_timer.o 


# Each subdirectory must supply rules for building sources it contributes
Mp_core_timer/%.o: ../Mp_core_timer/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM C Compiler 5'
	armcc --cpu=Cortex-A9.no_neon.no_vfp --arm -O0 -g --md --depend_format=unix_escaped --no_depend_system_headers --depend_dir="Mp_core_timer" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


