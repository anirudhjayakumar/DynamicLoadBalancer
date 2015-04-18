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
../DynLB_constants.cpp \
../DynLB_types.cpp \
../MultiplicationService.cpp \
../MultiplicationService_server.skeleton.cpp \
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
./DynLB_constants.o \
./DynLB_types.o \
./MultiplicationService.o \
./MultiplicationService_server.skeleton.o \
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
./DynLB_constants.d \
./DynLB_types.d \
./MultiplicationService.d \
./MultiplicationService_server.skeleton.d \
./main.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -std=c++11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


