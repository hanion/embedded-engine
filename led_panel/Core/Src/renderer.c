/*
 * renderer.c
 *
 *  Created on: Aug 15, 2024
 *      Author: han
 */

#include "renderer.h"


uint8_t buffer[WIDTH][HEIGHT];


void clear_buffer(void) {
    for (int x = 0; x < WIDTH; x++) {
        for (int y = 0; y < HEIGHT; y++) {
            buffer[x][y] = 0;
        }
    }
}

void set_pixel(int x, int y, uint8_t r, uint8_t g, uint8_t b) {
	r = r ? 1 : 0;
    g = g ? 1 : 0;
    b = b ? 1 : 0;
    buffer[x][y] = (r << 2) | (g << 1) | b;
}
void set_pixel_w(int x, int y, uint8_t w) {
	set_pixel(x, y, w, w, w);
}

void get_rgb(uint8_t pixel, uint8_t *r, uint8_t *g, uint8_t *b) {
	*r = (pixel >> 2) & 0x01;
	*g = (pixel >> 1) & 0x01;
	*b = (pixel     ) & 0x01;
}

uint8_t current_row = 0;
void render_row() {
	uint8_t row = current_row;
	for (int segment = 0; segment < 16; ++segment) {
		for (int block = 1; block >= 0; --block) {
			for (int window = 0; window < 4; ++window) {
				uint8_t data_area_1 = buffer[segment*4+window][row+block*8];
				uint8_t data_area_2 = buffer[segment*4+window][row+block*8 + 16];

				uint8_t r, g, b;

				get_rgb(data_area_1, &r, &g, &b);
				R1(r);
				G1(g);
				B1(b);

				get_rgb(data_area_2, &r, &g, &b);
				R2(r);
				G2(g);
				B2(b);

				CLK_H;
				CLK_L;
			}
		}
	}

	OE_TIMER_DISABLE;
	LAT_H;
	LAT_L;
	ROW(row);
	OE_TIMER_ENABLE;
}

void render_buffer() {
	render_row();
	if (++current_row == 8) {
		current_row = 0;
	}
}

