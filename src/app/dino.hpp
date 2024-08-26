#pragma once
#include "application.hpp"
#include "renderer.hpp"

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


typedef struct {
	Rect rect;
	float real_pos;
	float jump_velocity;
	bool is_jumping;
	bool is_dead;
	int score;
} Dino;


typedef struct {
	Rect rect;
	bool active;
	float real_x;
	float velocity;
} Obstacle;




class DinoGame : public Application {
public:
	DinoGame() : Application("DinoGame") {}
	virtual ~DinoGame() {}

	virtual void on_ready() override final;
	virtual void on_update() override final;
	virtual void on_event(Event event) override final;

private:
	bool check_collision(Rect a, Rect b);
	void dino_die();
	void dino_jump();
	void dino_respawn();

	void respawn_obstacle(int i);
	void init_obstacles();
	void move_obstacles();
	void move_dino();

	void draw_ground();
	void draw_dino();
	void draw_obstacles();
	void draw_score();


private:
	Obstacle obstacles[OBSTACLES_MAX];

	uint32_t dino_death_time = 0;
	float dino_accel = 0;
	bool dead_dino_jumped = false;
	
	double DeltaTime = 0.01f;

	Dino dino = {
		.rect = { 10, DINO_START_Y, DINO_WIDTH, DINO_HEIGHT },
		.real_pos = DINO_START_Y,
		.jump_velocity = 0,
		.is_jumping = false,
		.is_dead = false,
		.score = 0
	};
};

