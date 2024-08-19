/*
 * testing.c
 *
 *  Created on: Aug 16, 2024
 *      Author: han
 */

#ifdef testing_enabled

#include "main.h"



void scroll_buffer_down() {
    uint8_t last_row[WIDTH];
    for (int x = 0; x < WIDTH; ++x) {
        last_row[x] = (*back_buffer)[x][HEIGHT - 1];
    }

    for (int y = HEIGHT - 1; y > 0; --y) {
        for (int x = 0; x < WIDTH; ++x) {
        	(*back_buffer)[x][y] = (*back_buffer)[x][y - 1];
        }
    }

    for (int x = 0; x < WIDTH; ++x) {
    	(*back_buffer)[x][0] = last_row[x];
    }
}
void scroll_buffer_left() {
	uint8_t first_column[HEIGHT];
	for (int y = 0; y < HEIGHT; ++y) {
		first_column[y] = (*back_buffer)[0][y];
	}

	for (int x = 0; x < WIDTH - 1; ++x) {
		for (int y = 0; y < HEIGHT; ++y) {
			(*back_buffer)[x][y] = (*back_buffer)[x + 1][y];
		}
	}

	for (int y = 0; y < HEIGHT; ++y) {
		(*back_buffer)[WIDTH - 1][y] = first_column[y];
	}
}

void generate_rainbow() {
    for (int y = 0; y < HEIGHT; ++y) {
        for (int x = 0; x < WIDTH; ++x) {
            uint8_t color = (x * 6) / WIDTH; // Create a value that cycles through 0 to 5
            uint8_t r = 0, g = 0, b = 0;

            switch (color) {
                case 0: // Red
                    r = 1;
                    g = 0;
                    b = 0;
                    break;
                case 1: // Yellow
                    r = 1;
                    g = 1;
                    b = 0;
                    break;
                case 2: // Green
                    r = 0;
                    g = 1;
                    b = 0;
                    break;
                case 3: // Cyan
                    r = 0;
                    g = 1;
                    b = 1;
                    break;
                case 4: // Blue
                    r = 0;
                    g = 0;
                    b = 1;
                    break;
                case 5: // Magenta
                    r = 1;
                    g = 0;
                    b = 1;
                    break;
            }

            set_pixel(x, y, r, g, b);
        }
    }
}

void generate_diagonal_line() {
	int xoffset = 0;
	for (int y = 0; y < 32; ++y) {
		set_pixel(xoffset++, y, 1,1,1);
		set_pixel(xoffset++, y, 1,1,1);
	}
}




typedef struct {
    uint8_t x;
    uint8_t y;
} pixel;

pixel line_start = { 4, 4 };
pixel line_end   = { 62, 25 };

int8_t dir = 0;
int8_t dir2 = -1;



void on_ready() {
	clear_back_buffer();
	generate_rainbow();
	generate_diagonal_line();
	//memset(buffer, 7, sizeof(buffer));
}
void on_update() {
	clear_back_buffer();
	//generate_rainbow();
	draw_line(line_start.x, line_start.y, line_end.x, line_end.y);



	line_start.y += dir;
	if (line_start.y >= 31 || line_start.y <= 0) {
		dir = -dir;
	}

	line_end.y += dir2;
	if (line_end.y >= 31 || line_end.y <= 1) {
		dir2 = -dir2;
	}


	//scroll_buffer_down();
}






void on_button_pressed() {
	scroll_buffer_left();
}
void on_button_held() {
	scroll_buffer_left();
}
void on_button_released() {

}

#endif

