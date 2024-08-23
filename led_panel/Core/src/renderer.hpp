#pragma once

#include "base.hpp"
#include "math.hpp"
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


class Renderer {
public:
	static uint8_t (*front_buffer)[WIDTH][HEIGHT];
	static uint8_t (*back_buffer)[WIDTH][HEIGHT];
	static bool is_back_buffer_new;
	static uint8_t RENDER_INTERVAL_MS;


	static void render_buffer(void);
	static void swap_buffers(void);


	static void render_row();
	static void clear_back_buffer(void);
	static void set_pixel(int x, int y, uint8_t r, uint8_t g, uint8_t b);
	static void set_pixel_w(int x, int y, uint8_t w);
	static void set_Pixel(Pixel pixel);

	static void draw_line(int x0, int y0, int x1, int y1);
	static void draw_line_colored(int x0, int y0, int x1, int y1, uint8_t r, uint8_t g,uint8_t b);

	static void draw_rect(uint8_t x, uint8_t y, uint8_t width, uint8_t height, uint8_t r, uint8_t g, uint8_t b);
	static void draw_Rect(Rect rect, uint8_t r, uint8_t g, uint8_t b);
	static void Draw_Rect(Rect rect, Color color);

	static void draw_number(int num, int x, int y, bool bold);
	static void draw_text(const char *text, int x, int y, bool bold);
	static const int calculate_text_width(const char* text, bool bold);
	static const int calculate_number_width(int number, bool bold);

private:
	static uint32_t last_render_time;

};







