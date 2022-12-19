#include "Animation.hpp"

Animation::Animation(sf::Int32 delay) {
    globalDuration = delay;
}

int Animation::getLength() {
    return frames.size();
}

Animation::Frame Animation::getFrame(int i) {
    return frames.at(i);
}

sf::Int32 Animation::getGlobalDuration() {
    return globalDuration;
}

bool Animation::usesRelativeUV() {
    return relativeUV;
}

bool Animation::isLoop() {
    return loop;
}

void Animation::setLoop(bool loop) {
    this->loop = loop;
}

void Animation::setRelativeUV(bool relativeUV) {
    this->relativeUV = relativeUV;
}

void Animation::addFrame(Frame f) {
    frames.push_back(f);
}
