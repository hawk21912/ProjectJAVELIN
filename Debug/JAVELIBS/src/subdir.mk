################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../JAVELIBS/src/MSGHandler.c \
../JAVELIBS/src/RGB_LED.c \
../JAVELIBS/src/Servo.c \
../JAVELIBS/src/TraxxasESC.c \
../JAVELIBS/src/stepper.c \
../JAVELIBS/src/tcpclient.c \
../JAVELIBS/src/tcpserver.c 

OBJS += \
./JAVELIBS/src/MSGHandler.o \
./JAVELIBS/src/RGB_LED.o \
./JAVELIBS/src/Servo.o \
./JAVELIBS/src/TraxxasESC.o \
./JAVELIBS/src/stepper.o \
./JAVELIBS/src/tcpclient.o \
./JAVELIBS/src/tcpserver.o 

C_DEPS += \
./JAVELIBS/src/MSGHandler.d \
./JAVELIBS/src/RGB_LED.d \
./JAVELIBS/src/Servo.d \
./JAVELIBS/src/TraxxasESC.d \
./JAVELIBS/src/stepper.d \
./JAVELIBS/src/tcpclient.d \
./JAVELIBS/src/tcpserver.d 


# Each subdirectory must supply rules for building sources it contributes
JAVELIBS/src/%.o JAVELIBS/src/%.su: ../JAVELIBS/src/%.c JAVELIBS/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32H743xx -c -I../Core/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../Drivers/CMSIS/Include -I../LWIP/App -I../LWIP/Target -I../Middlewares/Third_Party/LwIP/src/include -I../Middlewares/Third_Party/LwIP/system -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I../Drivers/BSP/Components/lan8742 -I../Middlewares/Third_Party/LwIP/src/include/netif/ppp -I../Middlewares/Third_Party/LwIP/src/include/lwip -I../Middlewares/Third_Party/LwIP/src/include/lwip/apps -I../Middlewares/Third_Party/LwIP/src/include/lwip/priv -I../Middlewares/Third_Party/LwIP/src/include/lwip/prot -I../Middlewares/Third_Party/LwIP/src/include/netif -I../Middlewares/Third_Party/LwIP/src/include/compat/posix -I../Middlewares/Third_Party/LwIP/src/include/compat/posix/arpa -I../Middlewares/Third_Party/LwIP/src/include/compat/posix/net -I../Middlewares/Third_Party/LwIP/src/include/compat/posix/sys -I../Middlewares/Third_Party/LwIP/src/include/compat/stdc -I../Middlewares/Third_Party/LwIP/system/arch -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I"C:/Users/joshh/OneDrive/Documents/GitHub/STM32_Software/aaaaaaa/JAVELIBS/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-JAVELIBS-2f-src

clean-JAVELIBS-2f-src:
	-$(RM) ./JAVELIBS/src/MSGHandler.d ./JAVELIBS/src/MSGHandler.o ./JAVELIBS/src/MSGHandler.su ./JAVELIBS/src/RGB_LED.d ./JAVELIBS/src/RGB_LED.o ./JAVELIBS/src/RGB_LED.su ./JAVELIBS/src/Servo.d ./JAVELIBS/src/Servo.o ./JAVELIBS/src/Servo.su ./JAVELIBS/src/TraxxasESC.d ./JAVELIBS/src/TraxxasESC.o ./JAVELIBS/src/TraxxasESC.su ./JAVELIBS/src/stepper.d ./JAVELIBS/src/stepper.o ./JAVELIBS/src/stepper.su ./JAVELIBS/src/tcpclient.d ./JAVELIBS/src/tcpclient.o ./JAVELIBS/src/tcpclient.su ./JAVELIBS/src/tcpserver.d ./JAVELIBS/src/tcpserver.o ./JAVELIBS/src/tcpserver.su

.PHONY: clean-JAVELIBS-2f-src

