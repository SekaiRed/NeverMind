#pragma once

#include <SFML/Graphics.hpp>

namespace Engine
{
class State
{
public:
	// SHOULD BE VIRTUAL
	State()
	{}
	virtual ~State()
	{}

	virtual void initState() = 0;
	virtual void updateEvents(sf::Event e) = 0;
	virtual void updateState(float dt) = 0;
	virtual void drawState(float dt) = 0;
	virtual void pauseState()
	{}
	virtual void resumeState()
	{}

	sf::Event event;
	sf::Clock globalClock;
};
}