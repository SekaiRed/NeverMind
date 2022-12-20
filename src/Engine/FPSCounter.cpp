#include "FPSCounter.hpp"

#include <iostream>

void FPSCounter::update(sf::Time deltaTime) {
    fpsList.push_back(1.0f / deltaTime.asSeconds());

    timer += deltaTime;
    if(timer > limit) {
        timer -= limit;
        cachedFPS = 1.0 * std::accumulate(fpsList.begin(), fpsList.end(), 0.0f) / fpsList.size();
        fpsList.clear();
    }

    if(cachedFPS == -1) {
        cachedFPS = (int) (1.0f / deltaTime.asSeconds());
    }
}

int FPSCounter::getFPS() {
    return cachedFPS;
}