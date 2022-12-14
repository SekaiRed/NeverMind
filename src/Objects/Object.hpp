#pragma once

/*#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/System/Time.hpp>*/
#include <SFML/Graphics.hpp>

class Object : public sf::Drawable, public sf::Transformable {
public:
    virtual void update(sf::Time elapsed) = 0;
    virtual void draw(sf::RenderTarget& rt, sf::RenderStates states) const override = 0;
    virtual int getZIndex() = 0;
};