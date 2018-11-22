################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/impl/SqlSecurityManager.cpp 

OBJS += \
./src/impl/SqlSecurityManager.o 

CPP_DEPS += \
./src/impl/SqlSecurityManager.d 


# Each subdirectory must supply rules for building sources it contributes
src/impl/%.o: ../src/impl/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -ftest-coverage -fprofile-arcs -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


