#pragma once

#include <optional>
#include <SFML/Graphics.hpp>

class Animation {
public:
    struct Frame {
        std::optional<sf::Time> duration;
        std::optional<int> u;
        std::optional<int> v;
        std::optional<int> w;
        std::optional<int> h;
        std::optional<float> x;
        std::optional<float> y;
    };
    Animation(sf::Int64 delay = 0);
    int getLength();
    Frame getFrame(int i);
    sf::Int64 getGlobalDuration();
    void addFrame(Frame f);

private:
    sf::Int64 globalDuration;
    std::vector<Frame> frames;
};

/*class Animation {
private:
    std::vector<Frame> frames;
};*/