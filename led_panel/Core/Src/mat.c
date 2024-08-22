/*
 * mat.c
 *
 *  Created on: Aug 21, 2024
 *      Author: han
 */


#include "mat.h"
#include "base.h"
#include "main.h"
#include <math.h>
#include <stdlib.h>
#include <string.h>

Mat4 get_translation_matrix(float tx, float ty, float tz);
Mat4 get_rotation_matrix_x(float angle);
Mat4 get_rotation_matrix_y(float angle);
Mat4 get_rotation_matrix_z(float angle);
Mat4 get_scaling_matrix(float sx, float sy, float sz);



Mat4 mat4_mul_mat4(const Mat4 *a, const Mat4 *b) {
	Mat4 result;
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			result.m[i][j] = 0.0;
			for (int k = 0; k < 4; ++k) {
				result.m[i][j] += a->m[i][k] * b->m[k][j];
			}
		}
	}
	return result;
}

Vec4 mat4_mul_vec4(const Mat4 *m, const Vec4 *v) {
	Vec4 result;
    result.x = m->m[0][0] * v->x + m->m[0][1] * v->y + m->m[0][2] * v->z + m->m[0][3] * v->w;
    result.y = m->m[1][0] * v->x + m->m[1][1] * v->y + m->m[1][2] * v->z + m->m[1][3] * v->w;
    result.z = m->m[2][0] * v->x + m->m[2][1] * v->y + m->m[2][2] * v->z + m->m[2][3] * v->w;
    result.w = m->m[3][0] * v->x + m->m[3][1] * v->y + m->m[3][2] * v->z + m->m[3][3] * v->w;
    return result;
}

Mat4 mat4_make_perspective(float fov, float aspect, float znear, float zfar) {
	Mat4 m = {0};
	m.m[0][0] = aspect * (1 / tan(fov/2));
	m.m[1][1] = 1 / tan(fov/2);
	m.m[2][2] = zfar / (zfar - znear);
	m.m[2][3] = (-zfar * znear) / (zfar - znear);
	m.m[3][2] = 1.0;
	return m;
}

Vec4 mat4_mul_vec4_project(Mat4* mat_proj, Vec4* v) {
	Vec4 result = mat4_mul_vec4(mat_proj, v);

	if (result.w != 0.0) {
		result.x /= result.w;
		result.y /= result.w;
		result.z /= result.w;
	}
	return result;
}




Mat4 get_translation_matrix(float tx, float ty, float tz) {
	Mat4 mat = {{
		{1, 0, 0, tx},
		{0, 1, 0, ty},
		{0, 0, 1, tz},
		{0, 0, 0, 1}
	}};
	return mat;
}
Mat4 get_rotation_matrix_x(float angle) {
	Mat4 mat = {{
		{1, 0, 0, 0},
		{0, cos(angle), -sin(angle), 0},
		{0, sin(angle), cos(angle), 0},
		{0, 0, 0, 1}
	}};
	return mat;
}

Mat4 get_rotation_matrix_y(float angle) {
	Mat4 mat = {{
		{cos(angle), 0, sin(angle), 0},
		{0, 1, 0, 0},
		{-sin(angle), 0, cos(angle), 0},
		{0, 0, 0, 1}
	}};
	return mat;
}

Mat4 get_rotation_matrix_z(float angle) {
	Mat4 mat = {{
		{cos(angle), -sin(angle), 0, 0},
		{sin(angle), cos(angle), 0, 0},
		{0, 0, 1, 0},
		{0, 0, 0, 1}
	}};
	return mat;
}
Mat4 get_scaling_matrix(float sx, float sy, float sz) {
	Mat4 mat = {{
		{sx, 0, 0, 0},
		{0, sy, 0, 0},
		{0, 0, sz, 0},
		{0, 0, 0, 1}
	}};
	return mat;
}


Mat4 get_view_matrix(float cam_x, float cam_y, float cam_z) {
	return get_translation_matrix(-cam_x, -cam_y, -cam_z);
}



Mat4 calculate_transform_matrix(const Transform *transform) {
	Mat4 rotation_x = get_rotation_matrix_x(transform->rot_x);
	Mat4 rotation_y = get_rotation_matrix_y(transform->rot_y);
	Mat4 rotation_z = get_rotation_matrix_z(transform->rot_z);
	Mat4 rotation_combined = mat4_mul_mat4(&rotation_z, &rotation_y);
	rotation_combined = mat4_mul_mat4(&rotation_combined, &rotation_x);

	Mat4 scaling = get_scaling_matrix(transform->scale_x, transform->scale_y, transform->scale_z);

	Mat4 translation = get_translation_matrix(transform->x, transform->y, transform->z);

	Mat4 transform_matrix;
	transform_matrix = mat4_mul_mat4(&scaling, &rotation_combined);
	transform_matrix = mat4_mul_mat4(&translation, &transform_matrix);
	return transform_matrix;
}
