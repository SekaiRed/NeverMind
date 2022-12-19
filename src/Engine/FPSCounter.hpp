#pragma once

#include <SFML/System/Time.hpp>
#include <vector>
#include <numeric>

class FPSCounter {
private:
    int cachedFPS = -1;
    std::vector<float> fpsList;
    sf::Time timer = sf::microseconds(0);
    const sf::Time limit = sf::seconds(1);
public:
    void update(sf::Time deltaTime);
    int getFPS();
};