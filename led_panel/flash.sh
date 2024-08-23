#!/bin/bash

PROGRAMMER_CLI="/home/han/st/STM32CubeProgrammer/bin/STM32_Programmer.sh"
#FIRMWARE_PATH="/home/han/dev/2024/stm32/testing/led_panel/Release/led_panel.elf"
FIRMWARE_PATH="./build/ee-new.elf"
PORT="SWD"

# Check if STM32_Programmer_CLI exists
if [ ! -f "$PROGRAMMER_CLI" ]; then
    echo "Error: STM32_Programmer_CLI not found at $PROGRAMMER_CLI"
    exit 1
fi

$PROGRAMMER_CLI -c port=$PORT --write $FIRMWARE_PATH > /dev/null

if [ $? -ne 0 ]; then
    echo "Error: Firmware flash failed."
    exit 1
fi

# Reset the device (optional)
$PROGRAMMER_CLI -c port=$PORT -rst > /dev/null

if [ $? -ne 0 ]; then
    echo "Error: Device reset failed."
    exit 1
fi

echo "Done"

#sudo stm32flash -w ./build/ee-new.elf -v -g 0x0 /dev/stlinkv2_2

