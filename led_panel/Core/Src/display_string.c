/*
 * display_string.c
 *
 *  Created on: Aug 19, 2024
 *      Author: han
 */
#include "base.h"
#include "main.h"
#include <math.h>
#include <stdlib.h>


#if display_string




typedef struct {
	const char* string;
	Rect rect;
	bool bold;
	int dir;
} Message;


Message msg0 = {
		"LLLL The quick brown fox jumps over the lazy dog. LLLLL", {0,1,0,8}, true, -1
};
Message msg1 = {
		"LLL", {0,16,0,8}, false, 1
};

#define MSG_COUNT 2
Message msgs[MSG_COUNT];


void scroll_msg(Message* msg) {
	draw_text(msg->string, msg->rect.x, msg->rect.y, msg->bold);
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

void on_ready() {
	msgs[0] = msg0;
	msgs[1] = msg1;
	for (uint8_t i = 0; i < MSG_COUNT; ++i) {
		msgs[i].rect.width = calculate_text_width(msgs[i].string, msgs[i].bold);
	}
}
void on_update() {
	clear_back_buffer();
	for (uint8_t i = 0; i < MSG_COUNT; ++i) {
		scroll_msg(&msgs[i]);
	}
}

void create_performance_impact() {
#define ARRAY_SIZE 100
#define NUM_ITERATIONS 10
	double *data = (double *)malloc(ARRAY_SIZE * sizeof(double));
	if (data == NULL) {
		exit(EXIT_FAILURE);
	}

	for (int i = 0; i < ARRAY_SIZE; ++i) {
		data[i] = 1.0;
	}
	for (int i = 0; i < NUM_ITERATIONS; ++i) {
		for (int j = 0; j < ARRAY_SIZE; ++j) {
			data[j] = sin(data[j]) * cos(data[j]);
		}
	}
	free(data);
}

void on_button_pressed() {
	create_performance_impact();
	//buzzer();
}
void on_button_held() {
	//draw_text("LL", 0, 0, true);
}
void on_button_released() {
}

#endif
