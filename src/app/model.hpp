#pragma once
#include "mesh.hpp"
#include "renderer.hpp"
using namespace EE;

Mesh cube_mesh = Mesh(
	{
		{1.0f, 1.0f, -1.0f}, // 0
		{1.0f, -1.0f, -1.0f}, // 1
		{1.0f, 1.0f, 1.0f}, // 2
		{1.0f, -1.0f, 1.0f}, // 3
		{-1.0f, 1.0f, -1.0f}, // 4
		{-1.0f, -1.0f, -1.0f}, // 5
		{-1.0f, 1.0f, 1.0f}, // 6
		{-1.0f, -1.0f, 1.0f} // 7
	},
	{
		// .obj face indices are 1 based, reduce 1 for my format
		{{0,4,6,2}, Color{1, 0, 0}},
		{{3,2,6,7}, Color{0, 1, 0}},
		{{7,6,4,5}, Color{0, 0, 1}},
		{{5,1,3,7}, Color{1, 1, 0}},
		{{1,0,2,3}, Color{0, 1, 1}},
		{{5,4,0,1}, Color{1, 0, 1}}
	}
);
