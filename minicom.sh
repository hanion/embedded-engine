#!/bin/bash

SERIAL_PORT="/dev/ttyUSB0"
BAUD_RATE="115200"

if ! command -v minicom &> /dev/null; then
    echo "minicom could not be found, please install it."
    exit 1
fi

sudo minicom -b $BAUD_RATE -D $SERIAL_PORT

