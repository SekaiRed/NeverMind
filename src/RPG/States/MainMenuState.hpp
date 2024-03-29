#pragma once

#include <iostream>
#include "../../Game.hpp"
//#include "Global.hpp"
#include "../../Engine/States/BaseState.hpp"
#include "../../RPG/States/OverworldState.hpp"

class MainMenuState : public BaseState
{
public:
	MainMenuState(GameDataRef data);
	//~MainMenuState() = default;

	void initState();
	void updateEvents(sf::Event e);
	void updateState(sf::Time deltaTime);
	void drawState(sf::Time deltaTime);

private:
	//GameDataRef _data;
};
