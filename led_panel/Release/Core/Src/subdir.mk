################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/cube3d.c \
../Core/Src/display_string.c \
../Core/Src/display_test.c \
../Core/Src/event.c \
../Core/Src/game0.c \
../Core/Src/game_of_life.c \
../Core/Src/main.c \
../Core/Src/mat.c \
../Core/Src/renderer.c \
../Core/Src/rule110.c \
../Core/Src/stm32f1xx_hal_msp.c \
../Core/Src/stm32f1xx_it.c \
../Core/Src/syscalls.c \
../Core/Src/sysmem.c \
../Core/Src/system_stm32f1xx.c \
../Core/Src/testing.c 

C_DEPS += \
./Core/Src/cube3d.d \
./Core/Src/display_string.d \
./Core/Src/display_test.d \
./Core/Src/event.d \
./Core/Src/game0.d \
./Core/Src/game_of_life.d \
./Core/Src/main.d \
./Core/Src/mat.d \
./Core/Src/renderer.d \
./Core/Src/rule110.d \
./Core/Src/stm32f1xx_hal_msp.d \
./Core/Src/stm32f1xx_it.d \
./Core/Src/syscalls.d \
./Core/Src/sysmem.d \
./Core/Src/system_stm32f1xx.d \
./Core/Src/testing.d 

OBJS += \
./Core/Src/cube3d.o \
./Core/Src/display_string.o \
./Core/Src/display_test.o \
./Core/Src/event.o \
./Core/Src/game0.o \
./Core/Src/game_of_life.o \
./Core/Src/main.o \
./Core/Src/mat.o \
./Core/Src/renderer.o \
./Core/Src/rule110.o \
./Core/Src/stm32f1xx_hal_msp.o \
./Core/Src/stm32f1xx_it.o \
./Core/Src/syscalls.o \
./Core/Src/sysmem.o \
./Core/Src/system_stm32f1xx.o \
./Core/Src/testing.o 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/%.o Core/Src/%.su Core/Src/%.cyclo: ../Core/Src/%.c Core/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Core-2f-Src

clean-Core-2f-Src:
	-$(RM) ./Core/Src/cube3d.cyclo ./Core/Src/cube3d.d ./Core/Src/cube3d.o ./Core/Src/cube3d.su ./Core/Src/display_string.cyclo ./Core/Src/display_string.d ./Core/Src/display_string.o ./Core/Src/display_string.su ./Core/Src/display_test.cyclo ./Core/Src/display_test.d ./Core/Src/display_test.o ./Core/Src/display_test.su ./Core/Src/event.cyclo ./Core/Src/event.d ./Core/Src/event.o ./Core/Src/event.su ./Core/Src/game0.cyclo ./Core/Src/game0.d ./Core/Src/game0.o ./Core/Src/game0.su ./Core/Src/game_of_life.cyclo ./Core/Src/game_of_life.d ./Core/Src/game_of_life.o ./Core/Src/game_of_life.su ./Core/Src/main.cyclo ./Core/Src/main.d ./Core/Src/main.o ./Core/Src/main.su ./Core/Src/mat.cyclo ./Core/Src/mat.d ./Core/Src/mat.o ./Core/Src/mat.su ./Core/Src/renderer.cyclo ./Core/Src/renderer.d ./Core/Src/renderer.o ./Core/Src/renderer.su ./Core/Src/rule110.cyclo ./Core/Src/rule110.d ./Core/Src/rule110.o ./Core/Src/rule110.su ./Core/Src/stm32f1xx_hal_msp.cyclo ./Core/Src/stm32f1xx_hal_msp.d ./Core/Src/stm32f1xx_hal_msp.o ./Core/Src/stm32f1xx_hal_msp.su ./Core/Src/stm32f1xx_it.cyclo ./Core/Src/stm32f1xx_it.d ./Core/Src/stm32f1xx_it.o ./Core/Src/stm32f1xx_it.su ./Core/Src/syscalls.cyclo ./Core/Src/syscalls.d ./Core/Src/syscalls.o ./Core/Src/syscalls.su ./Core/Src/sysmem.cyclo ./Core/Src/sysmem.d ./Core/Src/sysmem.o ./Core/Src/sysmem.su ./Core/Src/system_stm32f1xx.cyclo ./Core/Src/system_stm32f1xx.d ./Core/Src/system_stm32f1xx.o ./Core/Src/system_stm32f1xx.su ./Core/Src/testing.cyclo ./Core/Src/testing.d ./Core/Src/testing.o ./Core/Src/testing.su

.PHONY: clean-Core-2f-Src

