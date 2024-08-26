#include "rule110.hpp"
#include "renderer.hpp"
#include <string.h>



void Rule110::advance_rule() {
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



void Rule110::copy_to_back_buffer() {
	//static_assert(sizeof((*back_buffer)) == sizeof(rbuffer));
	//memcpy((*back_buffer), rbuffer, sizeof(rbuffer));

	for (uint8_t x = 0; x < WIDTH; ++x) {
		for (uint8_t y = 0; y < HEIGHT; ++y) {
			Renderer::set_pixel_w(x, y, rbuffer[x][y]);
		}
	}
}



void Rule110::on_ready() {
	memset(rbuffer, 0, sizeof(rbuffer));
	rbuffer[WIDTH-1][0] = 1;
}

void Rule110::on_update() {
	Renderer::clear_back_buffer();

	if (++wait_frames > advance_rule_interval) {
		wait_frames = 0;
		advance_rule();
	}

	copy_to_back_buffer();
}



void Rule110::on_event(Event event) {
	if (event.type == Event::Type::Pressed) {
		advance_rule_interval -= 2;
		if (advance_rule_interval < 0) {
			advance_rule_interval = ADVANCE_RULE_INTERVAL_MAX;
		}
	}
}


