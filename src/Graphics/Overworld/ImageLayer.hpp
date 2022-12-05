#pragma once

#include "Layer.hpp"

#include <tmxlite/ImageLayer.hpp>

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

class ImageLayer final : public Layer {
public:
    ImageLayer(const tmx::Map& map, std::size_t idx);
    virtual LayerType getType() const;
    virtual void update(sf::Time elapsed);
    virtual void draw(sf::RenderTarget& rt, sf::RenderStates states) const override;
private:
    sf::Texture imageTex;
    //sf::Sprite imageSpr;
    double scrollX = 0;
    double scrollY = 0;
    double offsetX = 0;
    double offsetY = 0;
    bool fixed = false;
};