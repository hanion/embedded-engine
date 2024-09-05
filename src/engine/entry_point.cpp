#include "base.hpp"
#include "engine.hpp"
#include "application.hpp"

extern EE::Application* CreateApplication();

int main(int argc, char** argv) {
	EE::Application* app = CreateApplication();
	EE::Engine engine = EE::Engine(*app);
	engine.run();
	delete app;
}
