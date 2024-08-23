/*
 * game_of_life.c
 *
 *  Created on: Aug 21, 2024
 *      Author: han
 */


#include "base.hpp"
#include <math.h>
#include <stdlib.h>
#include <string.h>


#if game_of_life

uint8_t grid[WIDTH][HEIGHT] = {0};
uint8_t new_grid[WIDTH][HEIGHT] = {0};



void advance_rule() {
	 for (uint8_t x = 0; x < WIDTH; ++x) {
	        for (uint8_t y = 0; y < HEIGHT; ++y) {
	            uint8_t alive_neighbors = 0;

				for (int8_t dx = -1; dx <= 1; ++dx) {
					for (int8_t dy = -1; dy <= 1; ++dy) {
						if (dx == 0 && dy == 0) {
							continue;
						}
						int8_t nx = (x + dx + WIDTH)  % WIDTH;
						int8_t ny = (y + dy + HEIGHT) % HEIGHT;
						alive_neighbors += grid[nx][ny];
					}
				}

	            if (grid[x][y] == 1) {
	                new_grid[x][y] = (alive_neighbors == 2 || alive_neighbors == 3) ? 1 : 0;
	            } else {
	                new_grid[x][y] = (alive_neighbors == 3) ? 1 : 0;
	            }
	        }
	    }

	    memcpy(grid, new_grid, WIDTH * HEIGHT * sizeof(uint8_t));
}


void copy_to_back_buffer() {
	for (uint8_t x = 0; x < WIDTH; ++x) {
		for (uint8_t y = 0; y < HEIGHT; ++y) {
			set_pixel_w(x, y, grid[x][y]);
		}
	}
}


void create_r_pentomino(uint8_t x_offset, uint8_t y_offset) {
    uint8_t r_pentomino[3][3] = {
        {0, 1, 1},
        {1, 1, 0},
        {0, 1, 0}
    };

    for (uint8_t y = 0; y < 3; ++y) {
        for (uint8_t x = 0; x < 3; ++x) {
            grid[x + x_offset][y + y_offset] = r_pentomino[y][x];
        }
    }
}

void create_glider(uint8_t start_x, uint8_t start_y) {
	if (start_x < WIDTH-2 && start_y < HEIGHT-2) {
		grid[start_x+1][start_y  ] = 1;
		grid[start_x+2][start_y+1] = 1;
		grid[start_x  ][start_y+2] = 1;
		grid[start_x+1][start_y+2] = 1;
		grid[start_x+2][start_y+2] = 1;
	}
}

void on_ready() {
	memset(grid, 0, sizeof(grid));
	grid[51][22] = 1;
	grid[52][22] = 1;
	grid[53][22] = 1;
	create_glider(35,20);
	create_r_pentomino(32,16);
}

bool pause = false;

void on_update() {
	//clear_back_buffer();

	if (!pause) {
		advance_rule();
	}

	copy_to_back_buffer();
}


void on_button_pressed() {
	pause = !pause;
}
#endif


