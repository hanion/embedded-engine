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


#if cube3d
typedef struct {
	int x,y,z;
} Point;

typedef struct {
	float m[3][3];
} Matrix3x3;


typedef struct {
	Point p[8];
	Matrix3x3 transform;
	Matrix3x3 rotation;
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
    {1, 0, 0, 0, 1, 0, 0, 0, 1},
	{1, 0, 0, 0, 1, 0, 0, 0, 1}
};

void multiply_matrix_matrix(const Matrix3x3 *a, const Matrix3x3 *b, Matrix3x3 *result) {
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			result->m[i][j] = 0;
			for (int k = 0; k < 3; k++) {
				result->m[i][j] += a->m[i][k] * b->m[k][j];
			}
		}
	}
}
void multiply_matrix_vector(const Matrix3x3 *mat, const Point *in, Point *out) {
	out->x = mat->m[0][0] * in->x + mat->m[0][1] * in->y + mat->m[0][2] * in->z;
	out->y = mat->m[1][0] * in->x + mat->m[1][1] * in->y + mat->m[1][2] * in->z;
	out->z = mat->m[2][0] * in->x + mat->m[2][1] * in->y + mat->m[2][2] * in->z;
}
Matrix3x3 get_rotation_matrix_x(float angle) {
	Matrix3x3 mat = {
		{
			{1, 0, 0},
			{0, cos(angle), -sin(angle)},
			{0, sin(angle), cos(angle)}
		}
	};
	return mat;
}
Matrix3x3 get_rotation_matrix_y(float angle) {
	Matrix3x3 mat = {
		{
			{cos(angle), 0, sin(angle)},
			{0, 1, 0},
			{-sin(angle), 0, cos(angle)}
		}
	};
	return mat;
}
Matrix3x3 get_rotation_matrix_z(float angle) {
	Matrix3x3 mat = {
		{
			{cos(angle), -sin(angle), 0},
			{sin(angle), cos(angle), 0},
			{0, 0, 1}
		}
	};
	return mat;
}

void project(Point *p, float d) {
	float factor = d / (d + p->z);
	p->x = (int)(p->x * factor);
	p->y = (int)(p->y * factor);
}

Point get_center(const Cube *cube) {
	Point center = {0, 0, 0};

	for (int i = 0; i < 8; ++i) {
		center.x += cube->p[i].x;
		center.y += cube->p[i].y;
		center.z += cube->p[i].z;
	}

	center.x /= 8;
	center.y /= 8;
	center.z /= 8;

	return center;
}


void apply_transformation(Cube *cube) {
    Point center = get_center(cube);

    // Translate cube to origin
    Point translated[8];
    for (int i = 0; i < 8; ++i) {
        translated[i].x = cube->p[i].x - center.x;
        translated[i].y = cube->p[i].y - center.y;
        translated[i].z = cube->p[i].z - center.z;
    }

    // Apply rotation
    Point rotated[8];
    for (int i = 0; i < 8; ++i) {
        multiply_matrix_vector(&cube->transform, &translated[i], &rotated[i]);
    }

    // Translate back to original position
    Point projected[8];
    for (int i = 0; i < 8; ++i) {
        projected[i].x = rotated[i].x + center.x;
        projected[i].y = rotated[i].y + center.y;
        projected[i].z = rotated[i].z + center.z;
        project(&projected[i], 80.0);
        projected[i].x += WIDTH/2.0;
		projected[i].y += HEIGHT/2.0;
    }

    // Draw lines between the projected points
    draw_line(projected[0].x, projected[0].y, projected[1].x, projected[1].y);
    draw_line(projected[0].x, projected[0].y, projected[2].x, projected[2].y);
    draw_line(projected[1].x, projected[1].y, projected[3].x, projected[3].y);
    draw_line(projected[2].x, projected[2].y, projected[3].x, projected[3].y);
    draw_line(projected[4].x, projected[4].y, projected[5].x, projected[5].y);
    draw_line(projected[4].x, projected[4].y, projected[6].x, projected[6].y);
    draw_line(projected[5].x, projected[5].y, projected[7].x, projected[7].y);
    draw_line(projected[6].x, projected[6].y, projected[7].x, projected[7].y);
    draw_line(projected[0].x, projected[0].y, projected[4].x, projected[4].y);
    draw_line(projected[1].x, projected[1].y, projected[5].x, projected[5].y);
    draw_line(projected[2].x, projected[2].y, projected[6].x, projected[6].y);
    draw_line(projected[3].x, projected[3].y, projected[7].x, projected[7].y);
}



void draw_cube(Cube *cube) {
	// Apply rotation matrix
	//multiply_matrix_matrix(&cube->rotation, &cube->transform, &cube->transform);

	// Apply transformation with offsets and draw the cube
	apply_transformation(cube);
}

void update_rotation_matrix(Cube *cube, float angle_x, float angle_y, float angle_z) {
    Matrix3x3 rot_x = get_rotation_matrix_x(angle_x);
    Matrix3x3 rot_y = get_rotation_matrix_y(angle_y);
    Matrix3x3 rot_z = get_rotation_matrix_z(angle_z);

    // Combine rotations: Z * Y * X
    Matrix3x3 temp;
    multiply_matrix_matrix(&rot_z, &rot_y, &temp);
    multiply_matrix_matrix(&temp, &rot_x, &cube->transform);
}


void on_ready() {
	int scale = 10;
	int offset = 0;
	for (int i = 0; i < 8; ++i) {
		Point* p = &cube0.p[i];
		p->x = p->x * scale + offset;
		p->y = p->y * scale + offset;
		p->z = p->z * scale + offset;
	}
}


float angle_x = 0.0;
float angle_y = 0.0;
float angle_z = 0.0;
void on_update() {
	clear_back_buffer();
	angle_x += 0.1;
	angle_y += 0.1;
	angle_z += 0.1;
	update_rotation_matrix(&cube0, angle_x, angle_y, angle_z);
	draw_cube(&cube0);
}


void on_button_pressed() {
}

#endif
