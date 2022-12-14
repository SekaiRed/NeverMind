#pragma once

#include <SFML/Graphics.hpp>
#include "../Objects/Object.hpp"
//#include "../GameData.hpp"

namespace Engine
{
class State
{
protected:
	//GameDataRef _data;
	sf::Clock _clock;
	//std::multimap<int, Object*> objects;
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
	//virtual void updateState(float dt) = 0; 
	/*virtual void updateState(float dt) {

	}
	//virtual void drawState(float dt) = 0;
	virtual void drawState(float dt) {
		std::multimap<int, Object*>::iterator itr;
		for (itr = objects.begin(); itr != objects.end(); ++itr) {
			_data->window->draw(*(itr->second));
		}
	}*/
	virtual void pauseState()
	{}
	virtual void resumeState()
	{}

	/*Object* addObject(Object* o) {
		objects.insert(std::pair<int, Object*>(o->getZIndex(), o));
		return o;
	}
	void removeObject(Object* o) {
		std::multimap<int, Object*>::iterator itr;
		for (itr = objects.begin(); itr != objects.end(); ++itr) {
			if(itr->second == o) {
				itr = objects.erase(itr); //Remove every entry with this pointer
			}
		}
		delete o; //It is now safe to delete
	}*/
};
}