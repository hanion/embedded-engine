#pragma once

struct Event {
	enum class Type {
		Pressed, Held, Released
	};

	Type type;
	int key_id;

	Event(Type type, int key_id) : type(type), key_id(key_id) {}
};
