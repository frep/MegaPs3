################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../arduinolib/Dhcp.cpp \
../arduinolib/Dns.cpp \
../arduinolib/EEPROM.cpp \
../arduinolib/Ethernet.cpp \
../arduinolib/EthernetClient.cpp \
../arduinolib/EthernetServer.cpp \
../arduinolib/EthernetUdp.cpp \
../arduinolib/File.cpp \
../arduinolib/Firmata.cpp \
../arduinolib/LiquidCrystal.cpp \
../arduinolib/SD.cpp \
../arduinolib/SPI.cpp \
../arduinolib/Sd2Card.cpp \
../arduinolib/SdFile.cpp \
../arduinolib/SdVolume.cpp \
../arduinolib/Servo.cpp \
../arduinolib/SoftwareSerial.cpp \
../arduinolib/Stepper.cpp \
../arduinolib/Wire.cpp \
../arduinolib/socket.cpp \
../arduinolib/w5100.cpp 

C_SRCS += \
../arduinolib/twi.c 

OBJS += \
./arduinolib/Dhcp.o \
./arduinolib/Dns.o \
./arduinolib/EEPROM.o \
./arduinolib/Ethernet.o \
./arduinolib/EthernetClient.o \
./arduinolib/EthernetServer.o \
./arduinolib/EthernetUdp.o \
./arduinolib/File.o \
./arduinolib/Firmata.o \
./arduinolib/LiquidCrystal.o \
./arduinolib/SD.o \
./arduinolib/SPI.o \
./arduinolib/Sd2Card.o \
./arduinolib/SdFile.o \
./arduinolib/SdVolume.o \
./arduinolib/Servo.o \
./arduinolib/SoftwareSerial.o \
./arduinolib/Stepper.o \
./arduinolib/Wire.o \
./arduinolib/socket.o \
./arduinolib/twi.o \
./arduinolib/w5100.o 

C_DEPS += \
./arduinolib/twi.d 

CPP_DEPS += \
./arduinolib/Dhcp.d \
./arduinolib/Dns.d \
./arduinolib/EEPROM.d \
./arduinolib/Ethernet.d \
./arduinolib/EthernetClient.d \
./arduinolib/EthernetServer.d \
./arduinolib/EthernetUdp.d \
./arduinolib/File.d \
./arduinolib/Firmata.d \
./arduinolib/LiquidCrystal.d \
./arduinolib/SD.d \
./arduinolib/SPI.d \
./arduinolib/Sd2Card.d \
./arduinolib/SdFile.d \
./arduinolib/SdVolume.d \
./arduinolib/Servo.d \
./arduinolib/SoftwareSerial.d \
./arduinolib/Stepper.d \
./arduinolib/Wire.d \
./arduinolib/socket.d \
./arduinolib/w5100.d 


# Each subdirectory must supply rules for building sources it contributes
arduinolib/%.o: ../arduinolib/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: AVR C++ Compiler'
	avr-g++ -I"/Users/frehnerp/Documents/eclipse/ws/Arduino/ArduinoCore/source/inc" -I"/Users/frehnerp/Documents/eclipse/ws/Arduino/ArduinoCore/source/src" -I"/Users/frehnerp/Documents/eclipse/ws/Arduino/ArduinoBase2/arduinolib" -I"/Users/frehnerp/Documents/eclipse/ws/Arduino/ArduinoBase2/lib" -I"/Users/frehnerp/Documents/eclipse/ws/Arduino/ArduinoBase2/src" -Wall -g2 -gstabs -O0 -ffunction-sections -fdata-sections -fno-exceptions -mmcu=atmega328p -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -c -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

arduinolib/%.o: ../arduinolib/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -I"/Users/frehnerp/Documents/eclipse/ws/Arduino/ArduinoCore/source/inc" -I"/Users/frehnerp/Documents/eclipse/ws/Arduino/ArduinoCore/source/src" -I"/Users/frehnerp/Documents/eclipse/ws/Arduino/ArduinoBase2/arduinolib" -I"/Users/frehnerp/Documents/eclipse/ws/Arduino/ArduinoBase2/lib" -I"/Users/frehnerp/Documents/eclipse/ws/Arduino/ArduinoBase2/src" -Wall -g2 -gstabs -Os -ffunction-sections -fdata-sections -std=gnu99 -mmcu=atmega328p -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -c -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


