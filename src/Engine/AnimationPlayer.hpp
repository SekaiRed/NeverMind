#pragma once

#include "Animation.hpp"

#include <iostream>

class AnimationPlayer {
private:
    sf::Time timer = sf::seconds(0);
    Animation current;
    int index = 0;
    bool pause = false;

public:
    //set playback percentage?
    void update(sf::Sprite& spr, sf::Transformable& transform, sf::Time elapsed);
    sf::Int32 getDuration();
    void play();
    void stop();
    bool isPlaying();
    void change(Animation anim);
};