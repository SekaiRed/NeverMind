#include "Actor.hpp"

Actor::Actor(Engine::AssetManager* man, std::string filename, int zIndex, IBlocking * world) : Entity(man, filename, zIndex) {
    this->world = world;
}

void Actor::update(sf::Time elapsed) {
    /*overworldPosition.setPosition(sf::Vector2f(worldPos.x, worldPos.y) * static_cast<float>(TEMP_TILE_SIZE));
    Animated::update(elapsed);*/
    if(movingTimer > 0)
        movingTimer--;
}

sf::Transform Actor::getModifiedTransform() const {
    return animationOffset.getTransform() * Entity::getModifiedTransform();
}

bool Actor::move(Direction dir, sf::Int32 speed) {
    //return true;
    if(movingTimer > 0)
        return false;
    
    if(!world->isValidMove(getWorldPos() + dir.getVector(), getWorldPos()))
        return false;

    setWorldPos(getWorldPos() + dir.getVector());
    movingTimer = speed;
    return true;
}