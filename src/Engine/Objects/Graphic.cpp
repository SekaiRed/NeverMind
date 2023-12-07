#include "Graphic.hpp"

Graphic::Graphic(Engine::AssetManager* man, std::string filename, int zIndex) {
    spr.setTexture(man->getTexture(filename));

    this->zIndex = zIndex;
}

void Graphic::update(sf::Time elapsed) {
    //setPosition(getPosition().x + 1, getPosition().y);
}

void Graphic::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    //states.transform *= getTransform();
    states.transform *= getModifiedTransform();

    target.draw(spr, states);
}

sf::Transform Graphic::getModifiedTransform() const {
    return getTransform();
}

void Graphic::setSprite(Engine::AssetManager* man, std::string filename) {
    spr.setTexture(man->getTexture(filename));
}

int Graphic::getZIndex() {
    return zIndex;
}

void Graphic::setZIndex(int zIndex) {
    this->zIndex = zIndex;
}

void Graphic::setUV(int u, int v, int w, int h) {
    spr.setTextureRect(sf::IntRect(u, v, w, h));
}

//left, top, width and height
sf::FloatRect Graphic::getBounds() {
    sf::Vector2f corner = getModifiedTransform().transformPoint(0,0);
    sf::Vector2f size = { spr.getGlobalBounds().width, spr.getGlobalBounds().height };
    return { corner.x, corner.y, size.x, size.y };
    //return {}spr.getGlobalBounds();
}
