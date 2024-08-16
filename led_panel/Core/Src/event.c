/*
 * event.c
 *
 *  Created on: Aug 16, 2024
 *      Author: han
 */


#include "event.h"
#include "main.h"


static uint8_t is_button_held = 0;

void on_event() {
	if ((HAL_GPIO_ReadPin(BUTTON_GPIO_Port, BUTTON_Pin) == GPIO_PIN_RESET)) {
		if (!is_button_held) {
			is_button_held = 1;
			on_button_pressed();
		} else {
			on_button_held();
		}
	} else {
		if (is_button_held) {
			is_button_held = 0;
			on_button_released();
		}
	}
}
