################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include Src/subdir.mk
-include Middlewares/Third_Party/Contiki/core/sys/subdir.mk
-include Middlewares/Third_Party/Contiki/core/net/rpl/subdir.mk
-include Middlewares/Third_Party/Contiki/core/net/mac/subdir.mk
-include Middlewares/Third_Party/Contiki/core/net/llsec/subdir.mk
-include Middlewares/Third_Party/Contiki/core/net/ipv6/multicast/subdir.mk
-include Middlewares/Third_Party/Contiki/core/net/ipv6/subdir.mk
-include Middlewares/Third_Party/Contiki/core/net/ip/subdir.mk
-include Middlewares/Third_Party/Contiki/core/net/subdir.mk
-include Middlewares/Third_Party/Contiki/core/lib/subdir.mk
-include Middlewares/Third_Party/Contiki/core/dev/subdir.mk
-include Middlewares/Third_Party/Contiki/apps/servreg-hack/subdir.mk
-include Middlewares/ST/Contiki_STM32_Library/dev/subdir.mk
-include Middlewares/ST/Contiki_STM32_Library/Src/subdir.mk
-include Drivers/STM32F4xx_HAL_Driver/Src/subdir.mk
-include Drivers/CMSIS/Device/ST/STM32F4xx/Source/Templates/gcc/subdir.mk
-include Drivers/CMSIS/Device/ST/STM32F4xx/Source/Templates/subdir.mk
-include Drivers/BSP/X_NUCLEO_IKS01A2/subdir.mk
-include Drivers/BSP/X-NUCLEO-IDS01Ax/Src/subdir.mk
-include Drivers/BSP/STM32F4xx_Nucleo/subdir.mk
-include Drivers/BSP/Components/spirit1/SPIRIT1_Library/Src/subdir.mk
-include Drivers/BSP/Components/lsm6dsl/subdir.mk
-include Drivers/BSP/Components/lsm6ds3/subdir.mk
-include Drivers/BSP/Components/lsm6ds0/subdir.mk
-include Drivers/BSP/Components/lsm303agr/subdir.mk
-include Drivers/BSP/Components/lps25hb/subdir.mk
-include Drivers/BSP/Components/lps22hb/subdir.mk
-include Drivers/BSP/Components/lis3mdl/subdir.mk
-include Drivers/BSP/Components/hts221/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: STM32F4xx-Nucleo-Udp_sender.elf

# Tool invocations
STM32F4xx-Nucleo-Udp_sender.elf: $(OBJS) $(USER_OBJS) ../STM32F401RE_FLASH.ld
	@echo 'Building target: $@'
	@echo 'Invoking: MCU GCC Linker'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=soft -specs=nano.specs -T"../STM32F401RE_FLASH.ld" -Wl,-Map=output.map -Wl,--gc-sections -lm -o "STM32F4xx-Nucleo-Udp_sender.elf" @"objects.list" $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '
	$(MAKE) --no-print-directory post-build

# Other Targets
clean:
	-$(RM) *
	-@echo ' '

post-build:
	-@echo 'Generating binary and Printing size information:'
	arm-none-eabi-objcopy -O binary "STM32F4xx-Nucleo-Udp_sender.elf" "STM32F4xx-Nucleo-Udp_sender.bin"
	arm-none-eabi-size "STM32F4xx-Nucleo-Udp_sender.elf"
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY: post-build

-include ../makefile.targets
