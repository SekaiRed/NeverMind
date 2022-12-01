#pragma once
#include <SFML/Graphics.hpp>

namespace Engine
{
class InputManager
{
public:
	InputManager()
	{}
	~InputManager()
	{}

	// sample implementations -- expand on what is needed

	bool IsSpriteClicked(sf::Sprite object, sf::Mouse::Button button, sf::RenderWindow& window);

	sf::Vector2i GetMousePosition(sf::RenderWindow& window);
};
}