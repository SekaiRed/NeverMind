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

public:
    //set playback percentage?
    //void pause();
    void update(sf::Sprite* spr, sf::Time elapsed) {
        if(current.getLength() == 0)
            return;

        Animation::Frame frame = current.getFrame(index);

        sf::IntRect rect = spr->getTextureRect();

        rect.left = frame.u.value_or(rect.left);
        rect.top = frame.v.value_or(rect.top);
        rect.width = frame.w.value_or(rect.width);
        rect.height = frame.h.value_or(rect.height);

        spr->setTextureRect(rect);

        timer += elapsed.asMicroseconds();
        while(timer >= current.getGlobalDuration()) {
            //index = index<current.getLength()-1 ? index+1 : 0;
            index++;
            if(index >= current.getLength())
                index = 0;

            timer-= current.getGlobalDuration();
            /*index = index<current.getLength()-1 ? index+1 : 0;
            m_timer = m_timer - current.getGlobalDuration().asMicroseconds();*/
        }

        /*sf::Vector2f pos;
        pos.x = frame.x.value_or(pos.x);
        pos.y = frame.y.value_or(pos.y);
        spr.setPosition(spr.getPosition().x + frame.x - offsetPosition.x, spr.getPosition().y + frame.y - offsetPosition.y);
        offsetPosition = frame.xy;*/
    }

    void setAnimationUVOffset(sf::Vector2i offset) {
        this->offsetUV = offset;
    }

    void change(Animation anim) {
        current = anim;
        index = 0;
        timer = 0;
    }
};