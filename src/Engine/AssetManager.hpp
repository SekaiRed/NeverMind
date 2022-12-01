#pragma once

#include <SFML/Graphics.hpp>
#include "Exceptions.hpp"

namespace Engine
{
class AssetManager
{

private:
	std::map<std::string, sf::Texture> _textures;
	std::map<std::string, sf::Font> _fonts;

public:
	AssetManager() {}
	~AssetManager() {}

	void loadTexture(std::string name);
	sf::Texture& getTexture(std::string name);

	void loadFont(std::string name);
	sf::Font& getFont(std::string name);

	// expand for sounds and other needs
};
}