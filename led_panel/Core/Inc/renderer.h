/*
 * renderer.h
 *
 *  Created on: Aug 15, 2024
 *      Author: han
 */

#ifndef INC_RENDERER_H_
#define INC_RENDERER_H_

#include "base.h"
#include <stdint.h>




typedef struct {
	int32_t x, y;
	int32_t width, height;
} Rect;

typedef struct {
	uint8_t r, g, b;
} Color;

typedef struct {
	uint8_t x, y;
	Color color;
} Pixel;





extern uint8_t (*front_buffer)[WIDTH][HEIGHT];
extern uint8_t (*back_buffer)[WIDTH][HEIGHT];

extern bool is_back_buffer_new;
void render_buffer(void);
void swap_buffers(void);

void clear_back_buffer(void);
void set_pixel(int x, int y, uint8_t r, uint8_t g, uint8_t b);
void set_pixel_w(int x, int y, uint8_t w);
void set_Pixel(Pixel pixel);


void draw_line(int x0, int y0, int x1, int y1);
void draw_line_colored(int x0, int y0, int x1, int y1, uint8_t r, uint8_t g,uint8_t b);

void draw_rect(uint8_t x, uint8_t y, uint8_t width, uint8_t height, uint8_t r, uint8_t g, uint8_t b);
void draw_Rect(Rect rect, uint8_t r, uint8_t g, uint8_t b);
void Draw_Rect(Rect rect, Color color);

void draw_number(int num, int x, int y, bool bold);
void draw_text(const char *text, int x, int y, bool bold);
const int calculate_text_width(const char* text, bool bold);
const int calculate_number_width(int number, bool bold);

#endif /* INC_RENDERER_H_ */
