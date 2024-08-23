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
bool should_render = false;

void swap_buffers() {
    uint8_t (*temp)[WIDTH][HEIGHT] = front_buffer;
    front_buffer = back_buffer;
    back_buffer = temp;
}


void clear_back_buffer(void) {
	memset((*back_buffer), 0, sizeof(buffer1));
}

void set_pixel(int x, int y, uint8_t r, uint8_t g, uint8_t b) {
	if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT) {
		return;
	}

	r = r ? 1 : 0;
    g = g ? 1 : 0;
    b = b ? 1 : 0;
    (*back_buffer)[x][y] = (r << 2) | (g << 1) | b;
}
void set_pixel_w(int x, int y, uint8_t w) {
	set_pixel(x, y, w, w, w);
}


void get_rgb(uint8_t pixel, uint8_t *r, uint8_t *g, uint8_t *b) {
	*r = (pixel) & 0b100;
	*g = (pixel) & 0b010;
	*b = (pixel) & 0b001;
}

bool TEARING_FIX = false;
uint8_t current_row = 0;
void render_row() {
	uint8_t r, g, b;
	for (uint8_t segment = 0; segment < 16; ++segment) {
		for (int8_t block = 1; block >= 0; --block) {
			for (uint8_t window = 0; window < 4; ++window) {
				uint8_t x = segment*4 + window;
				if (TEARING_FIX) {
					x -= block;
				}
				uint8_t y = current_row + block*8;
				uint8_t data_area_1 = (*front_buffer)[x][y];
				uint8_t data_area_2 = (*front_buffer)[x][y + 16];

				if(TEARING_FIX) {
					if (x >= WIDTH) {
						data_area_1 = 0;
						data_area_2 = 0;
					}
				}


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
	ROW(current_row);
	OE_TIMER_ENABLE;
}


// this is calculating the time between each display refresh
// (time between rendering of 0th rows)
// it does not account for the time it takes to render all rows
// so it should be minimum time of 8 row rendering otherwise this is useless
// FIX: this needs to be set to 10 for scrolling text to not be doubled
uint8_t RENDER_INTERVAL_MS = 0;
uint32_t last_render_time = 0;

void render_buffer() {
	if (current_row == 0) {
		uint32_t tick = HAL_GetTick();
		if (tick - last_render_time < RENDER_INTERVAL_MS) {
			return;
		} else {
			last_render_time = tick;
		}
	}


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
void draw_line(int x0, int y0, int x1, int y1) {
	draw_line_colored(x0, y0, x1, y1, 1, 1, 1);
}
void draw_line_colored(int x0, int y0, int x1, int y1, uint8_t r, uint8_t g,uint8_t b) {
	int dx = abs(x1 - x0);
	int sx = (x0 < x1) ? 1 : -1;
	int dy = -abs(y1 - y0);
	int sy = (y0 < y1) ? 1 : -1;
	int error = dx + dy;

	while (1) {
		set_pixel(x0, y0, r, g, b);

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



const uint8_t text_bitmaps[69][5] = {
    { 0x7E, 0x11, 0x11, 0x11, 0x7E }, // A
    { 0x7F, 0x49, 0x49, 0x49, 0x36 }, // B
    { 0x3E, 0x41, 0x41, 0x41, 0x22 }, // C
    { 0x7F, 0x41, 0x41, 0x22, 0x1C }, // D
    { 0x7F, 0x49, 0x49, 0x49, 0x41 }, // E
    { 0x7F, 0x09, 0x09, 0x09, 0x01 }, // F
    { 0x3E, 0x41, 0x49, 0x49, 0x7A }, // G
    { 0x7F, 0x08, 0x08, 0x08, 0x7F }, // H
    { 0x00, 0x41, 0x7F, 0x41, 0x00 }, // I
    { 0x20, 0x40, 0x41, 0x3F, 0x01 }, // J
    { 0x7F, 0x08, 0x14, 0x22, 0x41 }, // K
    { 0x7F, 0x40, 0x40, 0x40, 0x40 }, // L
    { 0x7F, 0x02, 0x04, 0x02, 0x7F }, // M
    { 0x7F, 0x04, 0x08, 0x10, 0x7F }, // N
    { 0x3E, 0x41, 0x41, 0x41, 0x3E }, // O
    { 0x7F, 0x09, 0x09, 0x09, 0x06 }, // P
    { 0x3E, 0x41, 0x51, 0x21, 0x5E }, // Q
    { 0x7F, 0x09, 0x19, 0x29, 0x46 }, // R
    { 0x46, 0x49, 0x49, 0x49, 0x31 }, // S
    { 0x01, 0x01, 0x7F, 0x01, 0x01 }, // T
    { 0x3F, 0x40, 0x40, 0x40, 0x3F }, // U
    { 0x1F, 0x20, 0x40, 0x20, 0x1F }, // V
    { 0x7F, 0x20, 0x18, 0x20, 0x7F }, // W
    { 0x63, 0x14, 0x08, 0x14, 0x63 }, // X
    { 0x03, 0x04, 0x78, 0x04, 0x03 }, // Y
    { 0x61, 0x51, 0x49, 0x45, 0x43 }, // Z

	{ 0x20, 0x54, 0x54, 0x54, 0x78 },  // a
	{ 0x7F, 0x48, 0x44, 0x44, 0x38 },  // b
	{ 0x38, 0x44, 0x44, 0x44, 0x20 },  // c
	{ 0x38, 0x44, 0x44, 0x48, 0x7F },  // d
	{ 0x38, 0x54, 0x54, 0x54, 0x18 },  // e
	{ 0x08, 0x7E, 0x09, 0x01, 0x02 },  // f
	{ 0x0C, 0x52, 0x52, 0x52, 0x3E },  // g
	{ 0x7F, 0x08, 0x04, 0x04, 0x78 },  // h
	{ 0x00, 0x44, 0x7D, 0x40, 0x00 },  // i
	{ 0x20, 0x40, 0x44, 0x3D, 0x00 },  // j
	{ 0x7F, 0x10, 0x28, 0x44, 0x00 },  // k
	{ 0x00, 0x41, 0x7F, 0x40, 0x00 },  // l
	{ 0x7C, 0x04, 0x18, 0x04, 0x78 },  // m
	{ 0x7C, 0x08, 0x04, 0x04, 0x78 },  // n
	{ 0x38, 0x44, 0x44, 0x44, 0x38 },  // o
	{ 0x7C, 0x14, 0x14, 0x14, 0x08 },  // p
	{ 0x08, 0x14, 0x14, 0x18, 0x7C },  // q
	{ 0x7C, 0x08, 0x04, 0x04, 0x08 },  // r
	{ 0x48, 0x54, 0x54, 0x54, 0x20 },  // s
	{ 0x04, 0x3F, 0x44, 0x40, 0x20 },  // t
	{ 0x3C, 0x40, 0x40, 0x20, 0x7C },  // u
	{ 0x1C, 0x20, 0x40, 0x20, 0x1C },  // v
	{ 0x3C, 0x40, 0x38, 0x40, 0x3C },  // w
	{ 0x44, 0x28, 0x10, 0x28, 0x44 },  // x
	{ 0x0C, 0x50, 0x50, 0x50, 0x3C },  // y
	{ 0x44, 0x64, 0x54, 0x4C, 0x44 },  // z

	{ 0x00, 0x00, 0x00, 0x00, 0x00 }, // SPACE
	{ 0x00, 0x6F, 0x6F, 0x00, 0x00 }, // !
    { 0x0A, 0x0E, 0x00, 0x0A, 0x0E }, // ?
	{ 0x00, 0x60, 0x60, 0x00, 0x00 }, // .
    { 0x00, 0x20, 0x10, 0x08, 0x00 }, // ,
    { 0x00, 0x00, 0x1F, 0x00, 0x00 }, // -
    { 0x00, 0x03, 0x04, 0x03, 0x00 }, // '
	{ 0x3E, 0x51, 0x49, 0x45, 0x3E }, // 0
	{ 0x00, 0x42, 0x7F, 0x40, 0x00 }, // 1
	{ 0x62, 0x51, 0x49, 0x49, 0x46 }, // 2
	{ 0x22, 0x41, 0x49, 0x49, 0x36 }, // 3
	{ 0x18, 0x14, 0x12, 0x7F, 0x10 }, // 4
	{ 0x27, 0x45, 0x45, 0x45, 0x39 }, // 5
	{ 0x3E, 0x49, 0x49, 0x49, 0x30 }, // 6
	{ 0x01, 0x01, 0x71, 0x0D, 0x03 }, // 7
	{ 0x36, 0x49, 0x49, 0x49, 0x36 }, // 8
	{ 0x06, 0x49, 0x49, 0x29, 0x1E }  // 9
};
#define FONT_WIDTH 5
#define FONT_HEIGHT 7


void set_pixel_w_bold(int x, int y, uint8_t w) {
	set_pixel_w(x  , y  , w);
	set_pixel_w(x+1, y  , w);
	set_pixel_w(x  , y+1, w);
	set_pixel_w(x+1, y+1, w);
}

void draw_digit(uint8_t num, int x, int y, bool bold) {
	if (num > 9) {
		return;
	}
	if (x > WIDTH || y > HEIGHT) {
		return;
	}
	if (x < -FONT_WIDTH - FONT_WIDTH*bold || y < -FONT_HEIGHT - FONT_HEIGHT*bold) {
		return;
	}

	for (uint8_t col = 0; col < FONT_WIDTH; ++col) {
		uint8_t col_bitmap = text_bitmaps[num+59][col];

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

void draw_number(int num, int x, int y, bool bold) {
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


void draw_char(char c, int x, int y, bool bold) {
	if (x > WIDTH || y > HEIGHT) {
		return;
	}
	if (x < -FONT_WIDTH - FONT_WIDTH*bold || y < -FONT_HEIGHT - FONT_HEIGHT*bold) {
		return;
	}

	uint8_t index;
	if (c >= 'A' && c <= 'Z') {
		index = c - 'A';
	} else if (c >= 'a' && c <= 'z') {
		index = c - 'a' + 26;
	} else if (c >= '0' && c <= '9') {
		index = c - '0' + 59;
	} else if (c == ' ') {
		index = 52;
	} else if (c == '!') {
		index = 53;
	} else if (c == '?') {
		index = 54;
	} else if (c == '.') {
		index = 55;
	} else if (c == ',') {
		index = 56;
	} else if (c == '-') {
		index = 57;
	} else if (c == '\'') {
		index = 58;
	} else {
		return;
	}

	for (uint8_t col = 0; col < FONT_WIDTH; ++col) {
		uint8_t col_bitmap = text_bitmaps[index][col];

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

void draw_text(const char *text, int x, int y, bool bold) {
	while (*text) {
		draw_char(*text++, x, y, bold);
		x += FONT_WIDTH + 1 + FONT_WIDTH*bold;
	}
}

const int calculate_text_width(const char* text, bool bold) {
	int width = 0;
	uint8_t char_width = bold ? FONT_WIDTH * 2 : FONT_WIDTH;

	while (*text) {
		width += char_width + 1;
		text++;
	}

	return width > 0 ? width - 1 : 0;
}

const int calculate_number_width(int number, bool bold) {
	uint8_t digit_width = FONT_WIDTH;
	int width = 0;

	if (number == 0) {
		width += digit_width + 1;
	} else {
		while (number > 0) {
			width += digit_width + 1 + digit_width*bold;
			number /= 10;
		}
	}
	return width > 0 ? width - 1 : 0;
}





