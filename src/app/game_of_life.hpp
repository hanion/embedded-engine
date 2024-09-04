#pragma once

#include "application.hpp"

class GameOfLife : public Application {
public:
	GameOfLife() : Application("GameOfLife") {}
	virtual ~GameOfLife() {}

	virtual void on_ready() override final;
	virtual void on_update(double delta_time) override final;
	virtual void on_event(Event event) override final;

private:
	void advance_rule();
	void copy_to_back_buffer();

	void create_r_pentomino(uint8_t x_offset, uint8_t y_offset);
	void create_glider(uint8_t start_x, uint8_t start_y);

private:
	uint8_t grid[WIDTH][HEIGHT] = {{0}};
	uint8_t new_grid[WIDTH][HEIGHT] = {{0}};

	#define ADVANCE_RULE_INTERVAL_MAX 10;
	int8_t advance_rule_interval = 4;
	int8_t wait_frames = 0;
};

