#pragma once

#include "Entity.hpp"
#include "../Utils/Direction.hpp"
#include "../Interface/IBlocking.hpp"

class Actor : public Entity {
private:
    Direction facing;
    IBlocking * world;
    sf::Transformable animationOffset;
    sf::Time moveSpeed = sf::seconds(0);
    sf::Time movingTimer = sf::seconds(0);
    bool isMoving;
    // Animation data

protected:
    std::string animationWalk = "OW_WALK";

public:
    Actor(Engine::AssetManager* man, std::string filename, int zIndex, IBlocking* world);
    virtual void update(sf::Time elapsed);
    virtual sf::Transform getModifiedTransform() const;
    
    virtual bool move(Direction dir, sf::Int32 speed);
    void setWalkAnimation(std::string filename);

    //setAffectedByDirection
};