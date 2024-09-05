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

private:
	uint32_t get_tick_delta_time();

private:
	uint32_t m_last_tick_time = 0;
	double m_DeltaTime = 0.0;

	uint8_t m_update_interval_ms = 25;
	Application& m_application;
};

}



