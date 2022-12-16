#pragma once

#include <SFML/Graphics.hpp>
#include "ExternalLoader.hpp"
#include "Animation.hpp"
#include "Exceptions.hpp"

namespace Engine
{
class AssetManager
{

private:
	sf::Image fallback;
	std::map<std::string, sf::Texture> _textures;
	std::map<std::string, sf::Font> _fonts;
	std::map<std::string, Animation> _animations;

public:
	AssetManager();
	~AssetManager() {}

	void loadTexture(std::string name);
	sf::Texture& getTexture(std::string name);

	void loadFont(std::string name);
	sf::Font& getFont(std::string name);

	void loadAnimation(std::string name);
	Animation& getAnimation(std::string name);

	// expand for sounds and other needs
};
}