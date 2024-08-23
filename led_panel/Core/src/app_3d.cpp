#include "application.hpp"
#include <math.h>

#include "base.hpp"
#include "renderer.hpp"
#include "event.hpp"
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

class App3D : public Application {
public:
	App3D() {}
	~App3D() {}

	virtual void on_ready() override final;
	virtual void on_update() override final;
	virtual void on_event(Event event) override final;
};

Application* CreateApplication() {
	return new App3D();
}


Mat4 view_projection_matrix;


#define POINT_COUNT 8
#define EDGE_COUNT 12

typedef struct {
	Vec3 p[8];
	int edges[EDGE_COUNT][2];
	Transform transform;
} Cube;

// 0 2
// 1 3
//     4 6
//     5 7
Cube cube0 = {
    .p = {
		{-1, -1, -1},
		{-1,  1, -1},
		{ 1, -1, -1},
		{ 1,  1, -1},
		{-1, -1,  1},
		{-1,  1,  1},
		{ 1, -1,  1},
		{ 1,  1,  1}
	},
	.edges = {
		{0, 1}, {1, 3}, {3, 2}, {2, 0},
		{4, 5}, {5, 7}, {7, 6}, {6, 4},
		{0, 4}, {1, 5}, {2, 6}, {3, 7}
	},
// 	.edges = {
// 		{0, 1}, {1, 5}, {2, 6},
// 		{0, 4}, {4, 5}, {6, 4},
// 		{0, 2}, {5, 7}, {7, 6},
// 		{3, 2}, {1, 3}, {3, 7}
// 	    },
    .transform = { -6,0,0, 0,0,0, 3,3,3 }
};


Cube pyramid0 = {
    .p = {
		{-1,  1, -1}, // 0 left  front
		{ 1,  1, -1}, // 1 right front
		{-1,  1,  1}, // 2 left  back
		{ 1,  1,  1}, // 3 right back
		{ 0, -1,  0}, // 4 top
		{ 0, -1,  0},
		{ 0, -1,  0},
		{ 0, -1,  0},
	},
    .edges = {
        {0, 1}, {0, 2}, {3, 2}, {3, 1},
        {4, 0}, {4, 1}, {4, 2}, {4, 3},
        {4, 0}, {4, 1}, {4, 2}, {4, 3}
    },
    .transform = { 6,0,0, 0,0,0, 3,3,3 }
};

void draw_cube(Cube *cube) {
	Mat4 transform_matrix = Math::calculate_transform_matrix(&cube->transform);
	Mat4 transform_proj_matrix = Math::mat4_mul_mat4(&view_projection_matrix, &transform_matrix);

	Vec4 transformed[POINT_COUNT];
	for (int i = 0; i < POINT_COUNT; ++i) {
		Vec4 model_space = { cube->p[i].x, cube->p[i].y, cube->p[i].z, 1.0 };

		transformed[i] = Math::mat4_mul_vec4_project(&transform_proj_matrix, &model_space);

		// center
		transformed[i].x += (float)WIDTH/2.0;
		transformed[i].y += (float)HEIGHT/2.0;
	}

	uint8_t color = 1;
	for (int i = 0; i < EDGE_COUNT; ++i) {
		Vec4 a = transformed[cube->edges[i][0]];
		Vec4 b = transformed[cube->edges[i][1]];
 		//Renderer::draw_line(a.x, a.y, b.x, b.y);
		Renderer::draw_line_colored(a.x, a.y, b.x, b.y, (color&0b100), (color&0b010), (color&0b001));
		if (++color == 8) {
			color = 1;
		}
	}
}


void App3D::on_ready() {
	Mat4 perspective_projection = Math::mat4_make_perspective(4.0 * (M_PI / 180.0), 1, 1.0, 100.0);
	Mat4 view_matrix = Math::get_view_matrix(0, 0, -15); // camera position
	view_projection_matrix = Math::mat4_mul_mat4(&perspective_projection, &view_matrix);
}



float speed = 0.01;
int level = 2;
void App3D::on_update() {
	Renderer::clear_back_buffer();
	cube0.transform.rot_x += speed * level;
	cube0.transform.rot_y += speed * level;
	cube0.transform.rot_z += speed * level;
	draw_cube(&cube0);


	pyramid0.transform.rot_x += speed * level;
	pyramid0.transform.rot_y += speed * level;
	pyramid0.transform.rot_z += speed * level;
	draw_cube(&pyramid0);
}



void App3D::on_event(Event event) {
	if (event.type == Event::Type::Pressed) {
		if (++level > 5) {
			level = 0;
		}
	}
}


