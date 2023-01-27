#include "Actor.hpp"

Actor::Actor(Engine::AssetManager* man, std::string filename, int zIndex, Vec2i worldPos) : Entity(man, filename, zIndex, worldPos) {}

void Actor::update(sf::Time elapsed) {
    /*overworldPosition.setPosition(sf::Vector2f(worldPos.x, worldPos.y) * static_cast<float>(TEMP_TILE_SIZE));
    Animated::update(elapsed);*/
}

sf::Transform Actor::getModifiedTransform() const {
    return animationOffset.getTransform() * Entity::getModifiedTransform();
}