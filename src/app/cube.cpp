#include "cube.hpp"
#include "mesh.hpp"
#include "renderer.hpp"
#include <math.h>

#include "model.hpp"

#include "../torus.cpp"


Transform model0 = {
	-6,0,0, 0,0,0, 5,5,5
};

Transform model1 = {
	6,0,0, 0,0,0, 3,3,3
};


void CubeDemo::on_ready() {
	m_rotation_speed = m_camera.fov * 0.38f;
}


void CubeDemo::on_update(double delta_time) {
	m_delta_time = delta_time;
	Renderer::clear_back_buffer();
	model0.rot_x += m_cube_speed * m_level;
	model0.rot_y += m_cube_speed * m_level;
	model0.rot_z += m_cube_speed * m_level;
	Renderer::draw_mesh(formatted_model, model0, m_camera);


	model1.rot_x += m_cube_speed * m_level;
	model1.rot_y += m_cube_speed * m_level;
	model1.rot_z += m_cube_speed * m_level;
	
	Renderer::draw_mesh(cube_mesh, model1, m_camera);
}





void CubeDemo::on_event(Event event) {
	if (event.type == Event::Type::Pressed) {
		if (event.keycode == 'r') {
			if (++m_level > 5) {
				m_level = 0;
			}
		}
	}
	
	if (event.type == Event::Type::Released) {
		return;
	}




	Vec3 movement = {0.0f, 0.0f, 0.0f};

	switch (event.keycode) {
		case 'w':
			movement += m_camera.forward() * m_speed * m_delta_time;
			break;
		case 's':
			movement -= m_camera.forward() * m_speed * m_delta_time;
			break;
		case 'a':
			movement -= m_camera.right() * m_speed * m_delta_time;
			break;
		case 'd':
			movement += m_camera.right() * m_speed * m_delta_time;
			break;
		case 'e':
			movement += UP_VECTOR * m_speed * m_delta_time;
			break;
		case 'q':
			movement -= UP_VECTOR * m_speed * m_delta_time;
			break;
		case 'i':
			m_camera.rotate_x(-m_rotation_speed * m_delta_time);
			break;
		case 'k':
			m_camera.rotate_x(m_rotation_speed * m_delta_time);
			break;
		case 'j':
			m_camera.rotate_y(-m_rotation_speed * m_delta_time);
			break;
		case 'l':
			m_camera.rotate_y(m_rotation_speed * m_delta_time);
			break;
		case 'z':
			m_camera.zoom(m_zoom_speed * m_delta_time);
			m_rotation_speed = m_camera.fov * 0.33f;
			break;
		case 'x':
			m_camera.zoom(-m_zoom_speed * m_delta_time);
			m_rotation_speed = m_camera.fov * 0.33f;
			break;
		default:
			break;
	}

	if (movement.x || movement.y || movement.z) {
		m_camera.transform.x += movement.x;
		m_camera.transform.y += movement.y;
		m_camera.transform.z += movement.z;
		m_camera.recalculate_view_projection();
	}
}




