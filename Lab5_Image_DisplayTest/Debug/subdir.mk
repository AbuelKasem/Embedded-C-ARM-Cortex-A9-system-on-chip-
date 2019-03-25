################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Test.c \
../flowers.c \
../joker.c \
../main.c \
../man.c \
../sea.c 

C_DEPS += \
./Test.d \
./flowers.d \
./joker.d \
./main.d \
./man.d \
./sea.d 

OBJS += \
./Test.o \
./flowers.o \
./joker.o \
./main.o \
./man.o \
./sea.o 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM C Compiler 5'
	armcc -O0 -g --md --depend_format=unix_escaped --no_depend_system_headers -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


