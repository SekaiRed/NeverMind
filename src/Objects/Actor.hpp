#pragma once

#include "Entity.hpp"
#include "../Overworld/Direction.hpp"

class Actor : public Entity {
private:
    Direction facing;
    sf::Transformable animationOffset;
public:
    Actor(Engine::AssetManager* man, std::string filename, int zIndex, Vec2i worldPos);
    virtual void update(sf::Time elapsed);
    virtual sf::Transform getModifiedTransform() const;
};