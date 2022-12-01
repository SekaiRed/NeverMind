#include "Game.hpp"
#include <SFML/Graphics.hpp>
#include "States/MainMenuState.hpp"
/*#include "Engine/StateMachine.hpp"
#include "States/MainMenuState.hpp"*/

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

/*
	This Game object holds all of the primary game code and keeps it out of main.
	(based on: https://youtu.be/kxb0GvBNOGU)
	This also incorporates the cross-platform boilerplate created by Andrew King
	(found here: https://github.com/andrew-r-king/sfml-vscode-boilerplate)
 */

// private
void Game::initVariables()
{
	this->_data->window = nullptr;
	this->_data->states.addState(Engine::StateRef(new MainMenuState(this->_data)), false);
}
void Game::initWindow()
{
	// creating our window object
	this->_data->window = new sf::RenderWindow();

	// in Windows at least, this must be called before creating the window
	//float screenScalingFactor = _platform.getScreenScalingFactor(this->_data->window->getSystemHandle());

	// Use the screenScalingFactor to create video mode and set screen size - 720p by default
	/*this->_videoMode.height = SCREEN_HEIGHT * screenScalingFactor;
	this->_videoMode.width = SCREEN_WIDTH * screenScalingFactor;*/
	this->_videoMode.height = SCREEN_HEIGHT;
	this->_videoMode.width = SCREEN_WIDTH;

	// creating our window view using the video mode and disabling resizablilty
	this->_data->window->create(this->_videoMode, "LILY", sf::Style::Titlebar | sf::Style::Close);
	sf::Image imgIco;
	imgIco.loadFromFile("resources/img/heart.png");
	this->_data->window->setIcon(imgIco.getSize().x, imgIco.getSize().y, imgIco.getPixelsPtr());
	//_platform.setIcon(this->_data->window->getSystemHandle());

	// sets FPS vsync
	this->_data->window->setFramerateLimit(30);
	/*window.setFramerateLimit(30);
    window.setVerticalSyncEnabled(false);*/
}

// Constructors

Game::Game()
{
	this->initVariables();
	this->initWindow();

	// running the new game
	this->run();
}

Game::~Game()
{
	delete this->_data->window;
}

// Accessors
bool Game::isRunning() const
{
	return this->_data->window->isOpen();
}

void Game::run()
{
	// initializing a new Game

	// time initialization
	float newTime, frameTime, interpolation;
	float currentTime = this->_clock.getElapsedTime().asSeconds();
	float accumulator = 0.0f;

	//new MainMenuState(_data);

	// Game Loop
	while (this->isRunning())
	{
		this->_data->states.processStates();

		newTime = this->_clock.getElapsedTime().asSeconds();
		frameTime = newTime - currentTime;

		if (frameTime > 0.25f)
		{
			frameTime = 0.25f;
		}

		currentTime = newTime;
		accumulator += frameTime;

		while (accumulator >= dt)
		{
			this->_data->states.getActiveState()->updateInputs();
			this->_data->states.getActiveState()->updateState(dt);

			accumulator -= dt;
		}

		interpolation = accumulator / dt;
		this->_data->states.getActiveState()->drawState(interpolation);
	}
}
