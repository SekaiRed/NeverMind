#pragma once

#include "State.hpp"
#include "../GameData.hpp"
#include "../Engine/FPSCounter.hpp"

class BaseState : public Engine::State {
public:
    BaseState(GameDataRef data);
    virtual void updateState(sf::Time deltaTime);
	virtual void drawState(sf::Time deltaTime);
    Object* addObject(Object* o);
	void removeObject(Object* o);
protected:
    GameDataRef _data;
    std::multimap<int, Object*> _objects;
    std::vector<Object*> _deleteQueue;
    FPSCounter counter;
    sf::Text fpsCounter;
    sf::Font fpsFont;
};