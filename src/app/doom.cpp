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


struct ray_cast_result {
	bool successful = false;
	vf2 intersection;
	float distance;
	int map_value;
	bool side;
};

ray_cast_result cast_ray(vf2 ray_start, vf2 ray_dir) {
	ray_cast_result result;

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




void Doom::on_ready() {}
void Doom::on_update() {
	Renderer::clear_back_buffer();

	vf2 ray_dir = player_dir.normalized().rotated_z(-m_view_degree/2.0f);
	for (int ray = 0; ray < 64; ray++) {
		ray_dir = ray_dir.rotated_z(m_view_degree/64.0f);

		ray_cast_result result = cast_ray(player, ray_dir);
		if (result.successful) {
			float line_height = m_wall_height/(result.distance * player_dir.dot(ray_dir));

			Color color;
			color.value = result.map_value;
			if (result.side) {
				color.value+=2;
			}
			draw_filled(ray, line_height, color);
			//draw_edges(ray, line_height, Color(1));
		}
	}
// 	Renderer::draw_number(m_view_degree, 0,0);
// 	Renderer::draw_number(m_wall_height, 0,8);
}




void Doom::on_event(Event event) {
	if (event.type == Event::Type::Released) {
		return;
	}

	switch (event.keycode) {
		case 'w':
			player += player_dir * m_speed;
			break;
		case 's':
			player -= player_dir * m_speed;
			break;
		case 'a':
			player.x += player_dir.y * m_speed;
			player.y -= player_dir.x * m_speed;
			break;
		case 'd':
			player.x -= player_dir.y * m_speed;
			player.y += player_dir.x * m_speed;
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
}