#include "MainMenuState.hpp"
#include "OverworldState.hpp"
#include "BattleState.hpp"
#include "../Engine/ExternalLoader.hpp"
#include "../Objects/Animated.hpp"
//#include "Game.hpp"

MainMenuState::MainMenuState(GameDataRef data) :
	BaseState(data)
{
}

void MainMenuState::initState()
{
	Animated* player_anim = new Animated(&this->_data->assets, "sprites/characters/DW_MARI", 8);
    player_anim->setUV(0, 0, 32, 32);
	sf::Vector2u rect = _data->window->getSize();
    player_anim->setPosition(rect.x/2 - 32/2, rect.y/2 - 32/2);
    player_anim->assignAnimation("OW_SPIN");
    addObject(player_anim);
	//delete player_anim;
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
			if (e.key.code == sf::Keyboard::W)
				this->_data->states.addState(Engine::StateRef(new OverworldState("whitespace", this->_data)), false);
			if (e.key.code == sf::Keyboard::A)
				this->_data->states.addState(Engine::StateRef(new OverworldState("alcoholspace", this->_data)), false);
			if (e.key.code == sf::Keyboard::Z)
				this->_data->states.addState(Engine::StateRef(new OverworldState("apartment", this->_data)), false);
			break;
		default:
			break;
	}
}

// marks dt to not warn compiler
void MainMenuState::updateState(sf::Time deltaTime)
{
	BaseState::updateState(deltaTime);
}

// marks dt to not warn compiler
void MainMenuState::drawState(sf::Time deltaTime)
{
	// just for fun, heres hello world text
	// SAMPLE RENDER CODE:

	// background color
	/*this->_data->window->clear(sf::Color::Black);

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
	this->_data->window->draw(text);*/
	this->_data->window->clear(sf::Color::Black);

	BaseState::drawState(deltaTime);
	// END SAMPLE RENDER CODE

	// Displays rendered obejcts
	this->_data->window->display();
}