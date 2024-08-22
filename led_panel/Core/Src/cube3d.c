/*
 * 3d_cube.c
 *
 *  Created on: Aug 21, 2024
 *      Author: han
 */



#include "base.h"
#include "main.h"
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include "mat.h"

#if cube3d


Mat4 perspective_projection;
Mat4 view_matrix;
Mat4 view_projection_matrix;



typedef struct {
	float x,y,z;
} Point;


typedef struct {
	Point p[8];
	int edges[12][2];
	Transform t;
} Cube;

// 0 2
// 1 3
//     4 6
//     5 7
Cube cube0 = {
    {
	 {-1, -1, -1},
	 {-1,  1, -1},
	 { 1, -1, -1},
	 { 1,  1, -1},
	 {-1, -1,  1},
	 {-1,  1,  1},
	 { 1, -1,  1},
	 { 1,  1,  1}
    },
	{
	 {0,1},{0,2},{0,4},{1,3},{1,5},{2,3},
	 {2,6},{3,7},{4,5},{4,6},{5,7},{6,7}
	},
	{ 0,0,0, 0,0,0, 3,3,3 }
};
#define POINT_COUNT 8
#define EDGE_COUNT 12



void draw_cube(Cube *cube) {
	Mat4 transform_matrix = calculate_transform_matrix(&cube->t);
	Mat4 transform_proj_matrix = mat4_mul_mat4(&view_projection_matrix, &transform_matrix);


	Vec4 transformed[POINT_COUNT];
	for (int i = 0; i < POINT_COUNT; ++i) {
		Vec4 point;
		point.x = cube->p[i].x;
		point.y = cube->p[i].y;
		point.z = cube->p[i].z;
		point.w = 1.0;

		// model space -> world space
		Vec4 model_space = mat4_mul_vec4(&transform_matrix, &point);

		// world space -> camera space -> screen space
		transformed[i] = mat4_mul_vec4_project(&transform_proj_matrix, &model_space);

		// center
		transformed[i].x += (float)WIDTH/2.0;
		transformed[i].y += (float)HEIGHT/2.0;
	}

	for (int i = 0; i < EDGE_COUNT; ++i) {
		Vec4 a = transformed[cube->edges[i][0]];
		Vec4 b = transformed[cube->edges[i][1]];
		draw_line(a.x, a.y, b.x, b.y);
	}
}

void on_ready() {
	perspective_projection = mat4_make_perspective(10.0 * (M_PI / 180.0), 1, 1.0, 100.0);
	view_matrix = get_view_matrix(0, 0, -20);
	view_projection_matrix = mat4_mul_mat4(&perspective_projection, &view_matrix);
}


float speed = 0.02;
void on_update() {
	clear_back_buffer();
	cube0.t.rot_x += speed;
	cube0.t.rot_y += speed;
	cube0.t.rot_z += speed;
	draw_cube(&cube0);
}


void on_button_pressed() {
	speed *= 2.0;
	if (speed > 0.16) {
		speed = 0.01;
	}
}

#endif
