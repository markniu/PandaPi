################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../system/src/system/_exit.c \
../system/src/system/_sbrk.c \
../system/src/system/_startup.c \
../system/src/system/_syscalls.c \
../system/src/system/assert.c \
../system/src/system/system_stm32f10x.c \
../system/src/system/vectors_stm32f10x.c 

CPP_SRCS += \
../system/src/system/_cxx.cpp 

OBJS += \
./system/src/system/_cxx.o \
./system/src/system/_exit.o \
./system/src/system/_sbrk.o \
./system/src/system/_startup.o \
./system/src/system/_syscalls.o \
./system/src/system/assert.o \
./system/src/system/system_stm32f10x.o \
./system/src/system/vectors_stm32f10x.o 

C_DEPS += \
./system/src/system/_exit.d \
./system/src/system/_sbrk.d \
./system/src/system/_startup.d \
./system/src/system/_syscalls.d \
./system/src/system/assert.d \
./system/src/system/system_stm32f10x.d \
./system/src/system/vectors_stm32f10x.d 

CPP_DEPS += \
./system/src/system/_cxx.d 


# Each subdirectory must supply rules for building sources it contributes
system/src/system/%.o: ../system/src/system/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM Cross C++ Compiler'
	arm-none-eabi-g++ -mcpu=cortex-m3 -mthumb -Og -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -ffreestanding -fno-move-loop-invariants -Wall -Wextra  -g3 -DDEBUG -DUSE_FULL_ASSERT -DSTM32F10X_MD -DUSE_STDPERIPH_DRIVER -DHSE_VALUE=8000000 -I"../system" -I"../system/system" -I"../system/system/system" -I"../system/system/stm32f1-stdperiph" -std=gnu++11 -fabi-version=0 -fno-exceptions -fno-rtti -fno-use-cxa-atexit -fno-threadsafe-statics -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

system/src/system/%.o: ../system/src/system/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM Cross C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -Og -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -ffreestanding -fno-move-loop-invariants -Wall -Wextra  -g3 -DDEBUG -DUSE_FULL_ASSERT -DSTM32F10X_MD -DUSE_STDPERIPH_DRIVER -DHSE_VALUE=8000000 -I"../system" -I"../system/system" -I"../system/system/system" -I"../system/system/stm32f1-stdperiph" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


