################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/ConfigurationsManager.cpp \
../src/CornerStoneBProject.cpp \
../src/Map.cpp \
../src/PathFinder.cpp \
../src/PathPlanner.cpp 

C_SRCS += \
../src/Globals.c 

OBJS += \
./src/ConfigurationsManager.o \
./src/CornerStoneBProject.o \
./src/Globals.o \
./src/Map.o \
./src/PathFinder.o \
./src/PathPlanner.o 

C_DEPS += \
./src/Globals.d 

CPP_DEPS += \
./src/ConfigurationsManager.d \
./src/CornerStoneBProject.d \
./src/Map.d \
./src/PathFinder.d \
./src/PathPlanner.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	gcc -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


