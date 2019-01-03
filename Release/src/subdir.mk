################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/xmagma_backend.cpp 

OBJS += \
./src/xmagma_backend.o 

CPP_DEPS += \
./src/xmagma_backend.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -fPIC -DHAVE_CUBLAS -DADD_ -I"/home/hzhang/Documents/workspace/xmagma/include" -I/usr/local/magma/include -I/usr/local/cuda/include -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


