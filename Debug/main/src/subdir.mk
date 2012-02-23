################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../main/src/PS3BT.cpp \
../main/src/PS3BTExample.cpp \
../main/src/RCRx.cpp \
../main/src/Timer3.cpp \
../main/src/UdpTerminal.cpp \
../main/src/Usb.cpp \
../main/src/message.cpp 

OBJS += \
./main/src/PS3BT.o \
./main/src/PS3BTExample.o \
./main/src/RCRx.o \
./main/src/Timer3.o \
./main/src/UdpTerminal.o \
./main/src/Usb.o \
./main/src/message.o 

CPP_DEPS += \
./main/src/PS3BT.d \
./main/src/PS3BTExample.d \
./main/src/RCRx.d \
./main/src/Timer3.d \
./main/src/UdpTerminal.d \
./main/src/Usb.d \
./main/src/message.d 


# Each subdirectory must supply rules for building sources it contributes
main/src/%.o: ../main/src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: AVR C++ Compiler'
	avr-g++ -I"/Users/frehnerp/Documents/eclipse/ws/Arduino/ArduinoCore/source/inc" -I"/Users/frehnerp/Documents/eclipse/ws/Arduino/ArduinoCore/source/src" -I"/Users/frehnerp/Documents/eclipse/ws/Arduino/MegaPS3/arduinolib/inc" -I"/Users/frehnerp/Documents/eclipse/ws/Arduino/MegaPS3/arduinolib/src" -I"/Users/frehnerp/Documents/eclipse/ws/Arduino/MegaPS3/redfly/inc" -I"/Users/frehnerp/Documents/eclipse/ws/Arduino/MegaPS3/redfly/src" -I"/Users/frehnerp/Documents/eclipse/ws/Arduino/MegaPS3/main/inc" -I"/Users/frehnerp/Documents/eclipse/ws/Arduino/MegaPS3/main/src" -D__AVR_ATmega2560__ -DARDUINO=100 -U__AVR_ATmega328P__ -Wall -g2 -gstabs -Os -ffunction-sections -fdata-sections -fno-exceptions -mmcu=atmega2560 -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -c -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


