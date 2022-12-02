#include "SpriteRender.hpp"

SpriteRender::SpriteRender(Engine::AssetManager* man, std::string filename) {
    /*tex.loadFromFile(filename);
    tex.setSmooth(false);
    tex.setRepeated(false);*/
    //spr.setTexture(tex);
    //spr.setTextureRect(sf::Rect(u, v, uw, uh));
    spr.setTexture(man->getTexture(filename));
    x = 0;
    y = 0;
    offset_x = 0;
    offset_y = 0;
    //spr.move(10.5,10.5);
}

void SpriteRender::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    states.transform *= getTransform();

    //spr.move(-16, -16);
    //spr.setPosition(-1, -1);
    //spr.m_position = sf::Vector2f(-10,-10);

    target.draw(spr, states);

    //spr.move(16, 16);
}

void SpriteRender::update() {
    
}

bool SpriteRender::destroy() {
    return false;
}

void SpriteRender::setPosition(float x, float y) {
    this->x = x;
    this->y = y;
    sf::Transformable::setPosition(x + offset_x, y + offset_y);
}

void SpriteRender::setOrigin(float x, float y) {
    spr.setOrigin(x, y);
    sf::Transformable::setOrigin(x, y);
}

void SpriteRender::setOffset(float offset_x, float offset_y) {
    this->offset_x = offset_x;
    this->offset_y = offset_y;
    setPosition(x, y);
}

void SpriteRender::setUV(int u, int v, int w, int h) {
    spr.setTextureRect(sf::IntRect(u, v, w, h));
}
