#include "BattleState.hpp"

BattleState::BattleState(GameDataRef data) :
	BaseState(data),
	_render(/*this*/)
{}

void BattleState::initState()
{
    /*BattlePlayer omori = BattlePlayer("Omori", "omori", 1, true);
	players.push_back(omori);

	BattlePlayer aubrey = BattlePlayer("Aubrey", "aubrey", 2, false);
	players.push_back(aubrey);

	BattlePlayer sekai = BattlePlayer("Sekai", "sekai", 1, true);
	players.push_back(sekai);

	BattlePlayer kel = BattlePlayer("Kel", "kel", 50, true);
	players.push_back(kel);

    players.at(0).setEmotion(&Emotion::SAD);
	PlayerBoxRender* omoriBox = new PlayerBoxRender(&_rsc, &players.at(0));
    omoriBox->scale(1, 1);
    omoriBox->setPosition(14, 7);
    _render.addInstance(omoriBox, 1);

	players.at(1).setEmotion(&Emotion::ANGRY);
	PlayerBoxRender* aubreyBox = new PlayerBoxRender(&_rsc, &players.at(1));
    aubreyBox->scale(1, 1);
    aubreyBox->setPosition(SCREEN_WIDTH - 114 - 14, 7);
    _render.addInstance(aubreyBox, 1);

	players.at(2).setEmotion(&Emotion::NEUTRAL);
	PlayerBoxRender* sekaiBox = new PlayerBoxRender(&_rsc, &players.at(2));
    sekaiBox->scale(1, 1);
    sekaiBox->setPosition(14, SCREEN_HEIGHT - 164 - 14);
    _render.addInstance(sekaiBox, 1);

	players.at(3).setEmotion(&Emotion::HAPPY);
	PlayerBoxRender* kelBox = new PlayerBoxRender(&_rsc, &players.at(3));
    kelBox->scale(1, 1);
    kelBox->setPosition(SCREEN_WIDTH - 114 - 14, SCREEN_HEIGHT - 164 - 14);
    _render.addInstance(kelBox, 1);

	EnemyRender* bnuy = new EnemyRender(&_rsc, "resources/img/sprites/enemies/space_bunny.png");
	bnuy->setPosition(SCREEN_WIDTH/2 - 146/2, SCREEN_HEIGHT/2 - 202/2 - 40);
	_render.addInstance(bnuy, 20);*/

	_data->window->setView(_data->window->getDefaultView());
}

void BattleState::updateEvents(sf::Event e)
{
	switch (e.type) {
		case sf::Event::Closed:
			this->_data->window->close();
			break;
		case sf::Event::KeyPressed:
			if (e.key.code == sf::Keyboard::Escape)
				this->_data->window->close();
			if (e.key.code == sf::Keyboard::A) {
				std::cout << players.size() << "\n";
				std::cout << players.at(0).getInfo()->getName() << "\n";
			}
			if (e.key.code == sf::Keyboard::Q) {
				this->_data->states.removeState();
			}
			/*if (e.key.code == sf::Keyboard::Enter)
				this->_data->states.addState(Engine::StateRef(new MainMenuState(this->_data)), false);*/
			break;
		default:
			break;
	}
}

// marks dt to not warn compiler
void BattleState::updateState(sf::Time deltaTime)
{
	BaseState::updateState(deltaTime);
}

// marks dt to not warn compiler
void BattleState::drawState(sf::Time deltaTime)
{
	// just for fun, heres hello world text
	// SAMPLE RENDER CODE:

	// background color
	this->_data->window->clear(sf::Color::Black);

	/*sf::Texture texBg;
    texBg.loadFromFile("resources/img/backgrounds/ow_outskirts.png");*/
    sf::Sprite sprBg;
    sprBg.setTexture(_rsc.getTexture("backgrounds/ow_outskirts"));
	this->_data->window->draw(sprBg);

	this->_render.draw(this->_data->window);
	//this->_data->assets.getTexture();

	BaseState::drawState(deltaTime);

	//this->_data->window->draw(omoriBox);

	// Displays rendered obejcts
	this->_data->window->display();
}