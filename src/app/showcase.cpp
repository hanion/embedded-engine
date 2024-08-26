#include "application.hpp"
#include "cube.hpp"
#include "dino.hpp"
#include "game_of_life.hpp"
#include "rule110.hpp"


class ShowcaseDemos : public Application {
public:
	ShowcaseDemos() : Application("ShowcaseDemos") {}
	~ShowcaseDemos() {}

	virtual void on_ready() override final;
	virtual void on_update() override final;
	virtual void on_event(Event event) override final;

private:
	CubeDemo cube_demo;
	DinoGame dino_game;
	Rule110 rule110;
	GameOfLife game_of_life;
	Application* m_active_app = &game_of_life;
};

Application* CreateApplication() {
	return new ShowcaseDemos();
}



void ShowcaseDemos::on_ready() {
	m_active_app->on_ready();
}

void ShowcaseDemos::on_update() {
	m_active_app->on_update();
}

void ShowcaseDemos::on_event(Event event) {
	m_active_app->on_event(event);
}






