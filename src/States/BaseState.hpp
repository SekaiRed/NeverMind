#pragma once

#include "State.hpp"
#include "../GameData.hpp"

class BaseState : public Engine::State {
public:
    BaseState(GameDataRef data);
    virtual void updateState(float dt);
	virtual void drawState(float dt);
    Object* addObject(Object* o);
	void removeObject(Object* o);
protected:
    GameDataRef _data;
    std::multimap<int, Object*> _objects;
};