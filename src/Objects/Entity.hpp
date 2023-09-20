#pragma once

#include "Animated.hpp"
#include "../Engine/Vec2i.hpp"
#include "../Overworld/Constant.hpp"

//#define TEMP_TILE_SIZE 32

class Entity : public Animated {
private:
    // Meta world data
    Vec2i worldPos = {0, 0};
    Vec2i worldSize = {1, 1};
    bool isMovementBlocking = true;
    // Rendering data
    sf::Transformable overworldOffset;
    sf::Transformable overworldPosition;
    void updateTransform();
public:
    Entity(Engine::AssetManager* man, std::string filename, int zIndex);
    virtual void update(sf::Time elapsed);
    virtual sf::Transform getModifiedTransform() const;
    virtual void setUV(int u, int v, int w, int h);
    void setWorldPos(Vec2i pos);
    Vec2i getWorldPos();
    void setWorldSize(Vec2i size);
    Vec2i getWorldSize();
    bool isSolid();
};
