#include "dino.hpp"

#include "platform.hpp"
#include "base.hpp"
#include "renderer.hpp"

#include <stdlib.h>
#include <time.h>

void DinoGame::respawn_obstacle(int i) {
	int last = WIDTH - OBSTACLES_MIN_SPACING;
	for (int j = 0; j < OBSTACLES_MAX; ++j) {
		if (obstacles[j].rect.x > last) {
			last = obstacles[j].rect.x;
		}
	}

	obstacles[i].rect.x = last + OBSTACLES_MIN_SPACING;
	int offset = (rand()%OBSTACLES_MAX_SPACING);
	if (offset > 0) {
		obstacles[i].rect.x += offset;
	}
	if (obstacles[i].rect.x - last < OBSTACLES_MIN_SPACING) {
		//buzzer();
	}

	obstacles[i].velocity = OBSTACLES_VELOCITY + OBSTACLES_VELOCITY * (dino.score/100.0);

	int y = GROUND_Y - 2;
	if (rand()%100 < 20) {
		y = GROUND_Y - 7;

		if (rand()%100 < 20) {
			obstacles[i].velocity = OBSTACLES_VELOCITY + OBSTACLES_VELOCITY * (dino.score/20.0);
		}
	}

	obstacles[i].real_x = obstacles[i].rect.x;
	obstacles[i].rect.y = y;
	obstacles[i].rect.width = 2;
	obstacles[i].rect.height = 2;
	obstacles[i].active = true;
}

void DinoGame::init_obstacles() {
	for (int i = 0; i < OBSTACLES_MAX; ++i) {
		obstacles[i].rect.x = -10;
		obstacles[i].rect.y = 10;
		obstacles[i].real_x = -10.0;
		obstacles[i].velocity = OBSTACLES_VELOCITY;
		obstacles[i].active = false;
	}
}

void DinoGame::move_obstacles() {
	if (dino.is_dead) {
		return;
	}

	for (int i = 0; i < OBSTACLES_MAX; ++i) {
		Obstacle* o = &obstacles[i];
		if (o->active || true) {
			o->real_x += o->velocity * DeltaTime;
			o->rect.x = (o->real_x);
			if (o->rect.x + o->rect.width < 0) {
				if (o->active) {
					dino.score++;
				}

				o->active = false;
				respawn_obstacle(i);
				continue;
			}

			if (!dino.is_dead && o->active && check_collision(dino.rect, o->rect)) {
				dino_die();
				return;
			}
		}
	}
}

void DinoGame::move_dino() {
	if (!dino.is_jumping) {
		return;
	}

	dino.jump_velocity += dino_accel * DeltaTime;
	dino.real_pos += dino.jump_velocity * DeltaTime;
	dino.rect.y = (dino.real_pos);

	if (!dino.is_dead && dino.rect.y >= DINO_START_Y) {
		dino.rect.y = DINO_START_Y;
		dino.real_pos = DINO_START_Y;
		dino.is_jumping = false;
		dino.jump_velocity = 0;
	}
	else if (dino.rect.y > HEIGHT) {
		dino.is_jumping = false;
		dino.jump_velocity = 0;
	}
}


void DinoGame::draw_ground() {
	Renderer::draw_line(0, GROUND_Y, 63, GROUND_Y);
}
void DinoGame::draw_dino() {
	if (!dino.is_dead) {
		Renderer::draw_Rect(dino.rect, {0, 1, 0});
	} else {
		Renderer::draw_Rect(dino.rect, {1, 0, 0});
	}
}


void DinoGame::draw_obstacles() {
	for (int i = 0; i < OBSTACLES_MAX; ++i) {
		if (!obstacles[i].active) {
			continue;
		}
		if (obstacles[i].rect.x < 0 || obstacles[i].rect.y < 0 || 
			(obstacles[i].rect.x > WIDTH || obstacles[i].rect.y > HEIGHT)) {
			continue;
		}
		Renderer::draw_Rect(obstacles[i].rect, {0, 0, 1});
	}
}


void DinoGame::draw_score() {
	Renderer::draw_number(dino.score, 2, 2, false);
	return;
	uint8_t x = 2;
	uint8_t y = 2;

	for (uint8_t var = 0; var < 10; ++var) {
		Renderer::draw_number(var, x, y, true);
		x += 8;
	}
}


bool DinoGame::check_collision(Rect a, Rect b) {
	return (a.x < (b.x + b.width) &&
			(a.x + a.width) > b.x &&
			a.y < (b.y + b.height) &&
			(a.y + a.height) > b.y);
}


void DinoGame::dino_die() {
	dino.is_dead = true;
	dino.is_jumping = false;
	dino_death_time = Platform::get_tick();
	//buzzer();
}

void DinoGame::dino_respawn() {
	dino.score = 0;
	dino.is_dead = false;
	dino.is_jumping = false;
	dead_dino_jumped = false;
	dino.rect.y = DINO_START_Y;
	dino.real_pos = dino.rect.y;
}

void DinoGame::dino_jump() {
	dino.is_jumping = true;
	dino.jump_velocity = DINO_JUMP_VELOCITY;
	float v0 = DINO_JUMP_VELOCITY;
	float d = (DINO_START_Y - DINO_JUMP_TO_Y);
	dino_accel = (v0*v0)/(2*d);
}

void DinoGame::on_ready() {
	srand(time(NULL));
	init_obstacles();
}

void DinoGame::on_update() {
	Renderer::clear_back_buffer();

	draw_ground();
	draw_dino();
	draw_obstacles();
	draw_score();

	move_dino();
	move_obstacles();

	// death animation & restart
	if (dino.is_dead) {
		uint32_t time_passed = Platform::get_tick() - dino_death_time;
		if (time_passed > 1000 && !dead_dino_jumped) {
			dino_jump();
			dead_dino_jumped = true;
		}
		else if (time_passed > 3000) {
			init_obstacles();
			dino_respawn();
		}
	}
}


void DinoGame::on_event(Event event) {
	if (event.type == Event::Type::Pressed) {
		if (!dino.is_dead && !dino.is_jumping) {
			dino_jump();
		}
	
	}
	else if (event.type == Event::Type::Held) {
		if (!dino.is_dead && dino.is_jumping) {
			dino.jump_velocity -= 60 * DeltaTime;
		}
	}

}

