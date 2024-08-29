#pragma once
#include "base.hpp"

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
		return (value & 0b100) >> 2;
	}
	uint8_t g() {
		return (value & 0b010) >> 1;
	}
	uint8_t b() {
		return value & 0b001;
	}

};
