/*
 * display_string.c
 *
 *  Created on: Aug 19, 2024
 *      Author: han
 */
#include "base.h"
#include "main.h"


#if display_string




double string_pos_x = 65;
const char* string = "The quick brown fox jumps over the lazy dog.";
int string_size = 0;

double numbers_pos_x = 70;

void on_ready() {
	string_size = calculate_text_width(string, false);
}
void on_update() {
	clear_back_buffer();

	draw_number(1234567890, ceil(numbers_pos_x), 20, false);
	numbers_pos_x -= DeltaTime * 20;
	if (numbers_pos_x < -calculate_number_width(1234567890, false)) {
		numbers_pos_x = 65;
	}

	draw_text(string, string_pos_x, 6, false);
	string_pos_x -= DeltaTime * 40;
	if (string_pos_x < -string_size) {
		string_pos_x = 65;
	}
}



void on_button_pressed() {
}
void on_button_held() {
}
void on_button_released() {
}

#endif
