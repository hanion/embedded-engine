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
}


void CubeDemo::on_update(double delta_time) {
	Renderer::clear_back_buffer();
	model0.rot_x += m_speed * m_level;
	model0.rot_y += m_speed * m_level;
	model0.rot_z += m_speed * m_level;
	Renderer::draw_mesh(formatted_model, model0, m_camera);


	model1.rot_x += m_speed * m_level;
	model1.rot_y += m_speed * m_level;
	model1.rot_z += m_speed * m_level;
	
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


	float speed = 0.2f;
	float rotation_speed = 0.01f;

	switch (event.keycode) {
		case 'w':
			m_camera.move_z(speed);
			break;
		case 's':
			m_camera.move_z(-speed);
			break;
		case 'a':
			m_camera.move_x(-speed);
			break;
		case 'd':
			m_camera.move_x(speed);
			break;
		case 'e':
			m_camera.move_y(speed);
			break;
		case 'q':
			m_camera.move_y(-speed);
			break;
		case 'i':
			m_camera.rotate_x(-rotation_speed);
			break;
		case 'k':
			m_camera.rotate_x(rotation_speed);
			break;
		case 'j':
			m_camera.rotate_y(-rotation_speed);
			break;
		case 'l':
			m_camera.rotate_y(rotation_speed);
			break;
		case 'z':
			m_camera.zoom(speed/8.0f);
			break;
		case 'x':
			m_camera.zoom(-speed/8.0f);
			break;
		default:
			break;
	}
}




