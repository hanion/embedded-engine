#include "engine.hpp"
#include "event.hpp"
#include "platform.hpp"
#include "renderer.hpp"
#include <iostream>
#include <thread>

#define DEBUG_PRINT_FRAME 0

namespace EE {

void Engine::stop() {
	m_stop = true;
}

void Engine::run() {
	Platform::on_init();
	m_application.on_ready();

	double accumulator = 0.0;
	while (!m_stop) {
		uint32_t delta = get_tick_delta_time();

		accumulator += delta;
		if (accumulator >= m_update_interval_ms) {
			//m_DeltaTime = m_update_interval_ms / 1000.0;

			Platform::poll_events(this);
			EventManager::enqueue_active_events();
			EventManager::send_events_in_queue(this);

			if (!Renderer::is_back_buffer_new){
				m_application.on_update(m_DeltaTime);
				Renderer::is_back_buffer_new = true;
				Platform::on_render();
				m_frame++;
			}
#if DEBUG_PRINT_FRAME
			printf("frame %zu: acc=%f\n", m_frame, accumulator);
			std::cout << std::flush;
#endif
			accumulator = 0;
		} else {
			uint32_t time_until_next_frame = std::floor((m_update_interval_ms - accumulator)/2.0);
			std::this_thread::sleep_for(std::chrono::milliseconds(time_until_next_frame));
		}
	}
}




uint32_t Engine::get_tick_delta_time() {
    uint32_t current_time = Platform::get_tick();
    uint32_t tick_delta_time = current_time - m_last_tick_time;
    m_last_tick_time = current_time;
    return tick_delta_time;
}

void Engine::on_event(Event event) {
	m_application.on_event(event);
}

}

