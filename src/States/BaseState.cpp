#include "BaseState.hpp"

BaseState::BaseState(GameDataRef data) : _data(data) {
    fpsFont = data->assets.getFont("resources/fonts/OMORI_GAME2.ttf");
    fpsCounter.setFont(fpsFont);
    fpsCounter.setCharacterSize(20);
	fpsCounter.setFillColor(sf::Color::White);
	fpsCounter.setStyle(sf::Text::Bold);
    fpsCounter.setOutlineColor(sf::Color(20, 20, 20));
    fpsCounter.setOutlineThickness(2);
}

BaseState::~BaseState() {
    std::multimap<int, Object*>::iterator itr = _objects.begin();
    while(itr != _objects.end()) {
        delete itr->second;
    }
}

void BaseState::updateState(sf::Time deltaTime) {
    //Update the FPS counter
    counter.update(deltaTime);

    //List of objects I need to add back into the map with an updated key
    std::vector<Object*> zIndexChanged;

    //Update objects, and update them if they
    std::multimap<int, Object*>::iterator itr = _objects.begin();
    while(itr != _objects.end()) {
        itr->second->update(deltaTime);

        if(itr->first == itr->second->getZIndex()) {
            //zIndex is a match
            ++itr;
        } else {
            //zIndex is different!
            zIndexChanged.push_back(itr->second);
            itr = _objects.erase(itr);
        }
    }

    //Add objects for the next frame
    std::vector<Object*>::iterator itrDel = zIndexChanged.begin();
    while(itrDel != zIndexChanged.end()) {
        _objects.insert(std::pair<int, Object*>((*itrDel)->getZIndex(), (*itrDel)));
        itrDel++;
    }
}

void BaseState::drawState(sf::Time deltaTime) {
    std::multimap<int, Object*>::iterator itr;
    for (itr = _objects.begin(); itr != _objects.end(); ++itr) {
        _data->window->draw(*(itr->second));
    }
    
    fpsCounter.setPosition(
        this->_data->window->getView().getCenter().x - this->_data->window->getView().getSize().x/2 + 4,
        this->_data->window->getView().getCenter().y - this->_data->window->getView().getSize().y/2 - 4
    );
    fpsCounter.setString("FPS: " + std::to_string(counter.getFPS()));
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