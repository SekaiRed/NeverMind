#pragma once

#include <vector>
#include "../../Engine/AssetManager.hpp"
#include "../AbstractRender.hpp"
#include "../SpriteRender.hpp"
#include "BattleBox.hpp"

//class PlayerBoxRender;
//class Engine::AssetManager;

class BattleRender {
    private:
        //BattleState* parent;
        Engine::AssetManager rsc;
        std::map<int, std::vector<AbstractRender*>> drawn; //Layer and list of elements
        //BattlePlayer omoriPlayer;
        

    public:
        BattleRender(/*Engine::AssetManager* rsc*/);
        ~BattleRender();
        void draw(sf::RenderWindow* window);
        void addInstance(AbstractRender* instance, int layer = 0);
};