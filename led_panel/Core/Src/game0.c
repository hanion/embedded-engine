/*
 * game0.c
 *
 *  Created on: Aug 16, 2024
 *      Author: han
 */

#include "main.h"
#include <stdlib.h>
#include <time.h>

#define GROUND_Y 26
#define GRAVITY 0.4

#define DINO_START_Y 23
#define DINO_JUMP_TO_Y 13
#define DINO_JUMP_VELOCITY -60.0
#define DINO_WIDTH 2
#define DINO_HEIGHT 3


#define OBSTACLES_VELOCITY -25.0
#define OBSTACLES_MAX 10
#define OBSTACLES_MIN_SPACING 12
#define OBSTACLES_MAX_SPACING 40

float dino_accel = 0;


bool check_collision(Rect a, Rect b);
void dino_die();
void dino_jump();
void dino_respawn();

typedef struct {
    Rect rect;
    float real_pos;
    float jump_velocity;
    bool is_jumping;
    bool is_dead;
    int score;
} Dino;

Dino dino = {
	.rect = { 10, DINO_START_Y, DINO_WIDTH, DINO_HEIGHT },
	.real_pos = DINO_START_Y,
	.jump_velocity = 0,
	.is_jumping = false,
	.is_dead = false,
	.score = 0
};
uint32_t dino_death_time = 0;


typedef struct {
	Rect rect;
	bool active;
	float real_x;
	float velocity;
} Obstacle;



Obstacle obstacles[OBSTACLES_MAX];


void respawn_obstacle(int i) {
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
		buzzer();
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

void init_obstacles() {
	for (int i = 0; i < OBSTACLES_MAX; ++i) {
		obstacles[i].rect.x = -10;
		obstacles[i].rect.y = 10;
		obstacles[i].real_x = -10.0;
		obstacles[i].velocity = OBSTACLES_VELOCITY;
		obstacles[i].active = false;

	}
}

void move_obstacles() {
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

			if (!dino.is_dead && check_collision(dino.rect, o->rect)) {
				dino_die();
				return;
			}
		}
	}
}


void move_dino() {
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



void draw_ground() {
	draw_line(0, GROUND_Y, 63, GROUND_Y);
}
void draw_dino() {
	if (!dino.is_dead) {
		Draw_Rect(dino.rect, (Color){0, 1, 0});
	} else {
		Draw_Rect(dino.rect, (Color){1, 0, 0});
	}
}

void draw_obstacles() {
	for (int i = 0; i < OBSTACLES_MAX; ++i) {
		if (!obstacles[i].active) {
			continue;
		}
		if (obstacles[i].rect.x < 0 || obstacles[i].rect.y < 0 ) {
			continue;
		}
		if (obstacles[i].rect.x > WIDTH || obstacles[i].rect.y > HEIGHT ) {
			continue;
		}
		Draw_Rect(obstacles[i].rect, (Color){0, 0, 1});
	}
}

void draw_score() {
	draw_number(dino.score, 2, 2, false);
	return;
	uint8_t x = 2;
	uint8_t y = 2;

	for (uint8_t var = 0; var < 10; ++var) {
		draw_number(var, x, y, true);
		x += 8;
	}
}



bool check_collision(Rect a, Rect b) {
	return (a.x < (b.x + b.width) &&
			(a.x + a.width) > b.x &&
			a.y < (b.y + b.height) &&
			(a.y + a.height) > b.y);
}


void dino_die() {
	dino.is_dead = true;
	dino.is_jumping = false;
	dino_death_time = HAL_GetTick();
	//buzzer();
}

bool dead_dino_jumped = false;
void dino_respawn() {
	dino.score = 0;
	dino.is_dead = false;
	dino.is_jumping = false;
	dead_dino_jumped = false;
	dino.rect.y = DINO_START_Y;
	dino.real_pos = dino.rect.y;
}

void dino_jump() {
	dino.is_jumping = true;
	dino.jump_velocity = DINO_JUMP_VELOCITY;
	float v0 = DINO_JUMP_VELOCITY;
	float d = (DINO_START_Y - DINO_JUMP_TO_Y);
	dino_accel = (v0*v0)/(2*d);
}

void on_ready() {
	//srand(time(NULL));
	init_obstacles();
}

void on_update() {
	clear_back_buffer();

	draw_ground();
	draw_dino();
	draw_obstacles();
	draw_score();

	move_dino();
	move_obstacles();

	// death animation & restart
	if (dino.is_dead) {
		uint32_t time_passed = HAL_GetTick() - dino_death_time;
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



void on_button_pressed() {
	if (!dino.is_dead && !dino.is_jumping) {
		dino_jump();
	}
}
void on_button_held() {
	if (!dino.is_dead && dino.is_jumping) {
		dino.jump_velocity -= 60 * DeltaTime;
	}
}
void on_button_released() {
}
