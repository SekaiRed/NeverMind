#pragma once

#include <optional>
#include <SFML/Graphics.hpp>

class Animation {
public:
    struct Frame {
        std::optional<bool> flipX;
        std::optional<bool> flipY;
        std::optional<sf::Int32> duration;
        std::optional<int> u;
        std::optional<int> v;
        std::optional<int> w;
        std::optional<int> h;
        std::optional<float> x;
        std::optional<float> y;
    };
    Animation(sf::Int32 delay = 0);
    int getLength();
    Frame getFrame(int i);
    sf::Int32 getGlobalDuration();
    bool usesRelativeUV();
    bool isLoop();
    void setLoop(bool loop);
    void setRelativeUV(bool relativeUV);
    void addFrame(Frame f);

private:
    sf::Int32 globalDuration;
    bool loop = true;
    bool relativeUV = false;
    std::vector<Frame> frames;
};

/*class Animation {
private:
    std::vector<Frame> frames;
};*/