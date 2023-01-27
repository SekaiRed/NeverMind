#include "AssetManager.hpp"

#include <iostream>

namespace Engine
{
	AssetManager::AssetManager() {
		fallback.create(2, 2, sf::Color::Magenta);
	}
	
	void AssetManager::loadTexture(std::string name)
	{
		std::cout << "Loaded " << name << "\n";

		sf::Texture tex;

		if (tex.loadFromFile("resources/img/" + name + ".png")) {
			tex.setSmooth(false); // maybe make it an option
			tex.setRepeated(true);
			this->_textures[name] = tex;
		} else {
			throw NoFileFoundException("resources/img/" + name + ".png");
		}
	}

	sf::Texture &AssetManager::getTexture(std::string name)
	{
		if(!this->_textures.count(name))
			loadTexture(name);

		return this->_textures.at(name);
	}

	void AssetManager::loadFont(std::string name)
	{
		std::cout << "Loaded " << name << "\n";

		sf::Font font;
		
		if (font.loadFromFile("resources/font/" + name + ".ttf")) {
			this->_fonts[name] = font;
		} else {
			throw NoFileFoundException("resources/font/" + name + ".ttf");
		}
	}

	sf::Font &AssetManager::getFont(std::string name)
	{
		if(!this->_fonts.count(name))
			loadFont(name);

		return this->_fonts.at(name);
	}

	void AssetManager::loadAnimation(std::string name)
	{
		std::cout << "Loaded " << name << "\n";

		Animation animation;

		animation = Loader::loadAnimation("resources/data/animation/" + name + ".json");

		this->_animations[name] = animation;
	}

	Animation& AssetManager::getAnimation(std::string name)
	{
		if(!this->_animations.count(name))
			loadAnimation(name);

		return this->_animations.at(name);
	}
}