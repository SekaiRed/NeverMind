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
    if(frame.flipX.has_value()) {
        int mult = frame.flipX.value()?-1:1;
        if(rect.width < 0)
            mult = -mult;
        rect.width *= mult;
    }//rect.width *= frame.flipX.value()?-1:1;
    if(frame.flipY.has_value()) rect.height *= frame.flipY.value()?-1:1;
    spr.setTextureRect(rect);

    sf::Vector2f pos;
    pos.x = frame.x.value_or(pos.x);
    pos.y = frame.y.value_or(pos.y);
    transform.setPosition(pos);

    //transform.setOrigin(sf::Vector2f{(float)rect.width, (float)rect.height}/2.0f);
    //transform.setOrigin({ spr.getLocalBounds().width, 0 });
    /*sf::Vector2f scale = transform.getScale();
    if(frame.flipX.has_value()) scale.x = frame.flipX.value()?-1:1;
    if(frame.flipY.has_value()) scale.y = frame.flipY.value()?-1:1;*/
    //std::cout << scale.x << "\n";
    /*scale.x = flipX?-1:1;
    if(frame.flipY) scale.setScale(1, -1);*/
    //transform.setOrigin({rect.width, rect.height});
    //transform.setScale(scale);
    //transform.setScale({2, 2});

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
