################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/PngUtils/PngUtil.cpp \
../src/PngUtils/lodepng.cpp 

OBJS += \
./src/PngUtils/PngUtil.o \
./src/PngUtils/lodepng.o 

CPP_DEPS += \
./src/PngUtils/PngUtil.d \
./src/PngUtils/lodepng.d 


# Each subdirectory must supply rules for building sources it contributes
src/PngUtils/%.o: ../src/PngUtils/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


