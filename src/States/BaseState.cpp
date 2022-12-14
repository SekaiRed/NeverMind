#include "BaseState.hpp"

BaseState::BaseState(GameDataRef data) : _data(data) {}

void BaseState::updateState(float dt) {
    std::multimap<int, Object*>::iterator itr;
    for (itr = _objects.begin(); itr != _objects.end(); ++itr) {
        itr->second->update(_clock.getElapsedTime());
    }
}

void BaseState::drawState(float dt) {
    std::multimap<int, Object*>::iterator itr;
    for (itr = _objects.begin(); itr != _objects.end(); ++itr) {
        _data->window->draw(*(itr->second));
    }
}

Object* BaseState::addObject(Object* o) {
    _objects.insert(std::pair<int, Object*>(o->getZIndex(), o));
    return o;
}

void BaseState::removeObject(Object* o) {
    std::multimap<int, Object*>::iterator itr;
    for (itr = _objects.begin(); itr != _objects.end(); ++itr) {
        if(itr->second == o) {
            itr = _objects.erase(itr); //Remove every entry with this pointer
        }
    }
    delete o; //It is now safe to delete
}