#pragma once
#include "base.hpp"
#include "event.hpp"


class Application {
public:
	Application() {}
	virtual ~Application() {}

	virtual void on_ready() {}
	virtual void on_update() {}
	virtual void on_event(Event event) {}

};

