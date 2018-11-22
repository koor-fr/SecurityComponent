################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/api/Role.cpp \
../src/api/User.cpp 

OBJS += \
./src/api/Role.o \
./src/api/User.o 

CPP_DEPS += \
./src/api/Role.d \
./src/api/User.d 


# Each subdirectory must supply rules for building sources it contributes
src/api/%.o: ../src/api/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -ftest-coverage -fprofile-arcs -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


