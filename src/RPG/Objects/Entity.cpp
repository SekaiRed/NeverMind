#include "Entity.hpp"

#include <iostream>

Entity::Entity(Engine::AssetManager* man, std::string filename, int zIndex) : Animated(man, filename, zIndex) {
    updateTransform();
}

void Entity::update(sf::Time elapsed) {
    overworldPosition.setPosition(sf::Vector2f(worldPos.x, worldPos.y) * static_cast<float>(TILE_SIZE));
    //std::cout << overworldPosition
    Animated::update(elapsed);
}

void Entity::updateTransform() {
    overworldOffset.setPosition(0, 0);
    overworldOffset.setOrigin(spr.getLocalBounds().width/2, spr.getLocalBounds().height);
    overworldOffset.setPosition(TILE_SIZE * worldSize.x /2.0, TILE_SIZE * worldSize.y);
}

sf::Transform Entity::getModifiedTransform() const {
    /*std::cout << "overworldPosition " << overworldPosition.getTransform().transformPoint << std::endl;
    std::cout << "overworldPosition " << overworldOffset << std::endl;
    std::cout << "getModifiedTransform " << Animated::getModifiedTransform() << std::endl;*/
    return overworldPosition.getTransform() * overworldOffset.getTransform() * Animated::getModifiedTransform();
}

void Entity::setUV(int u, int v, int w, int h) {
    Graphic::setUV(u, v, w, h);
    updateTransform();
}

void Entity::setWorldPos(Vec2i pos) {
    worldPos = pos;
    updateTransform();
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

void Entity::setIdleAnimation(std::string filename) {
    animationIdle = filename;
}