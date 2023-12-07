#include "Animated.hpp"
#include <iostream>

Animated::Animated(Engine::AssetManager* man, std::string filename, int zIndex) : Graphic(man, filename, zIndex) {
    this->man = man;
}

void Animated::update(sf::Time elapsed) {
    //std::cout << elapsed.asMicroseconds() << "\n";
    Graphic::update(elapsed);
    player.update(spr, animatedTransform, elapsed, offset);
}

sf::Transform Animated::getModifiedTransform() const {
    return animatedTransform.getTransform() * Graphic::getModifiedTransform();
}

void Animated::assignAnimation(std::string filename) {
    if(filename != "")
        player.change(man->getAnimation(filename));
    else
        player.stop();

    lastPlayed = filename;
}

std::string Animated::getAnimation() {
    return lastPlayed;
}

void Animated::setUVOffset(sf::Vector2i offset) {
    this->offset = offset;
}