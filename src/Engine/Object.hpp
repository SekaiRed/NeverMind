#pragma once

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/System/Time.hpp>

#include "AssetManager.hpp"

class Object/* : public sf::Drawable*/ {
public:
    Object(Engine::AssetManager man, std::string path);
    /*virtual void update(sf::Time elapsed);
    virtual void draw(sf::RenderTarget& rt, sf::RenderStates states) const override;*/
private:
    sf::Texture lol;
    sf::Sprite spr;
};