################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
S_SRCS += \
../ACC_Project/Core/Startup/startup_stm32f407vetx.s 

OBJS += \
./ACC_Project/Core/Startup/startup_stm32f407vetx.o 

S_DEPS += \
./ACC_Project/Core/Startup/startup_stm32f407vetx.d 


# Each subdirectory must supply rules for building sources it contributes
ACC_Project/Core/Startup/%.o: ../ACC_Project/Core/Startup/%.s ACC_Project/Core/Startup/subdir.mk
	arm-none-eabi-gcc -mcpu=cortex-m4 -g3 -DDEBUG -c -x assembler-with-cpp -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@" "$<"

clean: clean-ACC_Project-2f-Core-2f-Startup

clean-ACC_Project-2f-Core-2f-Startup:
	-$(RM) ./ACC_Project/Core/Startup/startup_stm32f407vetx.d ./ACC_Project/Core/Startup/startup_stm32f407vetx.o

.PHONY: clean-ACC_Project-2f-Core-2f-Startup

