#!/bin/bash

# clean previous builds
rm -f *.elf *.hex test

if [[ "$1" == "test" ]]; then
    gcc -Wall -Wextra -std=c11 src/logic.c tests/test.c -o test || exit 1
    ./test
    exit 0
fi

# build AVR firmware
avr-gcc -DF_CPU=16000000UL -mmcu=atmega328p -Os -Wall -Wextra -std=c11 \
    src/main.c src/logic.c src/app.c src/hw_avr.c -o main.elf || exit 1

avr-objcopy -O ihex -R .eeprom main.elf main.hex || exit 1

echo "Built: main.elf, main.hex"
