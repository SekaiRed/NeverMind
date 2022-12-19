#pragma once

#include "../Game.hpp"
//#include "Global.hpp"
#include "State.hpp"
#include "../Graphics/Battle/BattleRender.hpp"
#include "../Engine/AssetManager.hpp"
#include "../Graphics/Battle/EnemyRender.hpp"
//#include "../src/Battle/EventChain.hpp"

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

class BattleState : public BaseState
{
public:
	BattleState(GameDataRef data);
	//~MainMenuState() = default;

	void initState();
	void updateEvents(sf::Event e);
	void updateState(sf::Time deltaTime);
	void drawState(sf::Time deltaTime);

	//BattlePlayer* players[12];
	std::vector<BattlePlayer> players;

private:
	//GameDataRef _data;
	Engine::AssetManager _rsc;
	BattleRender _render;
	//TODO logic database goes here (skills, items data, event chains)

	//EventChain chain;
	
};
