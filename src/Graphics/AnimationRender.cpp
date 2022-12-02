#include "AnimationRender.hpp"

int AnimationRender::counter = 0;

AnimationRender::AnimationRender(Engine::AssetManager* man, std::string filename, AnimationData* anim, int animation_speed, bool loop) : SpriteRender::SpriteRender(man, filename), anim(anim) {
    //this->anim = anim;
    this->animation_speed = animation_speed;
    this->loop = loop;
    this->number = counter++;
}

void AnimationRender::update(sf::Time elapsed) {
    timer++;
    if(timer > animation_speed) {
        timer = 0;
        frame++;
        if(frame >= anim->getFrameAmount()) {
            if(!loop)
                ended = true;

            frame = 0;
        }
    }
    updateFrame();
}

bool AnimationRender::destroy() {
    return ended;
}

void AnimationRender::updateFrame() {
    AnimationDataFrame currentFrame = anim->getFrame(frame);
    setOffset(currentFrame.offset_x, currentFrame.offset_y);
    setUV(currentFrame.u, currentFrame.v, currentFrame.w, currentFrame.h);
}

