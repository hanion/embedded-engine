#pragma once
#include "base.hpp"
#include "event.hpp"


class Application {
public:
	Application(const char* name) : name(name) {}
	virtual ~Application() {}

	virtual void on_ready() {}
	virtual void on_update() {}
	virtual void on_event(Event event) {}

protected:
	const char* name;
};

