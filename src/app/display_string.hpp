#pragma once

#include "application.hpp"
#include "renderer.hpp"

typedef struct {
	const char* string;
	Rect rect;
	bool bold;
	int dir;
} Message;


class DisplayString : public Application {
public:
	DisplayString() : Application("DisplayString") {}
	virtual ~DisplayString() {}

	virtual void on_ready() override final;
	virtual void on_update(double delta_time) override final;

private:
	void scroll_msg(Message* msg);

private:
	#define MSG_COUNT 2
	Message msgs[MSG_COUNT] = {
		{ "The quick brown fox jumps over the lazy dog.", {0,0,0,8}, false, -1 },
		{ "LLL", {0,16,0,8}, false, -1 }
	};
};

