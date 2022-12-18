#include "Entity.hpp"

Entity::Entity(Engine::AssetManager* man, std::string filename, int zIndex, Vec2i worldPos) : Animated(man, filename, zIndex) {
    this->worldPos = worldPos;
    updateTransform();
}

void Entity::updateTransform() {
    overworldOffset.setPosition(0, 0);
    overworldOffset.setOrigin(spr.getLocalBounds().width/2, spr.getLocalBounds().height);
    overworldOffset.setPosition(TEMP_TILE_SIZE * worldSize.x /2.0, TEMP_TILE_SIZE * worldSize.y);
}

sf::Transform Entity::getModifiedTransform() const {
    return overworldOffset.getTransform() * Graphic::getModifiedTransform();
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