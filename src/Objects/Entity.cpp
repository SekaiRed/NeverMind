#include "Entity.hpp"

Entity::Entity(Engine::AssetManager* man, std::string filename, int zIndex, Vec2i worldPos) : Animated(man, filename, zIndex) {
    this->worldPos = worldPos;
    updateTransform();
}

void Entity::update(sf::Time elapsed) {
    overworldPosition.setPosition(sf::Vector2f(worldPos.x, worldPos.y) * static_cast<float>(TEMP_TILE_SIZE));
    Animated::update(elapsed);
}

void Entity::updateTransform() {
    overworldOffset.setPosition(0, 0);
    overworldOffset.setOrigin(spr.getLocalBounds().width/2, spr.getLocalBounds().height);
    overworldOffset.setPosition(TEMP_TILE_SIZE * worldSize.x /2.0, TEMP_TILE_SIZE * worldSize.y);
}

sf::Transform Entity::getModifiedTransform() const {
    return overworldPosition.getTransform() * overworldOffset.getTransform() * Animated::getModifiedTransform();
}

void Entity::setUV(int u, int v, int w, int h) {
    Graphic::setUV(u, v, w, h);
    updateTransform();
}

void Entity::setWorldPos(Vec2i pos) {
    worldPos = pos;
}

Vec2i Entity::getWorldPos() {
    return worldPos;
}

void Entity::setWorldSize(Vec2i size) {
    worldSize = size;
    updateTransform();
}

Vec2i Entity::getWorldSize() {
    return worldSize;
}

bool Entity::isSolid() {
    return isMovementBlocking;
}