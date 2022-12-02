#include "BattleRender.hpp"
#include <iostream>

BattleRender::BattleRender() {
    SpriteRender* spr = new SpriteRender(&rsc, "resources/img/sprites/system/cursor_menu.png");
    spr->setPosition(128, 128);
    addInstance(spr);
    /*omoriPlayer = BattlePlayer("Omori", "omori", 1, true);
    omoriPlayer.setEmotion(&Emotion::HAPPY);
	PlayerBoxRender* omoriBox = new PlayerBoxRender(&rsc, &omoriPlayer);
    omoriBox->scale(1, 1);
    omoriBox->setPosition(14, 7);
    addInstance(omoriBox, 1);*/
    //this->parent = parent;
}

BattleRender::~BattleRender()
{
    std::map<int, std::vector<AbstractRender *>>::iterator itm = drawn.begin();
    while (itm != drawn.end())
    {
        std::vector<AbstractRender *>::iterator itv = itm->second.begin();
        while (itv != itm->second.end())
        {
            delete (*itv);
        }
        itm->second.clear();
    }
    drawn.clear();
    /*std::vector<AbstractRender *>::iterator it = drawn.begin();
    while (it != drawn.end())
    {
        delete (*it);
    }
    drawn.clear();*/
}

void BattleRender::draw(sf::RenderWindow *window)
{
    /*std::vector<AbstractRender*>::iterator it = drawn.begin();
    while(it != drawn.end()) {
        (*it)->update(); //First we update
        if ((*it)->destroy()) { //We check if it is destroyed
            delete (*it); //Remember to free the memory
            it = drawn.erase(it); //Remove the pointer from our vector
        } else {
            window->draw(**it); //Otherwise draw and move on to the next
            ++it;
        }
    }*/
    std::map<int, std::vector<AbstractRender *>>::iterator itm = drawn.begin();
    while (itm != drawn.end())
    {
        std::vector<AbstractRender *>::iterator itv = itm->second.begin();
        while (itv != itm->second.end())
        {
            (*itv)->update(); // First we update
            if ((*itv)->destroy())
            {                           // We check if it is destroyed
                delete (*itv);          // Remember to free the memory
                itv = itm->second.erase(itv); // Remove the pointer from our vector
            }
            else
            {
                window->draw(**itv); // Otherwise draw and move on to the next
                ++itv;
            }
        }

        if(itm->second.size() == 0) // If this layer is empty, remove it
            itm = drawn.erase(itm);
        else
            ++itm;
    }
}

void BattleRender::addInstance(AbstractRender* instance, int layer) {
    if(drawn.count(layer) == 0)
        drawn.insert(std::pair<int, std::vector<AbstractRender*>>(layer, std::vector<AbstractRender*>()));
    
    drawn[layer].push_back(instance);
}