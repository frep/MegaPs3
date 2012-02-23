################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../redfly/src/RedFly.cpp \
../redfly/src/RedFlyClient.cpp \
../redfly/src/RedFlyServer.cpp 

OBJS += \
./redfly/src/RedFly.o \
./redfly/src/RedFlyClient.o \
./redfly/src/RedFlyServer.o 

CPP_DEPS += \
./redfly/src/RedFly.d \
./redfly/src/RedFlyClient.d \
./redfly/src/RedFlyServer.d 


# Each subdirectory must supply rules for building sources it contributes
redfly/src/%.o: ../redfly/src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: AVR C++ Compiler'
	avr-g++ -I"/Users/frehnerp/Documents/eclipse/ws/Arduino/ArduinoCore/source/inc" -I"/Users/frehnerp/Documents/eclipse/ws/Arduino/ArduinoCore/source/src" -I"/Users/frehnerp/Documents/eclipse/ws/Arduino/MegaPS3/arduinolib/inc" -I"/Users/frehnerp/Documents/eclipse/ws/Arduino/MegaPS3/arduinolib/src" -I"/Users/frehnerp/Documents/eclipse/ws/Arduino/MegaPS3/redfly/inc" -I"/Users/frehnerp/Documents/eclipse/ws/Arduino/MegaPS3/redfly/src" -I"/Users/frehnerp/Documents/eclipse/ws/Arduino/MegaPS3/main/inc" -I"/Users/frehnerp/Documents/eclipse/ws/Arduino/MegaPS3/main/src" -D__AVR_ATmega2560__ -DARDUINO=100 -U__AVR_ATmega328P__ -Wall -g2 -gstabs -Os -ffunction-sections -fdata-sections -fno-exceptions -mmcu=atmega2560 -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -c -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


