#include "BaseState.hpp"

BaseState::BaseState(GameDataRef data) : _data(data) {
    fpsFont = data->assets.getFont("OMORI_GAME2");
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

    //Remove and delete objects that are waiting (I could have a onDelete function)
    std::multimap<int, Object*>::iterator objectIterator;
    std::vector<Object*>::iterator deleteIterator = _deleteQueue.begin();
    while(deleteIterator != _deleteQueue.end()) {
        Object* o = (*deleteIterator);

        objectIterator = _objects.begin();
        while (objectIterator != _objects.end()) {
            if(objectIterator->second == o) {
                objectIterator = _objects.erase(objectIterator);
            } else {
                ++objectIterator;
            }
        }

        o->onDeleted();
        delete o;
        deleteIterator = _deleteQueue.erase(deleteIterator);
    }

    //Add objects that are waiting to be added
    std::vector<Object*>::iterator addingIterator = _addingQueue.begin();
    while(addingIterator != _addingQueue.end()) {
        Object* o = (*addingIterator);
        _objects.insert(std::pair<int, Object*>(o->getZIndex(), o));
        o->onCreated();
        addingIterator = _addingQueue.erase(addingIterator);
    }

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
        (int) (this->_data->window->getView().getCenter().x - this->_data->window->getView().getSize().x/2 + 4),
        (int) (this->_data->window->getView().getCenter().y - this->_data->window->getView().getSize().y/2 - 4)
    );
    fpsCounter.setString("FPS: " + std::to_string(counter.getFPS()));
    _data->window->draw(fpsCounter);
}

Object* BaseState::addObject(Object* o) {
    //_objects.insert(std::pair<int, Object*>(o->getZIndex(), o));
    _addingQueue.push_back(o);
    return o;
}

void BaseState::removeObject(Object* o) {
    /*std::multimap<int, Object*>::iterator itr;
    for (itr = _objects.begin(); itr != _objects.end(); ++itr) {
        if(itr->second == o) {
            itr = _objects.erase(itr); //Remove every entry with this pointer
        }
    }
    delete o;*/ //It is now safe to delete
    _deleteQueue.push_back(o);
}