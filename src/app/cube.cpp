#include "cube.hpp"
#include "renderer.hpp"
#include <math.h>





// 0 2
// 1 3
//     4 6
//     5 7
Cube cube0 = {
    .p = {
		{-1, -1, -1},
		{-1,  1, -1},
		{ 1, -1, -1},
		{ 1,  1, -1},
		{-1, -1,  1},
		{-1,  1,  1},
		{ 1, -1,  1},
		{ 1,  1,  1}
	},
	.edges = {
		{0, 1}, {1, 3}, {3, 2}, {2, 0},
		{4, 5}, {5, 7}, {7, 6}, {6, 4},
		{0, 4}, {1, 5}, {2, 6}, {3, 7}
	},
    .transform = { -6,0,0, 0,0,0, 3,3,3 }
};


Cube pyramid0 = {
    .p = {
		{-1,  1, -1}, // 0 left  front
		{ 1,  1, -1}, // 1 right front
		{-1,  1,  1}, // 2 left  back
		{ 1,  1,  1}, // 3 right back
		{ 0, -1,  0}, // 4 top
		{ 0, -1,  0},
		{ 0, -1,  0},
		{ 0, -1,  0},
	},
    .edges = {
        {0, 1}, {0, 2}, {3, 2}, {3, 1},
        {4, 0}, {4, 1}, {4, 2}, {4, 3},
        {4, 0}, {4, 1}, {4, 2}, {4, 3}
    },
    .transform = { 6,0,0, 0,0,0, 3,3,3 }
};



void CubeDemo::draw_cube(Cube *cube) {
	Mat4 transform_matrix = Math::calculate_transform_matrix(&cube->transform);
	Mat4 transform_proj_matrix = Math::mat4_mul_mat4(&m_view_projection_matrix, &transform_matrix);

	Vec4 transformed[POINT_COUNT];
	for (int i = 0; i < POINT_COUNT; ++i) {
		Vec4 model_space = { cube->p[i].x, cube->p[i].y, cube->p[i].z, 1.0 };

		transformed[i] = Math::mat4_mul_vec4_project(&transform_proj_matrix, &model_space);

		// center
		transformed[i].x += (float)WIDTH/2.0;
		transformed[i].y += (float)HEIGHT/2.0;
	}

	Color color = 1;
	for (int i = 0; i < EDGE_COUNT; ++i) {
		Vec4 a = transformed[cube->edges[i][0]];
		Vec4 b = transformed[cube->edges[i][1]];
 		//Renderer::draw_line(a.x, a.y, b.x, b.y);
		Renderer::draw_line_colored(a.x, a.y, b.x, b.y, color);
		if (++color.value == 8) {
			color.value = 1;
		}
	}
}


void CubeDemo::on_ready() {
	Mat4 perspective_projection = Math::mat4_make_perspective(4.0 * (M_PI / 180.0), 1, 1.0, 100.0);
	Mat4 view_matrix = Math::get_view_matrix(0, 0, -15); // camera position
	m_view_projection_matrix = Math::mat4_mul_mat4(&perspective_projection, &view_matrix);
}


void CubeDemo::on_update() {
	Renderer::clear_back_buffer();
	cube0.transform.rot_x += m_speed * m_level;
	cube0.transform.rot_y += m_speed * m_level;
	cube0.transform.rot_z += m_speed * m_level;
	draw_cube(&cube0);


	pyramid0.transform.rot_x += m_speed * m_level;
	pyramid0.transform.rot_y += m_speed * m_level;
	pyramid0.transform.rot_z += m_speed * m_level;
	draw_cube(&pyramid0);
}




void CubeDemo::on_event(Event event) {
	if (event.type == Event::Type::Pressed) {
		if (++m_level > 5) {
			m_level = 0;
		}
	}
}




