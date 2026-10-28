CC = arm-none-eabi-gcc
HW_FLAGS = -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16
CFLAGS = -c -std=c11 -Wall -Wextra
ASM_FLAGS = -x assembler-with-cpp
DEBUG_FLAGS = -O0 -g3 -ffunction-sections -fdata-sections
LINKER_FLAGS = -nostdlib -T STM32F407VGTX_FLASH.ld -Wl,-Map=manual_linker_startup.map


final: output.elf

main.o: main.c
	$(CC) $(HW_FLAGS) $(CFLAGS) $(DEBUG_FLAGS) $^ -o $@
startup_stm32f407vgtx.o: startup_stm32f407vgtx.c
	$(CC) $(HW_FLAGS) $(CFLAGS) $(DEBUG_FLAGS) $^ -o $@

output.elf: main.o startup_stm32f407vgtx.o
	$(CC) $(HW_FLAGS) $(LINKER_FLAGS) $^ -o $@
load: output.elf 
	openocd -f interface/stlink.cfg -f target/stm32f4x.cfg -c "program $^ verify reset exit"
clean:
	rm -f *.o *.map *.elf