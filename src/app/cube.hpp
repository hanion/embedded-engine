#pragma once

#include "application.hpp"
#include "math.hpp"


#define POINT_COUNT 8
#define EDGE_COUNT 12

typedef struct {
	Vec3 p[8];
	int edges[EDGE_COUNT][2];
	Transform transform;
} Cube;




class CubeDemo : public Application {
public:
	CubeDemo() : Application("CubeDemo") {}
	virtual ~CubeDemo() {}

	virtual void on_ready() override final;
	virtual void on_update() override final;
	virtual void on_event(Event event) override final;

private:
	void recalculate_view_projection();

	Transform m_camera = {
		.x = 0, .y = 0, .z = -15,
		.rot_x = 0, .rot_y = 0, .rot_z = 0,
		.scale_x = 1, .scale_y = 1, .scale_z = 1,
	};

	Mat4 m_view_projection_matrix;
	Mat4 perspective_projection;

	float m_speed = 0.01;
	int m_level = 2;
};


