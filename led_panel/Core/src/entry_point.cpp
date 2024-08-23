#include "base.hpp"
#include "engine.hpp"
#include "application.hpp"

extern Application* CreateApplication();

int main(int argc, char** argv) {
	Application* app = CreateApplication();
	Engine engine = Engine(*app);
	engine.run();
	delete app;
}
