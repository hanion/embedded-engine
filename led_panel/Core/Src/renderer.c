/*
 * renderer.c
 *
 *  Created on: Aug 15, 2024
 *      Author: han
 */

#include "renderer.h"
#include<stdlib.h>
#include<string.h>

uint8_t buffer1[WIDTH][HEIGHT];
uint8_t buffer2[WIDTH][HEIGHT];
uint8_t (*front_buffer)[WIDTH][HEIGHT] = &buffer1;
uint8_t (*back_buffer)[WIDTH][HEIGHT] = &buffer2;
bool is_back_buffer_new = false;

void swap_buffers() {
    uint8_t (*temp)[WIDTH][HEIGHT] = front_buffer;
    front_buffer = back_buffer;
    back_buffer = temp;
}


void clear_back_buffer(void) {
	memset((*back_buffer), 0, sizeof(buffer1));
}

void set_pixel(int x, int y, uint8_t r, uint8_t g, uint8_t b) {
	r = r ? 1 : 0;
    g = g ? 1 : 0;
    b = b ? 1 : 0;
    (*back_buffer)[x][y] = (r << 2) | (g << 1) | b;
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
				uint8_t data_area_1 = (*front_buffer)[segment*4+window][row+block*8];
				uint8_t data_area_2 = (*front_buffer)[segment*4+window][row+block*8 + 16];

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
		if (is_back_buffer_new) {
			swap_buffers();
			is_back_buffer_new = false;
		}
	}
}

// Bresenham's line algorithm
// (https://en.wikipedia.org/wiki/Bresenham's_line_algorithm)
void draw_line(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1) {
	int dx = abs(x1 - x0);
	int sx = (x0 < x1) ? 1 : -1;
	int dy = -abs(y1 - y0);
	int sy = (y0 < y1) ? 1 : -1;
	int error = dx + dy;

	while (1) {
		set_pixel_w(x0, y0, 1);

		if (x0 == x1 && y0 == y1) {
			break;
		}

		int e2 = 2 * error;
		if (e2 >= dy) {
			if (x0 == x1) {
				break;
			}
			error += dy;
			x0 += sx;
		}
		if (e2 <= dx) {
			if (y0 == y1) {
				break;
			}
			error += dx;
			y0 += sy;
		}
	}
}

void draw_rect(uint8_t x, uint8_t y, uint8_t width, uint8_t height, uint8_t r, uint8_t g, uint8_t b) {
	for (uint8_t i = y; i < y + height && i < HEIGHT; ++i) {
		for (uint8_t j = x; j < x + width && j < WIDTH; ++j) {
			set_pixel(j, i, r, g, b);
		}
	}
}
void draw_Rect(Rect rect, uint8_t r, uint8_t g, uint8_t b) {
	draw_rect(rect.x, rect.y, rect.width, rect.height, r, g, b);
}
void Draw_Rect(Rect rect, Color color) {
	draw_Rect(rect, color.r, color.g, color.b);
}


#if 0
const uint8_t number_bitmaps[10][5] = {
    {0b111, 0b101, 0b101, 0b101, 0b111}, // 0
    //{0b010, 0b110, 0b010, 0b010, 0b111}, // 1
	{0b001, 0b001, 0b001, 0b001, 0b001}, // 1
    {0b111, 0b001, 0b111, 0b100, 0b111}, // 2
    {0b111, 0b001, 0b111, 0b001, 0b111}, // 3
    {0b101, 0b101, 0b111, 0b001, 0b001}, // 4
    {0b111, 0b100, 0b111, 0b001, 0b111}, // 5
    {0b111, 0b100, 0b111, 0b101, 0b111}, // 6
    {0b111, 0b001, 0b010, 0b010, 0b010}, // 7
    {0b111, 0b101, 0b111, 0b101, 0b111}, // 8
    {0b111, 0b101, 0b111, 0b001, 0b111}  // 9
};
#endif

const uint8_t number_bitmaps[11][7] = {
	{0x3E, 0x51, 0x49, 0x45, 0x3E}, // 0
	{0x00, 0x42, 0x7F, 0x40, 0x00}, // 1
	{0x62, 0x51, 0x49, 0x49, 0x46}, // 2
	{0x22, 0x41, 0x49, 0x49, 0x36}, // 3
	{0x18, 0x14, 0x12, 0x7F, 0x10}, // 4
	{0x27, 0x45, 0x45, 0x45, 0x39}, // 5
	{0x3E, 0x49, 0x49, 0x49, 0x30}, // 6
	{0x01, 0x01, 0x71, 0x0D, 0x03}, // 7
	{0x36, 0x49, 0x49, 0x49, 0x36}, // 8
	{0x06, 0x49, 0x49, 0x29, 0x1E}  // 9
};
#define FONT_WIDTH 5
#define FONT_HEIGHT 7


void set_pixel_w_bold(int x, int y, uint8_t w) {
	set_pixel_w(x  , y  , w);
	set_pixel_w(x+1, y  , w);
	set_pixel_w(x  , y+1, w);
	set_pixel_w(x+1, y+1, w);
}

void draw_digit(uint8_t num, uint8_t x, uint8_t y, bool bold) {
	if (num > 9) {
		return;
	}

	for (uint8_t col = 0; col < FONT_WIDTH; ++col) {
		uint8_t col_bitmap = number_bitmaps[num][col];

		for (uint8_t row = 0; row < FONT_HEIGHT; ++row) {
			if (col_bitmap & (1 << row)) {
				if (bold) {
					set_pixel_w_bold(x + 2 * col, y + 2 * row, 1);
				} else {
					set_pixel_w(x + col, y + row, 1);
				}
			}
		}
	}
}

void draw_number(int num, uint8_t x, uint8_t y, bool bold) {
	if (num == 0) {
		draw_digit(0, x, y, bold);
		return;
	}

	uint8_t digit_count = 0;
	int tmp = num;
	while (tmp > 0) {
		tmp /= 10;
		digit_count++;
	}

	uint8_t digit_width = bold ? (FONT_WIDTH * 2) : FONT_WIDTH;
	for (int i = digit_count - 1; i >= 0; --i) {
		int digit = num % 10;
		draw_digit(digit, x + i * (digit_width + 1), y, bold);
		num /= 10;
	}
}




