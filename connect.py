#!/bin/python

import pygame
import serial
import time

pygame.display.init()

ser = serial.Serial(
    port='/dev/ttyUSB0',
    baudrate=115200,
    bytesize=serial.EIGHTBITS,
    parity=serial.PARITY_NONE,
    stopbits=serial.STOPBITS_ONE,
    timeout=1
)

byte_count = 0
def send_key_state(pressed, ascii_code):
    global byte_count;
    state_byte = b'\x01' if pressed else b'\x00'
    if ascii_code < 0:
        return
    if ascii_code > 255:
        return

    ser.write(state_byte)
    time.sleep(0.001)
    ser.write(bytes([ascii_code]))


def main():
    print("Press Esc to exit.")
    screen = pygame.display.set_mode((600, 300))
    pygame.display.set_caption("UART Game Controller")

    key_states = {}

    running = True
    while running:
        for event in pygame.event.get():
            if event.type == pygame.KEYDOWN:
                if event.key == pygame.K_ESCAPE:
                    running = False
                else:
                    ascii_code = event.key
                    if ascii_code not in key_states or not key_states[ascii_code]:
                        send_key_state(True, ascii_code)
                        key_states[ascii_code] = True

            if event.type == pygame.KEYUP:
                ascii_code = event.key
                if ascii_code in key_states and key_states[ascii_code]:
                    send_key_state(False, ascii_code)
                    key_states[ascii_code] = False

    pygame.quit()
    ser.close()

if __name__ == "__main__":
    main()
