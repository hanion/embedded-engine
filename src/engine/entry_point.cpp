#include "base.hpp"
#include "engine.hpp"
#include "application.hpp"

using namespace EE;

extern Application* CreateApplication();

int main() {
	Application* app = CreateApplication();
	Engine engine = Engine(*app);
	engine.run();
	delete app;
}
