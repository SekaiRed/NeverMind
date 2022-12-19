#include "BaseState.hpp"

BaseState::BaseState(GameDataRef data) : _data(data) {
    fpsFont = data->assets.getFont("resources/fonts/OMORI_GAME2.ttf");
    fpsCounter.setFont(fpsFont);
    fpsCounter.setCharacterSize(42);
	fpsCounter.setFillColor(sf::Color::White);
	fpsCounter.setStyle(sf::Text::Bold);
    fpsCounter.setOutlineColor(sf::Color(20, 20, 20));
    fpsCounter.setOutlineThickness(2);
}

void BaseState::updateState(sf::Time deltaTime) {
    counter.update(deltaTime);

    std::multimap<int, Object*>::iterator itr;
    for (itr = _objects.begin(); itr != _objects.end(); ++itr) {
        itr->second->update(deltaTime);
    }
    //_clock.restart();
}

void BaseState::drawState(sf::Time deltaTime) {
    std::multimap<int, Object*>::iterator itr;
    for (itr = _objects.begin(); itr != _objects.end(); ++itr) {
        _data->window->draw(*(itr->second));
    }
    
    fpsCounter.setPosition(
        this->_data->window->getView().getCenter().x - this->_data->window->getView().getSize().x/2 + 32,
        this->_data->window->getView().getCenter().y - this->_data->window->getView().getSize().y/2 + 32
    );
    fpsCounter.setString(std::to_string(counter.getFPS()));
    _data->window->draw(fpsCounter);
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