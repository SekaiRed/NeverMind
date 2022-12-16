#include "Animation.hpp"

Animation::Animation(sf::Int64 delay) {
    globalDuration = delay;
}

int Animation::getLength() {
    return frames.size();
}

Animation::Frame Animation::getFrame(int i) {
    return frames.at(i);
}

sf::Int64 Animation::getGlobalDuration() {
    return globalDuration;
}

void Animation::addFrame(Frame f) {
    frames.push_back(f);
}