#include "engine.hpp"
#include "event.hpp"
#include "platform.hpp"
#include "renderer.hpp"

namespace EE {

void Engine::run() {
	Platform::on_init();
	m_application.on_ready();

	double accumulator = 0.0;
	while (1) {
		uint32_t delta = get_tick_delta_time();

		accumulator += delta;
		if (accumulator >= m_update_interval_ms) {
			m_DeltaTime = accumulator / 1000.0;
			accumulator -= m_update_interval_ms;

			Platform::poll_events(this);
			EventManager::enqueue_active_events();
			EventManager::send_events_in_queue(this);

			if (!Renderer::is_back_buffer_new){
				m_application.on_update(m_DeltaTime);
				Renderer::is_back_buffer_new = true;
			}
			// TODO: on_render();
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

