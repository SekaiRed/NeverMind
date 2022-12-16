#include "Animated.hpp"

Animated::Animated(Engine::AssetManager* man, std::string filename, int zIndex) : Graphic(man, filename, zIndex) {
    this->man = man;
}

void Animated::update(sf::Time elapsed) {
    Graphic::update(elapsed);
    player.update(&spr, elapsed);
}

void Animated::assignAnimation(std::string filename) {
    player.change(man->getAnimation(filename));
}