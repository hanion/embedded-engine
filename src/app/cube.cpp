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


void CubeDemo::recalculate_view_projection() {
	Mat4 view_matrix = Math::calculate_view_matrix(&m_camera);
	m_view_projection_matrix = Math::mat4_mul_mat4(&perspective_projection, &view_matrix);
}

void CubeDemo::on_ready() {
	perspective_projection = Math::mat4_make_perspective(3.5 * (M_PI / 180.0), 1, 1.0, 100.0);
	recalculate_view_projection();
}


void CubeDemo::on_update() {
	Renderer::clear_back_buffer();
	model0.rot_x += m_speed * m_level;
	model0.rot_y += m_speed * m_level;
	model0.rot_z += m_speed * m_level;
	Renderer::draw_mesh(formatted_model, model0, m_view_projection_matrix);


	model1.rot_x += m_speed * m_level;
	model1.rot_y += m_speed * m_level;
	model1.rot_z += m_speed * m_level;
	
	Renderer::draw_mesh(cube_mesh, model1, m_view_projection_matrix);
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
			m_camera.z += speed;
			recalculate_view_projection();
			break;
		case 's':
			m_camera.z -= speed;
			recalculate_view_projection();
			break;
		case 'a':
			m_camera.x -= speed;
			recalculate_view_projection();
			break;
		case 'd':
			m_camera.x += speed;
			recalculate_view_projection();
			break;
		case 'i':
			m_camera.rot_x -= rotation_speed;
			recalculate_view_projection();
			break;
		case 'k':
			m_camera.rot_x += rotation_speed;
			recalculate_view_projection();
			break;
		case 'j':
			m_camera.rot_y -= rotation_speed;
			recalculate_view_projection();
			break;
		case 'l':
			m_camera.rot_y += rotation_speed;
			recalculate_view_projection();
			break;
		default:
			break;
	}
}




