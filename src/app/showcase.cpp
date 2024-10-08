#include "application.hpp"
using namespace EE;
#include "cube.hpp"
#include "dino.hpp"
#include "display_string.hpp"
#include "doom.hpp"
#include "game_of_life.hpp"
#include "rule110.hpp"


class ShowcaseDemos : public Application {
public:
	ShowcaseDemos() : Application("ShowcaseDemos") {}
	~ShowcaseDemos() {}

	virtual void on_ready() override final;
	virtual void on_update(double delta_time) override final;
	virtual void on_event(Event event) override final;

private:
	CubeDemo cube_demo;
	DinoGame dino_game;
	Rule110 rule110;
	GameOfLife game_of_life;
	DisplayString display_string;
	Doom doom;
	Application* m_active_app = &doom;
};

Application* CreateApplication() {
	return new ShowcaseDemos();
}



void ShowcaseDemos::on_ready() {
	m_active_app->on_ready();
}

void ShowcaseDemos::on_update(double delta_time) {
	m_active_app->on_update(delta_time);
}

void ShowcaseDemos::on_event(Event event) {
	m_active_app->on_event(event);
}






