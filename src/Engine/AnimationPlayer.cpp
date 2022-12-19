#include "AnimationPlayer.hpp"

void AnimationPlayer::update(sf::Sprite& spr, sf::Transformable& transform, sf::Time elapsed) {
    if(pause || current.getLength() == 0)
        return;

    Animation::Frame frame = current.getFrame(index);

    sf::IntRect rect = spr.getTextureRect();
    rect.left = frame.u.value_or(rect.left);
    rect.top = frame.v.value_or(rect.top);
    rect.width = frame.w.value_or(rect.width);
    rect.height = frame.h.value_or(rect.height);
    if(current.usesRelativeUV()) {
        rect.left *= rect.width;
        rect.top *= rect.height;
    }
    spr.setTextureRect(rect);

    sf::Vector2f pos;
    pos.x = frame.x.value_or(pos.x);
    pos.y = frame.y.value_or(pos.y);
    transform.setPosition(pos);

    if(frame.flipX) transform.scale(-1, 1);
    if(frame.flipY) transform.scale(1, -1);

    timer += elapsed.asMilliseconds();
    while(timer >= getDuration()) {
        timer-= getDuration();

        index++;
        if(index >= current.getLength())
            index = 0;
    }
}

sf::Int32 AnimationPlayer::getDuration() {
    if(current.getFrame(index).duration.has_value())
        return current.getFrame(index).duration.value();
    else
        return current.getGlobalDuration();
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
    current = anim;
    index = 0;
    timer = 0;
    play();
}
