
#include "base.hpp"
#include <stdint.h>
#include "math.h"
#include <stdlib.h>
#include <string.h>

#if cpptest

class TestMessage {
public:
	TestMessage() {
		width = calculate_text_width(str, false);
	}

	void scroll() {
		if (--position < -width) {
			position = WIDTH;
		}
	}

	void draw() {
		draw_text(str, position, 0, false);
	}

private:
	const char* str = "hello from cpp class";
	int position = 64;
	int width;
};



TestMessage tm;
void on_ready() {
	RENDER_INTERVAL_MS = 10;
	TEARING_FIX = true;
}
bool scrol = true;
void on_update() {
	clear_back_buffer();
	tm.draw();
	if (scrol)
	tm.scroll();
}


void on_button_pressed() {
	scrol = !scrol;
}

#endif

