#pragma once

#include "base.hpp"
#include "math.hpp"
#include <stdint.h>




typedef struct {
	int32_t x, y;
	int32_t width, height;
} Rect;


struct Color {
	uint8_t value;

	Color (uint8_t rgb = 0) {
		set(rgb,rgb,rgb);
	}
	Color(uint8_t r, uint8_t g, uint8_t b) {
		set(r,g,b);
	}

	void set(uint8_t r, uint8_t g, uint8_t b) {
		r = r ? 1 : 0;
		g = g ? 1 : 0;
		b = b ? 1 : 0;
		value = (r << 2) | (g << 1) | b;
	}

	uint8_t r() {
		return value & 0b100;
	}
	uint8_t g() {
		return value & 0b010;
	}
	uint8_t b() {
		return value & 0b001;
	}

};

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
	static void set_pixel(int x, int y, Color color);
	static void set_Pixel(Pixel pixel);

	static void draw_line(int x0, int y0, int x1, int y1);
	static void draw_line_colored(int x0, int y0, int x1, int y1, Color color);

	static void draw_rect(uint8_t x, uint8_t y, uint8_t width, uint8_t height, Color color);
	static void draw_Rect(Rect rect, Color color);

	static void draw_number(int num, int x, int y, bool bold);
	static void draw_text(const char *text, int x, int y, bool bold);
	static const int calculate_text_width(const char* text, bool bold);
	static const int calculate_number_width(int number, bool bold);

private:
	static uint32_t last_render_time;

};







