#pragma once

#include "base.hpp"
#include "event.hpp"
#include "application.hpp"
#include <cstdint>

namespace EE {

class Engine {
public:
	Engine(Application& app) : m_application(app) {}

	void run();
	void on_event(Event event);

	void stop();

private:
	uint32_t get_tick_delta_time();

private:
	uint8_t m_update_interval_ms = 25;

	uint32_t m_last_tick_time = 0;
	double m_DeltaTime = m_update_interval_ms / 1000.0;

	bool m_stop = false;

	size_t m_frame = 0;

	Application& m_application;
};

}



