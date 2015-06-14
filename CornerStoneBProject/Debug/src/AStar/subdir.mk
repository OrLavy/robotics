################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/AStar/AStarSearcher.cpp \
../src/AStar/MapGraphObject.cpp \
../src/AStar/MatrixHolder.cpp 

OBJS += \
./src/AStar/AStarSearcher.o \
./src/AStar/MapGraphObject.o \
./src/AStar/MatrixHolder.o 

CPP_DEPS += \
./src/AStar/AStarSearcher.d \
./src/AStar/MapGraphObject.d \
./src/AStar/MatrixHolder.d 


# Each subdirectory must supply rules for building sources it contributes
src/AStar/%.o: ../src/AStar/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -D__cplusplus=201103L -I/usr/local/include/player-2.0 -I"/home/colman/git/robotics/CornerStoneBProject/src" -O0 -g3 -Wall -c -fmessage-length=0  -std=c++11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


