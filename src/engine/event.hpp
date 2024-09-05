#pragma once
#include <cstdint>
#include <vector>

namespace EE {
#define EVENT_QUEUE_MAX 32

struct Event {
	enum class Type {
		NONE, Pressed, Held, Released
	};

	Type type;
	int keycode;

	Event() : type(Type::NONE), keycode(-1) {}
	Event(Type type, int keycode) : type(type), keycode(keycode) {}
};




class EventManager {
public:
	static void enqueue_active_events();
	static void send_events_in_queue(class Engine* engine);
	static void enqueue_event(Event event);

	// creates a pressed event, will repeat held events until deactivated
	static void activate_key(int keycode);
	static void deactivate_key(int keycode);

private:
	static Event event_queue[EVENT_QUEUE_MAX];
	static uint8_t enqueued_event_count;

	static std::vector<int> active_keys;
};

}
