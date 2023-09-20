/*#include <iostream>
//#include <memory>
#include "GameData.hpp"
#include "States/MainMenuState.hpp"*/
/*#include <SFML/Graphics.hpp>
#include "Engine/StateMachine.hpp"
#include "Engine/AssetManager.hpp"
#include "Engine/InputManager.hpp"*/
/*#include "Global.hpp"
#include "Platform/Platform.hpp"*/
//#include <stdlib>

// causes source files to only be loaded once
#pragma once

#include <iostream>
#include "GameData.hpp"
#include "RPG/States/MainMenuState.hpp"

/*
	This class wraps the game engine into its own class.
 */

/*struct GameData
{
	sf::RenderWindow* window;
	Engine::StateMachine states;
	Engine::InputManager inputs;
	Engine::AssetManager assets;
};*/

//typedef std::shared_ptr<GameData> GameDataRef;
class Game
{

private:
	// For platform specific methods
	//util::Platform _platform;

	// Game Variables
	sf::VideoMode _videoMode;
	sf::Event _event;

	// Private Functions
	void initVariables();
	void initWindow();
	void processEvent(sf::Event _event);

	// Game Data ref
	GameDataRef _data = std::make_shared<GameData>();

	// Time data
	const float dt = 1.0f / 60.0f;
	sf::Clock _clock;

public:
	// Constructors and Destructors
	Game();
	virtual ~Game();

	// Accessors
	bool isRunning() const;
	void run();
};

// custom exception to use for debugging
struct GameException : public std::exception
{
protected:
	const char* errorMsg;

public:
	GameException(const char* str)
	{
		errorMsg = str;
	}
	const char* what() const throw()
	{
		return errorMsg;
	}
};
