################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
O_SRCS += \
../src/actions/QCADesigner-array.o \
../src/actions/QCADesigner-pan.o \
../src/actions/QCADesigner-rotate.o \
../src/actions/QCADesigner-select.o 

C_SRCS += \
../src/actions/array.c \
../src/actions/pan.c \
../src/actions/rotate.c \
../src/actions/select.c 

OBJS += \
./src/actions/array.o \
./src/actions/pan.o \
./src/actions/rotate.o \
./src/actions/select.o 

C_DEPS += \
./src/actions/array.d \
./src/actions/pan.d \
./src/actions/rotate.d \
./src/actions/select.d 


# Each subdirectory must supply rules for building sources it contributes
src/actions/%.o: ../src/actions/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O2 -g -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


