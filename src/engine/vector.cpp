#include "vector.hpp"

Vec3 Vec3::operator+(const Vec3& rhs) const {
	return Vec3{
		x + rhs.x,
		y + rhs.y,
		z + rhs.z
	};
}
Vec3 Vec3::operator-(const Vec3& rhs) const {
	return Vec3{
		x - rhs.x,
		y - rhs.y,
		z - rhs.z
	};
}
Vec3 Vec3::operator/(float value) const {
	return Vec3{
		x / value,
		y / value,
		z / value
	};
}

Vec4 Vec4::operator+(const Vec4& rhs) const {
	return Vec4{
		x + rhs.x,
		y + rhs.y,
		z + rhs.z,
		w + rhs.w
	};
}
Vec4 Vec4::operator/(float value) const {
	return Vec4{
		x / value,
		y / value,
		z / value,
		w / value
	};
}
