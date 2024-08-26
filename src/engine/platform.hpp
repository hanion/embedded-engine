#pragma once

#include "base.hpp"
#include "engine.hpp"

class Platform {
public:
	static void poll_events(Engine* engine);
	static uint32_t get_tick();
	static void on_init();
};

