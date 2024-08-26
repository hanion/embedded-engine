#!/bin/bash

PROGRAMMER_CLI="/home/han/st/STM32CubeProgrammer/bin/STM32_Programmer.sh"
FIRMWARE_PATH="./build_stm/ee-stm.elf"
PORT="SWD"

if [ ! -f "$PROGRAMMER_CLI" ]; then
    echo "Error: STM32_Programmer_CLI not found at $PROGRAMMER_CLI"
    exit 1
fi

$PROGRAMMER_CLI -c port=$PORT --write $FIRMWARE_PATH > /dev/null

if [ $? -ne 0 ]; then
    echo "Error: Firmware flash failed."
    exit 1
fi

$PROGRAMMER_CLI -c port=$PORT -rst > /dev/null

if [ $? -ne 0 ]; then
    echo "Error: Device reset failed."
    exit 1
fi

echo "Flash Done"

