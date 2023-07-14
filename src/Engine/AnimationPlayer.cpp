#include "AnimationPlayer.hpp"

void AnimationPlayer::update(sf::Sprite& spr, sf::Transformable& transform, sf::Time elapsed, sf::Vector2i uvOffset) {
    if(pause || animation.getLength() == 0)
        return;

    Animation::Frame frame = animation.getFrame(index);

    sf::IntRect rect = spr.getTextureRect();
    rect.left = frame.u.value_or(rect.left) + uvOffset.x;
    rect.top = frame.v.value_or(rect.top) + uvOffset.y;
    rect.width = frame.w.value_or(rect.width);
    rect.height = frame.h.value_or(rect.height);
    if(animation.usesRelativeUV()) {
        rect.left *= rect.width;
        rect.top *= rect.height;
    }
    if(frame.flipX.has_value()) {
        int mult = frame.flipX.value()?-1:1;
        if(rect.width < 0)
            mult = -mult;
        rect.width *= mult;
    }
    if(frame.flipY.has_value()) {
        int mult = frame.flipY.value()?-1:1;
        if(rect.height < 0)
            mult = -mult;
        rect.height *= mult;
    }
    spr.setTextureRect(rect);

    sf::Vector2f pos;
    pos.x = frame.x.value_or(pos.x);
    pos.y = frame.y.value_or(pos.y);
    transform.setPosition(pos);

    timer += elapsed;
    while(timer >= sf::milliseconds(getDuration())) {
        timer-= sf::milliseconds(getDuration());

        index++;
        if(index >= animation.getLength()) {
            index = 0;
            if(!animation.isLoop())
                stop(); //If we're not meant to loop then pause it
        }
    }
}

sf::Int32 AnimationPlayer::getDuration() {
    if(animation.getFrame(index).duration.has_value())
        return animation.getFrame(index).duration.value();
    else
        return animation.getGlobalDuration();
}

void AnimationPlayer::play() {
    pause = false;
}

void AnimationPlayer::stop() {
    pause = true;
}

bool AnimationPlayer::isPlaying() {
    return !pause;
}

void AnimationPlayer::change(Animation anim) {
    animation = anim;
    index = 0;
    timer = sf::seconds(0);
    play();
}
