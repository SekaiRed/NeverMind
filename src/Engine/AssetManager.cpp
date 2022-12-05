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

		if (tex.loadFromFile(name)) {
			tex.setSmooth(false); // maybe make it an option
			tex.setRepeated(true);
			this->_textures[name] = tex;
		} else {
			throw NoFileFoundException(name);
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
		
		if (font.loadFromFile(name)) {
			this->_fonts[name] = font;
		} else {
			throw NoFileFoundException(name);
		}
	}

	sf::Font &AssetManager::getFont(std::string name)
	{
		if(!this->_fonts.count(name))
			loadFont(name);

		return this->_fonts.at(name);
	}
}