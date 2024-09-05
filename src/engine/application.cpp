#include "application.hpp"

EE::Application::Application(const char* name) : name(name) {}

EE::Application::~Application() {}

void EE::Application::on_ready() {}
void EE::Application::on_update(double delta_time) {}
void EE::Application::on_event(EE::Event event) {}
