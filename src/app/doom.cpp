#include "doom.hpp"
#include "base.hpp"
#include "math.hpp"
#include "renderer.hpp"
#include <cmath>

#define RAY_MAX_DISTANCE 100

#define MAP_WIDTH 16
#define MAP_HEIGHT 16

uint8_t map[MAP_HEIGHT][MAP_WIDTH] = {
	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 1, 4, 2, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1},
	{1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1},
	{1, 0, 1, 0, 1, 1, 1, 1, 4, 4, 0, 0, 1, 0, 0, 1},
	{1, 0, 1, 0, 1, 0, 0, 0, 4, 4, 0, 0, 1, 0, 0, 1},
	{1, 0, 1, 0, 1, 1, 1, 0, 0, 0, 0, 0, 1, 0, 0, 1},
	{1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 2, 2, 1, 0, 0, 1},
	{1, 0, 1, 1, 1, 0, 1, 0, 0, 1, 2, 2, 1, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1},
	{1, 1, 1, 1, 1, 0, 1, 0, 0, 0, 0, 0, 1, 1, 1, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
};

float depth_buffer[WIDTH];

#define TEXTURE_WIDTH 16
#define TEXTURE_HEIGHT 16
uint8_t circle_texture[TEXTURE_HEIGHT][TEXTURE_WIDTH] = {
	{0, 0, 0, 0, 0, 5, 5, 5, 5, 5, 5, 0, 0, 0, 0, 0},
	{0, 0, 0, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 0, 0, 0},
	{0, 0, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 0, 0},
	{0, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 0},
	{0, 5, 5, 5, 5, 8, 8, 5, 5, 8, 8, 5, 5, 5, 5, 0},
	{5, 5, 5, 5, 5, 8, 8, 5, 5, 8, 8, 5, 5, 5, 5, 5},
	{5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5},
	{5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5},
	{5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5},
	{5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5},
	{5, 5, 5, 5, 5, 8, 8, 8, 8, 8, 8, 5, 5, 5, 5, 5},
	{0, 5, 5, 5, 5, 8, 8, 8, 8, 8, 8, 5, 5, 5, 5, 0},
	{0, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 0},
	{0, 0, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 0, 0},
	{0, 0, 0, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 0, 0, 0},
	{0, 0, 0, 0, 0, 5, 5, 5, 5, 5, 5, 0, 0, 0, 0, 0}
};

struct raycast_result {
	bool successful = false;
	vf2 intersection;
	float distance;
	int map_value;
	bool side;
};

raycast_result cast_ray(vf2 ray_start, vf2 ray_dir) {
	raycast_result result;

	vf2 ray_unit_step_size = {
		std::sqrt(1+ (ray_dir.y/ray_dir.x) * (ray_dir.y/ray_dir.x)),
		std::sqrt(1+ (ray_dir.x/ray_dir.y) * (ray_dir.x/ray_dir.y))
	};

	vi2 map_check = { int(ray_start.x), int(ray_start.y) };
	vf2 ray_length_1d;
	vi2 step;

	if (ray_dir.x < 0) {
		step.x = -1;
		ray_length_1d.x = ray_unit_step_size.x * (ray_start.x - float(map_check.x));
	} else {
		step.x = 1;
		ray_length_1d.x = ray_unit_step_size.x * (float(map_check.x+1) - ray_start.x);
	}
	if (ray_dir.y < 0) {
		step.y = -1;
		ray_length_1d.y = ray_unit_step_size.y * (ray_start.y - float(map_check.y));
	} else {
		step.y = 1;
		ray_length_1d.y = ray_unit_step_size.y * (float(map_check.y+1) - ray_start.y);
	}

	float distance = 0.0f;
	while (distance < RAY_MAX_DISTANCE) {
		if (ray_length_1d.x < ray_length_1d.y) {
			map_check.x += step.x;
			distance = ray_length_1d.x;
			ray_length_1d.x += ray_unit_step_size.x;
			result.side = true;
		} else {
			map_check.y += step.y;
			distance = ray_length_1d.y;
			ray_length_1d.y += ray_unit_step_size.y;
			result.side = false;
		}

		if (map_check.x < 0 || map_check.y < 0 || map_check.x >= MAP_WIDTH || map_check.y >= MAP_HEIGHT) {
			continue;
		}

		result.map_value = map[map_check.y][map_check.x];
		if (result.map_value) {
			result.successful = true;
			result.distance = distance;
			result.intersection = ray_start + ray_dir * distance;
			return result;
		}
	}
	return {};
}

void draw_edges(int x, float line_height, const Color& color) {
	float wall_top    = HEIGHT / 2.0f - line_height / 2.0f;
	float wall_bottom = HEIGHT / 2.0f + line_height / 2.0f;
	Renderer::set_pixel(x, wall_top, color);
	Renderer::set_pixel(x, wall_bottom, color);
}

void draw_filled(int x, float line_height, const Color& color) {
	if (line_height > HEIGHT) {
		line_height = HEIGHT;
	}
	for (int y = 0; y < line_height; ++y) {
		Renderer::set_pixel(x, y + (HEIGHT/2.0f-line_height/2.0f), color);
	}
}


void Doom::draw_sprite(vf2 sprite) {
	vf2 relative_position = sprite - player;

	vf2 transformed_position = {
		relative_position.x * player_dir.y - relative_position.y * player_dir.x,
		relative_position.x * player_dir.x + relative_position.y * player_dir.y
	};

	if (transformed_position.y < 0.4f) {
		return;
	}

	float screen_x = (WIDTH / 2.0f) * (1 - transformed_position.x / transformed_position.y);
	float sprite_size = HEIGHT / transformed_position.y;

	int sprite_left = static_cast<int>(screen_x - sprite_size / 2);
	int sprite_right = static_cast<int>(screen_x + sprite_size / 2);

	for (int x = sprite_left; x < sprite_right; ++x) {
		if (x >= 0 && x < WIDTH) {
			float tex_x = (x - sprite_left) / sprite_size * TEXTURE_WIDTH;
			tex_x = std::min(std::max(tex_x, 0.0f), static_cast<float>(TEXTURE_WIDTH - 1));

			if (transformed_position.y < depth_buffer[x]) {
				for (int y = 0; y < sprite_size; ++y) {
					int screen_y = static_cast<int>(HEIGHT / 2.0f - sprite_size / 2 + y);
					if (screen_y >= 0 && screen_y < HEIGHT) {
						float tex_y = y / sprite_size * TEXTURE_HEIGHT;
						tex_y = std::min(std::max(tex_y, 0.0f), static_cast<float>(TEXTURE_HEIGHT - 1));

						uint8_t tex_color = circle_texture[static_cast<int>(tex_y)][static_cast<int>(tex_x)];
						if (tex_color) {
							Color color;
							color.value = tex_color;
							Renderer::set_pixel(x, screen_y, color);
						}
					}
				}
			}
		}
	}
}




void Doom::on_ready() {}
void Doom::on_update() {
	Renderer::clear_back_buffer();

	vf2 ray_dir = player_dir.normalized().rotated_z(-m_view_degree/2.0f);
	for (int ray = 0; ray < 64; ray++) {
		ray_dir = ray_dir.rotated_z(m_view_degree/64.0f);

		raycast_result result = cast_ray(player, ray_dir);
		if (result.successful) {
			float line_height = m_wall_height/(result.distance * player_dir.dot(ray_dir));
			depth_buffer[ray] = result.distance;

			Color color;
			color.value = result.map_value;
			if (result.side) {
				color.value+=2;
			}
			draw_filled(ray, line_height, color);
		}
	}
	draw_sprite(test_sprite);
// 	Renderer::draw_number(m_view_degree, 0,0);
// 	Renderer::draw_number(m_wall_height, 0,8);
}



bool collision(vf2 pos) {
	if (pos.x < 0 || pos.x >= MAP_WIDTH || pos.y < 0 || pos.y >= MAP_HEIGHT) {
		return true;
	}

	if (map[int(pos.y)][int(pos.x)]) {
		return true;
	}

	return false;
}

void Doom::on_event(Event event) {
	if (event.type == Event::Type::Released) {
		return;
	}

	vf2 new_pos = player;
	switch (event.keycode) {
		case 'w':
			new_pos += player_dir * m_speed;
			break;
		case 's':
			new_pos -= player_dir * m_speed;
			break;
		case 'a':
			new_pos.x += player_dir.y * m_speed;
			new_pos.y -= player_dir.x * m_speed;
			break;
		case 'd':
			new_pos.x -= player_dir.y * m_speed;
			new_pos.y += player_dir.x * m_speed;
			break;
		case 'j':
			player_dir = player_dir.rotated_z(-m_rotation_speed);
			break;
		case 'l':
			player_dir = player_dir.rotated_z(m_rotation_speed);
			break;
		case 'x':
			m_view_degree += 0.1f;
			break;
		case 'z':
			m_view_degree -= 0.1f;
			break;
		case 'i':
			m_wall_height += 0.1f;
			break;
		case 'k':
			m_wall_height -= 0.1f;
			break;
		default:
			break;
	}

	if (new_pos != player) {
		if (!collision(new_pos)) {
			player = new_pos;
		} else if (!collision({new_pos.x, player.y})) {
			player.x = new_pos.x;
		} else if (!collision({player.x, new_pos.y})) {
			player.y = new_pos.y;
		}
	}
	
}
