#pragma once

#include "base.hpp"
#include "camera.hpp"
#include "math.hpp"
#include "mesh.hpp"
#include <stdint.h>


namespace EE {


typedef struct {
	int32_t x, y;
	int32_t width, height;
} Rect;


typedef struct {
	uint8_t x, y;
	Color color;
} Pixel;


class Renderer {
public:
	static uint8_t (*front_buffer)[WIDTH][HEIGHT];
	static uint8_t (*back_buffer)[WIDTH][HEIGHT];
	static bool is_back_buffer_new;

	static void swap_buffers(void);

	static void clear_back_buffer(void);
	static void set_pixel(int x, int y, const Color& color);
	static void set_Pixel(Pixel pixel);

	static void draw_line(int x0, int y0, int x1, int y1);
	static void draw_line(int x0, int y0, int x1, int y1, Color color);

	static void draw_rect(uint8_t x, uint8_t y, uint8_t width, uint8_t height, Color color);
	static void draw_Rect(Rect rect, Color color);

	static void draw_number(int num, int x, int y, bool bold = false);
	static void draw_text(const char *text, int x, int y, bool bold = false);
	static int calculate_text_width(const char* text, bool bold = false);
	static int calculate_number_width(int number, bool bold = false);

	static void draw_mesh(const Mesh& mesh, const Transform& transform, const Camera& camera);
	inline static Vec3 calculate_face_normal(const Vec3& v0, const Vec3& v1, const Vec3& v2);
	inline static Vec3 calculate_face_normal(const Vec3& v0, const Vec3& v1, const Vec3& v2, const Vec3& v3);


	static void fill_face(const std::vector<Vec4>& vertices, const Index indices[4], const Color& color);
};





}


