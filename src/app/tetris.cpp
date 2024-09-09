#include "tetris.hpp"
#include "renderer.hpp"
#include <cstdint>
#include <cstdlib>
#include <cstring>

void Tetris::on_ready() {
	reset_game();
}

void Tetris::on_update(double delta_time) {
	Renderer::clear_back_buffer();

	m_time_passed += delta_time;
	if (m_time_passed > m_move_timer) {
		m_time_passed = 0;
		if (!move_tetromino(m_current, {0,1})) {
			place_current();
			spawn_new();
			m_score++;
		}
	}

	draw_frame();
	copy_to_back_buffer();
	draw_current();

	Renderer::draw_number(m_score, 1,1);
}

void Tetris::draw_frame() {
	vi2 top_left  = { TETRIS_OFFSET_X-1, TETRIS_OFFSET_Y-1 };
	vi2 top_right = { TETRIS_OFFSET_X+TETRIS_WIDTH, TETRIS_OFFSET_Y-1 };

	vi2 bottom_left  = { TETRIS_OFFSET_X-1, TETRIS_OFFSET_Y + TETRIS_HEIGHT };
	vi2 bottom_right = { TETRIS_OFFSET_X+TETRIS_WIDTH, TETRIS_OFFSET_Y + TETRIS_HEIGHT };


	Renderer::draw_line(top_left.x, top_left.y, top_right.x, top_right.y);
	Renderer::draw_line(bottom_left.x, bottom_left.y, bottom_right.x, bottom_right.y);
	Renderer::draw_line(top_right.x, top_right.y, bottom_right.x, bottom_right.y);
	Renderer::draw_line(top_left.x, top_left.y, bottom_left.x, bottom_left.y);
}
void Tetris::draw_current() {
	for (uint8_t block = 0; block < 4; ++block) {
		Renderer::set_pixel(
			TETRIS_OFFSET_X + m_current.position.x + m_current.shape.blocks[block].x,
			TETRIS_OFFSET_Y + m_current.position.y + m_current.shape.blocks[block].y,
			m_current.shape.color
		);
	}
}

void Tetris::reset_game() {
	memset(m_grid, 0, sizeof(m_grid));
	m_move_timer = 1.0f;
	m_score = 0;
	spawn_new();
}

void Tetris::copy_to_back_buffer() {
	for (uint8_t x = 0; x < TETRIS_WIDTH; ++x) {
		for (uint8_t y = 0; y < TETRIS_HEIGHT; ++y) {
			if (m_grid[x][y]) {
				Color c;
				c.value = m_grid[x][y];
				Renderer::set_pixel(x+TETRIS_OFFSET_X, y+TETRIS_OFFSET_Y, c);
			}
		}
	}
}


bool Tetris::is_valid_position(const Tetromino& t) {
	for (uint8_t block = 0; block < 4; ++block) {
		vi2 pos = t.position + t.shape.blocks[block];
		if (pos.y < 0 || pos.x < 0 || pos.y >= TETRIS_HEIGHT || pos.x >= TETRIS_WIDTH) {
			return false;
		}
		if (m_grid[pos.x][pos.y]) {
			return false;
		}
	}
	return true;
}

bool Tetris::move_tetromino(Tetromino& t, vi2 dir) {
	Tetromino nt = t;
	nt.position = t.position + dir;
	if (is_valid_position(nt)) {
		t.position = nt.position;
		return true;
	}
	return false;
}


// NOTE: it must be valid position before calling this
void Tetris::place_current() {
	for (uint8_t block = 0; block < 4; ++block) {
		vi2 pos = m_current.position + m_current.shape.blocks[block];
		m_grid[pos.x][pos.y] = m_current.shape.color.value;
	}
	clear_lines();
}


void Tetris::spawn_new() {
	m_current.position = {TETRIS_WIDTH/2,1};
	m_current.shape = all_shapes[rand()%SHAPE_COUNT];
	if (!is_valid_position(m_current)) {
		reset_game();
	}
}

void Tetris::clear_lines() {
	for (int8_t row = TETRIS_HEIGHT; row > 0; ) {
		bool full = true;
		for (uint8_t col = 0; col < TETRIS_WIDTH; ++col) {
			if (m_grid[col][row]==0) {
				full = false;
				break;
			}
		}

		if (full) {
			for (int8_t y = row; y > 1; --y) {
				for (uint8_t col = 0; col < TETRIS_WIDTH; ++col) {
					m_grid[col][y] = m_grid[col][y-1];
				}
			}
			for (uint8_t col = 0; col < TETRIS_WIDTH; ++col) {
				m_grid[col][0] = 0;
			}
			m_score += 10;
		} else {
			row--;
		}
	}
}




void Tetris::on_event(Event event) {
	if (event.type == Event::Type::Pressed) {
		switch (event.keycode) {
			case 's':
				move_tetromino(m_current, {0,1});
				break;
			case 'a':
				move_tetromino(m_current, {-1,0});
				break;
			case 'd':
				move_tetromino(m_current, {1,0});
				break;
			case 'e':
				m_current.rotate_clockwise();
				if(!is_valid_position(m_current)) {
					m_current.rotate_counter_clockwise();
				}
				break;
			case 'q':
				m_current.rotate_counter_clockwise();
				if(!is_valid_position(m_current)) {
					m_current.rotate_clockwise();
				}
				break;
			case ' ':
				m_move_timer = 0.001f;
				break;
		
		}
	} else if (event.type == Event::Type::Released) {
		switch (event.keycode) {
			case ' ':
				m_move_timer = 1.0f;
				break;
		}
	}
}

