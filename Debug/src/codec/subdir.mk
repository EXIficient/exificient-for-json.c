################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/codec/AbstractDecoderChannel.c \
../src/codec/AbstractEncoderChannel.c \
../src/codec/BitDecoderChannel.c \
../src/codec/BitEncoderChannel.c \
../src/codec/BitInputStream.c \
../src/codec/BitOutputStream.c \
../src/codec/ByteDecoderChannel.c \
../src/codec/ByteEncoderChannel.c \
../src/codec/DynamicMemory.c \
../src/codec/EXIHeaderDecoder.c \
../src/codec/EXIHeaderEncoder.c \
../src/codec/EXIforJSONEXICoder.c \
../src/codec/EXIforJSONEXIDecoder.c \
../src/codec/EXIforJSONEXIEncoder.c \
../src/codec/EXIforJSONNameTableEntries.c \
../src/codec/EXIforJSONQNames.c \
../src/codec/MethodsBag.c \
../src/codec/StringNameTable.c \
../src/codec/StringValueTable.c 

OBJS += \
./src/codec/AbstractDecoderChannel.o \
./src/codec/AbstractEncoderChannel.o \
./src/codec/BitDecoderChannel.o \
./src/codec/BitEncoderChannel.o \
./src/codec/BitInputStream.o \
./src/codec/BitOutputStream.o \
./src/codec/ByteDecoderChannel.o \
./src/codec/ByteEncoderChannel.o \
./src/codec/DynamicMemory.o \
./src/codec/EXIHeaderDecoder.o \
./src/codec/EXIHeaderEncoder.o \
./src/codec/EXIforJSONEXICoder.o \
./src/codec/EXIforJSONEXIDecoder.o \
./src/codec/EXIforJSONEXIEncoder.o \
./src/codec/EXIforJSONNameTableEntries.o \
./src/codec/EXIforJSONQNames.o \
./src/codec/MethodsBag.o \
./src/codec/StringNameTable.o \
./src/codec/StringValueTable.o 

C_DEPS += \
./src/codec/AbstractDecoderChannel.d \
./src/codec/AbstractEncoderChannel.d \
./src/codec/BitDecoderChannel.d \
./src/codec/BitEncoderChannel.d \
./src/codec/BitInputStream.d \
./src/codec/BitOutputStream.d \
./src/codec/ByteDecoderChannel.d \
./src/codec/ByteEncoderChannel.d \
./src/codec/DynamicMemory.d \
./src/codec/EXIHeaderDecoder.d \
./src/codec/EXIHeaderEncoder.d \
./src/codec/EXIforJSONEXICoder.d \
./src/codec/EXIforJSONEXIDecoder.d \
./src/codec/EXIforJSONEXIEncoder.d \
./src/codec/EXIforJSONNameTableEntries.d \
./src/codec/EXIforJSONQNames.d \
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


