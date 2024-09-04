#pragma once

#include "application.hpp"
#include "math.hpp"
#include "vector.hpp"


struct Texture {
	const uint8_t *data = nullptr;
	uint8_t width = 0;
	uint8_t height = 0;
	float scale = 1.0f;
};

struct Enemy {
	vf2 position = { 0.0f, 0.0f };
	float health = 100.0f;
	float speed = 2.0f;
	float fire_interval = 2.0f;

	Texture* texture = nullptr;
};

struct Projectile {
	vf2 position = { 0.0f, 0.0f };
	vf2 direction;
	float speed;
	Texture* texture = nullptr;
};




class Doom : public Application {
public:
	Doom() : Application("Doom") {}
	virtual ~Doom() {}

	virtual void on_ready() override final;
	virtual void on_update(double delta_time) override final;
	virtual void on_event(Event event) override final;

private:
	void draw_sprite(vf2 sprite, const Texture& texture);
	void shoot();
	void update_projectiles(double delta_time);
	void update_enemies(double delta_time);

	bool collision(vf2 pos);
	bool collide_with_enemy(vf2 pos);

	void move_and_slide(vf2& source, const vf2& delta);

private:
	float m_delta_time = 0.1f;

	float m_speed = 1.2f;
	float m_rotation_speed = 100.0f;

	vf2 player = { 8.4f, 10.6f };
	vf2 player_dir = { 1.0f, -1.0f };

	float m_view_degree = 88.0f;
	float m_wall_height = 28.0f;

	std::vector<Projectile> m_projectiles;
	std::vector<Enemy> m_enemies;
};


