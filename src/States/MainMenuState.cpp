#include "MainMenuState.hpp"
#include "OverworldState.hpp"
#include "BattleState.hpp"
#include "../Engine/ExternalLoader.hpp"
//#include "Game.hpp"

MainMenuState::MainMenuState(GameDataRef data) :
	BaseState(data)
{
}

void MainMenuState::initState()
{
	//Loader::debug();
}

void MainMenuState::updateEvents(sf::Event e)
{
	switch (e.type) {
		case sf::Event::Closed:
			this->_data->window->close();
			break;
		case sf::Event::KeyPressed:
			/*if (e.key.code == sf::Keyboard::Escape)
				this->_data->window->close();*/
			if (e.key.code == sf::Keyboard::Enter)
				this->_data->states.addState(Engine::StateRef(new BattleState(this->_data)), false);
			if (e.key.code == sf::Keyboard::M)
				this->_data->states.addState(Engine::StateRef(new OverworldState("test-full", this->_data)), false);
			break;
		default:
			break;
	}
}

// marks dt to not warn compiler
void MainMenuState::updateState(float dt __attribute__((unused)))
{
	BaseState::updateState(dt);
}

// marks dt to not warn compiler
void MainMenuState::drawState(float dt __attribute__((unused)))
{
	// just for fun, heres hello world text
	// SAMPLE RENDER CODE:

	// background color
	this->_data->window->clear(sf::Color::Black);

	// write text
	sf::Text text;
	sf::Font font;

	// throws error if cant load font
	if (!font.loadFromFile("resources/fonts/OMORI_GAME2.ttf"))
	{
		// error...
		throw GameException("Could not load font");
	}

	// select the font
	text.setFont(font); // font is a sf::Font

	// set the string to display
	text.setString("Main menu");

	// set the character size
	text.setCharacterSize(56); // in pixels, not points!

	// set the color
	text.setFillColor(sf::Color::White);

	// set the text style
	text.setStyle(sf::Text::Bold | sf::Text::Underlined);

	text.setPosition(
		(this->_data->window->getSize().x / 2) - (text.getLocalBounds().width / 2),
		(this->_data->window->getSize().y / 2) - (text.getLocalBounds().height / 2));

	// inside the main loop, between window.clear() and window.display()
	this->_data->window->draw(text);

	BaseState::drawState(dt);
	// END SAMPLE RENDER CODE

	// Displays rendered obejcts
	this->_data->window->display();
}