################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/codec/BitInputStream.c \
../src/codec/BitOutputStream.c \
../src/codec/DecoderChannel.c \
../src/codec/DynamicMemory.c \
../src/codec/EXIHeaderDecoder.c \
../src/codec/EXIHeaderEncoder.c \
../src/codec/EXIforJSONEXICoder.c \
../src/codec/EXIforJSONEXIDecoder.c \
../src/codec/EXIforJSONEXIEncoder.c \
../src/codec/EXIforJSONQNames.c \
../src/codec/EncoderChannel.c \
../src/codec/MethodsBag.c \
../src/codec/StringNameTable.c \
../src/codec/StringValueTable.c 

OBJS += \
./src/codec/BitInputStream.o \
./src/codec/BitOutputStream.o \
./src/codec/DecoderChannel.o \
./src/codec/DynamicMemory.o \
./src/codec/EXIHeaderDecoder.o \
./src/codec/EXIHeaderEncoder.o \
./src/codec/EXIforJSONEXICoder.o \
./src/codec/EXIforJSONEXIDecoder.o \
./src/codec/EXIforJSONEXIEncoder.o \
./src/codec/EXIforJSONQNames.o \
./src/codec/EncoderChannel.o \
./src/codec/MethodsBag.o \
./src/codec/StringNameTable.o \
./src/codec/StringValueTable.o 

C_DEPS += \
./src/codec/BitInputStream.d \
./src/codec/BitOutputStream.d \
./src/codec/DecoderChannel.d \
./src/codec/DynamicMemory.d \
./src/codec/EXIHeaderDecoder.d \
./src/codec/EXIHeaderEncoder.d \
./src/codec/EXIforJSONEXICoder.d \
./src/codec/EXIforJSONEXIDecoder.d \
./src/codec/EXIforJSONEXIEncoder.d \
./src/codec/EXIforJSONQNames.d \
./src/codec/EncoderChannel.d \
./src/codec/MethodsBag.d \
./src/codec/StringNameTable.d \
./src/codec/StringValueTable.d 


# Each subdirectory must supply rules for building sources it contributes
src/codec/%.o: ../src/codec/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -I"../src/codec" -I"../src/test" -I"../src/json" -I"../src/exiforjson" -O0 -g3 -Wall -c -fmessage-length=0 -ansi -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


