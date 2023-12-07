#pragma once

#include "Graphic.hpp"
#include "../AnimationPlayer.hpp"

class Animated : public Graphic {
public:
    Animated(Engine::AssetManager* man, std::string filename, int zIndex);
    virtual void update(sf::Time elapsed);
    virtual sf::Transform getModifiedTransform() const;
    void assignAnimation(std::string filename);
    std::string getAnimation();
    void setUVOffset(sf::Vector2i offset);
private:
    Engine::AssetManager* man;
    AnimationPlayer player;
    std::string lastPlayed = "";
    sf::Transformable animatedTransform;
    sf::Vector2i offset;
};