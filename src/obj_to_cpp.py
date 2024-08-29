#!/bin/python

import sys
import os
import re

def parse_obj(file_path):
	vertices = []
	faces = []

	with open(file_path, 'r') as file:
		for line in file:
			if line.startswith('v '):
				_, x, y, z = line.split()
				vertices.append(f'{{{float(x):.6f}, {float(y):.6f}, {float(z):.6f}}}')
			elif line.startswith('f '):
				face = re.findall(r'(\d+)', line)
				indices = [int(f) - 1 for f in face]
				color = 'Color{1, 1, 1}'
				faces.append(f'{{{{{", ".join(map(str, indices))}}}, {color}}}')

	return vertices, faces

def format_mesh(vertices, faces):
	formatted_vertices = '\n'.join(f'\t{v},' for v in vertices)
	formatted_faces = '\n'.join(f'\t{f},' for f in faces)

	mesh_str = f'''
#include "mesh.hpp"
Mesh formatted_model = Mesh(
	{{
{formatted_vertices}
	}},
	{{
{formatted_faces}
	}}
);
'''
	return mesh_str

def main():
	if len(sys.argv) != 2:
		print(f"Usage:\n	{sys.argv[0]} <path_to_obj_file>")
		return

	input_path = sys.argv[1]
	vertices, faces = parse_obj(input_path)
	mesh_str = format_mesh(vertices, faces)

	base_name = os.path.splitext(os.path.basename(input_path))[0]
	output_path = f'{base_name}.cpp'

	with open(output_path, 'w') as file:
		file.write(mesh_str)

	print(f'Formatted mesh written to {output_path}')

if __name__ == "__main__":
	main()
