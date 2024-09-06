#pragma once

#include "application.hpp"
#include "base.hpp"
#include "color.hpp"
using namespace EE;

enum Block {
	EMPTY = 0,
	SAND, WATER, STONE, FIRE,
	BARRIER
};

class SandSim : public Application {
public:
	SandSim() : Application("SandSim") {}
	virtual ~SandSim() {}

	virtual void on_ready() override final;
	virtual void on_update(double delta_time) override final;
	virtual void on_event(Event event) override final;

private:
	Color get_color(Block block);

	bool is_in_bounds(uint8_t row, uint8_t col);

	Block get(uint8_t row, uint8_t col);
	bool is_empty(uint8_t row, uint8_t col);
	void move(uint8_t row, uint8_t col, uint8_t to_row, uint8_t to_col);
	void swap(uint8_t row, uint8_t col, uint8_t to_row, uint8_t to_col);
	bool move_if_empty(uint8_t row, uint8_t col, uint8_t to_row, uint8_t to_col);
	bool copy(uint8_t row, uint8_t col);
	bool swap_if_water_sink(uint8_t row, uint8_t col, uint8_t to_row, uint8_t to_col);

	void advance_rule();
	void copy_to_back_buffer();
	void clear_grids();

	
	void spawn_at_cursor();
	void spawn_circle_at_cursor();

private:
	uint8_t m_grid    [HEIGHT][WIDTH] = {{Block::EMPTY}};
	uint8_t m_grid_new[HEIGHT][WIDTH] = {{Block::EMPTY}};
	
	uint8_t m_current_row = 0;

	#define ADVANCE_RULE_INTERVAL_MAX 10;
	int8_t m_advance_rule_interval = 0;
	int8_t m_wait_frames = 0;

	struct Cursor {
		int8_t row, col;
		float pos_row, pos_col;
		float speed = 0.6f;
		int8_t radius = 2;
		Block block = Block::SAND;
		void update_pos() { row = (int8_t)pos_row; col = (int8_t)pos_col; }
		void move_up()    { if (row > 0)        { pos_row-=speed; update_pos(); } }
		void move_down()  { if (row+1 < HEIGHT) { pos_row+=speed; update_pos(); } }
		void move_left()  { if (col > 0)        { pos_col-=speed; update_pos(); } }
		void move_right() { if (col+1 < WIDTH)  { pos_col+=speed; update_pos(); } }
	};
	Cursor m_cursor = {16,32, 16.0f, 32.0f};
};

