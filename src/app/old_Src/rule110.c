/*
 * rule110.c
 *
 *  Created on: Aug 21, 2024
 *      Author: han
 */

#include "base.hpp"
#include <math.h>
#include <stdlib.h>
#include <string.h>


#if rule110

uint8_t rbuffer[WIDTH][HEIGHT] = {0};
uint8_t rcurrent_row = 0;


void advance_rule() {
	uint8_t new_row[WIDTH] = {0};

	for (uint8_t i = 0; i < WIDTH; ++i) {
		uint8_t a = (i > 0)       ? rbuffer[i-1][rcurrent_row] : 0;
		uint8_t b =                 rbuffer[i  ][rcurrent_row]    ;
		uint8_t c = (i+1 < WIDTH) ? rbuffer[i+1][rcurrent_row] : 0;

		uint8_t pattern = (a << 2) | (b << 1) | c;
		uint8_t rule = 110;
		new_row[i] = (rule >> pattern) & 1;
	}

	// push new_row
	if (rcurrent_row < HEIGHT-1) {
		rcurrent_row++;
		for (uint8_t i = 0; i < WIDTH; ++i) {
			rbuffer[i][rcurrent_row] = new_row[i];
		}
	}
	else {
		// scroll buffer up
		for (uint8_t x = 0; x < WIDTH; ++x) {
			for (uint8_t y = 0; y < (HEIGHT-1); ++y) {
				rbuffer[x][y] = rbuffer[x][y+1];
			}
		}
		for (uint8_t i = 0; i < WIDTH; ++i) {
			rbuffer[i][HEIGHT-1] = new_row[i];
		}
	}

}
void copy_to_back_buffer() {
	//static_assert(sizeof((*back_buffer)) == sizeof(rbuffer));
	//memcpy((*back_buffer), rbuffer, sizeof(rbuffer));

	for (uint8_t x = 0; x < WIDTH; ++x) {
		for (uint8_t y = 0; y < HEIGHT; ++y) {
			set_pixel_w(x, y, rbuffer[x][y]);
		}
	}
}



void on_ready() {
	memset(rbuffer, 0, sizeof(rbuffer));
	rbuffer[WIDTH-1][0] = 1;
	//rbuffer[31][0] = 1;
}

void on_update() {
	clear_back_buffer();

	advance_rule();

	copy_to_back_buffer();

//	// for fun
//	if (rbuffer[0][HEIGHT-1]) {
//		// scroll buffer up
//		for (uint8_t x = 0; x < WIDTH; ++x) {
//			for (uint8_t y = 0; y < (HEIGHT-1); ++y) {
//				rbuffer[x][y] = rbuffer[x][y+1];
//			}
//		}
//		for (int i = 0; i < WIDTH; ++i) {
//			rbuffer[i][HEIGHT-1] = 0;
//		}
//		rbuffer[WIDTH-1][HEIGHT-1] = 1;
//	}
}



void create_performance_impact() {
#define ARRAY_SIZE 100
#define NUM_ITERATIONS 10
	double *data = (double *)malloc(ARRAY_SIZE * sizeof(double));
	if (data == NULL) {
		exit(EXIT_FAILURE);
	}

	for (int i = 0; i < ARRAY_SIZE; ++i) {
		data[i] = 1.0;
	}
	for (int i = 0; i < NUM_ITERATIONS; ++i) {
		for (int j = 0; j < ARRAY_SIZE; ++j) {
			data[j] = sin(data[j]) * cos(data[j]);
		}
	}
	free(data);
}

void on_button_pressed() {
	create_performance_impact();
}
void on_button_held() {
}
void on_button_released() {
}

#endif

