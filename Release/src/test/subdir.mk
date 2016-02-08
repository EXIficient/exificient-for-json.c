################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/test/main.c \
../src/test/main_codec.c \
../src/test/main_json_encode.c 

OBJS += \
./src/test/main.o \
./src/test/main_codec.o \
./src/test/main_json_encode.o 

C_DEPS += \
./src/test/main.d \
./src/test/main_codec.d \
./src/test/main_json_encode.d 


# Each subdirectory must supply rules for building sources it contributes
src/test/%.o: ../src/test/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -I"../src/codec" -I"../src/test" -I"../src/json" -Os -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


