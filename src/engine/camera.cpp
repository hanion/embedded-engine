#include "camera.hpp"
#include <cmath>


Camera::Camera() {
	recalculate_perspective_projection();
	recalculate_view_projection();
}
Camera::Camera(Transform t) : transform(t) {
	recalculate_perspective_projection();
	recalculate_view_projection();
}

void Camera::recalculate_view_projection() {
	Mat4 view_matrix = Math::calculate_view_matrix(&transform);
	view_projection_matrix = Math::mat4_mul_mat4(&perspective_projection, &view_matrix);
}


void Camera::recalculate_perspective_projection() {
	perspective_projection = Math::mat4_make_perspective(fov * (M_PI / 180.0), 1, 1.0, 100.0);
}


void Camera::move(Vec3 v) {
	transform.x += v.x;
	transform.y += v.y;
	transform.z += v.z;
	recalculate_view_projection();
}

void Camera::move_x(float x) {
	transform.x += x;
	recalculate_view_projection();
}
void Camera::move_y(float y) {
	transform.y += y;
	recalculate_view_projection();
}
void Camera::move_z(float z) {
	transform.z += z;
	recalculate_view_projection();
}

void Camera::rotate(Vec3 v) {
	transform.rot_x += v.x;
	transform.rot_y += v.y;
	transform.rot_z += v.z;
	recalculate_view_projection();
}


void Camera::rotate_x(float x) {
	transform.rot_x += x;
	recalculate_view_projection();
}
void Camera::rotate_y(float y) {
	transform.rot_y += y;
	recalculate_view_projection();
}
void Camera::rotate_z(float z) {
	transform.rot_z += z;
	recalculate_view_projection();
}



void Camera::zoom(float f) {
	fov -= f;
	recalculate_perspective_projection();
	recalculate_view_projection();
}



