#include "application.hpp"
#include "cube.hpp"
#include "dino.hpp"


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

};

// TODO: can this be a stack allocated app ???
Application* CreateApplication() {
	return new ShowcaseDemos();
}



void ShowcaseDemos::on_ready() {
	cube_demo.on_ready();
}

void ShowcaseDemos::on_update() {
	cube_demo.on_update();
}

void ShowcaseDemos::on_event(Event event) {
	cube_demo.on_event(event);
}






