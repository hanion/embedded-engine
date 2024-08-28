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
	void draw_cube(Cube* cube);

	void recalculate_view_projection();

	Transform m_camera = {0};

	Mat4 m_view_projection_matrix;
	Mat4 perspective_projection;

	float m_speed = 0.01;
	int m_level = 2;
};


