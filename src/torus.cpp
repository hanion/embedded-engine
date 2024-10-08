
#include "mesh.hpp"
using namespace EE;

Mesh formatted_model = Mesh(
	{
	{1.250000, 0.000000, 0.000000},
	{1.176777, 0.176777, 0.000000},
	{1.000000, 0.250000, 0.000000},
	{0.823223, 0.176777, 0.000000},
	{0.750000, 0.000000, 0.000000},
	{0.823223, -0.176777, 0.000000},
	{1.000000, -0.250000, 0.000000},
	{1.176777, -0.176777, 0.000000},
	{1.082532, 0.000000, -0.625000},
	{1.019118, 0.176777, -0.588388},
	{0.866025, 0.250000, -0.500000},
	{0.712932, 0.176777, -0.411612},
	{0.649519, 0.000000, -0.375000},
	{0.712932, -0.176777, -0.411612},
	{0.866025, -0.250000, -0.500000},
	{1.019118, -0.176777, -0.588388},
	{0.625000, 0.000000, -1.082532},
	{0.588388, 0.176777, -1.019119},
	{0.500000, 0.250000, -0.866025},
	{0.411612, 0.176777, -0.712932},
	{0.375000, 0.000000, -0.649519},
	{0.411612, -0.176777, -0.712932},
	{0.500000, -0.250000, -0.866025},
	{0.588388, -0.176777, -1.019119},
	{0.000000, 0.000000, -1.250000},
	{0.000000, 0.176777, -1.176777},
	{0.000000, 0.250000, -1.000000},
	{0.000000, 0.176777, -0.823223},
	{0.000000, 0.000000, -0.750000},
	{0.000000, -0.176777, -0.823223},
	{0.000000, -0.250000, -1.000000},
	{0.000000, -0.176777, -1.176777},
	{-0.625000, 0.000000, -1.082532},
	{-0.588388, 0.176777, -1.019119},
	{-0.500000, 0.250000, -0.866026},
	{-0.411612, 0.176777, -0.712932},
	{-0.375000, 0.000000, -0.649519},
	{-0.411612, -0.176777, -0.712932},
	{-0.500000, -0.250000, -0.866026},
	{-0.588388, -0.176777, -1.019119},
	{-1.082532, 0.000000, -0.625000},
	{-1.019118, 0.176777, -0.588389},
	{-0.866025, 0.250000, -0.500000},
	{-0.712932, 0.176777, -0.411612},
	{-0.649519, 0.000000, -0.375000},
	{-0.712932, -0.176777, -0.411612},
	{-0.866025, -0.250000, -0.500000},
	{-1.019118, -0.176777, -0.588389},
	{-1.250000, 0.000000, -0.000000},
	{-1.176777, 0.176777, -0.000000},
	{-1.000000, 0.250000, -0.000000},
	{-0.823223, 0.176777, -0.000000},
	{-0.750000, 0.000000, -0.000000},
	{-0.823223, -0.176777, -0.000000},
	{-1.000000, -0.250000, -0.000000},
	{-1.176777, -0.176777, -0.000000},
	{-1.082532, 0.000000, 0.625000},
	{-1.019119, 0.176777, 0.588388},
	{-0.866026, 0.250000, 0.500000},
	{-0.712932, 0.176777, 0.411611},
	{-0.649519, 0.000000, 0.375000},
	{-0.712932, -0.176777, 0.411611},
	{-0.866026, -0.250000, 0.500000},
	{-1.019119, -0.176777, 0.588388},
	{-0.625000, 0.000000, 1.082532},
	{-0.588388, 0.176777, 1.019119},
	{-0.500000, 0.250000, 0.866026},
	{-0.411612, 0.176777, 0.712932},
	{-0.375000, 0.000000, 0.649519},
	{-0.411612, -0.176777, 0.712932},
	{-0.500000, -0.250000, 0.866026},
	{-0.588388, -0.176777, 1.019119},
	{0.000000, 0.000000, 1.250000},
	{0.000000, 0.176777, 1.176777},
	{0.000000, 0.250000, 1.000000},
	{0.000000, 0.176777, 0.823223},
	{0.000000, 0.000000, 0.750000},
	{0.000000, -0.176777, 0.823223},
	{0.000000, -0.250000, 1.000000},
	{0.000000, -0.176777, 1.176777},
	{0.625000, 0.000000, 1.082532},
	{0.588388, 0.176777, 1.019119},
	{0.500000, 0.250000, 0.866025},
	{0.411612, 0.176777, 0.712932},
	{0.375000, 0.000000, 0.649519},
	{0.411612, -0.176777, 0.712932},
	{0.500000, -0.250000, 0.866025},
	{0.588388, -0.176777, 1.019119},
	{1.082532, 0.000000, 0.625000},
	{1.019118, 0.176777, 0.588388},
	{0.866025, 0.250000, 0.500000},
	{0.712932, 0.176777, 0.411612},
	{0.649519, 0.000000, 0.375000},
	{0.712932, -0.176777, 0.411612},
	{0.866025, -0.250000, 0.500000},
	{1.019118, -0.176777, 0.588388},
	},
	{
	{{0, 8, 9, 1}, Color{1, 1, 1}},
	{{1, 9, 10, 2}, Color{1, 1, 1}},
	{{2, 10, 11, 3}, Color{1, 1, 1}},
	{{3, 11, 12, 4}, Color{1, 1, 1}},
	{{4, 12, 13, 5}, Color{1, 1, 1}},
	{{5, 13, 14, 6}, Color{1, 1, 1}},
	{{6, 14, 15, 7}, Color{1, 1, 1}},
	{{7, 15, 8, 0}, Color{1, 1, 1}},
	{{8, 16, 17, 9}, Color{1, 1, 1}},
	{{9, 17, 18, 10}, Color{1, 1, 1}},
	{{10, 18, 19, 11}, Color{1, 1, 1}},
	{{11, 19, 20, 12}, Color{1, 1, 1}},
	{{12, 20, 21, 13}, Color{1, 1, 1}},
	{{13, 21, 22, 14}, Color{1, 1, 1}},
	{{14, 22, 23, 15}, Color{1, 1, 1}},
	{{15, 23, 16, 8}, Color{1, 1, 1}},
	{{16, 24, 25, 17}, Color{1, 1, 1}},
	{{17, 25, 26, 18}, Color{1, 1, 1}},
	{{18, 26, 27, 19}, Color{1, 1, 1}},
	{{19, 27, 28, 20}, Color{1, 1, 1}},
	{{20, 28, 29, 21}, Color{1, 1, 1}},
	{{21, 29, 30, 22}, Color{1, 1, 1}},
	{{22, 30, 31, 23}, Color{1, 1, 1}},
	{{23, 31, 24, 16}, Color{1, 1, 1}},
	{{24, 32, 33, 25}, Color{1, 1, 1}},
	{{25, 33, 34, 26}, Color{1, 1, 1}},
	{{26, 34, 35, 27}, Color{1, 1, 1}},
	{{27, 35, 36, 28}, Color{1, 1, 1}},
	{{28, 36, 37, 29}, Color{1, 1, 1}},
	{{29, 37, 38, 30}, Color{1, 1, 1}},
	{{30, 38, 39, 31}, Color{1, 1, 1}},
	{{31, 39, 32, 24}, Color{1, 1, 1}},
	{{32, 40, 41, 33}, Color{1, 1, 1}},
	{{33, 41, 42, 34}, Color{1, 1, 1}},
	{{34, 42, 43, 35}, Color{1, 1, 1}},
	{{35, 43, 44, 36}, Color{1, 1, 1}},
	{{36, 44, 45, 37}, Color{1, 1, 1}},
	{{37, 45, 46, 38}, Color{1, 1, 1}},
	{{38, 46, 47, 39}, Color{1, 1, 1}},
	{{39, 47, 40, 32}, Color{1, 1, 1}},
	{{40, 48, 49, 41}, Color{1, 1, 1}},
	{{41, 49, 50, 42}, Color{1, 1, 1}},
	{{42, 50, 51, 43}, Color{1, 1, 1}},
	{{43, 51, 52, 44}, Color{1, 1, 1}},
	{{44, 52, 53, 45}, Color{1, 1, 1}},
	{{45, 53, 54, 46}, Color{1, 1, 1}},
	{{46, 54, 55, 47}, Color{1, 1, 1}},
	{{47, 55, 48, 40}, Color{1, 1, 1}},
	{{48, 56, 57, 49}, Color{1, 1, 1}},
	{{49, 57, 58, 50}, Color{1, 1, 1}},
	{{50, 58, 59, 51}, Color{1, 1, 1}},
	{{51, 59, 60, 52}, Color{1, 1, 1}},
	{{52, 60, 61, 53}, Color{1, 1, 1}},
	{{53, 61, 62, 54}, Color{1, 1, 1}},
	{{54, 62, 63, 55}, Color{1, 1, 1}},
	{{55, 63, 56, 48}, Color{1, 1, 1}},
	{{56, 64, 65, 57}, Color{1, 1, 1}},
	{{57, 65, 66, 58}, Color{1, 1, 1}},
	{{58, 66, 67, 59}, Color{1, 1, 1}},
	{{59, 67, 68, 60}, Color{1, 1, 1}},
	{{60, 68, 69, 61}, Color{1, 1, 1}},
	{{61, 69, 70, 62}, Color{1, 1, 1}},
	{{62, 70, 71, 63}, Color{1, 1, 1}},
	{{63, 71, 64, 56}, Color{1, 1, 1}},
	{{64, 72, 73, 65}, Color{1, 1, 1}},
	{{65, 73, 74, 66}, Color{1, 1, 1}},
	{{66, 74, 75, 67}, Color{1, 1, 1}},
	{{67, 75, 76, 68}, Color{1, 1, 1}},
	{{68, 76, 77, 69}, Color{1, 1, 1}},
	{{69, 77, 78, 70}, Color{1, 1, 1}},
	{{70, 78, 79, 71}, Color{1, 1, 1}},
	{{71, 79, 72, 64}, Color{1, 1, 1}},
	{{72, 80, 81, 73}, Color{1, 1, 1}},
	{{73, 81, 82, 74}, Color{1, 1, 1}},
	{{74, 82, 83, 75}, Color{1, 1, 1}},
	{{75, 83, 84, 76}, Color{1, 1, 1}},
	{{76, 84, 85, 77}, Color{1, 1, 1}},
	{{77, 85, 86, 78}, Color{1, 1, 1}},
	{{78, 86, 87, 79}, Color{1, 1, 1}},
	{{79, 87, 80, 72}, Color{1, 1, 1}},
	{{80, 88, 89, 81}, Color{1, 1, 1}},
	{{81, 89, 90, 82}, Color{1, 1, 1}},
	{{82, 90, 91, 83}, Color{1, 1, 1}},
	{{83, 91, 92, 84}, Color{1, 1, 1}},
	{{84, 92, 93, 85}, Color{1, 1, 1}},
	{{85, 93, 94, 86}, Color{1, 1, 1}},
	{{86, 94, 95, 87}, Color{1, 1, 1}},
	{{87, 95, 88, 80}, Color{1, 1, 1}},
	{{88, 0, 1, 89}, Color{1, 1, 1}},
	{{89, 1, 2, 90}, Color{1, 1, 1}},
	{{90, 2, 3, 91}, Color{1, 1, 1}},
	{{91, 3, 4, 92}, Color{1, 1, 1}},
	{{92, 4, 5, 93}, Color{1, 1, 1}},
	{{93, 5, 6, 94}, Color{1, 1, 1}},
	{{94, 6, 7, 95}, Color{1, 1, 1}},
	{{95, 7, 0, 88}, Color{1, 1, 1}},
	}
);
