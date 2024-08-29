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
