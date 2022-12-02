#include "EnemyRender.hpp"

EnemyRender::EnemyRender(Engine::AssetManager* man, std::string filename) : SpriteRender(man, filename) {
    timer = 0;
    frame = 0;
}

void EnemyRender::update() {
    timer++;
    if(timer>6) {
        timer=0;
        frame++;
        if(frame>3) {
            frame = 0;
        }
    }

    spr.setTextureRect(sf::IntRect(frame * 146, 0, 146, 202));
}

float EnemyRender::getWidth() {
    return spr.getGlobalBounds().width;
}
float EnemyRender::getHeight() {
    return spr.getGlobalBounds().height;
}