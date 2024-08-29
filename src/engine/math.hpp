#pragma once
#include "base.hpp"
#include "vector.hpp"


struct Mat4 {
	float m[4][4];
};

typedef struct {
    float x, y, z;
    float rot_x, rot_y, rot_z;
    float scale_x, scale_y, scale_z;
} Transform;


namespace Math {

Mat4 mat4_mul_mat4(const Mat4 *a, const Mat4 *b);
Vec4 mat4_mul_vec4(const Mat4 *m, const Vec4 *v);

Mat4 calculate_transform_matrix(const Transform *transform);
Mat4 calculate_view_matrix(const Transform *transform);


Mat4 mat4_make_perspective(float fov, float aspect, float znear, float zfar);
Vec4 mat4_mul_vec4_project(Mat4* mat_proj, Vec4* v);

Mat4 get_view_matrix(float cam_x, float cam_y, float cam_z);


Mat4 get_translation_matrix(float tx, float ty, float tz);
Mat4 get_rotation_matrix_x(float angle);
Mat4 get_rotation_matrix_y(float angle);
Mat4 get_rotation_matrix_z(float angle);
Mat4 get_scaling_matrix(float sx, float sy, float sz);

Vec3 normalize(const Vec3& v);
Vec3 cross(const Vec3& a, const Vec3& b);
float dot(const Vec3& a, const Vec3& b);

};

