#pragma once
#include "base.hpp"


typedef struct {
    float x, y, z;
} Vec3;
typedef struct {
    float x, y, z, w;
} Vec4;


typedef struct {
	float m[4][4];
} Mat4;

typedef struct {
    float x, y, z;
    float rot_x, rot_y, rot_z;
    float scale_x, scale_y, scale_z;
} Transform;


class Math {
public:
	static Mat4 mat4_mul_mat4(const Mat4 *a, const Mat4 *b);
	static Vec4 mat4_mul_vec4(const Mat4 *m, const Vec4 *v);

	static Mat4 calculate_transform_matrix(const Transform *transform);
	static Mat4 calculate_view_matrix(const Transform *transform);


	static Mat4 mat4_make_perspective(float fov, float aspect, float znear, float zfar);
	static Vec4 mat4_mul_vec4_project(Mat4* mat_proj, Vec4* v);

	static Mat4 get_view_matrix(float cam_x, float cam_y, float cam_z);


	static Mat4 get_translation_matrix(float tx, float ty, float tz);
	static Mat4 get_rotation_matrix_x(float angle);
	static Mat4 get_rotation_matrix_y(float angle);
	static Mat4 get_rotation_matrix_z(float angle);
	static Mat4 get_scaling_matrix(float sx, float sy, float sz);
};

