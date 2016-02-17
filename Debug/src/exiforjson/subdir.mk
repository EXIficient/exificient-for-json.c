################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/exiforjson/EXIforJSONDecoder.c \
../src/exiforjson/EXIforJSONEncoder.c 

OBJS += \
./src/exiforjson/EXIforJSONDecoder.o \
./src/exiforjson/EXIforJSONEncoder.o 

C_DEPS += \
./src/exiforjson/EXIforJSONDecoder.d \
./src/exiforjson/EXIforJSONEncoder.d 


# Each subdirectory must supply rules for building sources it contributes
src/exiforjson/%.o: ../src/exiforjson/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -I"../src/codec" -I"../src/test" -I"../src/json" -I"../src/exiforjson" -O0 -g3 -Wall -c -fmessage-length=0 -ansi -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


