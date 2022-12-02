#pragma once

//#include <SFML/Graphics.hpp>
#include <vector>
#include "AnimationData.hpp"
#include "SpriteRender.hpp"

class AnimationRender : public SpriteRender {
    private:
        static int counter;
        int number;
        int animation_speed;
        bool loop, ended = false;
        int frame = 0, timer = 0;
        AnimationData* anim;

    public:
        AnimationRender(Engine::AssetManager* man, std::string filename, AnimationData* anim, int animation_speed, bool loop = false);
        virtual ~AnimationRender() {};
        void updateFrame();
        virtual void update(sf::Time elapsed);
        virtual bool destroy();
};
