#include "Actor.hpp"

#include <iostream>

Actor::Actor(Engine::AssetManager* man, std::string filename, int zIndex, IBlocking * world) : Entity(man, filename, zIndex) {
    this->world = world;
}

void Actor::update(sf::Time elapsed) {
    //overworldPosition.setPosition(sf::Vector2f(worldPos.x, worldPos.y) * static_cast<float>(TEMP_TILE_SIZE));
    //Animated::update(elapsed);
    /*std::cout << "facing : " << "(" << facing.getVector().x << ", " << facing.getVector().y << ")" << std::endl;
    std::cout << "moveProgress : " << movingTimer << std::endl;
    std::cout << "moveSpeed : " << moveSpeed << std::endl;
    std::cout << "isMoving : " << isMoving << std::endl;*/
    //MAKE MOVEMENT NOT DEPEND ON FPS
    if(movingTimer < moveSpeed) {
        movingTimer += elapsed;
        sf::Vector2f facingOffset = sf::Vector2f(facing.getVector().x, facing.getVector().y);
        float moveProgress = 1.0f * movingTimer / moveSpeed;
        animationOffset.setPosition((moveProgress - 1) * facingOffset * static_cast<float>(TILE_SIZE));
    } else if(isMoving) {
        moveSpeed = sf::seconds(0);
        movingTimer = sf::seconds(0);
        isMoving = false;
        animationOffset.setPosition({0, 0});
        //if(getAnimation() != animationIdle)
        assignAnimation(animationIdle);
    }

    if(facing == Direction::DOWN) setUVOffset({0,0});
    if(facing == Direction::LEFT) setUVOffset({0,1});
    if(facing == Direction::RIGHT) setUVOffset({0,2});
    if(facing == Direction::UP) setUVOffset({0,3});
    
    Entity::update(elapsed);
}

sf::Transform Actor::getModifiedTransform() const {
    return animationOffset.getTransform() * Entity::getModifiedTransform();
    //return Entity::getModifiedTransform();
}

bool Actor::move(Direction dir, sf::Int32 speed) {
    //return true;
    if(movingTimer < moveSpeed)
        return false;
        
    /*if(movingTimer != moveSpeed)
        return false;*/

    facing = dir;
    
    if(!world->isValidMove(this, getWorldPos() + dir.getVector()))
        return false;

    setWorldPos(getWorldPos() + dir.getVector());
    
    moveSpeed = sf::milliseconds(speed);
    movingTimer = sf::seconds(0);
    isMoving = true;
    //std::cout << getAnimation() << std::endl;
    if(getAnimation() != animationWalk)
        assignAnimation(animationWalk);
    return true;
}

void Actor::setWalkAnimation(std::string filename) {
    animationWalk = filename;
}