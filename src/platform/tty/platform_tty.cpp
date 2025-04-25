#include "base.hpp"
#include "platform.hpp"
#include "event.hpp"
#include "engine.hpp"
#include "renderer.hpp"

#include <csignal>
#include <iostream>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include <cstring>
#include <chrono>
bool TEARING_FIX = false;

bool stop_signal = false;

static bool key_states[356] = { false };

static std::chrono::time_point<std::chrono::high_resolution_clock> start_time;

void set_raw_mode(bool enable);

void sigint_handler(int sig) {
	set_raw_mode(false);
	stop_signal = true;
	//exit(0);
}


void Platform::on_init() {
	set_raw_mode(true);
	std::cout.setf(std::ios::unitbuf);
	signal(SIGINT, sigint_handler);
	start_time = std::chrono::high_resolution_clock::now();
}
bool is_key_pressed(char key) {
	return key_states[key];
}

char get_keypress() {
	char buf = 0;
	if (read(STDIN_FILENO, &buf, 1) == 1) {
		return buf;
	}
	return 0;
}

void Platform::poll_events(EE::Engine* engine) {
	if (stop_signal) {
		engine->stop();
		return;
	}

	//update_terminal_size();

	char keycode = get_keypress();
	while (keycode != 0) {
		if (!key_states[keycode]) {
			key_states[keycode] = true;
			EE::EventManager::enqueue_event({ EE::Event::Type::Pressed, keycode });
		} else {
			EE::EventManager::enqueue_event({ EE::Event::Type::Held, keycode });
		}
		keycode = get_keypress();
	}

	for (int i = 0; i < 356; ++i) {
		if (key_states[i]) {
			key_states[i] = false;
			EE::EventManager::enqueue_event({ EE::Event::Type::Released, i });
		}
	}
}

uint32_t Platform::get_tick() {
	auto now = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(now - start_time);
	return static_cast<uint32_t>(duration.count());
}

void Platform::on_render() {
	// clear terminal
	std::cout << "\033[H\033[J";

	for (int y = 0; y < HEIGHT; ++y) {
		for (int x = 0; x < WIDTH; ++x) {
			uint8_t col = (*EE::Renderer::front_buffer)[x][y];

			switch (col) {
				case 0b000: std::cout << "\033[0m  ";  break; // black / off
				case 0b001: std::cout << "\033[34m██"; break; // blue
				case 0b010: std::cout << "\033[32m██"; break; // green
				case 0b011: std::cout << "\033[36m██"; break; // cyan (green + blue)
				case 0b100: std::cout << "\033[31m██"; break; // red
				case 0b101: std::cout << "\033[35m██"; break; // magenta (red + blue)
				case 0b110: std::cout << "\033[33m██"; break; // yellow (red + green)
				case 0b111: std::cout << "\033[37m██"; break; // white (all on)
				case 0x008: std::cout << "\033[37m  "; break; // transparent (8)
				default:    std::cout << "\033[0m  "; break;
			}

		}
		std::cout << std::endl;
	}

	// reset color
	std::cout << "\033[0m";
	std::cout << std::flush;
	
	if (std::cout.fail()) {
		std::cout.clear();
	}

	EE::Renderer::swap_buffers();
	EE::Renderer::is_back_buffer_new = false;
}

void Platform::render_buffer() {}
void Platform::render_row() {}



void set_raw_mode(bool enable) {
	static struct termios oldt, newt;
	static int oldf;

	if (enable) {
		tcgetattr(STDIN_FILENO, &oldt);
		newt = oldt;
		newt.c_lflag &= ~(ICANON | ECHO | IXON);
		tcsetattr(STDIN_FILENO, TCSANOW, &newt);

		oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
		fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);
	} else {
		tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
		fcntl(STDIN_FILENO, F_SETFL, oldf);
	}
}


