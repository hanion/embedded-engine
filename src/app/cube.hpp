#pragma once

#include "application.hpp"
using namespace EE;
#include "camera.hpp"
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
	virtual void on_update(double delta_time) override final;
	virtual void on_event(Event event) override final;

private:
	double m_delta_time;
	Camera m_camera;

	float m_cube_speed = 0.01;
	int m_level = 2;

	float m_speed = 15.0f;
	float m_rotation_speed;
	float m_zoom_speed = 2.0f;
};


