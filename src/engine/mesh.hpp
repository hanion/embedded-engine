#pragma once
#include <cstdint>
#include <vector>

#include "color.hpp"

namespace EE {

struct Vertex {
	float x,y,z;
};


using Index = uint16_t;
struct Face {
	Index indices[4];
	Color color;
};

struct Mesh {
    Mesh(const std::vector<Vertex>& vertices, const std::vector<Face>& faces)
    : vertices(vertices), faces(faces) {}

    std::vector<Vertex> vertices;
    std::vector<Face> faces;
};

}
