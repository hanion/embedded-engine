#include "base.hpp"
#include "color.hpp"
#include "platform.hpp"
#include "event.hpp"
#include "engine.hpp"
#include "renderer.hpp"
bool TEARING_FIX = false;

#include "raylib.h"
#include <chrono>

#define GAP_RATIO 0.0f

static const int fps = 40;
static int pixel_size = 25;
static int screen_width = WIDTH * pixel_size;
static int screen_height = HEIGHT * pixel_size;
static int led_gap = pixel_size * GAP_RATIO;
static int screen_offset_x = 0;
static int screen_offset_y = 0;


static bool key_states[KEY_KP_ENTER + 1] = { false };

static std::chrono::time_point<std::chrono::high_resolution_clock> start_time;

void Platform::on_init() {
	SetConfigFlags(FLAG_WINDOW_RESIZABLE);
	InitWindow(screen_width, screen_height, "LED Panel Simulator");
	SetTargetFPS(fps);
	start_time = std::chrono::high_resolution_clock::now();
}

char raylib_key_to_char(int keycode);

void Platform::poll_events(EE::Engine* engine) {
	if (WindowShouldClose()) {
		engine->stop();
	}

	// NOTE: exit key
	if (IsKeyPressed(KEY_CAPS_LOCK)) {
		engine->stop();
	}

	if (GetScreenWidth() != screen_width || GetScreenHeight() != screen_height) {
		screen_width = GetScreenWidth();
		screen_height = GetScreenHeight();
		pixel_size = std::min(screen_width/64, screen_height/32);
		screen_offset_x = (screen_width  - pixel_size * WIDTH )/2;
		screen_offset_y = (screen_height - pixel_size * HEIGHT)/2;
		led_gap = pixel_size * GAP_RATIO;
	}

	for (int key = KEY_SPACE; key <= KEY_KP_EQUAL; ++key) {
		char keycode = raylib_key_to_char(key);
		if (IsKeyPressed(key)) {
			key_states[key] = true;
			EE::EventManager::enqueue_event({ EE::Event::Type::Pressed, keycode });
		} else if (IsKeyDown(key) && key_states[key]) {
			EE::EventManager::enqueue_event({ EE::Event::Type::Held, keycode });
		} else if (IsKeyReleased(key)) {
			key_states[key] = false;
			EE::EventManager::enqueue_event({ EE::Event::Type::Released, keycode });
		}
	}
}

uint32_t Platform::get_tick() {
	auto now = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(now - start_time);
	return static_cast<uint32_t>(duration.count());
}

void Platform::on_render() {
	BeginDrawing();
	ClearBackground({10,10,10,255});

	for (int y = 0; y < HEIGHT; ++y) {
		for (int x = 0; x < WIDTH; ++x) {
			EE::Color ecol;
			ecol.value = (*EE::Renderer::front_buffer)[x][y];
				Color rcol;
				rcol.r = 255 * ecol.r();
				rcol.g = 255 * ecol.g();
				rcol.b = 255 * ecol.b();
				rcol.a = 255;
				DrawRectangle(
					led_gap + screen_offset_x + x * pixel_size,
					led_gap + screen_offset_y + y * pixel_size,
					pixel_size-led_gap, pixel_size-led_gap, rcol
				);
		}
	}

	EndDrawing();

	EE::Renderer::swap_buffers();
	EE::Renderer::is_back_buffer_new = false;
}

void Platform::render_buffer() {}
void Platform::render_row() {}

char raylib_key_to_char(int keycode) {
	switch (keycode) {
		case KEY_A: return 'a';
		case KEY_B: return 'b';
		case KEY_C: return 'c';
		case KEY_D: return 'd';
		case KEY_E: return 'e';
		case KEY_F: return 'f';
		case KEY_G: return 'g';
		case KEY_H: return 'h';
		case KEY_I: return 'i';
		case KEY_J: return 'j';
		case KEY_K: return 'k';
		case KEY_L: return 'l';
		case KEY_M: return 'm';
		case KEY_N: return 'n';
		case KEY_O: return 'o';
		case KEY_P: return 'p';
		case KEY_Q: return 'q';
		case KEY_R: return 'r';
		case KEY_S: return 's';
		case KEY_T: return 't';
		case KEY_U: return 'u';
		case KEY_V: return 'v';
		case KEY_W: return 'w';
		case KEY_X: return 'x';
		case KEY_Y: return 'y';
		case KEY_Z: return 'z';
		case KEY_APOSTROPHE: return '\'';
		case KEY_COMMA: return ',';
		case KEY_MINUS: return '-';
		case KEY_PERIOD: return '.';
		case KEY_SPACE: return ' ';
		case KEY_SLASH: return '/';
		case KEY_BACKSLASH: return '\\';
		case KEY_ENTER: return '\n';
		case KEY_TAB: return '\t';
		case KEY_BACKSPACE: return '\b';
		default: return '\0';
	}
}
