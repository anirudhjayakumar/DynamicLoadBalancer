################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../CAdaptor.cpp \
../CCommProxy.cpp \
../CCommServer.cpp \
../CHWMonitor.cpp \
../CJob.cpp \
../CJobQueue.cpp \
../CStateManager.cpp \
../CTransferManager.cpp \
../CWorker.cpp \
../main.cpp 

OBJS += \
./CAdaptor.o \
./CCommProxy.o \
./CCommServer.o \
./CHWMonitor.o \
./CJob.o \
./CJobQueue.o \
./CStateManager.o \
./CTransferManager.o \
./CWorker.o \
./main.o 

CPP_DEPS += \
./CAdaptor.d \
./CCommProxy.d \
./CCommServer.d \
./CHWMonitor.d \
./CJob.d \
./CJobQueue.d \
./CStateManager.d \
./CTransferManager.d \
./CWorker.d \
./main.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O3 -Wall -c -fmessage-length=0 -std=c++11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


