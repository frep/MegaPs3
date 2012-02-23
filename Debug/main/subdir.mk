################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../main/scretch.cpp 

OBJS += \
./main/scretch.o 

CPP_DEPS += \
./main/scretch.d 


# Each subdirectory must supply rules for building sources it contributes
main/%.o: ../main/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: AVR C++ Compiler'
	avr-g++ -I"/Users/frehnerp/Documents/eclipse/ws/Arduino/ArduinoCore/source/inc" -I"/Users/frehnerp/Documents/eclipse/ws/Arduino/ArduinoCore/source/src" -I"/Users/frehnerp/Documents/eclipse/ws/Arduino/ArduinoBase/arduinolib/inc" -I"/Users/frehnerp/Documents/eclipse/ws/Arduino/ArduinoBase/arduinolib/src" -I"/Users/frehnerp/Documents/eclipse/ws/Arduino/ArduinoBase/redfly/inc" -I"/Users/frehnerp/Documents/eclipse/ws/Arduino/ArduinoBase/redfly/src" -D__AVR_ATmega328P__ -DARDUINO=100 -Wall -g2 -gstabs -O0 -ffunction-sections -fdata-sections -fno-exceptions -mmcu=atmega328p -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -c -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


