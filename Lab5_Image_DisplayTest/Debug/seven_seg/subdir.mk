################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../seven_seg/seven_seg.c 

C_DEPS += \
./seven_seg/seven_seg.d 

OBJS += \
./seven_seg/seven_seg.o 


# Each subdirectory must supply rules for building sources it contributes
seven_seg/%.o: ../seven_seg/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM C Compiler 5'
	armcc -O0 -g --md --depend_format=unix_escaped --no_depend_system_headers --depend_dir="seven_seg" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


