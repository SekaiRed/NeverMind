#pragma once

#include "Animation.hpp"

#include <iostream>

class AnimationPlayer {
private:
    sf::Int64 timer = 0;
    sf::Vector2i offsetPosition = {0, 0};
    sf::Vector2i offsetUV;
    Animation current;
    int index = 0;
    bool pause = false;

public:
    //set playback percentage?
    //void pause();
    void update(sf::Sprite& spr, sf::Transformable& transform, sf::Time elapsed) {
        if(pause || current.getLength() == 0)
            return;

        Animation::Frame frame = current.getFrame(index);

        sf::IntRect rect = spr.getTextureRect();

        rect.left = frame.u.value_or(rect.left);
        rect.top = frame.v.value_or(rect.top);
        rect.width = frame.w.value_or(rect.width);
        rect.height = frame.h.value_or(rect.height);

        spr.setTextureRect(rect);

        timer += elapsed.asMicroseconds();
        while(timer >= getDuration()) {
            timer-= getDuration();

            index++;
            if(index >= current.getLength())
                index = 0;
        }


        sf::Vector2f pos;
        pos.x = frame.x.value_or(pos.x);
        pos.y = frame.y.value_or(pos.y);
        transform.setPosition(pos);
    }

    sf::Int64 getDuration() {
        if(current.getFrame(index).duration.has_value())
            return current.getFrame(index).duration.value();
        else
            return current.getGlobalDuration();
        //return current.getFrame(index).duration.value_or(current.getGlobalDuration());
    }

    void setAnimationUVOffset(sf::Vector2i offset) {
        this->offsetUV = offset;
    }

    void play() {
        pause = false;
    }
    void stop() {
        pause = true;
    }
    bool isPlaying() {
        return !pause;
    }

    void change(Animation anim) {
        current = anim;
        index = 0;
        timer = 0;
        play();
    }
};