################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/font/Font_Processor.c \
../Core/font/Graphic.c \
../Core/font/TextBank.c \
../Core/font/font_RU_11x18.c \
../Core/font/font_RU_18x27.c \
../Core/font/ub_font_arial_10x15.c \
../Core/font/ub_font_arial_11x18.c \
../Core/font/ub_font_arial_13x19.c \
../Core/font/ub_font_arial_14x22.c \
../Core/font/ub_font_arial_16x25.c \
../Core/font/ub_font_arial_18x27.c \
../Core/font/ub_font_arial_7x10.c \
../Core/font/ub_font_arial_8x13.c \
../Core/font/ub_font_pArial_10.c \
../Core/font/ub_font_pArial_13.c \
../Core/font/ub_font_pArial_16.c \
../Core/font/ub_font_pArial_21.c \
../Core/font/ub_font_pComic_12.c \
../Core/font/ub_font_pComic_16.c \
../Core/font/ub_font_pComic_19.c \
../Core/font/ub_font_pTimes_12.c \
../Core/font/ub_font_pTimes_15.c \
../Core/font/ub_font_pTimes_18.c 

OBJS += \
./Core/font/Font_Processor.o \
./Core/font/Graphic.o \
./Core/font/TextBank.o \
./Core/font/font_RU_11x18.o \
./Core/font/font_RU_18x27.o \
./Core/font/ub_font_arial_10x15.o \
./Core/font/ub_font_arial_11x18.o \
./Core/font/ub_font_arial_13x19.o \
./Core/font/ub_font_arial_14x22.o \
./Core/font/ub_font_arial_16x25.o \
./Core/font/ub_font_arial_18x27.o \
./Core/font/ub_font_arial_7x10.o \
./Core/font/ub_font_arial_8x13.o \
./Core/font/ub_font_pArial_10.o \
./Core/font/ub_font_pArial_13.o \
./Core/font/ub_font_pArial_16.o \
./Core/font/ub_font_pArial_21.o \
./Core/font/ub_font_pComic_12.o \
./Core/font/ub_font_pComic_16.o \
./Core/font/ub_font_pComic_19.o \
./Core/font/ub_font_pTimes_12.o \
./Core/font/ub_font_pTimes_15.o \
./Core/font/ub_font_pTimes_18.o 

C_DEPS += \
./Core/font/Font_Processor.d \
./Core/font/Graphic.d \
./Core/font/TextBank.d \
./Core/font/font_RU_11x18.d \
./Core/font/font_RU_18x27.d \
./Core/font/ub_font_arial_10x15.d \
./Core/font/ub_font_arial_11x18.d \
./Core/font/ub_font_arial_13x19.d \
./Core/font/ub_font_arial_14x22.d \
./Core/font/ub_font_arial_16x25.d \
./Core/font/ub_font_arial_18x27.d \
./Core/font/ub_font_arial_7x10.d \
./Core/font/ub_font_arial_8x13.d \
./Core/font/ub_font_pArial_10.d \
./Core/font/ub_font_pArial_13.d \
./Core/font/ub_font_pArial_16.d \
./Core/font/ub_font_pArial_21.d \
./Core/font/ub_font_pComic_12.d \
./Core/font/ub_font_pComic_16.d \
./Core/font/ub_font_pComic_19.d \
./Core/font/ub_font_pTimes_12.d \
./Core/font/ub_font_pTimes_15.d \
./Core/font/ub_font_pTimes_18.d 


# Each subdirectory must supply rules for building sources it contributes
Core/font/%.o Core/font/%.su Core/font/%.cyclo: ../Core/font/%.c Core/font/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -DUSE_HAL_DRIVER -DSTM32F429xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-font

clean-Core-2f-font:
	-$(RM) ./Core/font/Font_Processor.cyclo ./Core/font/Font_Processor.d ./Core/font/Font_Processor.o ./Core/font/Font_Processor.su ./Core/font/Graphic.cyclo ./Core/font/Graphic.d ./Core/font/Graphic.o ./Core/font/Graphic.su ./Core/font/TextBank.cyclo ./Core/font/TextBank.d ./Core/font/TextBank.o ./Core/font/TextBank.su ./Core/font/font_RU_11x18.cyclo ./Core/font/font_RU_11x18.d ./Core/font/font_RU_11x18.o ./Core/font/font_RU_11x18.su ./Core/font/font_RU_18x27.cyclo ./Core/font/font_RU_18x27.d ./Core/font/font_RU_18x27.o ./Core/font/font_RU_18x27.su ./Core/font/ub_font_arial_10x15.cyclo ./Core/font/ub_font_arial_10x15.d ./Core/font/ub_font_arial_10x15.o ./Core/font/ub_font_arial_10x15.su ./Core/font/ub_font_arial_11x18.cyclo ./Core/font/ub_font_arial_11x18.d ./Core/font/ub_font_arial_11x18.o ./Core/font/ub_font_arial_11x18.su ./Core/font/ub_font_arial_13x19.cyclo ./Core/font/ub_font_arial_13x19.d ./Core/font/ub_font_arial_13x19.o ./Core/font/ub_font_arial_13x19.su ./Core/font/ub_font_arial_14x22.cyclo ./Core/font/ub_font_arial_14x22.d ./Core/font/ub_font_arial_14x22.o ./Core/font/ub_font_arial_14x22.su ./Core/font/ub_font_arial_16x25.cyclo ./Core/font/ub_font_arial_16x25.d ./Core/font/ub_font_arial_16x25.o ./Core/font/ub_font_arial_16x25.su ./Core/font/ub_font_arial_18x27.cyclo ./Core/font/ub_font_arial_18x27.d ./Core/font/ub_font_arial_18x27.o ./Core/font/ub_font_arial_18x27.su ./Core/font/ub_font_arial_7x10.cyclo ./Core/font/ub_font_arial_7x10.d ./Core/font/ub_font_arial_7x10.o ./Core/font/ub_font_arial_7x10.su ./Core/font/ub_font_arial_8x13.cyclo ./Core/font/ub_font_arial_8x13.d ./Core/font/ub_font_arial_8x13.o ./Core/font/ub_font_arial_8x13.su ./Core/font/ub_font_pArial_10.cyclo ./Core/font/ub_font_pArial_10.d ./Core/font/ub_font_pArial_10.o ./Core/font/ub_font_pArial_10.su ./Core/font/ub_font_pArial_13.cyclo ./Core/font/ub_font_pArial_13.d ./Core/font/ub_font_pArial_13.o ./Core/font/ub_font_pArial_13.su ./Core/font/ub_font_pArial_16.cyclo ./Core/font/ub_font_pArial_16.d ./Core/font/ub_font_pArial_16.o ./Core/font/ub_font_pArial_16.su ./Core/font/ub_font_pArial_21.cyclo ./Core/font/ub_font_pArial_21.d ./Core/font/ub_font_pArial_21.o ./Core/font/ub_font_pArial_21.su ./Core/font/ub_font_pComic_12.cyclo ./Core/font/ub_font_pComic_12.d ./Core/font/ub_font_pComic_12.o ./Core/font/ub_font_pComic_12.su ./Core/font/ub_font_pComic_16.cyclo ./Core/font/ub_font_pComic_16.d ./Core/font/ub_font_pComic_16.o ./Core/font/ub_font_pComic_16.su ./Core/font/ub_font_pComic_19.cyclo ./Core/font/ub_font_pComic_19.d ./Core/font/ub_font_pComic_19.o ./Core/font/ub_font_pComic_19.su ./Core/font/ub_font_pTimes_12.cyclo ./Core/font/ub_font_pTimes_12.d ./Core/font/ub_font_pTimes_12.o ./Core/font/ub_font_pTimes_12.su ./Core/font/ub_font_pTimes_15.cyclo ./Core/font/ub_font_pTimes_15.d ./Core/font/ub_font_pTimes_15.o ./Core/font/ub_font_pTimes_15.su ./Core/font/ub_font_pTimes_18.cyclo ./Core/font/ub_font_pTimes_18.d ./Core/font/ub_font_pTimes_18.o ./Core/font/ub_font_pTimes_18.su

.PHONY: clean-Core-2f-font

