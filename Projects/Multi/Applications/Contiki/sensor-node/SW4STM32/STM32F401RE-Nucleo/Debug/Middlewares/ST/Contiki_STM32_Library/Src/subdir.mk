################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
C:/Users/Giovanni/Desktop/sensor-node-6lowpan/Middlewares/ST/Contiki_STM32_Library/Src/clock.c \
C:/Users/Giovanni/Desktop/sensor-node-6lowpan/Middlewares/ST/Contiki_STM32_Library/Src/console.c \
C:/Users/Giovanni/Desktop/sensor-node-6lowpan/Middlewares/ST/Contiki_STM32_Library/Src/contiki-spirit1-main.c \
C:/Users/Giovanni/Desktop/sensor-node-6lowpan/Middlewares/ST/Contiki_STM32_Library/Src/node-id.c \
C:/Users/Giovanni/Desktop/sensor-node-6lowpan/Middlewares/ST/Contiki_STM32_Library/Src/rtimer-arch.c \
C:/Users/Giovanni/Desktop/sensor-node-6lowpan/Middlewares/ST/Contiki_STM32_Library/Src/spirit1-arch.c \
C:/Users/Giovanni/Desktop/sensor-node-6lowpan/Middlewares/ST/Contiki_STM32_Library/Src/spirit1.c \
C:/Users/Giovanni/Desktop/sensor-node-6lowpan/Middlewares/ST/Contiki_STM32_Library/Src/watchdog.c 

OBJS += \
./Middlewares/ST/Contiki_STM32_Library/Src/clock.o \
./Middlewares/ST/Contiki_STM32_Library/Src/console.o \
./Middlewares/ST/Contiki_STM32_Library/Src/contiki-spirit1-main.o \
./Middlewares/ST/Contiki_STM32_Library/Src/node-id.o \
./Middlewares/ST/Contiki_STM32_Library/Src/rtimer-arch.o \
./Middlewares/ST/Contiki_STM32_Library/Src/spirit1-arch.o \
./Middlewares/ST/Contiki_STM32_Library/Src/spirit1.o \
./Middlewares/ST/Contiki_STM32_Library/Src/watchdog.o 

C_DEPS += \
./Middlewares/ST/Contiki_STM32_Library/Src/clock.d \
./Middlewares/ST/Contiki_STM32_Library/Src/console.d \
./Middlewares/ST/Contiki_STM32_Library/Src/contiki-spirit1-main.d \
./Middlewares/ST/Contiki_STM32_Library/Src/node-id.d \
./Middlewares/ST/Contiki_STM32_Library/Src/rtimer-arch.d \
./Middlewares/ST/Contiki_STM32_Library/Src/spirit1-arch.d \
./Middlewares/ST/Contiki_STM32_Library/Src/spirit1.d \
./Middlewares/ST/Contiki_STM32_Library/Src/watchdog.d 


# Each subdirectory must supply rules for building sources it contributes
Middlewares/ST/Contiki_STM32_Library/Src/clock.o: C:/Users/Giovanni/Desktop/sensor-node-6lowpan/Middlewares/ST/Contiki_STM32_Library/Src/clock.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo %cd%
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=soft -std=c99 '-DPROJECT_CONF_H=1' -DX_NUCLEO_IDS01A4 -DUSE_USART2 -DSTM32F401xE -DUSE_STM32F4XX_NUCLEO -DUSE_HAL_DRIVER '-DHSE_VALUE=84000000ul' -DUSE_STDPERIPH_DRIVER -DNO_EEPROM -DSPIRIT1_ST_SHIELD -DSPIRIT_MODULE -DUSE_SPIRIT1_DEFAULT -DWITH_UIP6 -DIAR_ARM_CM3 -DVECT_TAB_FLASH -DWITH_UIP -DWITH_ASCII '-DCONTIKI=1' '-DUIP_CONF_TCP=1' '-DNETSTACK_CONF_WITH_IPV6=1' '-DUIP_CONF_IPV6_RPL=1' '-DAUTOSTART_ENABLE=1' -I"C:/Users/Giovanni/Desktop/sensor-node-6lowpan/Projects/Multi/Applications/Contiki/sensor-node/Inc" -I"C:/Users/Giovanni/Desktop/sensor-node-6lowpan/Middlewares/ST/Contiki_STM32_Library" -I"C:/Users/Giovanni/Desktop/sensor-node-6lowpan/Middlewares/ST/Contiki_STM32_Library/Inc" -I"C:/Users/Giovanni/Desktop/sensor-node-6lowpan/Middlewares/ST/Contiki_STM32_Library/dev" -I"C:/Users/Giovanni/Desktop/sensor-node-6lowpan/Middlewares/Third_Party/Contiki" -I"C:/Users/Giovanni/Desktop/sensor-node-6lowpan/Middlewares/Third_Party/Contiki/apps/servreg-hack" -I"C:/Users/Giovanni/Desktop/sensor-node-6lowpan/Middlewares/Third_Party/Contiki/core" -I"C:/Users/Giovanni/Desktop/sensor-node-6lowpan/Middlewares/Third_Party/Contiki/core/sys" -I"C:/Users/Giovanni/Desktop/sensor-node-6lowpan/Middlewares/Third_Party/Contiki/core/lib" -I"C:/Users/Giovanni/Desktop/sensor-node-6lowpan/Middlewares/Third_Party/Contiki/core/net" -I"C:/Users/Giovanni/Desktop/sensor-node-6lowpan/Middlewares/Third_Party/Contiki/core/dev" -I"C:/Users/Giovanni/Desktop/sensor-node-6lowpan/Middlewares/Third_Party/Contiki/core/net/ip" -I"C:/Users/Giovanni/Desktop/sensor-node-6lowpan/Middlewares/Third_Party/Contiki/core/net/ipv6" -I"C:/Users/Giovanni/Desktop/sensor-node-6lowpan/Middlewares/Third_Party/Contiki/core/net/llsec" -I"C:/Users/Giovanni/Desktop/sensor-node-6lowpan/Middlewares/Third_Party/Contiki/core/net/rpl" -I"C:/Users/Giovanni/Desktop/sensor-node-6lowpan/Drivers/BSP/STM32F4xx_Nucleo" -I"C:/Users/Giovanni/Desktop/sensor-node-6lowpan/Drivers/BSP/X-NUCLEO-IDS01Ax/Inc" -I"C:/Users/Giovanni/Desktop/sensor-node-6lowpan/Drivers/BSP/Components" -I"C:/Users/Giovanni/Desktop/sensor-node-6lowpan/Drivers/BSP/Components/spirit1/SPIRIT1_Library/Inc" -I"C:/Users/Giovanni/Desktop/sensor-node-6lowpan/Drivers/BSP/Components/spirit1/SPIRIT1_Util/Inc" -I"C:/Users/Giovanni/Desktop/sensor-node-6lowpan/Drivers/CMSIS/Include" -I"C:/Users/Giovanni/Desktop/sensor-node-6lowpan/Drivers/CMSIS/Device/ST/STM32F4xx/Include" -I"C:/Users/Giovanni/Desktop/sensor-node-6lowpan/Drivers/STM32F4xx_HAL_Driver/Inc" -I"C:/Users/Giovanni/Desktop/sensor-node-6lowpan/Drivers/STM32F4xx_HAL_Driver/Inc/Legacy" -I"C:/Users/Giovanni/Desktop/sensor-node-6lowpan/Drivers/BSP/Components/Common" -I"C:/Users/Giovanni/Desktop/sensor-node-6lowpan/Drivers/BSP/Components/hts221" -I"C:/Users/Giovanni/Desktop/sensor-node-6lowpan/Drivers/BSP/Components/lis3mdl" -I"C:/Users/Giovanni/Desktop/sensor-node-6lowpan/Drivers/BSP/Components/lps22hb" -I"C:/Users/Giovanni/Desktop/sensor-node-6lowpan/Drivers/BSP/Components/lps25hb" -I"C:/Users/Giovanni/Desktop/sensor-node-6lowpan/Drivers/BSP/Components/lsm6ds0" -I"C:/Users/Giovanni/Desktop/sensor-node-6lowpan/Drivers/BSP/Components/lsm6ds3" -I"C:/Users/Giovanni/Desktop/sensor-node-6lowpan/Drivers/BSP/Components/lsm6dsl" -I"C:/Users/Giovanni/Desktop/sensor-node-6lowpan/Drivers/BSP/Components/lsm303agr" -I"C:/Users/Giovanni/Desktop/sensor-node-6lowpan/Drivers/BSP/X_NUCLEO_IKS01A2"  -O0 -g3 -Wall -fmessage-length=0 -mno-unaligned-access -Wl,-cref -ffunction-sections -fdata-sections -ffunction-sections -c -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Middlewares/ST/Contiki_STM32_Library/Src/console.o: C:/Users/Giovanni/Desktop/sensor-node-6lowpan/Middlewares/ST/Contiki_STM32_Library/Src/console.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo %cd%
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=soft -std=c99 '-DPROJECT_CONF_H=1' -DX_NUCLEO_IDS01A4 -DUSE_USART2 -DSTM32F401xE -DUSE_STM32F4XX_NUCLEO -DUSE_HAL_DRIVER '-DHSE_VALUE=84000000ul' -DUSE_STDPERIPH_DRIVER -DNO_EEPROM -DSPIRIT1_ST_SHIELD -DSPIRIT_MODULE -DUSE_SPIRIT1_DEFAULT -DWITH_UIP6 -DIAR_ARM_CM3 -DVECT_TAB_FLASH -DWITH_UIP -DWITH_ASCII '-DCONTIKI=1' '-DUIP_CONF_TCP=1' '-DNETSTACK_CONF_WITH_IPV6=1' '-DUIP_CONF_IPV6_RPL=1' '-DAUTOSTART_ENABLE=1' -I"C:/Users/Giovanni/Desktop/sensor-node-6lowpan/Projects/Multi/Applications/Contiki/sensor-node/Inc" -I"C:/Users/Giovanni/Desktop/sensor-node-6lowpan/Middlewares/ST/Contiki_STM32_Library" -I"C:/Users/Giovanni/Desktop/sensor-node-6lowpan/Middlewares/ST/Contiki_STM32_Library/Inc" -I"C:/Users/Giovanni/Desktop/sensor-node-6lowpan/Middlewares/ST/Contiki_STM32_Library/dev" -I"C:/Users/Giovanni/Desktop/sensor-node-6lowpan/Middlewares/Third_Party/Contiki" -I"C:/Users/Giovanni/Desktop/sensor-node-6lowpan/Middlewares/Third_Party/Contiki/apps/servreg-hack" -I"C:/Users/Giovanni/Desktop/sensor-node-6lowpan/Middlewares/Third_Party/Contiki/core" -I"C:/Users/Giovanni/Desktop/sensor-node-6lowpan/Middlewares/Third_Party/Contiki/core/sys" -I"C:/Users/Giovanni/Desktop/sensor-node-6lowpan/Middlewares/Third_Party/Contiki/core/lib" -I"C:/Users/Giovanni/Desktop/sensor-node-6lowpan/Middlewares/Third_Party/Contiki/core/net" -I"C:/Users/Giovanni/Desktop/sensor-node-6lowpan/Middlewares/Third_Party/Contiki/core/dev" -I"C:/Users/Giovanni/Desktop/sensor-node-6lowpan/Middlewares/Third_Party/Contiki/core/net/ip" -I"C:/Users/Giovanni/Desktop/sensor-node-6lowpan/Middlewares/Third_Party/Contiki/core/net/ipv6" -I"C:/Users/Giovanni/Desktop/sensor-node-6lowpan/Middlewares/Third_Party/Contiki/core/net/llsec" -I"C:/Users/Giovanni/Desktop/sensor-node-6lowpan/Middlewares/Third_Party/Contiki/core/net/rpl" -I"C:/Users/Giovanni/Desktop/sensor-node-6lowpan/Drivers/BSP/STM32F4xx_Nucleo" -I"C:/Users/Giovanni/Desktop/sensor-node-6lowpan/Drivers/BSP/X-NUCLEO-IDS01Ax/Inc" -I"C:/Users/Giovanni/Desktop/sensor-node-6lowpan/Drivers/BSP/Components" -I"C:/Users/Giovanni/Desktop/sensor-node-6lowpan/Drivers/BSP/Components/spirit1/SPIRIT1_Library/Inc" -I"C:/Users/Giovanni/Desktop/sensor-node-6lowpan/Drivers/BSP/Components/spirit1/SPIRIT1_Util/Inc" -I"C:/Users/Giovanni/Desktop/sensor-node-6lowpan/Drivers/CMSIS/Include" -I"C:/Users/Giovanni/Desktop/sensor-node-6lowpan/Drivers/CMSIS/Device/ST/STM32F4xx/Include" -I"C:/Users/Giovanni/Desktop/sensor-node-6lowpan/Drivers/STM32F4xx_HAL_Driver/Inc" -I"C:/Users/Giovanni/Desktop/sensor-node-6lowpan/Drivers/STM32F4xx_HAL_Driver/Inc/Legacy" -I"C:/Users/Giovanni/Desktop/sensor-node-6lowpan/Drivers/BSP/Components/Common" -I"C:/Users/Giovanni/Desktop/sensor-node-6lowpan/Drivers/BSP/Components/hts221" -I"C:/Users/Giovanni/Desktop/sensor-node-6lowpan/Drivers/BSP/Components/lis3mdl" -I"C:/Users/Giovanni/Desktop/sensor-node-6lowpan/Drivers/BSP/Components/lps22hb" -I"C:/Users/Giovanni/Desktop/sensor-node-6lowpan/Drivers/BSP/Components/lps25hb" -I"C:/Users/Giovanni/Desktop/sensor-node-6lowpan/Drivers/BSP/Components/lsm6ds0" -I"C:/Users/Giovanni/Desktop/sensor-node-6lowpan/Drivers/BSP/Components/lsm6ds3" -I"C:/Users/Giovanni/Desktop/sensor-node-6lowpan/Drivers/BSP/Components/lsm6dsl" -I"C:/Users/Giovanni/Desktop/sensor-node-6lowpan/Drivers/BSP/Components/lsm303agr" -I"C:/Users/Giovanni/Desktop/sensor-node-6lowpan/Drivers/BSP/X_NUCLEO_IKS01A2"  -O0 -g3 -Wall -fmessage-length=0 -mno-unaligned-access -Wl,-cref -ffunction-sections -fdata-sections -ffunction-sections -c -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Middlewares/ST/Contiki_STM32_Library/Src/contiki-spirit1-main.o: C:/Users/Giovanni/Desktop/sensor-node-6lowpan/Middlewares/ST/Contiki_STM32_Library/Src/contiki-spirit1-main.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo %cd%
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=soft -std=c99 '-DPROJECT_CONF_H=1' -DX_NUCLEO_IDS01A4 -DUSE_USART2 -DSTM32F401xE -DUSE_STM32F4XX_NUCLEO -DUSE_HAL_DRIVER '-DHSE_VALUE=84000000ul' -DUSE_STDPERIPH_DRIVER -DNO_EEPROM -DSPIRIT1_ST_SHIELD -DSPIRIT_MODULE -DUSE_SPIRIT1_DEFAULT -DWITH_UIP6 -DIAR_ARM_CM3 -DVECT_TAB_FLASH -DWITH_UIP -DWITH_ASCII '-DCONTIKI=1' '-DUIP_CONF_TCP=1' '-DNETSTACK_CONF_WITH_IPV6=1' '-DUIP_CONF_IPV6_RPL=1' '-DAUTOSTART_ENABLE=1' -I"C:/Users/Giovanni/Desktop/sensor-node-6lowpan/Projects/Multi/Applications/Contiki/sensor-node/Inc" -I"C:/Users/Giovanni/Desktop/sensor-node-6lowpan/Middlewares/ST/Contiki_STM32_Library" -I"C:/Users/Giovanni/Desktop/sensor-node-6lowpan/Middlewares/ST/Contiki_STM32_Library/Inc" -I"C:/Users/Giovanni/Desktop/sensor-node-6lowpan/Middlewares/ST/Contiki_STM32_Library/dev" -I"C:/Users/Giovanni/Desktop/sensor-node-6lowpan/Middlewares/Third_Party/Contiki" -I"C:/Users/Giovanni/Desktop/sensor-node-6lowpan/Middlewares/Third_Party/Contiki/apps/servreg-hack" -I"C:/Users/Giovanni/Desktop/sensor-node-6lowpan/Middlewares/Third_Party/Contiki/core" -I"C:/Users/Giovanni/Desktop/sensor-node-6lowpan/Middlewares/Third_Party/Contiki/core/sys" -I"C:/Users/Giovanni/Desktop/sensor-node-6lowpan/Middlewares/Third_Party/Contiki/core/lib" -I"C:/Users/Giovanni/Desktop/sensor-node-6lowpan/Middlewares/Third_Party/Contiki/core/net" -I"C:/Users/Giovanni/Desktop/sensor-node-6lowpan/Middlewares/Third_Party/Contiki/core/dev" -I"C:/Users/Giovanni/Desktop/sensor-node-6lowpan/Middlewares/Third_Party/Contiki/core/net/ip" -I"C:/Users/Giovanni/Desktop/sensor-node-6lowpan/Middlewares/Third_Party/Contiki/core/net/ipv6" -I"C:/Users/Giovanni/Desktop/sensor-node-6lowpan/Middlewares/Third_Party/Contiki/core/net/llsec" -I"C:/Users/Giovanni/Desktop/sensor-node-6lowpan/Middlewares/Third_Party/Contiki/core/net/rpl" -I"C:/Users/Giovanni/Desktop/sensor-node-6lowpan/Drivers/BSP/STM32F4xx_Nucleo" -I"C:/Users/Giovanni/Desktop/sensor-node-6lowpan/Drivers/BSP/X-NUCLEO-IDS01Ax/Inc" -I"C:/Users/Giovanni/Desktop/sensor-node-6lowpan/Drivers/BSP/Components" -I"C:/Users/Giovanni/Desktop/sensor-node-6lowpan/Drivers/BSP/Components/spirit1/SPIRIT1_Library/Inc" -I"C:/Users/Giovanni/Desktop/sensor-node-6lowpan/Drivers/BSP/Components/spirit1/SPIRIT1_Util/Inc" -I"C:/Users/Giovanni/Desktop/sensor-node-6lowpan/Drivers/CMSIS/Include" -I"C:/Users/Giovanni/Desktop/sensor-node-6lowpan/Drivers/CMSIS/Device/ST/STM32F4xx/Include" -I"C:/Users/Giovanni/Desktop/sensor-node-6lowpan/Drivers/STM32F4xx_HAL_Driver/Inc" -I"C:/Users/Giovanni/Desktop/sensor-node-6lowpan/Drivers/STM32F4xx_HAL_Driver/Inc/Legacy" -I"C:/Users/Giovanni/Desktop/sensor-node-6lowpan/Drivers/BSP/Components/Common" -I"C:/Users/Giovanni/Desktop/sensor-node-6lowpan/Drivers/BSP/Components/hts221" -I"C:/Users/Giovanni/Desktop/sensor-node-6lowpan/Drivers/BSP/Components/lis3mdl" -I"C:/Users/Giovanni/Desktop/sensor-node-6lowpan/Drivers/BSP/Components/lps22hb" -I"C:/Users/Giovanni/Desktop/sensor-node-6lowpan/Drivers/BSP/Components/lps25hb" -I"C:/Users/Giovanni/Desktop/sensor-node-6lowpan/Drivers/BSP/Components/lsm6ds0" -I"C:/Users/Giovanni/Desktop/sensor-node-6lowpan/Drivers/BSP/Components/lsm6ds3" -I"C:/Users/Giovanni/Desktop/sensor-node-6lowpan/Drivers/BSP/Components/lsm6dsl" -I"C:/Users/Giovanni/Desktop/sensor-node-6lowpan/Drivers/BSP/Components/lsm303agr" -I"C:/Users/Giovanni/Desktop/sensor-node-6lowpan/Drivers/BSP/X_NUCLEO_IKS01A2"  -O0 -g3 -Wall -fmessage-length=0 -mno-unaligned-access -Wl,-cref -ffunction-sections -fdata-sections -ffunction-sections -c -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Middlewares/ST/Contiki_STM32_Library/Src/node-id.o: C:/Users/Giovanni/Desktop/sensor-node-6lowpan/Middlewares/ST/Contiki_STM32_Library/Src/node-id.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo %cd%
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=soft -std=c99 '-DPROJECT_CONF_H=1' -DX_NUCLEO_IDS01A4 -DUSE_USART2 -DSTM32F401xE -DUSE_STM32F4XX_NUCLEO -DUSE_HAL_DRIVER '-DHSE_VALUE=84000000ul' -DUSE_STDPERIPH_DRIVER -DNO_EEPROM -DSPIRIT1_ST_SHIELD -DSPIRIT_MODULE -DUSE_SPIRIT1_DEFAULT -DWITH_UIP6 -DIAR_ARM_CM3 -DVECT_TAB_FLASH -DWITH_UIP -DWITH_ASCII '-DCONTIKI=1' '-DUIP_CONF_TCP=1' '-DNETSTACK_CONF_WITH_IPV6=1' '-DUIP_CONF_IPV6_RPL=1' '-DAUTOSTART_ENABLE=1' -I"C:/Users/Giovanni/Desktop/sensor-node-6lowpan/Projects/Multi/Applications/Contiki/sensor-node/Inc" -I"C:/Users/Giovanni/Desktop/sensor-node-6lowpan/Middlewares/ST/Contiki_STM32_Library" -I"C:/Users/Giovanni/Desktop/sensor-node-6lowpan/Middlewares/ST/Contiki_STM32_Library/Inc" -I"C:/Users/Giovanni/Desktop/sensor-node-6lowpan/Middlewares/ST/Contiki_STM32_Library/dev" -I"C:/Users/Giovanni/Desktop/sensor-node-6lowpan/Middlewares/Third_Party/Contiki" -I"C:/Users/Giovanni/Desktop/sensor-node-6lowpan/Middlewares/Third_Party/Contiki/apps/servreg-hack" -I"C:/Users/Giovanni/Desktop/sensor-node-6lowpan/Middlewares/Third_Party/Contiki/core" -I"C:/Users/Giovanni/Desktop/sensor-node-6lowpan/Middlewares/Third_Party/Contiki/core/sys" -I"C:/Users/Giovanni/Desktop/sensor-node-6lowpan/Middlewares/Third_Party/Contiki/core/lib" -I"C:/Users/Giovanni/Desktop/sensor-node-6lowpan/Middlewares/Third_Party/Contiki/core/net" -I"C:/Users/Giovanni/Desktop/sensor-node-6lowpan/Middlewares/Third_Party/Contiki/core/dev" -I"C:/Users/Giovanni/Desktop/sensor-node-6lowpan/Middlewares/Third_Party/Contiki/core/net/ip" -I"C:/Users/Giovanni/Desktop/sensor-node-6lowpan/Middlewares/Third_Party/Contiki/core/net/ipv6" -I"C:/Users/Giovanni/Desktop/sensor-node-6lowpan/Middlewares/Third_Party/Contiki/core/net/llsec" -I"C:/Users/Giovanni/Desktop/sensor-node-6lowpan/Middlewares/Third_Party/Contiki/core/net/rpl" -I"C:/Users/Giovanni/Desktop/sensor-node-6lowpan/Drivers/BSP/STM32F4xx_Nucleo" -I"C:/Users/Giovanni/Desktop/sensor-node-6lowpan/Drivers/BSP/X-NUCLEO-IDS01Ax/Inc" -I"C:/Users/Giovanni/Desktop/sensor-node-6lowpan/Drivers/BSP/Components" -I"C:/Users/Giovanni/Desktop/sensor-node-6lowpan/Drivers/BSP/Components/spirit1/SPIRIT1_Library/Inc" -I"C:/Users/Giovanni/Desktop/sensor-node-6lowpan/Drivers/BSP/Components/spirit1/SPIRIT1_Util/Inc" -I"C:/Users/Giovanni/Desktop/sensor-node-6lowpan/Drivers/CMSIS/Include" -I"C:/Users/Giovanni/Desktop/sensor-node-6lowpan/Drivers/CMSIS/Device/ST/STM32F4xx/Include" -I"C:/Users/Giovanni/Desktop/sensor-node-6lowpan/Drivers/STM32F4xx_HAL_Driver/Inc" -I"C:/Users/Giovanni/Desktop/sensor-node-6lowpan/Drivers/STM32F4xx_HAL_Driver/Inc/Legacy" -I"C:/Users/Giovanni/Desktop/sensor-node-6lowpan/Drivers/BSP/Components/Common" -I"C:/Users/Giovanni/Desktop/sensor-node-6lowpan/Drivers/BSP/Components/hts221" -I"C:/Users/Giovanni/Desktop/sensor-node-6lowpan/Drivers/BSP/Components/lis3mdl" -I"C:/Users/Giovanni/Desktop/sensor-node-6lowpan/Drivers/BSP/Components/lps22hb" -I"C:/Users/Giovanni/Desktop/sensor-node-6lowpan/Drivers/BSP/Components/lps25hb" -I"C:/Users/Giovanni/Desktop/sensor-node-6lowpan/Drivers/BSP/Components/lsm6ds0" -I"C:/Users/Giovanni/Desktop/sensor-node-6lowpan/Drivers/BSP/Components/lsm6ds3" -I"C:/Users/Giovanni/Desktop/sensor-node-6lowpan/Drivers/BSP/Components/lsm6dsl" -I"C:/Users/Giovanni/Desktop/sensor-node-6lowpan/Drivers/BSP/Components/lsm303agr" -I"C:/Users/Giovanni/Desktop/sensor-node-6lowpan/Drivers/BSP/X_NUCLEO_IKS01A2"  -O0 -g3 -Wall -fmessage-length=0 -mno-unaligned-access -Wl,-cref -ffunction-sections -fdata-sections -ffunction-sections -c -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Middlewares/ST/Contiki_STM32_Library/Src/rtimer-arch.o: C:/Users/Giovanni/Desktop/sensor-node-6lowpan/Middlewares/ST/Contiki_STM32_Library/Src/rtimer-arch.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo %cd%
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=soft -std=c99 '-DPROJECT_CONF_H=1' -DX_NUCLEO_IDS01A4 -DUSE_USART2 -DSTM32F401xE -DUSE_STM32F4XX_NUCLEO -DUSE_HAL_DRIVER '-DHSE_VALUE=84000000ul' -DUSE_STDPERIPH_DRIVER -DNO_EEPROM -DSPIRIT1_ST_SHIELD -DSPIRIT_MODULE -DUSE_SPIRIT1_DEFAULT -DWITH_UIP6 -DIAR_ARM_CM3 -DVECT_TAB_FLASH -DWITH_UIP -DWITH_ASCII '-DCONTIKI=1' '-DUIP_CONF_TCP=1' '-DNETSTACK_CONF_WITH_IPV6=1' '-DUIP_CONF_IPV6_RPL=1' '-DAUTOSTART_ENABLE=1' -I"C:/Users/Giovanni/Desktop/sensor-node-6lowpan/Projects/Multi/Applications/Contiki/sensor-node/Inc" -I"C:/Users/Giovanni/Desktop/sensor-node-6lowpan/Middlewares/ST/Contiki_STM32_Library" -I"C:/Users/Giovanni/Desktop/sensor-node-6lowpan/Middlewares/ST/Contiki_STM32_Library/Inc" -I"C:/Users/Giovanni/Desktop/sensor-node-6lowpan/Middlewares/ST/Contiki_STM32_Library/dev" -I"C:/Users/Giovanni/Desktop/sensor-node-6lowpan/Middlewares/Third_Party/Contiki" -I"C:/Users/Giovanni/Desktop/sensor-node-6lowpan/Middlewares/Third_Party/Contiki/apps/servreg-hack" -I"C:/Users/Giovanni/Desktop/sensor-node-6lowpan/Middlewares/Third_Party/Contiki/core" -I"C:/Users/Giovanni/Desktop/sensor-node-6lowpan/Middlewares/Third_Party/Contiki/core/sys" -I"C:/Users/Giovanni/Desktop/sensor-node-6lowpan/Middlewares/Third_Party/Contiki/core/lib" -I"C:/Users/Giovanni/Desktop/sensor-node-6lowpan/Middlewares/Third_Party/Contiki/core/net" -I"C:/Users/Giovanni/Desktop/sensor-node-6lowpan/Middlewares/Third_Party/Contiki/core/dev" -I"C:/Users/Giovanni/Desktop/sensor-node-6lowpan/Middlewares/Third_Party/Contiki/core/net/ip" -I"C:/Users/Giovanni/Desktop/sensor-node-6lowpan/Middlewares/Third_Party/Contiki/core/net/ipv6" -I"C:/Users/Giovanni/Desktop/sensor-node-6lowpan/Middlewares/Third_Party/Contiki/core/net/llsec" -I"C:/Users/Giovanni/Desktop/sensor-node-6lowpan/Middlewares/Third_Party/Contiki/core/net/rpl" -I"C:/Users/Giovanni/Desktop/sensor-node-6lowpan/Drivers/BSP/STM32F4xx_Nucleo" -I"C:/Users/Giovanni/Desktop/sensor-node-6lowpan/Drivers/BSP/X-NUCLEO-IDS01Ax/Inc" -I"C:/Users/Giovanni/Desktop/sensor-node-6lowpan/Drivers/BSP/Components" -I"C:/Users/Giovanni/Desktop/sensor-node-6lowpan/Drivers/BSP/Components/spirit1/SPIRIT1_Library/Inc" -I"C:/Users/Giovanni/Desktop/sensor-node-6lowpan/Drivers/BSP/Components/spirit1/SPIRIT1_Util/Inc" -I"C:/Users/Giovanni/Desktop/sensor-node-6lowpan/Drivers/CMSIS/Include" -I"C:/Users/Giovanni/Desktop/sensor-node-6lowpan/Drivers/CMSIS/Device/ST/STM32F4xx/Include" -I"C:/Users/Giovanni/Desktop/sensor-node-6lowpan/Drivers/STM32F4xx_HAL_Driver/Inc" -I"C:/Users/Giovanni/Desktop/sensor-node-6lowpan/Drivers/STM32F4xx_HAL_Driver/Inc/Legacy" -I"C:/Users/Giovanni/Desktop/sensor-node-6lowpan/Drivers/BSP/Components/Common" -I"C:/Users/Giovanni/Desktop/sensor-node-6lowpan/Drivers/BSP/Components/hts221" -I"C:/Users/Giovanni/Desktop/sensor-node-6lowpan/Drivers/BSP/Components/lis3mdl" -I"C:/Users/Giovanni/Desktop/sensor-node-6lowpan/Drivers/BSP/Components/lps22hb" -I"C:/Users/Giovanni/Desktop/sensor-node-6lowpan/Drivers/BSP/Components/lps25hb" -I"C:/Users/Giovanni/Desktop/sensor-node-6lowpan/Drivers/BSP/Components/lsm6ds0" -I"C:/Users/Giovanni/Desktop/sensor-node-6lowpan/Drivers/BSP/Components/lsm6ds3" -I"C:/Users/Giovanni/Desktop/sensor-node-6lowpan/Drivers/BSP/Components/lsm6dsl" -I"C:/Users/Giovanni/Desktop/sensor-node-6lowpan/Drivers/BSP/Components/lsm303agr" -I"C:/Users/Giovanni/Desktop/sensor-node-6lowpan/Drivers/BSP/X_NUCLEO_IKS01A2"  -O0 -g3 -Wall -fmessage-length=0 -mno-unaligned-access -Wl,-cref -ffunction-sections -fdata-sections -ffunction-sections -c -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Middlewares/ST/Contiki_STM32_Library/Src/spirit1-arch.o: C:/Users/Giovanni/Desktop/sensor-node-6lowpan/Middlewares/ST/Contiki_STM32_Library/Src/spirit1-arch.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo %cd%
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=soft -std=c99 '-DPROJECT_CONF_H=1' -DX_NUCLEO_IDS01A4 -DUSE_USART2 -DSTM32F401xE -DUSE_STM32F4XX_NUCLEO -DUSE_HAL_DRIVER '-DHSE_VALUE=84000000ul' -DUSE_STDPERIPH_DRIVER -DNO_EEPROM -DSPIRIT1_ST_SHIELD -DSPIRIT_MODULE -DUSE_SPIRIT1_DEFAULT -DWITH_UIP6 -DIAR_ARM_CM3 -DVECT_TAB_FLASH -DWITH_UIP -DWITH_ASCII '-DCONTIKI=1' '-DUIP_CONF_TCP=1' '-DNETSTACK_CONF_WITH_IPV6=1' '-DUIP_CONF_IPV6_RPL=1' '-DAUTOSTART_ENABLE=1' -I"C:/Users/Giovanni/Desktop/sensor-node-6lowpan/Projects/Multi/Applications/Contiki/sensor-node/Inc" -I"C:/Users/Giovanni/Desktop/sensor-node-6lowpan/Middlewares/ST/Contiki_STM32_Library" -I"C:/Users/Giovanni/Desktop/sensor-node-6lowpan/Middlewares/ST/Contiki_STM32_Library/Inc" -I"C:/Users/Giovanni/Desktop/sensor-node-6lowpan/Middlewares/ST/Contiki_STM32_Library/dev" -I"C:/Users/Giovanni/Desktop/sensor-node-6lowpan/Middlewares/Third_Party/Contiki" -I"C:/Users/Giovanni/Desktop/sensor-node-6lowpan/Middlewares/Third_Party/Contiki/apps/servreg-hack" -I"C:/Users/Giovanni/Desktop/sensor-node-6lowpan/Middlewares/Third_Party/Contiki/core" -I"C:/Users/Giovanni/Desktop/sensor-node-6lowpan/Middlewares/Third_Party/Contiki/core/sys" -I"C:/Users/Giovanni/Desktop/sensor-node-6lowpan/Middlewares/Third_Party/Contiki/core/lib" -I"C:/Users/Giovanni/Desktop/sensor-node-6lowpan/Middlewares/Third_Party/Contiki/core/net" -I"C:/Users/Giovanni/Desktop/sensor-node-6lowpan/Middlewares/Third_Party/Contiki/core/dev" -I"C:/Users/Giovanni/Desktop/sensor-node-6lowpan/Middlewares/Third_Party/Contiki/core/net/ip" -I"C:/Users/Giovanni/Desktop/sensor-node-6lowpan/Middlewares/Third_Party/Contiki/core/net/ipv6" -I"C:/Users/Giovanni/Desktop/sensor-node-6lowpan/Middlewares/Third_Party/Contiki/core/net/llsec" -I"C:/Users/Giovanni/Desktop/sensor-node-6lowpan/Middlewares/Third_Party/Contiki/core/net/rpl" -I"C:/Users/Giovanni/Desktop/sensor-node-6lowpan/Drivers/BSP/STM32F4xx_Nucleo" -I"C:/Users/Giovanni/Desktop/sensor-node-6lowpan/Drivers/BSP/X-NUCLEO-IDS01Ax/Inc" -I"C:/Users/Giovanni/Desktop/sensor-node-6lowpan/Drivers/BSP/Components" -I"C:/Users/Giovanni/Desktop/sensor-node-6lowpan/Drivers/BSP/Components/spirit1/SPIRIT1_Library/Inc" -I"C:/Users/Giovanni/Desktop/sensor-node-6lowpan/Drivers/BSP/Components/spirit1/SPIRIT1_Util/Inc" -I"C:/Users/Giovanni/Desktop/sensor-node-6lowpan/Drivers/CMSIS/Include" -I"C:/Users/Giovanni/Desktop/sensor-node-6lowpan/Drivers/CMSIS/Device/ST/STM32F4xx/Include" -I"C:/Users/Giovanni/Desktop/sensor-node-6lowpan/Drivers/STM32F4xx_HAL_Driver/Inc" -I"C:/Users/Giovanni/Desktop/sensor-node-6lowpan/Drivers/STM32F4xx_HAL_Driver/Inc/Legacy" -I"C:/Users/Giovanni/Desktop/sensor-node-6lowpan/Drivers/BSP/Components/Common" -I"C:/Users/Giovanni/Desktop/sensor-node-6lowpan/Drivers/BSP/Components/hts221" -I"C:/Users/Giovanni/Desktop/sensor-node-6lowpan/Drivers/BSP/Components/lis3mdl" -I"C:/Users/Giovanni/Desktop/sensor-node-6lowpan/Drivers/BSP/Components/lps22hb" -I"C:/Users/Giovanni/Desktop/sensor-node-6lowpan/Drivers/BSP/Components/lps25hb" -I"C:/Users/Giovanni/Desktop/sensor-node-6lowpan/Drivers/BSP/Components/lsm6ds0" -I"C:/Users/Giovanni/Desktop/sensor-node-6lowpan/Drivers/BSP/Components/lsm6ds3" -I"C:/Users/Giovanni/Desktop/sensor-node-6lowpan/Drivers/BSP/Components/lsm6dsl" -I"C:/Users/Giovanni/Desktop/sensor-node-6lowpan/Drivers/BSP/Components/lsm303agr" -I"C:/Users/Giovanni/Desktop/sensor-node-6lowpan/Drivers/BSP/X_NUCLEO_IKS01A2"  -O0 -g3 -Wall -fmessage-length=0 -mno-unaligned-access -Wl,-cref -ffunction-sections -fdata-sections -ffunction-sections -c -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Middlewares/ST/Contiki_STM32_Library/Src/spirit1.o: C:/Users/Giovanni/Desktop/sensor-node-6lowpan/Middlewares/ST/Contiki_STM32_Library/Src/spirit1.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo %cd%
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=soft -std=c99 '-DPROJECT_CONF_H=1' -DX_NUCLEO_IDS01A4 -DUSE_USART2 -DSTM32F401xE -DUSE_STM32F4XX_NUCLEO -DUSE_HAL_DRIVER '-DHSE_VALUE=84000000ul' -DUSE_STDPERIPH_DRIVER -DNO_EEPROM -DSPIRIT1_ST_SHIELD -DSPIRIT_MODULE -DUSE_SPIRIT1_DEFAULT -DWITH_UIP6 -DIAR_ARM_CM3 -DVECT_TAB_FLASH -DWITH_UIP -DWITH_ASCII '-DCONTIKI=1' '-DUIP_CONF_TCP=1' '-DNETSTACK_CONF_WITH_IPV6=1' '-DUIP_CONF_IPV6_RPL=1' '-DAUTOSTART_ENABLE=1' -I"C:/Users/Giovanni/Desktop/sensor-node-6lowpan/Projects/Multi/Applications/Contiki/sensor-node/Inc" -I"C:/Users/Giovanni/Desktop/sensor-node-6lowpan/Middlewares/ST/Contiki_STM32_Library" -I"C:/Users/Giovanni/Desktop/sensor-node-6lowpan/Middlewares/ST/Contiki_STM32_Library/Inc" -I"C:/Users/Giovanni/Desktop/sensor-node-6lowpan/Middlewares/ST/Contiki_STM32_Library/dev" -I"C:/Users/Giovanni/Desktop/sensor-node-6lowpan/Middlewares/Third_Party/Contiki" -I"C:/Users/Giovanni/Desktop/sensor-node-6lowpan/Middlewares/Third_Party/Contiki/apps/servreg-hack" -I"C:/Users/Giovanni/Desktop/sensor-node-6lowpan/Middlewares/Third_Party/Contiki/core" -I"C:/Users/Giovanni/Desktop/sensor-node-6lowpan/Middlewares/Third_Party/Contiki/core/sys" -I"C:/Users/Giovanni/Desktop/sensor-node-6lowpan/Middlewares/Third_Party/Contiki/core/lib" -I"C:/Users/Giovanni/Desktop/sensor-node-6lowpan/Middlewares/Third_Party/Contiki/core/net" -I"C:/Users/Giovanni/Desktop/sensor-node-6lowpan/Middlewares/Third_Party/Contiki/core/dev" -I"C:/Users/Giovanni/Desktop/sensor-node-6lowpan/Middlewares/Third_Party/Contiki/core/net/ip" -I"C:/Users/Giovanni/Desktop/sensor-node-6lowpan/Middlewares/Third_Party/Contiki/core/net/ipv6" -I"C:/Users/Giovanni/Desktop/sensor-node-6lowpan/Middlewares/Third_Party/Contiki/core/net/llsec" -I"C:/Users/Giovanni/Desktop/sensor-node-6lowpan/Middlewares/Third_Party/Contiki/core/net/rpl" -I"C:/Users/Giovanni/Desktop/sensor-node-6lowpan/Drivers/BSP/STM32F4xx_Nucleo" -I"C:/Users/Giovanni/Desktop/sensor-node-6lowpan/Drivers/BSP/X-NUCLEO-IDS01Ax/Inc" -I"C:/Users/Giovanni/Desktop/sensor-node-6lowpan/Drivers/BSP/Components" -I"C:/Users/Giovanni/Desktop/sensor-node-6lowpan/Drivers/BSP/Components/spirit1/SPIRIT1_Library/Inc" -I"C:/Users/Giovanni/Desktop/sensor-node-6lowpan/Drivers/BSP/Components/spirit1/SPIRIT1_Util/Inc" -I"C:/Users/Giovanni/Desktop/sensor-node-6lowpan/Drivers/CMSIS/Include" -I"C:/Users/Giovanni/Desktop/sensor-node-6lowpan/Drivers/CMSIS/Device/ST/STM32F4xx/Include" -I"C:/Users/Giovanni/Desktop/sensor-node-6lowpan/Drivers/STM32F4xx_HAL_Driver/Inc" -I"C:/Users/Giovanni/Desktop/sensor-node-6lowpan/Drivers/STM32F4xx_HAL_Driver/Inc/Legacy" -I"C:/Users/Giovanni/Desktop/sensor-node-6lowpan/Drivers/BSP/Components/Common" -I"C:/Users/Giovanni/Desktop/sensor-node-6lowpan/Drivers/BSP/Components/hts221" -I"C:/Users/Giovanni/Desktop/sensor-node-6lowpan/Drivers/BSP/Components/lis3mdl" -I"C:/Users/Giovanni/Desktop/sensor-node-6lowpan/Drivers/BSP/Components/lps22hb" -I"C:/Users/Giovanni/Desktop/sensor-node-6lowpan/Drivers/BSP/Components/lps25hb" -I"C:/Users/Giovanni/Desktop/sensor-node-6lowpan/Drivers/BSP/Components/lsm6ds0" -I"C:/Users/Giovanni/Desktop/sensor-node-6lowpan/Drivers/BSP/Components/lsm6ds3" -I"C:/Users/Giovanni/Desktop/sensor-node-6lowpan/Drivers/BSP/Components/lsm6dsl" -I"C:/Users/Giovanni/Desktop/sensor-node-6lowpan/Drivers/BSP/Components/lsm303agr" -I"C:/Users/Giovanni/Desktop/sensor-node-6lowpan/Drivers/BSP/X_NUCLEO_IKS01A2"  -O0 -g3 -Wall -fmessage-length=0 -mno-unaligned-access -Wl,-cref -ffunction-sections -fdata-sections -ffunction-sections -c -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Middlewares/ST/Contiki_STM32_Library/Src/watchdog.o: C:/Users/Giovanni/Desktop/sensor-node-6lowpan/Middlewares/ST/Contiki_STM32_Library/Src/watchdog.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo %cd%
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=soft -std=c99 '-DPROJECT_CONF_H=1' -DX_NUCLEO_IDS01A4 -DUSE_USART2 -DSTM32F401xE -DUSE_STM32F4XX_NUCLEO -DUSE_HAL_DRIVER '-DHSE_VALUE=84000000ul' -DUSE_STDPERIPH_DRIVER -DNO_EEPROM -DSPIRIT1_ST_SHIELD -DSPIRIT_MODULE -DUSE_SPIRIT1_DEFAULT -DWITH_UIP6 -DIAR_ARM_CM3 -DVECT_TAB_FLASH -DWITH_UIP -DWITH_ASCII '-DCONTIKI=1' '-DUIP_CONF_TCP=1' '-DNETSTACK_CONF_WITH_IPV6=1' '-DUIP_CONF_IPV6_RPL=1' '-DAUTOSTART_ENABLE=1' -I"C:/Users/Giovanni/Desktop/sensor-node-6lowpan/Projects/Multi/Applications/Contiki/sensor-node/Inc" -I"C:/Users/Giovanni/Desktop/sensor-node-6lowpan/Middlewares/ST/Contiki_STM32_Library" -I"C:/Users/Giovanni/Desktop/sensor-node-6lowpan/Middlewares/ST/Contiki_STM32_Library/Inc" -I"C:/Users/Giovanni/Desktop/sensor-node-6lowpan/Middlewares/ST/Contiki_STM32_Library/dev" -I"C:/Users/Giovanni/Desktop/sensor-node-6lowpan/Middlewares/Third_Party/Contiki" -I"C:/Users/Giovanni/Desktop/sensor-node-6lowpan/Middlewares/Third_Party/Contiki/apps/servreg-hack" -I"C:/Users/Giovanni/Desktop/sensor-node-6lowpan/Middlewares/Third_Party/Contiki/core" -I"C:/Users/Giovanni/Desktop/sensor-node-6lowpan/Middlewares/Third_Party/Contiki/core/sys" -I"C:/Users/Giovanni/Desktop/sensor-node-6lowpan/Middlewares/Third_Party/Contiki/core/lib" -I"C:/Users/Giovanni/Desktop/sensor-node-6lowpan/Middlewares/Third_Party/Contiki/core/net" -I"C:/Users/Giovanni/Desktop/sensor-node-6lowpan/Middlewares/Third_Party/Contiki/core/dev" -I"C:/Users/Giovanni/Desktop/sensor-node-6lowpan/Middlewares/Third_Party/Contiki/core/net/ip" -I"C:/Users/Giovanni/Desktop/sensor-node-6lowpan/Middlewares/Third_Party/Contiki/core/net/ipv6" -I"C:/Users/Giovanni/Desktop/sensor-node-6lowpan/Middlewares/Third_Party/Contiki/core/net/llsec" -I"C:/Users/Giovanni/Desktop/sensor-node-6lowpan/Middlewares/Third_Party/Contiki/core/net/rpl" -I"C:/Users/Giovanni/Desktop/sensor-node-6lowpan/Drivers/BSP/STM32F4xx_Nucleo" -I"C:/Users/Giovanni/Desktop/sensor-node-6lowpan/Drivers/BSP/X-NUCLEO-IDS01Ax/Inc" -I"C:/Users/Giovanni/Desktop/sensor-node-6lowpan/Drivers/BSP/Components" -I"C:/Users/Giovanni/Desktop/sensor-node-6lowpan/Drivers/BSP/Components/spirit1/SPIRIT1_Library/Inc" -I"C:/Users/Giovanni/Desktop/sensor-node-6lowpan/Drivers/BSP/Components/spirit1/SPIRIT1_Util/Inc" -I"C:/Users/Giovanni/Desktop/sensor-node-6lowpan/Drivers/CMSIS/Include" -I"C:/Users/Giovanni/Desktop/sensor-node-6lowpan/Drivers/CMSIS/Device/ST/STM32F4xx/Include" -I"C:/Users/Giovanni/Desktop/sensor-node-6lowpan/Drivers/STM32F4xx_HAL_Driver/Inc" -I"C:/Users/Giovanni/Desktop/sensor-node-6lowpan/Drivers/STM32F4xx_HAL_Driver/Inc/Legacy" -I"C:/Users/Giovanni/Desktop/sensor-node-6lowpan/Drivers/BSP/Components/Common" -I"C:/Users/Giovanni/Desktop/sensor-node-6lowpan/Drivers/BSP/Components/hts221" -I"C:/Users/Giovanni/Desktop/sensor-node-6lowpan/Drivers/BSP/Components/lis3mdl" -I"C:/Users/Giovanni/Desktop/sensor-node-6lowpan/Drivers/BSP/Components/lps22hb" -I"C:/Users/Giovanni/Desktop/sensor-node-6lowpan/Drivers/BSP/Components/lps25hb" -I"C:/Users/Giovanni/Desktop/sensor-node-6lowpan/Drivers/BSP/Components/lsm6ds0" -I"C:/Users/Giovanni/Desktop/sensor-node-6lowpan/Drivers/BSP/Components/lsm6ds3" -I"C:/Users/Giovanni/Desktop/sensor-node-6lowpan/Drivers/BSP/Components/lsm6dsl" -I"C:/Users/Giovanni/Desktop/sensor-node-6lowpan/Drivers/BSP/Components/lsm303agr" -I"C:/Users/Giovanni/Desktop/sensor-node-6lowpan/Drivers/BSP/X_NUCLEO_IKS01A2"  -O0 -g3 -Wall -fmessage-length=0 -mno-unaligned-access -Wl,-cref -ffunction-sections -fdata-sections -ffunction-sections -c -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


