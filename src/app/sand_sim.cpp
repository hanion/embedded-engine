#include "sand_sim.hpp"
#include "base.hpp"
#include "renderer.hpp"
#include <cstring>

static uint8_t RANDOMNESS = 1;

void SandSim::on_ready() {
	clear_grids();
}
void SandSim::on_update(double delta_time) {
	Renderer::clear_back_buffer();

	if (++m_wait_frames > m_advance_rule_interval) {
		m_wait_frames = 0;
		advance_rule();
		memcpy(m_grid, m_grid_new, sizeof(m_grid));
	}

	copy_to_back_buffer();

	Renderer::set_pixel(m_cursor.col, m_cursor.row, get_color(m_cursor.block));

	// draw pen
	uint8_t pen_length = 1;
	if (m_cursor.radius < 3) {
		pen_length = m_cursor.radius+1;
	} else {
		pen_length = 3;
	}
	for (uint8_t i = 0; i < pen_length; ++i) {
		Renderer::set_pixel(m_cursor.col+1+i, m_cursor.row+1+i, Color(1,0,1));
	}
}

void SandSim::copy_to_back_buffer() {
	for (uint8_t y = 0; y < HEIGHT; ++y) {
		for (uint8_t x = 0; x < WIDTH; ++x) {
			Renderer::set_pixel(x, y, get_color(get(y,x)));
		}
	}
}
void SandSim::clear_grids() {
	static_assert(sizeof(m_grid) == sizeof(m_grid_new), "");
	memset(m_grid, 0, sizeof(m_grid));
	memset(m_grid_new, 0, sizeof(m_grid));
}

Color SandSim::get_color(Block block) {
	switch (block) {
		case Block::EMPTY:   return Color(0,0,0);
		case Block::SAND:    return Color(1,1,0);
		case Block::WATER:   return Color(0,0,1);
		case Block::STONE:   return Color(0,1,1);
		case Block::FIRE:    return Color(1,0,0);
		case Block::BARRIER: return Color(1,0,1);
	}
}

bool SandSim::is_in_bounds(uint8_t row, uint8_t col) {
	return row >= 0 && col >= 0 && row < HEIGHT && col < WIDTH;
}

Block SandSim::get(uint8_t row, uint8_t col) {
	if (is_in_bounds(row, col)) {
		return (Block)m_grid[row][col];
	}
	return Block::BARRIER;
}
bool SandSim::is_empty(uint8_t row, uint8_t col) {
	return (get(row, col) == Block::EMPTY) && (Block::EMPTY == (Block)m_grid_new[row][col]);
}
void SandSim::move(uint8_t row, uint8_t col, uint8_t to_row, uint8_t to_col) {
	if (!is_in_bounds(row, col) || !is_in_bounds(to_row, to_col)) { return; }
	m_grid_new[to_row][to_col] = m_grid[row][col];
	m_grid_new[row][col] = Block::EMPTY;
}
void SandSim::swap(uint8_t row, uint8_t col, uint8_t to_row, uint8_t to_col) {
	if (!is_in_bounds(row, col) || !is_in_bounds(to_row, to_col)) { return; }
	m_grid_new[row][col] = m_grid[to_row][to_col];
	m_grid_new[to_row][to_col] = m_grid[row][col];
	m_grid[row][col] = m_grid_new[row][col];
	m_grid[to_row][to_col] = m_grid_new[to_row][to_col];
}

bool SandSim::move_if_empty(uint8_t row, uint8_t col, uint8_t to_row, uint8_t to_col) {
	if (is_empty(to_row, to_col)) {
		move(row, col, to_row, to_col);
		return true;
	}
	return false;
}
bool SandSim::swap_if_water_sink(uint8_t row, uint8_t col, uint8_t to_row, uint8_t to_col) {
	if (get(to_row, to_col) == Block::WATER) {
		swap(row,col, to_row,to_col);
		return true;
	}
	return false;
}
bool SandSim::copy(uint8_t row, uint8_t col) {
	m_grid_new[row][col] = m_grid[row][col];
	return true;
}

void SandSim::advance_rule() {
	for (uint8_t row = 0; row < HEIGHT; ++row) {
		for (uint8_t c = 0; c < WIDTH; ++c) {
			int8_t col = c;
			if (row%2) {
				col = WIDTH - c - 1;
			}

			int8_t dir = 1;
			if (RANDOMNESS && rand()%2) {
				dir = -1;
			}

			uint8_t down  = row+1;
			uint8_t right = col+dir;
			uint8_t left  = col-dir;

			switch (get(row,col)) {
				case Block::STONE:
					copy(row, col);
					break;
				case Block::SAND:
					move_if_empty(row, col, down, col)   ||
						swap_if_water_sink(row, col, down, col) ||
						move_if_empty(row, col, down, right) ||
						swap_if_water_sink(row, col, down, right) ||
						move_if_empty(row, col, down, left)  ||
						swap_if_water_sink(row, col, down, left) ||
						copy(row, col);
					break;
				case Block::WATER:
					move_if_empty(row, col, down, col)   ||
						move_if_empty(row, col, down, right) ||
						move_if_empty(row, col, down, left)  ||
						move_if_empty(row, col, row, right) ||
						move_if_empty(row, col, row, left) ||
						move_if_empty(row, col, row, col+1*dir) ||
						move_if_empty(row, col, row, col+2*dir) ||
						copy(row, col);
					break;
				case Block::FIRE:
					break;
				case Block::BARRIER:
					break;
				case Block::EMPTY:
					break;
			
			}
		}
	}

	memcpy(m_grid, m_grid_new, WIDTH * HEIGHT * sizeof(uint8_t));
}



void SandSim::spawn_at_cursor() {
	if (is_in_bounds(m_cursor.row, m_cursor.col)) {
		m_grid[m_cursor.row][m_cursor.col] = m_cursor.block;
		m_grid_new[m_cursor.row][m_cursor.col] = m_cursor.block;
	}
}
void SandSim::spawn_circle_at_cursor() {
	if (m_cursor.radius == 0) {
		spawn_at_cursor();
		return;
	}

	static const int prob = 60;
	for (int y = -m_cursor.radius; y <= m_cursor.radius; ++y) {
		for (int x = -m_cursor.radius; x <= m_cursor.radius; ++x) {
			if (x * x + y * y <= m_cursor.radius * m_cursor.radius) {
				if ((!RANDOMNESS) || rand() % 100 < prob) {
					uint8_t col = (m_cursor.col + x);
					uint8_t row = (m_cursor.row + y);
					if (is_in_bounds(row, col)) {
							m_grid[row][col] = m_cursor.block;
							m_grid_new[row][col] = m_cursor.block;
					}
				}
			}
		}
	}
}



void SandSim::on_event(Event event) {
	if (event.type == Event::Type::Released) {
		switch (event.keycode) {
			case 'i':
				m_cursor.speed = 0.8f;
				break;
		}
		return;
	} else if (event.type == Event::Type::Pressed) {
		switch (event.keycode) {
			case 'e':
				m_cursor.radius++;
				break;
			case 'q':
				if (m_cursor.radius > 0) {
					m_cursor.radius--;
				}
				break;
			case 'f':
				switch (m_cursor.block) {
					case Block::SAND:  m_cursor.block = Block::WATER; break;
					case Block::WATER: m_cursor.block = Block::STONE; break;
					case Block::STONE: m_cursor.block = Block::EMPTY; break;
					case Block::EMPTY: m_cursor.block = Block::SAND;  break;
					default: break;
				}
				break;
			case '\n':
				m_advance_rule_interval -= 2;
				if (m_advance_rule_interval < 0) {
					m_advance_rule_interval = ADVANCE_RULE_INTERVAL_MAX;
				}
				break;
			case 'p':
				clear_grids();
				break;
			case 'o':
				RANDOMNESS = 1 - RANDOMNESS;
				break;
			case 'i':
				m_cursor.speed = 0.1f;
				break;
		}
	}


	switch (event.keycode) {
		case ' ':
			spawn_circle_at_cursor();
			break;
		case 'k':
		case 'w':
			m_cursor.move_up();
			break;
		case 'j':
		case 's':
			m_cursor.move_down();
			break;
		case 'h':
		case 'a':
			m_cursor.move_left();
			break;
		case 'l':
		case 'd':
			m_cursor.move_right();
			break;
		default:
			break;
	}
}





