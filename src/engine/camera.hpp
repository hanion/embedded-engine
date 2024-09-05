#pragma once
#include "math.hpp"

namespace EE {

class Camera {
public:
	Camera();
	Camera(Transform t);

	void recalculate_perspective_projection();
	void recalculate_view_projection();

	void move(Vec3 v);
	void move_x(float x);
	void move_y(float y);
	void move_z(float z);

	void rotate(Vec3 v);
	void rotate_x(float x);
	void rotate_y(float y);
	void rotate_z(float z);

	void zoom(float fov);

public:
	Transform transform = {
		.x = 0, .y = 0, .z = -15,
		.rot_x = 0, .rot_y = 0, .rot_z = 0,
		.scale_x = 1, .scale_y = 1, .scale_z = 1,
	};

	Mat4 view_projection_matrix;
	Mat4 perspective_projection;

	float fov = 3.5f;
};

}
