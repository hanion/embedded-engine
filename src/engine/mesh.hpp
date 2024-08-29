#pragma once
#include "renderer.hpp"
#include <cstdint>
#include <vector>

struct Vertex {
	float x,y,z;
};

using Index = uint8_t;

struct Face {
	Index indices[3];
	Color color;
};


struct Mesh {
	Mesh(const std::vector<Vertex>& vertices, const std::vector<Face>& faces)
	: vertices(vertices), faces(faces) {}

	std::vector<Vertex> vertices;
	std::vector<Face> faces;
};
