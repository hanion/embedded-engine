#include "doom.hpp"
#include "base.hpp"
#include "math.hpp"
#include "renderer.hpp"
#include <cmath>
#include <cstring>

#define RAY_MAX_DISTANCE 100
#define ENEMY_COLLIDER_RADIUS 0.4f

#define MAP_WIDTH 16
#define MAP_HEIGHT 16
const uint8_t map[MAP_HEIGHT][MAP_WIDTH] = {
	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 1, 4, 2, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1},
	{1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1},
	{1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 0, 0, 1, 0, 0, 1},
	{1, 0, 1, 0, 1, 0, 0, 0, 1, 1, 0, 0, 1, 0, 0, 1},
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
const uint8_t circle_texture[TEXTURE_HEIGHT][TEXTURE_WIDTH] = {
	{0, 0, 0, 0, 0, 6, 6, 6, 6, 6, 6, 0, 0, 0, 0, 0},
	{0, 0, 0, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 0, 0, 0},
	{0, 0, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 0, 0},
	{0, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 0},
	{0, 6, 6, 6, 6, 8, 8, 6, 6, 8, 8, 6, 6, 6, 6, 0},
	{6, 6, 6, 6, 6, 8, 8, 6, 6, 8, 8, 6, 6, 6, 6, 6},
	{6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6},
	{6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6},
	{6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6},
	{6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6},
	{6, 6, 6, 6, 6, 8, 8, 8, 8, 8, 8, 6, 6, 6, 6, 6},
	{0, 6, 6, 6, 6, 8, 8, 8, 8, 8, 8, 6, 6, 6, 6, 0},
	{0, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 0},
	{0, 0, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 0, 0},
	{0, 0, 0, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 0, 0, 0},
	{0, 0, 0, 0, 0, 6, 6, 6, 6, 6, 6, 0, 0, 0, 0, 0}
};

#define PROJECTILE_TEXTURE_WIDTH 9
#define PROJECTILE_TEXTURE_HEIGHT 9
const uint8_t projectile_circle_texture[PROJECTILE_TEXTURE_HEIGHT][PROJECTILE_TEXTURE_WIDTH] = {
	{0, 0, 0, 7, 7, 7, 0, 0, 0},
	{0, 7, 7, 4, 4, 4, 7, 7, 0},
	{0, 7, 4, 4, 4, 4, 4, 7, 0},
	{7, 4, 4, 4, 4, 4, 4, 4, 7},
	{7, 4, 4, 4, 4, 4, 4, 4, 7},
	{7, 4, 4, 4, 4, 4, 4, 4, 7},
	{0, 7, 4, 4, 4, 4, 4, 7, 0},
	{0, 7, 7, 4, 4, 4, 7, 7, 0},
	{0, 0, 0, 7, 7, 7, 0, 0, 0}
};
Texture projectile_texture = {
	.data = &projectile_circle_texture[0][0],
	.width = PROJECTILE_TEXTURE_WIDTH,
	.height = PROJECTILE_TEXTURE_HEIGHT,
	.scale = 0.2f
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


void Doom::draw_sprite(vf2 sprite, const Texture& texture) {
	vf2 relative_position = sprite - player;

	vf2 transformed_position = {
		relative_position.x * player_dir.y - relative_position.y * player_dir.x,
		relative_position.x * player_dir.x + relative_position.y * player_dir.y
	};

	if (transformed_position.y < 0.4f) {
		return;
	}

	float screen_x = (WIDTH / 2.0f) * (1 - transformed_position.x / transformed_position.y);
	float sprite_size = (HEIGHT / transformed_position.y) * texture.scale;

	int sprite_left = static_cast<int>(screen_x - sprite_size / 2);
	int sprite_right = static_cast<int>(screen_x + sprite_size / 2);

	for (int x = sprite_left; x < sprite_right; ++x) {
		if (x >= 0 && x < WIDTH) {
			float tex_x = (x - sprite_left) / sprite_size * texture.width;
			tex_x = std::min(std::max(tex_x, 0.0f), static_cast<float>(texture.width - 1));

			if (transformed_position.y < depth_buffer[x]) {
				for (int y = 0; y < sprite_size; ++y) {
					int screen_y = static_cast<int>(HEIGHT / 2.0f - sprite_size / 2 + y);
					if (screen_y >= 0 && screen_y < HEIGHT) {
						float tex_y = y / sprite_size * texture.height;
						tex_y = std::min(std::max(tex_y, 0.0f), static_cast<float>(texture.height - 1));

						uint8_t tex_color = texture.data[static_cast<int>(tex_y) * texture.width + static_cast<int>(tex_x)];
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

void Doom::on_ready() {
	std::vector<vf2> enemy_positions = {
		{4.2f, 2.2f},
		{8.5f, 7.5f},
		{9.5f, 7.5f},
		{10.5f, 2.5f},
		{10.5f, 4.5f},
	};
	Enemy enemy = {
		.position = {8.2f, 8.2f},
		.texture = {
			.data = &circle_texture[0][0],
			.width = TEXTURE_WIDTH,
			.height = TEXTURE_HEIGHT,
		}
	};
	for (const auto& pos : enemy_positions) {
		enemy.position = pos;
		m_enemies.push_back(enemy);
	}
	m_enemies.push_back(enemy);
}

void Doom::on_update(double delta_time) {
	m_delta_time = delta_time;

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

	update_enemies(delta_time);

	// draw enemies
	for (auto& enemy : m_enemies) {
		draw_sprite(enemy.position, enemy.texture);
	}

	// update projectiles
	update_projectiles(delta_time);

	// draw projectiles
	for (auto& proj : m_projectiles) {
		draw_sprite(proj.position, proj.texture);
	}
}



void Doom::shoot() {
	Projectile proj = {
		.position = player,
		.direction = player_dir,
		.speed = 10.0f,
		.texture = projectile_texture
	};
	m_projectiles.push_back(proj);
}


bool Doom::collision(vf2 pos) {
	if (pos.x < 0 || pos.x >= MAP_WIDTH || pos.y < 0 || pos.y >= MAP_HEIGHT) {
		return true;
	}

	if (map[int(pos.y)][int(pos.x)]) {
		return true;
	}

	return false;
}

bool Doom::collide_with_enemy(vf2 pos) {
	for (auto it = m_enemies.begin(); it != m_enemies.end();) {
		auto& enemy = *it;

		float dx = std::abs(pos.x - enemy.position.x);
		float dy = std::abs(pos.y - enemy.position.y);
		if (dy < ENEMY_COLLIDER_RADIUS && dx < ENEMY_COLLIDER_RADIUS) {
			enemy.health -= 50.0f;
			if (enemy.health <= 0) {
				m_enemies.erase(it);
			}
			return true;
		} else {
			++it;
		}
	}
	return false;
}

void Doom::update_projectiles(double delta_time) {
	for (auto it = m_projectiles.begin(); it != m_projectiles.end();) {
		auto& p = *it;
		p.position += p.direction * p.speed * delta_time;

		if (p.position.x < 0 || p.position.y < 0 ||
			p.position.x > MAP_WIDTH || p.position.y > MAP_HEIGHT ||
			collision(p.position) ||
			collide_with_enemy(p.position) ) {
			//++it;
			it = m_projectiles.erase(it);
		} else {
			++it;
		}
	}
}

void Doom::update_enemies(double delta_time) {
	for (auto& enemy : m_enemies) {
		vf2 dif = player - enemy.position;
		float distance = sqrt(dif.x * dif.x + dif.y * dif.y);

		if (distance < ENEMY_COLLIDER_RADIUS) {
			continue;
		}

		vf2 direction = { dif.x / distance, dif.y / distance };
		move_and_slide(enemy.position, direction * enemy.speed * delta_time);

	}
}

void Doom::move_and_slide(vf2& source, const vf2& delta) {
	if (delta.x == 0.0f && delta.y == 0.0f) {
		return;
	}

	vf2 new_pos = source + delta;
	if (new_pos != source) {
		if (!collision(new_pos)) {
			source = new_pos;
		} else if (!collision({new_pos.x, source.y})) {
			source.x = new_pos.x;
		} else if (!collision({source.x, new_pos.y})) {
			source.y = new_pos.y;
		}
	}
}



void Doom::on_event(Event event) {
	if (event.type == Event::Type::Released) {
		return;
	} else if (event.type == Event::Type::Pressed) {
		switch (event.keycode) {
			case ' ':
				shoot();
			break;
		}
	}

	vf2 movement = {0.0f,0.0f};
	switch (event.keycode) {
		case 'w':
			movement += player_dir * m_speed * m_delta_time;
			break;
		case 's':
			movement -= player_dir * m_speed * m_delta_time;
			break;
		case 'a':
			movement.x += player_dir.y * m_speed * m_delta_time;
			movement.y -= player_dir.x * m_speed * m_delta_time;
			break;
		case 'd':
			movement.x -= player_dir.y * m_speed * m_delta_time;
			movement.y += player_dir.x * m_speed * m_delta_time;
			break;
		case 'j':
			player_dir = player_dir.rotated_z(-m_rotation_speed * m_delta_time);
			break;
		case 'l':
			player_dir = player_dir.rotated_z(m_rotation_speed * m_delta_time);
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
	move_and_slide(player, movement);
}
