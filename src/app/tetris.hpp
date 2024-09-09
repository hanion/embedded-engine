#pragma once
#include "application.hpp"
#include "vector.hpp"
#include "color.hpp"
using namespace EE;

#define TETRIS_WIDTH 10
#define TETRIS_HEIGHT 20

#define TETRIS_OFFSET_Y 6
#define TETRIS_OFFSET_X 27

#define SHAPE_COUNT 7

struct Shape {
	vi2 blocks[4];
	vf2 start_offset = { 0, 0 };
	Color color;
};

struct Tetromino {
	Shape shape;
	vi2 position;

	void rotate_clockwise() {
		for (int i = 0; i < 4; i++) {
			int x = shape.blocks[i].x;
			int y = shape.blocks[i].y;
			shape.blocks[i].x = -y;
			shape.blocks[i].y = x;
		}
	}
	void rotate_counter_clockwise() {
		for (int i = 0; i < 4; i++) {
			int x = shape.blocks[i].x;
			int y = shape.blocks[i].y;
			shape.blocks[i].x = y;
			shape.blocks[i].y = -x;
		}
	}
};

static Shape shape_l = {
	.blocks = { {0,-1}, {0,0}, {0,1}, {1,1} },
	.color = {1,0,0}
};
static Shape shape_j = {
	.blocks = { {0,-1}, {0,0}, {0,1}, {-1,1} },
	.color = {0,0,1}
};
static Shape shape_s = {
	.blocks = { {0,-1}, {0,0}, {1,0}, {1,1} },
	.color = {0,1,0}
};
static Shape shape_z = {
	.blocks = { {0,-1}, {0,0}, {-1,0}, {-1,1} },
	.color = {1,0,0}
};
static Shape shape_t = {
	.blocks = { {0,-1}, {0,0}, {-1,0}, {1,0} },
	.color = {1,0,1}
};
static Shape shape_o = {
	.blocks = { {0,-1}, {0,0}, {-1,-1}, {-1,0} },
	.color = {1,1,0}
};
static Shape shape_i = {
	.blocks = { {0,-1}, {0,0}, {0,1}, {0,2} },
	.color = {0,1,1}
};

static Shape all_shapes[7] = {
	shape_l, shape_j, shape_s, shape_z, shape_t, shape_o, shape_i
};



class Tetris : public Application {
public:
	Tetris() : Application("Tetris") {}
	virtual ~Tetris() {}

	virtual void on_ready() override final;
	virtual void on_update(double delta_time) override final;
	virtual void on_event(Event event) override final;

private:

	void reset_game();
	void draw_frame();
	void draw_current();
	void copy_to_back_buffer();

	bool is_valid_position(const Tetromino& t);
	bool move_tetromino(Tetromino& t, vi2 dir);
	void place_current();
	void spawn_new();

	void clear_lines();

private:
	double m_delta_time = 0.01f;
	float m_time_passed = 0.0f;
	float m_move_timer = 1.0f;

	uint m_score = 0;

	uint8_t m_grid[TETRIS_WIDTH][TETRIS_HEIGHT] = {{0}};

	Tetromino m_current = {};
};

