#pragma once
#include "base.hpp"
#include "event.hpp"
#include <cstdint>

namespace EE {

class Application {
public:
	Application(const char* name);
	virtual ~Application();

	virtual void on_ready();
	virtual void on_update(double delta_time);
	virtual void on_event(Event event);

protected:
	const char* name;
};

}
