#include "Graphic.hpp"

Graphic::Graphic(Engine::AssetManager* man, std::string filename, int zIndex) {
    spr.setTexture(man->getTexture(filename));

    this->zIndex = zIndex;
}

void Graphic::update(sf::Time elapsed) {
    //setPosition(getPosition().x + 1, getPosition().y);
}

void Graphic::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    states.transform *= getTransform();

    target.draw(spr, states);
}

int Graphic::getZIndex() {
    return zIndex;
}

void Graphic::setUV(int u, int v, int w, int h) {
    spr.setTextureRect(sf::IntRect(u, v, w, h));
}
