#include "doom.hpp"
#include "base.hpp"
#include "math.hpp"
#include "renderer.hpp"
#include <cmath>
#include <cstring>

#define RAY_MAX_DISTANCE 100
#define ENEMY_COLLIDER_RADIUS 0.4f
#define ENEMY_FIRE_INTERVAL 0.1f
#define HEALTH_BAR_SIZE 30
#define WEAPON_POS_X 40
#define WEAPON_POS_Y 23


#define MAP_WIDTH 16
#define MAP_HEIGHT 16
const uint8_t map[MAP_HEIGHT][MAP_WIDTH] = {
	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1},
	{1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 0, 0, 1, 0, 0, 1},
	{1, 0, 1, 0, 1, 0, 0, 0, 1, 1, 0, 0, 1, 0, 0, 1},
	{1, 0, 1, 0, 1, 1, 1, 0, 0, 0, 0, 0, 1, 0, 0, 1},
	{1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 1, 1, 0, 0, 1},
	{1, 0, 1, 1, 1, 0, 1, 0, 0, 1, 1, 1, 1, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1},
	{1, 1, 1, 1, 1, 0, 1, 0, 0, 0, 0, 0, 1, 1, 1, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1}
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

#define GUN_TEXTURE_WIDTH 9
#define GUN_TEXTURE_HEIGHT 9
const uint8_t gun_texture[GUN_TEXTURE_HEIGHT][GUN_TEXTURE_WIDTH] = {
	{0, 7, 7, 0, 0, 0, 0, 0, 0},
	{7, 8, 8, 7, 7, 0, 0, 0, 0},
	{7, 8, 8, 8, 8, 7, 7, 0, 0},
	{7, 8, 8, 8, 8, 8, 8, 7, 0},
	{0, 7, 8, 8, 8, 8, 8, 8, 7},
	{0, 0, 7, 8, 8, 8, 8, 8, 7},
	{0, 0, 0, 7, 8, 8, 8, 8, 7},
	{0, 0, 0, 7, 7, 8, 8, 8, 7},
	{0, 0, 0, 7, 8, 7, 7, 7, 0},
};
Texture enemy_texture = {
	.data = &circle_texture[0][0],
	.width = TEXTURE_WIDTH,
	.height = TEXTURE_HEIGHT,
	.scale = 1.0f
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

#define OPTIMIZE_LINE_DRAWING 1
#if OPTIMIZE_LINE_DRAWING
	int start_y = static_cast<int>(HEIGHT / 2.0f - line_height / 2.0f);
	int end_y = start_y + static_cast<int>(line_height);
	if (x < 0 || x >= WIDTH || start_y < 0 || end_y > HEIGHT) {
		return;
	}
	int num_pixels = end_y - start_y;
	int num_bytes = num_pixels * sizeof(uint8_t);
	uint8_t* column_start = &(*Renderer::back_buffer)[x][start_y];
	memset(column_start, color.value, num_bytes);
	return;
#else
	for (int y = 0; y < line_height; ++y) {
		Renderer::set_pixel(x, y + (HEIGHT/2.0f-line_height/2.0f), color);
	}
#endif
}


void Doom::draw_sprite(vf2 sprite, const Texture& texture) {
	vf2 relative_position = sprite - m_player.position;

	vf2 transformed_position = {
		relative_position.x * m_player.direction.y - relative_position.y * m_player.direction.x,
		relative_position.x * m_player.direction.x + relative_position.y * m_player.direction.y
	};

	if (transformed_position.y < 0.4f) {
		return;
	}

	float screen_x = (WIDTH / 2.0f) * (1 - transformed_position.x / transformed_position.y);
	float sprite_size = (HEIGHT / transformed_position.y) * texture.scale;

	int sprite_left  = static_cast<int>(screen_x - sprite_size / 2);
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
							depth_buffer[x] = transformed_position.y;
						}
					}
				}
			}
		}
	}
}

void Doom::on_ready() {
	restart_level();
}

void Doom::on_update(double delta_time) {
	m_delta_time = delta_time;

	Renderer::clear_back_buffer();

	vf2 ray_dir = m_player.direction.normalized().rotated_z(-m_view_degree/2.0f);
	for (int ray = 0; ray < 64; ray++) {
		ray_dir = ray_dir.rotated_z(m_view_degree/64.0f);

		raycast_result result = cast_ray(m_player.position, ray_dir);
		if (result.successful) {
			float line_height = m_wall_height/(result.distance * m_player.direction.dot(ray_dir));
			depth_buffer[ray] = result.distance;

			Color color;
			color.value = result.map_value;
			if (result.side) {
				color.value+=2;
			}
			draw_filled(ray, line_height, color);
		}
	}

	// sort enemy sprites
	std::sort(m_enemies.begin(), m_enemies.end(),
		[this](const Enemy& a, const Enemy& b) {
			float dist_a = std::pow(a.position.x - m_player.position.x, 2) + std::pow(a.position.y - m_player.position.y, 2);
			float dist_b = std::pow(b.position.x - m_player.position.x, 2) + std::pow(b.position.y - m_player.position.y, 2);
			return dist_a > dist_b;
		}
	);

	update_enemies(delta_time);

	// draw enemies
	for (auto& enemy : m_enemies) {
		draw_sprite(enemy.position, *enemy.texture);
	}

	update_projectiles(delta_time);

	// draw projectiles
	for (auto& proj : m_projectiles) {
		draw_sprite(proj.position, *proj.texture);
	}

	uint8_t enemy_count = m_enemies.size();
	if (enemy_count) {
		Renderer::draw_number(enemy_count, 58,1);
	}

	draw_health_bar();

	// draw weapon
	Color color;
	for (int row = 0; row < GUN_TEXTURE_HEIGHT; ++row) {
		for (int col = 0; col < GUN_TEXTURE_HEIGHT; ++col) {
			color.value = gun_texture[row][col];
			if (color.value) {
				Renderer::set_pixel(col+WEAPON_POS_X, row+WEAPON_POS_Y, color);
			}
		}
	}
	
}


void Doom::draw_health_bar() {
	uint8_t health_pixels = (m_player.health / 100.0f) * (HEALTH_BAR_SIZE-1);
	for (uint8_t i = 0; i < HEALTH_BAR_SIZE-1; ++i) {
		if (i >= health_pixels) {
			Renderer::set_pixel(1+i, 2, Color(0,0,0));
		} else {
			Renderer::set_pixel(1+i, 2, Color(1,0,0));
		}
	}
	Color healt_bar_color = {1,1,1};
	for (uint8_t i = 0; i < HEALTH_BAR_SIZE; ++i) {
		Renderer::set_pixel(1+i, 1, healt_bar_color);
		Renderer::set_pixel(1+i, 3, healt_bar_color);
	}
	Renderer::set_pixel(1, 2, healt_bar_color);
	Renderer::set_pixel(HEALTH_BAR_SIZE, 2, healt_bar_color);
}

void Doom::shoot() {
	Projectile proj = {
		.position = m_player.position,
		.direction = m_player.direction,
		.speed = 10.0f,
		.texture = &projectile_texture
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
			enemy.health -= 10.0f;
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
			it = m_projectiles.erase(it);
		} else {
			++it;
		}
	}
}

void Doom::update_enemies(double delta_time) {
	for (auto& enemy : m_enemies) {
		vf2 dif = m_player.position - enemy.position;

		float distance = sqrt(dif.x * dif.x + dif.y * dif.y);
		if (distance < ENEMY_COLLIDER_RADIUS) {
			enemy.hit_timer += delta_time;
			if (enemy.hit_timer > ENEMY_FIRE_INTERVAL) {
				enemy.hit_timer = 0.0f;
				m_player.hurt(10.0f);
				if (m_player.health <= 0) {
					restart_level();
				}
			}
			continue;
		}

		vf2 direction = dif.normalized();
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


void Doom::restart_level() {
	m_enemies.clear();
	m_projectiles.clear();

	std::vector<vf2> enemy_positions = {
		{9.5f, 7.5f},
		{10.5f, 4.5f},
		{14.5f, 13.5f},
	};
	Enemy enemy = {
		.texture = &enemy_texture
	};
	for (const auto& pos : enemy_positions) {
		enemy.position = pos;
		m_enemies.push_back(enemy);
	}

	m_player.position = { 1.5f, 1.5f };
	m_player.direction = { 1.0f, 1.0f };
	m_player.health = 100.0f;
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
			movement += m_player.direction * m_player.speed * m_delta_time;
			break;
		case 's':
			movement -= m_player.direction * m_player.speed * m_delta_time;
			break;
		case 'a':
			movement.x += m_player.direction.y * m_player.speed * m_delta_time;
			movement.y -= m_player.direction.x * m_player.speed * m_delta_time;
			break;
		case 'd':
			movement.x -= m_player.direction.y * m_player.speed * m_delta_time;
			movement.y += m_player.direction.x * m_player.speed * m_delta_time;
			break;
		case 'j':
			m_player.direction = m_player.direction.rotated_z(-m_player.rotation_speed * m_delta_time);
			break;
		case 'l':
			m_player.direction = m_player.direction.rotated_z(m_player.rotation_speed * m_delta_time);
			break;
		default:
			break;
	}
	if (collision(m_player.position+movement)) {
		if (map[int(m_player.position.y+movement.y)][int(m_player.position.x+movement.x)] == 2) {
			if (m_enemies.size() == 0) {
				// TODO: next level
				restart_level();
			}
		}
	}
	move_and_slide(m_player.position, movement);
}
