#pragma once

#include "application.hpp"
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
	Camera m_camera;

	float m_speed = 0.01;
	int m_level = 2;
};


