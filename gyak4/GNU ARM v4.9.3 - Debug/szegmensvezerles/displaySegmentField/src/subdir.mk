################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
C:/Users/student/Desktop/szegmensvezerles/displaySegmentField/src/InitDevice.c \
C:/Users/student/Desktop/szegmensvezerles/displaySegmentField/src/segmain.c 

OBJS += \
./szegmensvezerles/displaySegmentField/src/InitDevice.o \
./szegmensvezerles/displaySegmentField/src/segmain.o 

C_DEPS += \
./szegmensvezerles/displaySegmentField/src/InitDevice.d \
./szegmensvezerles/displaySegmentField/src/segmain.d 


# Each subdirectory must supply rules for building sources it contributes
szegmensvezerles/displaySegmentField/src/InitDevice.o: C:/Users/student/Desktop/szegmensvezerles/displaySegmentField/src/InitDevice.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g -gdwarf-2 -mcpu=cortex-m3 -mthumb -std=c99 '-DDEBUG=1' '-DEFM32GG990F1024=1' -I"C:\Workspace\gyak4\inc" -I"C:\SiliconLabs\SimplicityStudio\v4\developer\sdks\gecko_sdk_suite\v1.1\hardware\kit\common\drivers" -I"C:\Workspace\gyak4\driver" -I"C:\Workspace\gyak4\inc" -I"C:/Workspace/gyak4/inc" -I"C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v1.1//hardware/kit/common/bsp" -I"C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v1.1//platform/CMSIS/Include" -I"C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v1.1//hardware/kit/EFM32GG_STK3700/config" -I"C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v1.1//platform/Device/SiliconLabs/EFM32GG/Include" -I"C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v1.1//platform/emlib/inc" -I"C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v1.1//hardware/kit/common/drivers" -O0 -Wall -c -fmessage-length=0 -mno-sched-prolog -fno-builtin -ffunction-sections -fdata-sections -MMD -MP -MF"szegmensvezerles/displaySegmentField/src/InitDevice.d" -MT"szegmensvezerles/displaySegmentField/src/InitDevice.o" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

szegmensvezerles/displaySegmentField/src/segmain.o: C:/Users/student/Desktop/szegmensvezerles/displaySegmentField/src/segmain.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g -gdwarf-2 -mcpu=cortex-m3 -mthumb -std=c99 '-DDEBUG=1' '-DEFM32GG990F1024=1' -I"C:\Workspace\gyak4\inc" -I"C:\SiliconLabs\SimplicityStudio\v4\developer\sdks\gecko_sdk_suite\v1.1\hardware\kit\common\drivers" -I"C:\Workspace\gyak4\driver" -I"C:\Workspace\gyak4\inc" -I"C:/Workspace/gyak4/inc" -I"C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v1.1//hardware/kit/common/bsp" -I"C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v1.1//platform/CMSIS/Include" -I"C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v1.1//hardware/kit/EFM32GG_STK3700/config" -I"C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v1.1//platform/Device/SiliconLabs/EFM32GG/Include" -I"C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v1.1//platform/emlib/inc" -I"C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v1.1//hardware/kit/common/drivers" -O0 -Wall -c -fmessage-length=0 -mno-sched-prolog -fno-builtin -ffunction-sections -fdata-sections -MMD -MP -MF"szegmensvezerles/displaySegmentField/src/segmain.d" -MT"szegmensvezerles/displaySegmentField/src/segmain.o" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


