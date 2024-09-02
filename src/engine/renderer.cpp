#include "renderer.hpp"
#include "mesh.hpp"
#include "base.hpp"


#include <algorithm>
#include <cmath>
#include <limits>
#include <stdlib.h>
#include <string.h>
#include <vector>

uint8_t buffer1[WIDTH][HEIGHT];
uint8_t buffer2[WIDTH][HEIGHT];

uint8_t (*Renderer::front_buffer)[WIDTH][HEIGHT] = &buffer1;
uint8_t (*Renderer::back_buffer)[WIDTH][HEIGHT] = &buffer2;

bool Renderer::is_back_buffer_new = false;

void Renderer::swap_buffers() {
	uint8_t (*temp)[WIDTH][HEIGHT] = front_buffer;
	front_buffer = back_buffer;
	back_buffer = temp;
}


void Renderer::clear_back_buffer(void) {
	static_assert(sizeof(buffer1) == sizeof(buffer2), "");
	memset((*back_buffer), 0, sizeof(buffer1));
}

void Renderer::set_pixel(int x, int y, const Color& color) {
	if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT) {
		return;
	}

	(*back_buffer)[x][y] = color.value;
}




// Bresenham's line algorithm
// (https://en.wikipedia.org/wiki/Bresenham's_line_algorithm)
void Renderer::draw_line(int x0, int y0, int x1, int y1) {
	draw_line(x0, y0, x1, y1, {1});
}
void Renderer::draw_line(int x0, int y0, int x1, int y1, Color color) {
	if ((x0 < 0 && x1 < 0) || (x0 > WIDTH && x1 > WIDTH) ||
		(y0 < 0 && y1 < 0) || (y0 > HEIGHT && y1 > HEIGHT)) {
		return;
	}


	int dx = abs(x1 - x0);
	int sx = (x0 < x1) ? 1 : -1;
	int dy = -abs(y1 - y0);
	int sy = (y0 < y1) ? 1 : -1;
	int error = dx + dy;

	while (1) {
		if (x0 >= 0 && x0 < WIDTH && y0 >= 0 && y0 < HEIGHT) {
			set_pixel(x0, y0, color);
		}

		if (x0 == x1 && y0 == y1) {
			break;
		}

		int e2 = 2 * error;
		if (e2 >= dy) {
			if (x0 == x1) {
				break;
			}
			error += dy;
			x0 += sx;
		}
		if (e2 <= dx) {
			if (y0 == y1) {
				break;
			}
			error += dx;
			y0 += sy;
		}
	}
}

void Renderer::draw_rect(uint8_t x, uint8_t y, uint8_t width, uint8_t height, Color color) {
	for (uint8_t i = y; i < y + height && i < HEIGHT; ++i) {
		for (uint8_t j = x; j < x + width && j < WIDTH; ++j) {
			set_pixel(j, i, color);
		}
	}
}
void Renderer::draw_Rect(Rect rect, Color color) {
	draw_rect(rect.x, rect.y, rect.width, rect.height, color);
}



const uint8_t text_bitmaps[69][5] = {
    { 0x7E, 0x11, 0x11, 0x11, 0x7E }, // A
    { 0x7F, 0x49, 0x49, 0x49, 0x36 }, // B
    { 0x3E, 0x41, 0x41, 0x41, 0x22 }, // C
    { 0x7F, 0x41, 0x41, 0x22, 0x1C }, // D
    { 0x7F, 0x49, 0x49, 0x49, 0x41 }, // E
    { 0x7F, 0x09, 0x09, 0x09, 0x01 }, // F
    { 0x3E, 0x41, 0x49, 0x49, 0x7A }, // G
    { 0x7F, 0x08, 0x08, 0x08, 0x7F }, // H
    { 0x00, 0x41, 0x7F, 0x41, 0x00 }, // I
    { 0x20, 0x40, 0x41, 0x3F, 0x01 }, // J
    { 0x7F, 0x08, 0x14, 0x22, 0x41 }, // K
    { 0x7F, 0x40, 0x40, 0x40, 0x40 }, // L
    { 0x7F, 0x02, 0x04, 0x02, 0x7F }, // M
    { 0x7F, 0x04, 0x08, 0x10, 0x7F }, // N
    { 0x3E, 0x41, 0x41, 0x41, 0x3E }, // O
    { 0x7F, 0x09, 0x09, 0x09, 0x06 }, // P
    { 0x3E, 0x41, 0x51, 0x21, 0x5E }, // Q
    { 0x7F, 0x09, 0x19, 0x29, 0x46 }, // R
    { 0x46, 0x49, 0x49, 0x49, 0x31 }, // S
    { 0x01, 0x01, 0x7F, 0x01, 0x01 }, // T
    { 0x3F, 0x40, 0x40, 0x40, 0x3F }, // U
    { 0x1F, 0x20, 0x40, 0x20, 0x1F }, // V
    { 0x7F, 0x20, 0x18, 0x20, 0x7F }, // W
    { 0x63, 0x14, 0x08, 0x14, 0x63 }, // X
    { 0x03, 0x04, 0x78, 0x04, 0x03 }, // Y
    { 0x61, 0x51, 0x49, 0x45, 0x43 }, // Z

	{ 0x20, 0x54, 0x54, 0x54, 0x78 },  // a
	{ 0x7F, 0x48, 0x44, 0x44, 0x38 },  // b
	{ 0x38, 0x44, 0x44, 0x44, 0x20 },  // c
	{ 0x38, 0x44, 0x44, 0x48, 0x7F },  // d
	{ 0x38, 0x54, 0x54, 0x54, 0x18 },  // e
	{ 0x08, 0x7E, 0x09, 0x01, 0x02 },  // f
	{ 0x0C, 0x52, 0x52, 0x52, 0x3E },  // g
	{ 0x7F, 0x08, 0x04, 0x04, 0x78 },  // h
	{ 0x00, 0x44, 0x7D, 0x40, 0x00 },  // i
	{ 0x20, 0x40, 0x44, 0x3D, 0x00 },  // j
	{ 0x7F, 0x10, 0x28, 0x44, 0x00 },  // k
	{ 0x00, 0x41, 0x7F, 0x40, 0x00 },  // l
	{ 0x7C, 0x04, 0x18, 0x04, 0x78 },  // m
	{ 0x7C, 0x08, 0x04, 0x04, 0x78 },  // n
	{ 0x38, 0x44, 0x44, 0x44, 0x38 },  // o
	{ 0x7C, 0x14, 0x14, 0x14, 0x08 },  // p
	{ 0x08, 0x14, 0x14, 0x18, 0x7C },  // q
	{ 0x7C, 0x08, 0x04, 0x04, 0x08 },  // r
	{ 0x48, 0x54, 0x54, 0x54, 0x20 },  // s
	{ 0x04, 0x3F, 0x44, 0x40, 0x20 },  // t
	{ 0x3C, 0x40, 0x40, 0x20, 0x7C },  // u
	{ 0x1C, 0x20, 0x40, 0x20, 0x1C },  // v
	{ 0x3C, 0x40, 0x38, 0x40, 0x3C },  // w
	{ 0x44, 0x28, 0x10, 0x28, 0x44 },  // x
	{ 0x0C, 0x50, 0x50, 0x50, 0x3C },  // y
	{ 0x44, 0x64, 0x54, 0x4C, 0x44 },  // z

	{ 0x00, 0x00, 0x00, 0x00, 0x00 }, // SPACE
	{ 0x00, 0x6F, 0x6F, 0x00, 0x00 }, // !
    { 0x0A, 0x0E, 0x00, 0x0A, 0x0E }, // ?
	{ 0x00, 0x60, 0x60, 0x00, 0x00 }, // .
    { 0x00, 0x20, 0x10, 0x08, 0x00 }, // ,
    { 0x00, 0x00, 0x1F, 0x00, 0x00 }, // -
    { 0x00, 0x03, 0x04, 0x03, 0x00 }, // '
	{ 0x3E, 0x51, 0x49, 0x45, 0x3E }, // 0
	{ 0x00, 0x42, 0x7F, 0x40, 0x00 }, // 1
	{ 0x62, 0x51, 0x49, 0x49, 0x46 }, // 2
	{ 0x22, 0x41, 0x49, 0x49, 0x36 }, // 3
	{ 0x18, 0x14, 0x12, 0x7F, 0x10 }, // 4
	{ 0x27, 0x45, 0x45, 0x45, 0x39 }, // 5
	{ 0x3E, 0x49, 0x49, 0x49, 0x30 }, // 6
	{ 0x01, 0x01, 0x71, 0x0D, 0x03 }, // 7
	{ 0x36, 0x49, 0x49, 0x49, 0x36 }, // 8
	{ 0x06, 0x49, 0x49, 0x29, 0x1E }  // 9
};
#define FONT_WIDTH 5
#define FONT_HEIGHT 7


void set_pixel_w_bold(int x, int y, uint8_t w) {
	Renderer::set_pixel(x  , y  , w);
	Renderer::set_pixel(x+1, y  , w);
	Renderer::set_pixel(x  , y+1, w);
	Renderer::set_pixel(x+1, y+1, w);
}

void draw_digit(uint8_t num, int x, int y, bool bold) {
	if (num > 9) {
		return;
	}
	if (x > WIDTH || y > HEIGHT) {
		return;
	}
	if (x < -FONT_WIDTH - FONT_WIDTH*bold || y < -FONT_HEIGHT - FONT_HEIGHT*bold) {
		return;
	}

	for (uint8_t col = 0; col < FONT_WIDTH; ++col) {
		uint8_t col_bitmap = text_bitmaps[num+59][col];

		for (uint8_t row = 0; row < FONT_HEIGHT; ++row) {
			if (col_bitmap & (1 << row)) {
				if (bold) {
					set_pixel_w_bold(x + 2 * col, y + 2 * row, 1);
				} else {
					Renderer::set_pixel(x + col, y + row, 1);
				}
			}
		}
	}
}

void Renderer::draw_number(int num, int x, int y, bool bold) {
	if (num == 0) {
		draw_digit(0, x, y, bold);
		return;
	}

	uint8_t digit_count = 0;
	int tmp = num;
	while (tmp > 0) {
		tmp /= 10;
		digit_count++;
	}

	uint8_t digit_width = bold ? (FONT_WIDTH * 2) : FONT_WIDTH;
	for (int i = digit_count - 1; i >= 0; --i) {
		int digit = num % 10;
		draw_digit(digit, x + i * (digit_width + 1), y, bold);
		num /= 10;
	}
}


void draw_char(char c, int x, int y, bool bold) {
	if (x > WIDTH || y > HEIGHT) {
		return;
	}
	if (x < -FONT_WIDTH - FONT_WIDTH*bold || y < -FONT_HEIGHT - FONT_HEIGHT*bold) {
		return;
	}

	uint8_t index;
	if (c >= 'A' && c <= 'Z') {
		index = c - 'A';
	} else if (c >= 'a' && c <= 'z') {
		index = c - 'a' + 26;
	} else if (c >= '0' && c <= '9') {
		index = c - '0' + 59;
	} else if (c == ' ') {
		index = 52;
	} else if (c == '!') {
		index = 53;
	} else if (c == '?') {
		index = 54;
	} else if (c == '.') {
		index = 55;
	} else if (c == ',') {
		index = 56;
	} else if (c == '-') {
		index = 57;
	} else if (c == '\'') {
		index = 58;
	} else {
		return;
	}

	for (uint8_t col = 0; col < FONT_WIDTH; ++col) {
		uint8_t col_bitmap = text_bitmaps[index][col];

		for (uint8_t row = 0; row < FONT_HEIGHT; ++row) {
			if (col_bitmap & (1 << row)) {
				if (bold) {
					set_pixel_w_bold(x + 2 * col, y + 2 * row, 1);
				} else {
					Renderer::set_pixel(x + col, y + row, 1);
				}
			}
		}
	}
}

void Renderer::draw_text(const char *text, int x, int y, bool bold) {
	while (*text) {
		draw_char(*text++, x, y, bold);
		x += FONT_WIDTH + 1 + FONT_WIDTH*bold;
	}
}

const int Renderer::calculate_text_width(const char* text, bool bold) {
	int width = 0;
	uint8_t char_width = bold ? FONT_WIDTH * 2 : FONT_WIDTH;

	while (*text) {
		width += char_width + 1;
		text++;
	}

	return width > 0 ? width - 1 : 0;
}

const int Renderer::calculate_number_width(int number, bool bold) {
	uint8_t digit_width = FONT_WIDTH;
	int width = 0;

	if (number == 0) {
		width += digit_width + 1;
	} else {
		while (number > 0) {
			width += digit_width + 1 + digit_width*bold;
			number /= 10;
		}
	}
	return width > 0 ? width - 1 : 0;
}






void Renderer::draw_mesh(const Mesh& mesh, const Transform& transform, const Camera& camera) {
	Mat4 transform_matrix = Math::calculate_transform_matrix(&transform);
	Mat4 transform_proj_matrix = Math::mat4_mul_mat4(&camera.view_projection_matrix, &transform_matrix);

	std::vector<Vec4> transformed_vertices(mesh.vertices.size());
	std::vector<bool> vertex_valid(mesh.vertices.size(), true);

	for (int i = 0; i < mesh.vertices.size(); ++i) {
		Vec4 model_space = { mesh.vertices[i].x, mesh.vertices[i].y, mesh.vertices[i].z, 1.0f };

		transformed_vertices[i] = Math::mat4_mul_vec4_project(&transform_proj_matrix, &model_space);

		// center
		transformed_vertices[i].x += (float)WIDTH/2.0;
		transformed_vertices[i].y += (float)HEIGHT/2.0;
		// flip y
		transformed_vertices[i].y = (float)HEIGHT - transformed_vertices[i].y;
		
		// depth culling
		if (transformed_vertices[i].z <= -1.0f || transformed_vertices[i].w < 0.0f) {
			vertex_valid[i] = false;
			continue;
		}
	}

	for (const Face& face : mesh.faces) {
		if (std::any_of(face.indices, face.indices + 4, [&](Index i) { return !vertex_valid[i]; })) {
			continue;
		}

		Vec4 v0 = transformed_vertices[face.indices[0]];
		Vec4 v1 = transformed_vertices[face.indices[1]];
		Vec4 v2 = transformed_vertices[face.indices[2]];
		Vec4 v3 = transformed_vertices[face.indices[3]];

		Vec4 face_centroid = (v0 + v1 + v2 + v3) / 4.0f;
		Vec3 view_dir = { -face_centroid.x, -face_centroid.y, -face_centroid.z };

		Vec3 face_normal = calculate_face_normal(v0.vec3(),v1.vec3(),v2.vec3());
		//Vec3 face_normal = calculate_face_normal(v0.vec3(),v1.vec3(),v2.vec3(),v3.vec3());

		float dot_product = Math::dot(view_dir, face_normal);

		// backface culling
		if (dot_product > 0) {
			continue;
		}

		// NOTE: too slow
		// fill_face(transformed_vertices, face.indices, face.color);
		// continue;

		for (size_t i = 0; i < 4; ++i) {
			const Index& current = face.indices[i];
			const Index& next = face.indices[(i + 1) % 4];

			const Vec4& a = transformed_vertices[current];
			const Vec4& b = transformed_vertices[next];

			Renderer::draw_line(a.x, a.y, b.x, b.y, face.color);
		}
	}
}

Vec3 Renderer::calculate_face_normal(const Vec3& v0, const Vec3& v1, const Vec3& v2) {
    Vec3 edge1 = v1 - v0;
    Vec3 edge2 = v2 - v0;
    return Math::normalize(Math::cross(edge1, edge2));
}

Vec3 Renderer::calculate_face_normal(const Vec3& v0, const Vec3& v1, const Vec3& v2, const Vec3& v3) {
	Vec3 edge1 = v1 - v0;
	Vec3 edge2 = v2 - v0;
	Vec3 edge3 = v3 - v0;

	Vec3 normal1 = Math::normalize(Math::cross(edge1, edge2));
	Vec3 normal2 = Math::normalize(Math::cross(edge2, edge3));

	return Math::normalize(normal1 + normal2);
}






void Renderer::fill_face(const std::vector<Vec4>& vertices, const Index indices[4], const Color& color) {
	Index sorted_indices[4] = { indices[0], indices[1], indices[2], indices[3] };
	for (int i = 0; i < 4; ++i) {
		for (int j = i + 1; j < 4; ++j) {
			if (vertices[sorted_indices[i]].y > vertices[sorted_indices[j]].y) {
				std::swap(sorted_indices[i], sorted_indices[j]);
			}
		}
	}

	for (float y = vertices[sorted_indices[0]].y; y <= vertices[sorted_indices[3]].y; y++) {
		std::vector<float> x_intersections;
		for (int i = 0; i < 4; ++i) {
			int j = (i + 1) % 4;
			const Vec4& v1 = vertices[sorted_indices[i]];
			const Vec4& v2 = vertices[sorted_indices[j]];

			if ((v1.y <= y && v2.y >= y) || (v2.y <= y && v1.y >= y)) {
				float t = (y - v1.y) / (v2.y - v1.y);
				float x = v1.x + t * (v2.x - v1.x);
				x_intersections.push_back(x);
			}
		}

		std::sort(x_intersections.begin(), x_intersections.end());

		for (size_t i = 0; i < x_intersections.size(); i += 2) {
			draw_line(x_intersections[i], y, x_intersections[i + 1], y, color);
		}
	}
}

