#pragma once

#include "application.hpp"
#include "math.hpp"
#include "vector.hpp"


class Doom : public Application {
public:
	Doom() : Application("Doom") {}
	virtual ~Doom() {}

	virtual void on_ready() override final;
	virtual void on_update(double delta_time) override final;
	virtual void on_event(Event event) override final;

private:
	void draw_sprite(vf2 sprite);

private:
	float m_speed = 0.02f;
	float m_rotation_speed = 0.8f;

	vf2 player = { 8.4f, 10.6f };
	vf2 player_dir = { 1.0f, -1.0f };

	float m_view_degree = 88.0f;
	float m_wall_height = 24.0f;

	vf2 test_sprite = { 8.2f, 8.2f };
};


