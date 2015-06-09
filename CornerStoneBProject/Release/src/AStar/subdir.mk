################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/AStar/AStarSearcher.cpp \
../src/AStar/MapGraphObject.cpp 

OBJS += \
./src/AStar/AStarSearcher.o \
./src/AStar/MapGraphObject.o 

CPP_DEPS += \
./src/AStar/AStarSearcher.d \
./src/AStar/MapGraphObject.d 


# Each subdirectory must supply rules for building sources it contributes
src/AStar/%.o: ../src/AStar/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


