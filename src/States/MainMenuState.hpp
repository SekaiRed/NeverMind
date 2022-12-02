#pragma once

#include "../Game.hpp"
//#include "Global.hpp"
#include "State.hpp"

class MainMenuState : public Engine::State
{
public:
	MainMenuState(GameDataRef data);
	//~MainMenuState() = default;

	void initState();
	void updateEvents(sf::Event e);
	void updateState(float dt __attribute__((unused)));
	void drawState(float dt __attribute__((unused)));

private:
	GameDataRef _data;
};
