#pragma once

#include "application.hpp"
using namespace EE;

class Rule110 : public Application {
public:
	Rule110() : Application("Rule110") {}
	virtual ~Rule110() {}

	virtual void on_ready() override final;
	virtual void on_update(double delta_time) override final;
	virtual void on_event(Event event) override final;

private:
	void advance_rule();
	void copy_to_back_buffer();

private:
	uint8_t rbuffer[WIDTH][HEIGHT] = {{0}};
	uint8_t rcurrent_row = 0;

	#define ADVANCE_RULE_INTERVAL_MAX 10;
	int8_t advance_rule_interval = 4;
	int8_t wait_frames = 0;
};

