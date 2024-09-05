#pragma once
#include "base.hpp"
#include <cmath>
#include <algorithm>

#define UP_VECTOR Vec3{0.0f, 1.0f, 0.0f}

struct Vec3 {
	float x, y, z;
	Vec3() : x(0), y(0), z(0) {}
	Vec3(float x, float y, float z) : x(x), y(y), z(z) {}

	Vec3 normalized() const;

	Vec3 operator+(const Vec3& rhs) const;
	void operator+=(const Vec3& rhs);
	void operator-=(const Vec3& rhs);
	Vec3 operator-(const Vec3& rhs) const;
	Vec3 operator/(float value) const;
	Vec3 operator*(float value) const;
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



struct vi2 {
	int x, y;

	vi2() : x(0), y(0) {}
	vi2(int x, int y) : x(x), y(y) {}
};
struct vf2 {
	float x, y;

	vf2() : x(0), y(0) {}
	vf2(float x, float y) : x(x), y(y) {}

	vf2 normalized() const {
		float length = std::sqrt(x * x + y * y);

		if (length == 0) {
			return {0, 0};
		}

		return { x / length, y / length };
	}

	vf2 rotated_z(float angle) const {
		float radians = angle * (M_PI / 180.0f);
		float cos_angle = std::cos(radians);
		float sin_angle = std::sin(radians);

		return {
			x * cos_angle - y * sin_angle,
			x * sin_angle + y * cos_angle
		};
	}

	float dot(const vf2& other) const {
		vf2 norm = normalized();
		vf2 other_norm = other.normalized();

		float dot_product = norm.x * other_norm.x + norm.y * other_norm.y;

		if (dot_product > 1.0f) {
			dot_product = 1.0f;
		} else if (dot_product < -1.0f) {
			dot_product = -1.0f;
		}

		return dot_product;
	}

	vf2 operator*(float f) const {
		return { x*f, y*f };
	}
	vf2 operator/(float f) const {
		return { x/f, y/f };
	}
	vf2 operator+(const vf2& other) const {
		return { x+other.x, y+other.y };
	}
	vf2 operator-(const vf2& other) const {
		return { x-other.x, y-other.y };
	}
	void operator+=(const vf2& other) {
		x += other.x;
		y += other.y;
	}
	void operator-=(const vf2& other) {
		x -= other.x;
		y -= other.y;
	}
	bool operator==(const vf2& other) {
		return (x == other.x) && (y == other.y);
	}
	bool operator!=(const vf2& other) {
		return !(*this == other);
	}
};
