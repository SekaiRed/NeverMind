#pragma once

#include "Graphic.hpp"
#include "../Engine/AnimationPlayer.hpp"

class Animated : public Graphic {
public:
    Animated(Engine::AssetManager* man, std::string filename, int zIndex);
    virtual void update(sf::Time elapsed);
    void assignAnimation(std::string filename);
    void setAnimationUVOffset(sf::Vector2i offset);
private:
    Engine::AssetManager* man;
    AnimationPlayer player;
};