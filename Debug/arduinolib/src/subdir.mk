################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../arduinolib/src/Dhcp.cpp \
../arduinolib/src/Dns.cpp \
../arduinolib/src/EEPROM.cpp \
../arduinolib/src/Ethernet.cpp \
../arduinolib/src/EthernetClient.cpp \
../arduinolib/src/EthernetServer.cpp \
../arduinolib/src/EthernetUdp.cpp \
../arduinolib/src/File.cpp \
../arduinolib/src/Firmata.cpp \
../arduinolib/src/LiquidCrystal.cpp \
../arduinolib/src/SD.cpp \
../arduinolib/src/SPI.cpp \
../arduinolib/src/Sd2Card.cpp \
../arduinolib/src/SdFile.cpp \
../arduinolib/src/SdVolume.cpp \
../arduinolib/src/Servo.cpp \
../arduinolib/src/SoftwareSerial.cpp \
../arduinolib/src/Stepper.cpp \
../arduinolib/src/Wire.cpp \
../arduinolib/src/socket.cpp \
../arduinolib/src/w5100.cpp 

C_SRCS += \
../arduinolib/src/twi.c 

OBJS += \
./arduinolib/src/Dhcp.o \
./arduinolib/src/Dns.o \
./arduinolib/src/EEPROM.o \
./arduinolib/src/Ethernet.o \
./arduinolib/src/EthernetClient.o \
./arduinolib/src/EthernetServer.o \
./arduinolib/src/EthernetUdp.o \
./arduinolib/src/File.o \
./arduinolib/src/Firmata.o \
./arduinolib/src/LiquidCrystal.o \
./arduinolib/src/SD.o \
./arduinolib/src/SPI.o \
./arduinolib/src/Sd2Card.o \
./arduinolib/src/SdFile.o \
./arduinolib/src/SdVolume.o \
./arduinolib/src/Servo.o \
./arduinolib/src/SoftwareSerial.o \
./arduinolib/src/Stepper.o \
./arduinolib/src/Wire.o \
./arduinolib/src/socket.o \
./arduinolib/src/twi.o \
./arduinolib/src/w5100.o 

C_DEPS += \
./arduinolib/src/twi.d 

CPP_DEPS += \
./arduinolib/src/Dhcp.d \
./arduinolib/src/Dns.d \
./arduinolib/src/EEPROM.d \
./arduinolib/src/Ethernet.d \
./arduinolib/src/EthernetClient.d \
./arduinolib/src/EthernetServer.d \
./arduinolib/src/EthernetUdp.d \
./arduinolib/src/File.d \
./arduinolib/src/Firmata.d \
./arduinolib/src/LiquidCrystal.d \
./arduinolib/src/SD.d \
./arduinolib/src/SPI.d \
./arduinolib/src/Sd2Card.d \
./arduinolib/src/SdFile.d \
./arduinolib/src/SdVolume.d \
./arduinolib/src/Servo.d \
./arduinolib/src/SoftwareSerial.d \
./arduinolib/src/Stepper.d \
./arduinolib/src/Wire.d \
./arduinolib/src/socket.d \
./arduinolib/src/w5100.d 


# Each subdirectory must supply rules for building sources it contributes
arduinolib/src/%.o: ../arduinolib/src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: AVR C++ Compiler'
	avr-g++ -I"/Users/frehnerp/Documents/eclipse/ws/Arduino/ArduinoCore/source/inc" -I"/Users/frehnerp/Documents/eclipse/ws/Arduino/ArduinoCore/source/src" -I"/Users/frehnerp/Documents/eclipse/ws/Arduino/MegaPS3/arduinolib/inc" -I"/Users/frehnerp/Documents/eclipse/ws/Arduino/MegaPS3/arduinolib/src" -I"/Users/frehnerp/Documents/eclipse/ws/Arduino/MegaPS3/redfly/inc" -I"/Users/frehnerp/Documents/eclipse/ws/Arduino/MegaPS3/redfly/src" -I"/Users/frehnerp/Documents/eclipse/ws/Arduino/MegaPS3/main/inc" -I"/Users/frehnerp/Documents/eclipse/ws/Arduino/MegaPS3/main/src" -D__AVR_ATmega2560__ -DARDUINO=100 -U__AVR_ATmega328P__ -Wall -g2 -gstabs -Os -ffunction-sections -fdata-sections -fno-exceptions -mmcu=atmega2560 -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -c -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

arduinolib/src/%.o: ../arduinolib/src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -I"/Users/frehnerp/Documents/eclipse/ws/Arduino/ArduinoCore/source/inc" -I"/Users/frehnerp/Documents/eclipse/ws/Arduino/ArduinoCore/source/src" -I"/Users/frehnerp/Documents/eclipse/ws/Arduino/MegaPS3/arduinolib/inc" -I"/Users/frehnerp/Documents/eclipse/ws/Arduino/MegaPS3/arduinolib/src" -I"/Users/frehnerp/Documents/eclipse/ws/Arduino/MegaPS3/redfly/inc" -I"/Users/frehnerp/Documents/eclipse/ws/Arduino/MegaPS3/redfly/src" -I"/Users/frehnerp/Documents/eclipse/ws/Arduino/MegaPS3/main/inc" -I"/Users/frehnerp/Documents/eclipse/ws/Arduino/MegaPS3/main/src" -D__AVR_ATmega2560__ -DARDUINO=100 -U__AVR_ATmega328P__ -Wall -g2 -gstabs -Os -ffunction-sections -fdata-sections -std=gnu99 -mmcu=atmega2560 -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -c -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


