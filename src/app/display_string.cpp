#include "display_string.hpp"
#include "renderer.hpp"


void DisplayString::scroll_msg(Message* msg) {
	Renderer::draw_text(msg->string, msg->rect.x, msg->rect.y, msg->bold);
	msg->rect.x += msg->dir;//DeltaTime * 60;
	if (msg->dir < 0) {
		if (msg->rect.x < -msg->rect.width) {
			msg->rect.x = WIDTH;
		}
	} else {
		if (msg->rect.x > WIDTH) {
			msg->rect.x = -msg->rect.width;
		}
	}
}

void DisplayString::on_ready() {
	// NOTE: 10 fixes double x, but 8th rows are brighter
	Renderer::RENDER_INTERVAL_MS = 10;
	TEARING_FIX = true;
	for (uint8_t i = 0; i < MSG_COUNT; ++i) {
		msgs[i].rect.width = Renderer::calculate_text_width(msgs[i].string, msgs[i].bold);
	}
}


void DisplayString::on_update() {
	Renderer::clear_back_buffer();
	for (uint8_t i = 0; i < MSG_COUNT; ++i) {
		scroll_msg(&msgs[i]);
	}
}
