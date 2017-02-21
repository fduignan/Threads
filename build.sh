arm-none-eabi-gcc *.c -mcpu=cortex-m0 -mthumb -g -lgcc -T linker_script.ld -Xlinker --cref -Xlinker -Map -Xlinker main.map -nostartfiles -o main.elf
arm-none-eabi-gcc -S main.c -mcpu=cortex-m0 -mthumb -g -lgcc -T linker_script.ld -Xlinker --cref -Xlinker -Map -Xlinker main.map -nostartfiles -o main.s
# convert binary elf file to hex to help the stm32flash utility
arm-none-eabi-objcopy -O ihex main.elf main.hex
# convert binary elf file to bin for use with mbed virtual disk interface
arm-none-eabi-objcopy -O binary main.elf main.bin
