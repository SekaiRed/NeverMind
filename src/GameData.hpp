#pragma once

#include <memory>
#include <SFML/Graphics.hpp>
#include "Engine/StateMachine.hpp"
#include "Engine/AssetManager.hpp"
#include "Engine/InputManager.hpp"

struct GameData
{
	sf::RenderWindow* window;
	Engine::StateMachine states;
	Engine::InputManager inputs;
	Engine::AssetManager assets;
};

typedef std::shared_ptr<GameData> GameDataRef;