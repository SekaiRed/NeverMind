#pragma once

#include "Entity.hpp"
#include "../Overworld/Direction.hpp"
#include "../Overworld/IBlocking.hpp"

class Actor : public Entity {
private:
    Direction facing;
    IBlocking * world;
    sf::Transformable animationOffset;
    sf::Int32 movingTimer = 0;
    bool moving;

public:
    Actor(Engine::AssetManager* man, std::string filename, int zIndex, Vec2i worldPos, IBlocking* world);
    virtual void update(sf::Time elapsed);
    virtual sf::Transform getModifiedTransform() const;
    
    virtual bool move(Direction dir, sf::Int32 speed);

    //setAffectedByDirection
};