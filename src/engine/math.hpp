#pragma once
#include "base.hpp"


struct Vec3 {
	float x, y, z;
	Vec3() : x(0), y(0), z(0) {}
	Vec3(float x, float y, float z) : x(x), y(y), z(z) {}

	Vec3 operator+(const Vec3& rhs) const;
	Vec3 operator-(const Vec3& rhs) const;
	Vec3 operator/(float value) const;
};

struct Vec4 {
	float x, y, z, w;

	Vec4() : x(0), y(0), z(0), w(0) {}
	Vec4(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {}

	Vec4(Vec3 vec3) : x(vec3.x), y(vec3.y), z(vec3.z), w(1) {}
	Vec4(Vec3 vec3, float w) : x(vec3.x), y(vec3.y), z(vec3.z), w(w) {}

	inline Vec3 vec3() const {
		return {x,y,z};
	}

	Vec4 operator+(const Vec4& rhs) const;
	Vec4 operator/(float value) const;
};

struct Mat4 {
	float m[4][4];
};

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

	static Vec3 normalize(const Vec3& v);
	static Vec3 cross(const Vec3& a, const Vec3& b);
	static float dot(const Vec3& a, const Vec3& b);

};

