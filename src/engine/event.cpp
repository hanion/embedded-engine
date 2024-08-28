#include "event.hpp"
#include "engine.hpp"
#include "platform.hpp"
#include "renderer.hpp"
#include <cassert>

#define ERRORS_HALT 1


Event EventManager::event_queue[EVENT_QUEUE_MAX] = {};
uint8_t EventManager::enqueued_event_count = 0;

std::vector<int> EventManager::active_keys = {};

void EventManager::send_events_in_queue(Engine* engine) {
	for (int i = 0; i < enqueued_event_count; ++i) {
		engine->on_event(event_queue[i]);
	}
	enqueued_event_count = 0;
}

void EventManager::enqueue_event(Event event) {
	event_queue[enqueued_event_count++] = event;
	if (enqueued_event_count == EVENT_QUEUE_MAX) {
		enqueued_event_count = EVENT_QUEUE_MAX - 1;
	}
}



void EventManager::enqueue_active_events() {
	for (int keycode : active_keys) {
		Event new_held_event = Event(Event::Type::Held, keycode);
		enqueue_event(new_held_event);
	}
}


void EventManager::activate_key(int keycode) {
	// TODO: tmp remove, fix the input data issue
	if (keycode == 0 || keycode == 1) {
		return;
	}
	// NOTE: we should never receive key_down twice, without receiving key_up from the same keycode
	if (ERRORS_HALT) {
		for (int key : active_keys) {
			if (key == keycode) {
				while(ERRORS_HALT){
					Renderer::clear_back_buffer();
					Renderer::draw_number(keycode, 32,8);
					Platform::render_buffer();
					Renderer::is_back_buffer_new = true;
				}
			}
		}
	}
	active_keys.push_back(keycode);

	Event new_button_pressed = Event(Event::Type::Pressed, keycode);
	enqueue_event(new_button_pressed);
}


void EventManager::deactivate_key(int keycode) {
	for (uint8_t i = 0; i < active_keys.size(); ++i) {
		if (active_keys[i] == keycode) {
			Event new_button_released = Event(Event::Type::Released, keycode);
			enqueue_event(new_button_released);

			active_keys.erase(active_keys.begin() + i);

			return;
		}
	}

	// NOTE: fail, this should not happen, but happens, fix it
	
	for (uint8_t i = 0; i < active_keys.size(); ++i) {
		Event new_button_released = Event(Event::Type::Released, keycode);
		enqueue_event(new_button_released);
	}
	active_keys.clear();

	while(ERRORS_HALT){
		Renderer::clear_back_buffer();
		Renderer::draw_number(keycode, 32,0);
		Platform::render_buffer();
		Renderer::is_back_buffer_new = true;
	}
}



